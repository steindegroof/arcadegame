#include "arcade.h"
#include "parsers/FieldParser.h"
#include <iostream>

int main(int argc, char* argv[]){
	FieldParser fieldparser;
	fieldparser.loadFile("xml_files/Speelveld1.0.xml");
	fieldparser.parseFile();
	//std::cout << "Name of root: " << fieldparser.getRootName() << std::endl;
	
	return 0;
}
