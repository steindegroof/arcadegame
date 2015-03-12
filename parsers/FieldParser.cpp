#include "FieldParser.h"


FieldParser::FieldParser() {
	field = new Field();
}

FieldParser::~FieldParser() {
}

void FieldParser::parseFile() { //elem zal de root zijn van xml file
	//code veranderen
	//REQUIRE(this->getRootName() == "VELD", "Rootname must be equal to 'VELD'");
	for(TiXmlElement* e = this->root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
	    std::string tag = e->Value();
	}
	//return catalog;
}

bool FieldParser::writeFile(std::string filename){
    return true;
}

Field* FieldParser::getField() {
	 return field;
}
