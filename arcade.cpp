#include "arcade.h"

PlayPiece::PlayPiece(){
}

Obstacle::Obstacle() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = false;
    type = "";
}

bool Obstacle::properlyInitialized() {
    return this == _initCheck;
}

Field::Field(){
}

Field::Field(std::string name,const int length,const int width){
    this->name = name;
    this->length = length;
    this->width = width;
    this->playfield = new PlayPiece*[length];
    for(int i = 0; i < length; ++i){
        this->playfield[i] = new PlayPiece[width];
    }
}

/*
int main(int argc, char* argv[]){
	FieldParser fieldparser;
	fieldparser.loadFile("Speelveld1.0.xml");
	std::cout << "Name of root: " << fieldparser.getRootName() << std::endl;
	
	return 0;
}
*/
