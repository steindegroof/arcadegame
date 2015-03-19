#include "AbstractParser.h"
#include "../DesignByContract.h"

AbstractParser::AbstractParser() {
	_initCheck = this;
	ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

AbstractParser::~AbstractParser() {
}
bool AbstractParser::properlyInitialized() const{
	return this == _initCheck;
}

TiXmlElement* AbstractParser::getRoot(){
	REQUIRE(this->properlyInitialized(), 
	        "AbstractParser wasn't initialized when calling getRoot");
	return root;
}

bool AbstractParser::loadFile(std::string filename) {
	REQUIRE(this->properlyInitialized(), 
	        "AbstractParser wasn't initialized when calling loadFile");
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
	REQUIRE(this->properlyInitialized(), 
	        "AbstractParser wasn't initialized when calling getRootName");
	return root->Value();
}

const char* AbstractParser::readFirstChildElement(const char* s,TiXmlElement* root){
	REQUIRE(this->properlyInitialized(), 
	        "AbstractParser wasn't initialized when calling readFirstElement");
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

