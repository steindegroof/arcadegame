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

class PlayPiece{ //masterclass
protected:
    int x;
    int y;
    bool movable;
public:
    PlayPiece();
    PlayPiece(int,int,bool);
};

class Player:public PlayPiece{
private:
	Player* _initCheck;
	std::string name;
public:
/**
* \post Constructor must end in properlyInitialized state
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	Player();
	bool properlyInitialized();
};

class Obstacle:public PlayPiece{
protected:
	Obstacle* _initCheck;
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

class Field{
private:
	Field* _initCheck;
	std::string name;
	int length;
	int width;
	PlayPiece** playfield;
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
	Field(std::string,const int,const int);
	bool properlyInitialized();
};

#endif
