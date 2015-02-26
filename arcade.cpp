#include "arcade.h"
#include "parsers/FieldParser.h"
#include <iostream>

Field::Field(){
}

int main(int argc, char* argv[]){
	FieldParser fieldparser;
	fieldparser.loadFile("Speelveld1.0.xml");
	std::cout << "Name of root: " << fieldparser.getRootName() << std::endl;
	
	return 0;
}
