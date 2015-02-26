#include "FieldParser.h"

FieldParser::FieldParser() {
	field = new Field();
}

FieldParser::~FieldParser() {
}

Field* FieldParser::parseField(TiXmlElement* elem) {
	//code veranderen
	REQUIRE(this->getRootName() == "VELD", "Rootname must be equal to 'VELD'");
	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
		
	}

	//return catalog;
}

Field* FieldParser::getField() {
	 return field;
}
