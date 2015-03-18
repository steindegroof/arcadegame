#include "arcade.h"
#include "parsers/FieldParser.h"
#include "parsers/MovesParser.h"
#include <iostream>
#include "DesignByContract.h"

class Game{
private:
	FieldParser* fieldparser;
	MovesParser* movesparser;
	Game* _initCheck;
public:
	Game(std::string,std::string);
	void doOneMove();
	void doAllMoves();
	void writeOutField(std::string);
	void writeOutMoves(std::string);
	bool properlyInitialized() const;
};

Game::Game(std::string field_xml,std::string moves_xml){
	_initCheck = this;
	fieldparser = new FieldParser();
	movesparser = new MovesParser();
	fieldparser->loadFile(field_xml);
	movesparser->loadFile(moves_xml);
	fieldparser->parseFile();
	movesparser->parseFile();
	ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}
bool Game::properlyInitialized() const {
    return this == _initCheck;
}
void Game::doOneMove(){
	REQUIRE(this->properlyInitialized(), 
	        "Game wasn't initialized when calling doOneMove");
	Field* field = fieldparser->getField();
	std::vector<Move*>* moves = movesparser->getMoves();
	std::vector<Move*>::iterator it;
	if(!moves->empty()){
		it = moves->begin();
		field->doMove(**it);
		moves->erase(it);	
	}
}
void Game::doAllMoves(){
	REQUIRE(this->properlyInitialized(), 
	        "Game wasn't initialized when calling doAllMoves");
	std::vector<Move*>* moves = movesparser->getMoves();
	while(!moves->empty()){
		doOneMove();
	}
}
void Game::writeOutField(std::string filename){
	REQUIRE(this->properlyInitialized(), 
	        "Game wasn't initialized when calling writeOutField");
	fieldparser->writeFile(filename);
}
void Game::writeOutMoves(std::string filename){
	REQUIRE(this->properlyInitialized(), 
	        "Game wasn't initialized when calling writeOutMoves");
	movesparser->writeFile(filename);
}

int main(int argc, char* argv[]){
	Game* game = new Game("xml_files/Speelveld1.0.xml","xml_files/Bewegingen1.0.xml");
	game->writeOutField("speelveld.txt");
	game->writeOutMoves("ResterendeBewegingen.txt");
	game->doAllMoves();
	game->writeOutField("speelveld_einde.txt");
	game->writeOutMoves("ResterendeBewegingen_einde.txt");
	/*
	FieldParser fieldparser;
	fieldparser.loadFile("xml_files/Speelveld1.0.xml");
	fieldparser.parseFile();
	//std::cout << "Name of root: " << fieldparser.getRootName() << std::endl;
	fieldparser.writeFile("speelveld.txt");
	Field* field = fieldparser.getField();

	MovesParser movesparser;
	movesparser.loadFile("xml_files/Bewegingen1.0.xml");
	//std::cout << "Name of root: " << movesparser.getRootName() << std::endl;
	movesparser.parseFile();
	movesparser.writeFile("ResterendeBewegingen.txt"); //
	std::vector<Move*>* moves = movesparser.getMoves();
	std::vector<Move*>::iterator it;
	for( it = moves->begin(); it!=moves->end(); it++){
		field->doMove(**it);
	}
	fieldparser.writeFile("speelveld_na_moves.txt");
	*/

	return 0;
}
