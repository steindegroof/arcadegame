#ifndef ARCADE_H_
#define ARCADE_H_

#include <string>
#include <vector>

class Move{ //properlyini enzo
private:
    std::string playername;
    std::string direction;
public: //setters?
    Move();
    Move(std::string,std::string);
    std::string getPlayerName();
    std::string getDirection();
};

class Obstacle{
protected:
	Obstacle* _initCheck;
	int x;
	int y;
	bool movable;
	std::string type;
public:
/**
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	Obstacle();
	bool properlyInitialized();
	
};

class Barrel:public Obstacle{
private:
public:
	Barrel();
};

class Wall:public Obstacle{
private:
public:
	Wall();
};

class Player{
private:
	Player* _initCheck;
	std::string name;
	int x;
	int y;
public:
/**
* \post Constructor must end in properlyInitialized state
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	Player();
	bool properlyInitialized();
};

class Field{
private:
	Field* _initCheck;
	std::string name;
	int length;
	int width;
	std::vector<Obstacle> obstacles;
	std::vector<Player> players;
public:
/**omschrijving: zoek het object dat je wil bewegen,
*   
**/
    bool doMove(Move&);
/**
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	Field();
	bool properlyInitialized();
};

#endif
