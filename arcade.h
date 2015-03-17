#ifndef ARCADE_H_
#define ARCADE_H_

#include <string>
#include <vector>

const std::vector<std::string> directions = {"OMHOOG", "OMLAAG", "LINKS", "RECHTS"};

class Move{ 
private:
    Move* _initCheck;
    std::string playername;
    std::string direction;
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Move();
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    /**
    * \pre direction is one of: OMHOOG, LINKS, OMLAAG, RECHTS 
    */
    Move(std::string playername,std::string direction);
    bool properlyInitialized();
    std::string getPlayerName();
    std::string getDirection();
};

class PlayPiece{ 
protected:
    PlayPiece* _initCheck;
    int x;
    int y;
    bool movable;
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    PlayPiece();
    PlayPiece(int,int,bool);
    bool properlyInitialized();
};

class Player:public PlayPiece{
private:
	Player* _initCheck;
	std::string name;
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Player();
    Player(int, int, std::string);
    bool properlyInitialized();
};

class Obstacle:public PlayPiece{
protected:
	Obstacle* _initCheck;
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Obstacle();
    bool properlyInitialized();
	
};

class Barrel:public Obstacle{
private:
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Barrel();
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    /**
    * \pre x > 0, y > 0
    */
    Barrel(int x, int y);
};

class Wall:public Obstacle{
private:
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Wall();
    Wall(int, int);
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
        /**
        * \post Constructor must end in properlyInitialized state 
        */
	Field();
	Field(std::string,const int,const int);
	bool properlyInitialized();
        /** 
        * \brief verplaats een playpieve volgens de opgegeven move.
        * \param[in]	move	De te maken move
	* \param[out]   succes	Geeft weer of de move gelukt is
        **/
        bool doMove(Move&);
};

#endif
