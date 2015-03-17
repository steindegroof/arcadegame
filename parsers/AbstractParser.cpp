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

std::string AbstractParser::getRootName(){ //we hebben ook al getRoot...
	return root->Value();
}

const char* AbstractParser::readFirstChildElement(const char* s,TiXmlElement* root){
	TiXmlElement* e = root->FirstChildElement(s);
	if(e != NULL){
	    TiXmlNode* node = e->FirstChild();
	    if(node != NULL){
	        return node->ToText()->Value();
	    }
	    else{
	        std::cerr << s << " heeft geen childnodes." << std::endl;
	    }
	}
	else{
	    std::cerr << "XML bestand bevat geen " << s << " voor " << root->Value() << std::endl; //to lowercase??
	}
	return "";
}

