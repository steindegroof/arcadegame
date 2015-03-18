#include "FieldParser.h"
#include <stdlib.h>
#include <fstream>

FieldParser::FieldParser() {
	//field = new Field();
	field = nullptr;
}

FieldParser::~FieldParser() {
}

bool FieldParser::parseFile() {
	//PRECONDITIE dat root == VELD nog checken!
	const char* fieldname = readFirstChildElement("NAAM",this->root);
	if(fieldname[0] == '\0'){ //empty fieldname
		std::cerr << "Het speelveld heeft geen naam!" << std::endl;
	}
	int length = atoi(readFirstChildElement("LENGTE",this->root));
	int width = atoi(readFirstChildElement("BREEDTE",this->root));
	if(length < 0 || width < 0){
		std::cerr << "Het speelveld heeft negatieve dimensies! Inconsistent speelveld. Het parsen werd afgebroken." << std::endl;
		return false; //inconsistent speelveld.
	}
	//std::cout << fieldname << length << width << std::endl;
	field = new Field(fieldname,length,width);
	for(TiXmlElement* e = this->root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
	    std::string tag = e->Value();
	    if(tag == "NAAM" || tag == "LENGTE" || tag == "BREEDTE"){
	        //nothing to be done.
	    }
	    else if(tag == "SPELER"){
	        const char* x = e->Attribute("x");
	        const char* y = e->Attribute("y");
	        if(x != NULL && y != NULL){
                int x_ = atoi(x);
                int y_ = atoi(y);
				if(x_ < 0 || y_ < 0){
					std::cerr << "De speler bevat een negatief coordinaat. Inconsistent speelveld. Het parsen werd afgebroken." << std::endl;
					return false;
				}
				const char* playername = readFirstChildElement("NAAM",e);
				if(playername[0] == '\0'){ //empty playername
					std::cerr << "Spelernaam mag niet leeg zijn. Inconsistent speelveld. Het parsen werd afgebroken." << std::endl;
					return false; //inconsistent speelveld.
				}
				Player* player = new Player(x_,y_,playername); //speler aanmaken
				bool add_succes;
				add_succes = field->addPlayer(player);
				if(!add_succes){
					std::cerr << "Speler toevoegen aan speelveld mislukt."
							  << "Inconsistent speelveld. Het parsen werd afgebroken." << std::endl;
					delete player;
					return false;
				}
	        }
	        else{
	            std::cerr << "x of y coordinaat afwezig bij speler." << std::endl;
	            continue;
	        }
	    }
	    else if(tag == "OBSTAKEL"){
			const char* x = e->Attribute("x");
	        const char* y = e->Attribute("y");
			const char* beweegbaar = e->Attribute("beweegbaar");
	        if(x != NULL && y != NULL && beweegbaar != NULL){
                int x_ = atoi(x);
                int y_ = atoi(y);
				std::string beweegbaar_ = beweegbaar;
				if(x_ < 0 || y_ < 0){
					std::cerr << "Het obstakel bevat een negatief coordinaat. Inconsistent speelveld. Het parsen werd afgebroken." << std::endl;
					return false;
				}
				bool movable;
				if(beweegbaar_ == "true"){ //hoofdlettergevoelig maken!
					movable = true;
				}
				else if(beweegbaar_ == "false"){
					movable = false;
				}
				else{
					std::cerr << "Het obstakel heeft geen geldige waarde voor het attribuut 'beweegbaar'. Dit obstakel werd genegeerd." << std::endl;
					continue; //negeren.
				}
				std::string type = readFirstChildElement("TYPE",e);
				Obstacle* obstacle;
				if(type == "ton"){
					obstacle = new Barrel(x_,y_,movable);
				}
				else if(type == "muur"){
					obstacle = new Wall(x_,y_,movable);
				}
				else{ //empty type
					std::cerr << "Obstakel met een onbekend type. Dit obstakel werd genegeerd." << std::endl;
					continue; //negeren
				}
				bool add_succes;
				add_succes = field->addObstacle(obstacle);
				if(!add_succes){
					std::cerr << "Obstakel toevoegen aan speelveld mislukt."
							  << "Inconsistent speelveld. Het parsen werd afgebroken." << std::endl;
					delete obstacle;
					return false;
				}
	        }
	        else{
	            std::cerr << "x/y/beweegbaar attribuut afwezig bij obstakel" << std::endl;
	            continue;
	        }
	    }
	    else{
	        std::cerr << "Onherkenbaar element." << std::endl;
	    }
	}
	return true; //als we hier geraken is het parsen gelukt.
}

bool FieldParser::writeFile(std::string filename){
	std::ofstream myfile;
	std::ofstream output;
	output << "Bestand: " << filename << std::endl << std::endl;
  	output << "Het huidige speelveld is " << field->getName() << ":" << std::endl
		   << "Eigenschappen van dit veld:" << std::endl
		   << "-Breedte " << field->getWidth() << std::endl
		   << "-Lengte " << field->getLength() << std::endl << std::endl;
	std::vector<Player*> players = field->getPlayers();
	std::vector<Player*>::iterator it_pl;
	for(it_pl = players.begin(); it_pl!= players.end(); it_pl++){
		output << "Speler " << (*it_pl)->getName() << " bevindt zich in dit speelveld op positie (" 
			   << (*it_pl)->getX() << "," << (*it_pl)->getY() << ")." << std::endl << std::endl;
	}
	std::vector<Obstacle*> obstacles = field->getObstacles();
	std::vector<Obstacle*>::iterator it_obst;
	for(it_obst = obstacles.begin(); it_obst != obstacles.end(); it_obst++){
		if((*it_obst)->isMovable()){
			output << "Er bevindt zich een " << (*it_obst)->getType() << " op positie ("
				   << (*it_obst)->getX() << "," << (*it_obst)->getY() << ")." << std::endl << std::endl;
		}
	}
  	myfile.open(filename);
	if (myfile.fail()) {
	    std::cerr << "Couldn't open file " << filename << " for writing" << std::endl;
		std::cerr << "Writing to console..." << std::endl;
		std::cout << output;
	    return false;
    }
	else{
		myfile << "wtf?";
		myfile << output;
		myfile.close();
	}
    return true;
}

Field* FieldParser::getField() {
	 return field;
}
