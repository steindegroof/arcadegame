#include "arcade.h"

/**
* Move
**/
Move::Move() {
    _initCheck = this;
    playername = "";
    direction = "";
}
Move::Move(std::string playername, std::string direction) {
    _initCheck = this;
    this->playername = playername;
    this->direction = direction;
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
}
PlayPiece::PlayPiece(int x, int y, bool movable) {
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = movable;
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
}
Player::Player(int x, int y, std::string name) {
    _initCheck = this;
    this->name = name;
    this->x = x;
    this->y = y;
    this->movable = true;
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
}
Barrel::Barrel(int x, int y) {
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = true;
}

/**
* Wall
**/
Wall::Wall() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = false;
}
Wall::Wall(int, int) {
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = false;
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
}

Field::Field(std::string name,const int length,const int width){
    this->name = name;
    this->length = length;
    this->width = width;
    this->playfield = new PlayPiece*[length];
    for(int i = 0; i < length; ++i){
        this->playfield[i] = new PlayPiece[width];
    }
    this->obstacles = {};
    this->players = {};
}
bool Field::properlyInitialized() {
    return this == _initCheck;
}

