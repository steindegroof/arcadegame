#include <algorithm>
#include <iostream>
#include "arcade.h"
#include "DesignByContract.h"

/**
* helper functions
**/
bool isDirection(std::string direction) {
    return directions.count(direction) != 0;
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
    REQUIRE(x > 0 && y > 0, "coordinates must be greater than zero");
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
bool PlayPiece::isEmpty() {
    return this->x == 0 && this->y == 0;
}
bool PlayPiece::isMovable() {
    return this->movable;
}
int PlayPiece::getX() {
    return this->x;
} 
int PlayPiece::getY() {
    return this->y;
} 
void PlayPiece::setX(int x) {
    this->x = x;
}
void PlayPiece::setY(int y) {
    this->y = y;
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
    REQUIRE(x > 0 && y > 0, "coordinates must be greater than zero");
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
std::string Player::getName(){
	return name;
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
    REQUIRE(x > 0 && y > 0, "coordinates must be greater than zero");
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
    REQUIRE(x >= 0 && y >= 0, "coordinates must be greater than zero");
    _initCheck = this;
    this->x = x;
    this->y = y;
    this->movable = movable;
	type = "muur";
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
    REQUIRE(name != "", "name must not be an empty string");
    REQUIRE(length > 0 && width > 0,
               "length and width must be greater than zero");
    _initCheck = this;
    this->name = name;
    this->length = length;
    this->width = width;
    this->playfield = new PlayPiece*[width];
    for(int i = 0; i < width; ++i){
        this->playfield[i] = new PlayPiece[length];
    }
    this->obstacles = {};
    this->players = {};
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}
bool Field::properlyInitialized() {
    return this == _initCheck;
}
bool Field::pushObstacle(Obstacle& obstacle, const std::string& direction) {
    REQUIRE(isDirection(direction), "invalid direction");
    if (!obstacle.isMovable()) {
        return false;
    }
    int oldX = obstacle.getX();
    int oldY = obstacle.getY();
    std::pair<int,int> destination = this->getCoordinates(oldX, oldY,
                                                           direction);
    int newX = destination.first;
    int newY = destination.second;
    if (!this->hasCoordinates(newX, newY)) {
        return false;
    }
    if (!this->isEmpty(newX, newY)) {
        return false;
    }
    this->playfield[oldX][oldY] = this->playfield[newX][newY];
    this->playfield[newX][newY] = obstacle;
    obstacle.setX(newX);
    obstacle.setY(newY);
    return true;

}
bool Field::isEmpty(int x, int y) {
    REQUIRE(this->hasCoordinates(x, y), "invalid coordinates");
    if (this->playfield[x][y].isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}
bool Field::hasCoordinates(int x, int y) {
    if (x < 1 || y < 1 || x > this->width || y > this->length) {
        return false;
    }
    else {
        return true;
    }
}
std::pair<int, int> Field::getCoordinates(int x, int y, const
                                          std::string& direction) {
    REQUIRE(isDirection(direction), "invalid direction");
    int newx = directions.at(direction).first + x;
    int newy = directions.at(direction).second + y;
    return std::make_pair(newx,newy);
}
bool Field::hasPlayer(const Player&){
	return false;
}
bool Field::addPlayer(Player* player){
	if(hasPlayer(*player)){
		std::cerr << "De speler die je wou toevoegen bestaat al." << std::endl;
		return false;
	}
	int x = player->getX();
	int y = player->getY();
	int min_coo = 0;
	if( (x >= min_coo && x <= this->getWidth()) && ( y>= min_coo && y <= this->getLength() ) ){ //zien of player binnen veld zit.
		if(!isEmpty(x,y)){
			std::cerr << "Er bevind zich al een entiteit op de positie waarop je de speler wil initialiseren." << std::endl;
			return false;
		}
	}
	else{
		std::cerr << "De speler die je wou toevoegen heeft coordinaten die niet binnen het speelveld liggen." << std::endl;
		return false;
	}
	return true;   
}
bool Field::addObstacle(Obstacle*){
	return true;//nog implementeren
}
std::string Field::getName(){
	return name;
}
int Field::getLength(){
	return length;
}
int Field::getWidth(){
	return width;
}
std::vector<Obstacle*> Field::getObstacles(){
	return obstacles;
}
std::vector<Player*> Field::getPlayers(){
	return players;
}
