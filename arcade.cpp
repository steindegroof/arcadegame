#include "arcade.h"

Field::Field(){
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

/*
int main(int argc, char* argv[]){
	FieldParser fieldparser;
	fieldparser.loadFile("Speelveld1.0.xml");
	std::cout << "Name of root: " << fieldparser.getRootName() << std::endl;
	
	return 0;
}
*/
