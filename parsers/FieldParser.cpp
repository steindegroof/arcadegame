#include "FieldParser.h"

FieldParser::FieldParser() {
	field = new Field();
}

FieldParser::~FieldParser() {
}

void FieldParser::parseFile(TiXmlElement* elem) {
	//code veranderen
	REQUIRE(this->getRootName() == "VELD", "Rootname must be equal to 'VELD'");
	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
		
	}
	//return catalog;
}

bool FieldParser::writeFile(std::string filename){
    return true;
}

Field* FieldParser::getField() {
	 return field;
}
