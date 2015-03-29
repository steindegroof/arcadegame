
#include "arcadeUtils.h"
#include "DesignByContract.h"
#include "playpieces.h"



/** 
* Playpiece
*/
PlayPiece::PlayPiece() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = false;
	field = nullptr;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
PlayPiece::PlayPiece(int x, int y, bool movable, Field* field) {
    REQUIRE(x >= 0 && y >= 0, "coordinates must be greater than zero");
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = movable;
	this->field = field;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
bool PlayPiece::properlyInitialized() const {
    return this == _initCheck;
}
bool PlayPiece::isMovable() {
    REQUIRE(this->properlyInitialized(), 
	        "PlayPiece wasn't initialized when calling isMovable");
    return this->movable;
}
int PlayPiece::getX() const{
    REQUIRE(this->properlyInitialized(), 
	        "PlayPiece wasn't initialized when calling getX");
    return this->x;
} 
int PlayPiece::getY() const{
    REQUIRE(this->properlyInitialized(), 
	        "PlayPiece wasn't initialized when calling getY");
    return this->y;
} 
void PlayPiece::setX(int x) {
    REQUIRE(this->properlyInitialized(), 
	        "PlayPiece wasn't initialized when calling setX");
    this->x = x;
}
void PlayPiece::setY(int y) {
    REQUIRE(this->properlyInitialized(), 
	        "PlayPiece wasn't initialized when calling setY");
    this->y = y;
}

void PlayPiece::move(std::string direction) {
    REQUIRE(this->properlyInitialized(),
	        "PlayPiece wasn't initialized when calling setY");
	REQUIRE(isDirection(direction), 
	        "Invalid direction passed to PlayPiece");
     
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
    REQUIRE(x >= 0 && y >= 0, "coordinates must be >= 0");
    _initCheck = this;
    this->name = name;
    this->x = x;
    this->y = y;
    this->movable = true;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}
bool Player::properlyInitialized() const {
    return this == _initCheck;
}
std::string Player::getName() const{
    REQUIRE(this->properlyInitialized(), 
	        "Player wasn't initialized when calling getName");
    return this->name;
}
void Player::setName(std::string name) {
    REQUIRE(this->properlyInitialized(), 
   	        "Player wasn't initialized when calling setName");
    this->name = name;
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
bool Obstacle::properlyInitialized() const {
    return this == _initCheck;
}
std::string Obstacle::getType(){
	return type;
}

/**
* Barrel
**/
Barrel::Barrel() {
    _initCheck = this;
    x = 0;
    y = 0;
    movable = true;
	type = "ton";
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
Barrel::Barrel(int x, int y,bool movable) {
    REQUIRE(x >= 0 && y >= 0, "coordinates must be >= 0");
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = movable;
	type = "ton";
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
	type = "muur";
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
Wall::Wall(int x, int y, bool movable) {
    REQUIRE(x >= 0 && y >= 0, "coordinates must be >= 0");
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = movable;
	type = "muur";
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

