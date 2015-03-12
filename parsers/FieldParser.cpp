#include "FieldParser.h"
#include <stdlib.h>


FieldParser::FieldParser() {
	//field = new Field();
	field = nullptr;
}

FieldParser::~FieldParser() {
}

std::string ReadTag(TiXmlElement* e){
    TiXmlNode* node = e->FirstChild();
	TiXmlText* text = node->ToText();
	return text->Value();
}

void FieldParser::parseFile() { //elem zal de root zijn van xml file
	//code veranderen
	//TiXmlNode* node = e->FirstChild();
	//TiXmlText* text = node->ToText();
	//REQUIRE(this->getRootName() == "VELD", "Rootname must be equal to 'VELD'");
	
	const char* fieldname;
	TiXmlElement* e = this->root->FirstChildElement("NAAM");
	if(e != NULL){
	    TiXmlNode* node = e->FirstChild();
	    if(node != NULL){
	        fieldname = node->ToText()->Value();
	    }
	    else{
	        std::cerr << "NAAM heeft geen childnodes." << std::endl;
	    }
	}
	else{
	    std::cerr << "XML bestand bevat geen naam voor het speelveld." << std::endl;
	    return; //return false?
	}	
	int length;
	e = this->root->FirstChildElement("LENGTE");
	if(e != NULL){
	    TiXmlNode* node = e->FirstChild();
	    if(node != NULL){
	        length = atoi(node->ToText()->Value());
	    }
	    else{
	        std::cerr << "LENGTE heeft geen childnodes." << std::endl;
	    }
	}
	else{
	    std::cerr << "XML bestand bevat geen lengte voor het speelveld." << std::endl;
	    return;
	}
	
	int width;
	e = this->root->FirstChildElement("BREEDTE");
	if(e != NULL){
	    TiXmlNode* node = e->FirstChild();
	    if(node != NULL){
	        length = atoi(node->ToText()->Value());
	    }
	    else{
	        std::cerr << "BREEDTE heeft geen childnodes." << std::endl;
	    }
	}
	else{
	    std::cerr << "XML bestand bevat geen breedte voor het speelveld." << std::endl;
	    return;
	}
	field = new Field(fieldname,length,width);
	
	std::cout << "hallo is" << atoi("hallo") <<std::endl;
	
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
                TiXmlElement* name_el = e->FirstChildElement("NAAM");
                if(name_el != NULL){
                    TiXmlNode* name_node = name_el->FirstChild();
	                if(name_node != NULL){
	                    std::string spelernaam = name_node->ToText()->Value();
	                    //new speler
	                    std::cout << "spelernaam" << spelernaam;
	                    Player* player = new Player(x_,y_,spelernaam);
	                    
	                }
	                else{
	                    std::cerr << "SPELERNAAM heeft geen childnodes." << std::endl;
	                }
                }
                else{
                    std::cerr << "Speler bevat geen naam." << std::endl;
                }
	        }
	        else{
	            std::cerr << "x of y coordinaat afwezig bij speler" << std::endl;
	            continue;
	        }
	    }
	    else if(tag == "OBSTAKEL"){
	    }
	    else{
	        std::cout << tag << std::endl;
	        std::cerr << "Onherkenbaar element." << std::endl;
	        //continue;
	    }
	}
	
	
	/*
	const char* fieldname = this->root->FirstChildElement("NAAM")->FirstChild()->ToText()->Value();
	int length = atoi(this->root->FirstChildElement("LENGTE")->FirstChild()->ToText()->Value());
	int width = atoi(this->root->FirstChildElement("BREEDTE")->FirstChild()->ToText()->Value());
	
	for(TiXmlElement* e = this->root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
	    std::string tag = e->Value();
	    if(tag == "NAAM"){
            //field->name = ReadTag(e);
	    }
	    else if(tag == "LENGTE"){
	    }
	    else if(tag == "BREEDTE"){
	    }
	    else if(tag == "SPELER"){
	        const char* x = e->Attribute("x");
	        const char* y = e->Attribute("y");
	        if(x != NULL && y != NULL){
                //do smthng
                int x_ = atoi(x);
                int y_ = atoi(y);
                atoi("hallo");
	        }
	        else{
	            //blablabla
	            std::cerr << "x of y coordinaat afwezig bij speler" << std::endl;
	            continue;
	        }
	        //std::cout << x << std::endl;
	    }
	    else if(tag == "OBSTAKEL"){
	    }
	}*/
	//return catalog;
}

bool FieldParser::writeFile(std::string filename){
    return true;
}

Field* FieldParser::getField() {
	 return field;
}
