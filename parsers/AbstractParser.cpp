#include "AbstractParser.h"

AbstractParser::AbstractParser() {
}

AbstractParser::~AbstractParser() {
}

TiXmlElement* AbstractParser::getRoot(){
	return root;
}

bool AbstractParser::loadFile(std::string filename) {
	if(!doc.LoadFile(filename.c_str())){
		std::cerr << doc.ErrorDesc() << std::endl;
		return false;
	}

	root = doc.FirstChildElement();
	if(root == NULL){
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		return false;
	}
	return true;
}

std::string AbstractParser::getRootName(){
	return root->Value();
}

