#include <algorithm>
#include "arcade.h"
#include "DesignByContract.h"

/**
* helper functions
**/
bool isDirection(std::string) {
    return std::find(directions.begin(), directions.end(), "OMHOOG") 
               != directions.end();
}


/**
* Move
**/
Move::Move() {
    _initCheck = this;
    playername = "";
    direction = "";
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}
Move::Move(std::string playername, std::string direction) {
    REQUIRE( isDirection(direction), "invalid direction");
    _initCheck = this;
    this->playername = playername;
    this->direction = direction;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
bool Move::properlyInitialized() {
    return this == _initCheck;
}

/** 
* Playpiece
*/
PlayPiece::PlayPiece() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = false;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
PlayPiece::PlayPiece(int x, int y, bool movable) {
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = movable;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
bool PlayPiece::properlyInitialized() {
    return this == _initCheck;
}
/** 
* Player
**/
Player::Player() {
    _initCheck = this;
    name = "";
    x = 0;
    y = 0;
    movable = true;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
Player::Player(int x, int y, std::string name) {
    _initCheck = this;
    this->name = name;
    this->x = x;
    this->y = y;
    this->movable = true;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
bool Player::properlyInitialized() {
    return this == _initCheck;
}

/**
* Obstacle
**/
Obstacle::Obstacle() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = false;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
bool Obstacle::properlyInitialized() {
    return this == _initCheck;
}

/**
* Barrel
**/
Barrel::Barrel() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = true;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
Barrel::Barrel(int x, int y) {
    REQUIRE(x > 0 && y > 0, "coordinates must be greater than zero");
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = true;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}

/**
* Wall
**/
Wall::Wall() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = false;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
Wall::Wall(int, int) {
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = false;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

/**
* Field
**/
Field::Field(){
    _initCheck = this;
    name = "";
    length = 0;
    width = 0;
    playfield = nullptr;
    obstacles = {};
    players = {};
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

Field::Field(std::string name,const int length,const int width){
    _initCheck = this;
    this->name = name;
    this->length = length;
    this->width = width;
    this->playfield = new PlayPiece*[length];
    for(int i = 0; i < length; ++i){
        this->playfield[i] = new PlayPiece[width];
    }
    this->obstacles = {};
    this->players = {};
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}
bool Field::properlyInitialized() {
    return this == _initCheck;
}

