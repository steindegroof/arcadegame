#include "arcade.h"
#include "parsers/FieldParser.h"
#include "parsers/MovesParser.h"
#include <iostream>

int main(int argc, char* argv[]){
	FieldParser fieldparser;
	fieldparser.loadFile("xml_files/Speelveld1.0.xml");
	fieldparser.parseFile();
	//std::cout << "Name of root: " << fieldparser.getRootName() << std::endl;
	fieldparser.writeFile("speelveld.txt");

	MovesParser movesparser;
	movesparser.loadFile("xml_files/Bewegingen1.0.xml");
	//std::cout << "Name of root: " << movesparser.getRootName() << std::endl;
	movesparser.parseFile();
	movesparser.writeFile("ResterendeBewegingen.txt");
	
	return 0;
}
