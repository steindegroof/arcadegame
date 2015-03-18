#include "MovesParser.h"
#include <fstream>

MovesParser::MovesParser() {
	moves = new std::vector<Move*>;
}

MovesParser::~MovesParser() {
}

bool MovesParser::parseFile() {
	//PRECONDITIE rootname == BEWEGINGEN
	for(TiXmlElement* e = this->root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
	    std::string tag = e->Value();
		if(tag == "BEWEGING"){
			std::string playername = readFirstChildElement("SPELERNAAM",e);
			std::string direction = readFirstChildElement("RICHTING",e);
			if(playername == ""){
				std::cerr << "Beweging van speler zonder naam. Deze beweging werd genegeerd." << std::endl;
				continue;
			}
			if(!(direction == "OMHOOG" || direction == "OMLAAG" || direction == "RECHTS" || direction == "LINKS")){
				std::cerr << "Beweging met ongeldige richting. Deze beweging werd genegeerd." << std::endl;
				continue;
			}
			//ze is geldige, we gaan ze toevoegen aan vector met Moves.
			Move* move = new Move(playername,direction);
			moves->push_back(move);
		}
		else{
			std::cout << "Onherkenbaar element." << std::endl;
		}
	}
	return true; //bewegingen kunnen eigenlijk niet false worden... We negeren alle foutieve gewoon.
}

bool MovesParser::writeFile(std::string filename){
	std::ofstream myfile;
  	myfile.open(filename);
	myfile << "Bestand: " << filename << std::endl << std::endl;
	if(moves->empty()){
		myfile << "geen bewegingen." << std::endl;
	}
	else{
		std::vector<Move*>::iterator it;
		for(it = moves->begin(); it!= moves->end(); it++){
			myfile << "Speler " << (*it)->getPlayerName() << " zal volgende beweging nog uitvoeren:" << std::endl 
				   << (*it)->getDirection() << std::endl << std::endl;
		}
	}
	myfile.close();
    return true;
}

std::vector<Move*>* MovesParser::getMoves() {
	 return moves;
}
