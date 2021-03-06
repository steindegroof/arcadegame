#include <algorithm>
#include <iostream>
#include "arcadeUtils.h"
#include "arcade.h"
#include "playpieces.h"
#include "DesignByContract.h"

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
    REQUIRE(isDirection(direction), "invalid direction");
    _initCheck = this;
    this->playername = playername;
    this->direction = direction;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");

}
bool Move::properlyInitialized() const {
    return this == _initCheck;
}
const std::string Move::getPlayerName() const {
    REQUIRE(this->properlyInitialized(), 
	        "Move wasn't initialized when calling getPlayerName");
    return this->playername;
}
const std::string Move::getDirection() const {
    REQUIRE(this->properlyInitialized(), 
	        "Move wasn't initialized when calling getDirection");
    return this->direction;
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
    this->playfield = new PlayPiece**[width];
    for(int i = 0; i < width; ++i){
        this->playfield[i] = new PlayPiece*[length];
		for (int j = 0; j < length; ++j) {
		    this->playfield[i][j] = nullptr;
		}
    }
    this->obstacles = {};
    this->players = {};
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}
bool Field::properlyInitialized() const {
    return this == _initCheck;
}
bool Field::pushObstacle(PlayPiece* obstacle, const std::string& direction) {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling pushObstacle");
    REQUIRE(isDirection(direction), "invalid direction");
    if (!obstacle->isMovable()) {
        return false;
    }
    int oldX = obstacle->getX();
    int oldY = obstacle->getY();
    std::pair<int,int> destination = this->getCoordinates(oldX, oldY,
                                                           direction);
    int newX = destination.first;
    int newY = destination.second;
    if (!this->hasCoordinates(destination)) {
        return false;
    }
    if (!this->isEmpty(destination)) {
        return false;
    }
    this->playfield[oldX][oldY] = nullptr;
    this->playfield[newX][newY] = obstacle;
    obstacle->setX(newX);
    obstacle->setY(newY);
    return true;

}
bool Field::isEmpty(int x, int y) {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling isEmpty");
    REQUIRE(this->hasCoordinates(x, y), "invalid coordinates");
    if (this->playfield[x][y] == nullptr) {
        return true;
    }
    else {
        return false;
    }
}
bool Field::isEmpty(std::pair<int, int> coordinates) {
    return this->isEmpty(coordinates.first, coordinates.second);
}
bool Field::hasCoordinates(int x, int y) const {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling hasCoordinates");
    if (x < 0 || y < 0 || x >= this->width || y >= this->length) {
        return false;
    }
    else {
        return true;
    }
}
bool Field::hasCoordinates(std::pair<int, int> coordinates) const {
    return this->hasCoordinates(coordinates.first, coordinates.second);
}
std::pair<int, int> Field::getCoordinates(int x, int y, const
                                          std::string& direction) const {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getCoordinates");
    REQUIRE(isDirection(direction), "invalid direction");
    int newx = directions.at(direction).first + x;
    int newy = directions.at(direction).second + y;
    return std::make_pair(newx,newy);
}
bool Field::addPlayer(Player* player){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling addPlayer");
    REQUIRE(this->hasCoordinates(player->getX(),player->getY()), "invalid coordinates when calling addPlayer");
    if(hasPlayer(player)){
		std::cerr << "De speler die je wou toevoegen bestaat al." << std::endl;
		return false;
	}
	int x = player->getX();
	int y = player->getY();
	if(hasCoordinates(std::make_pair(x,y))){ //zien of player binnen veld zit.
		if(!isEmpty(x,y)){
			std::cerr << "Er bevind zich al een entiteit op de positie waar je de speler wil initialiseren." << std::endl;
			return false;
		}
		else{
			playfield[x][y] = player; 
            players.push_back(player);
	        return true;
		}
	}
	else{
		std::cerr << "De speler die je wou toevoegen heeft coordinaten die niet binnen het speelveld liggen." << std::endl;
		return false;
	}
}  
Player* Field::getPlayer(std::string playername) const {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getPlayer");
    std::vector<Player*>::const_iterator i;
    for (i = this->players.begin(); i != this->players.end(); i++) {
        Player* player = *i;
        if (player->getName() == playername) {
            return *i;
        }
    }
	return nullptr;
}
PlayPiece* Field::getPlayPiece(int x, int y) const {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getPlayPiece");
    REQUIRE(this->hasCoordinates(x,y), "invalid coordinates");
    return this->playfield[x][y];
}
PlayPiece* Field::getPlayPiece(std::pair<int, int> coordinates) const {
    return this->getPlayPiece(coordinates.first, coordinates.second);
}

bool Field::hasPlayer(const Player* player) {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling hasPlayer");
    return std::find(players.begin(),players.end(),player) != players.end();
}
bool Field::addObstacle(Obstacle* obstacle){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling addObstacle");
    REQUIRE(this->hasCoordinates(obstacle->getX(),obstacle->getY()), "invalid coordinates when calling addObstacle");
    int x = obstacle->getX();
	int y = obstacle->getY();
	if(hasCoordinates(x,y)){ //zien of obstacle binnen veld zit.
		if(!isEmpty(x,y)){
			std::cerr << "Er bevind zich al een entiteit op de positie waar je het obstakel wil initialiseren." << std::endl;
			return false;
		}
		else{
			playfield[x][y] = obstacle; 	
			obstacles.push_back(obstacle);
			return true;
		}
	}
	else{
		std::cerr << "Het obstakel dat je wou toevoegen heeft coordinaten die niet binnen het speelveld liggen." << std::endl;
		return false;
	}
	// We shouldn't get to this point.. 
	return false;
}
std::string Field::getName(){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getName");
    return name;
}
int Field::getLength(){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getLength");
    return length;
}
int Field::getWidth(){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getWidth");
    return width;
}
std::vector<Obstacle*> Field::getObstacles(){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getObstacles");
    return obstacles;
}
std::vector<Player*> Field::getPlayers(){
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling getPlayers");
    return players;
}
bool Field::doMove(const Move& move) {
    REQUIRE(this->properlyInitialized(), 
	        "Field wasn't initialized when calling doMove");
	REQUIRE(move.getPlayerName() != "","Empty playername when calling doMove.");
    std::string playername = move.getPlayerName();
    Player* player = this->getPlayer(playername);
	if(!this->hasPlayer(player)) {
	    return false;
	}
    int oldX = player->getX();
    int oldY = player->getY();
    std::string direction = move.getDirection();
    std::pair<int, int> newcoordinates =
            this->getCoordinates(oldX, oldY, direction);
    if (!this->hasCoordinates(newcoordinates)) {
        return false;
    }
    if (!this->isEmpty(newcoordinates)) {
        // try to move the piece that's in the way
        PlayPiece* piece = this->getPlayPiece(newcoordinates);
        if (!this->pushObstacle(piece, direction)) {
            return false;
        }
    }
    // move the player now
    int newX = newcoordinates.first;
    int newY = newcoordinates.second;
    this->playfield[oldX][oldY] = nullptr;
    this->playfield[newX][newY] = player;
    player->setX(newX);
    player->setY(newY);
    return true;
}
