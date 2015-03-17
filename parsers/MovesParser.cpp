#include "MovesParser.h"

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
    return true;
}

std::vector<Move*>* MovesParser::getMoves() {
	 return moves;
}
