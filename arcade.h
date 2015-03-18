#ifndef ARCADE_H_
#define ARCADE_H_

#include <string>
#include <vector>
#include <map>

const std::map<const std::string, std::pair<int, int>> directions = 
    {{"OMHOOG",{0,1}}, {"OMLAAG",{0,-1}}, {"LINKS",{-1,0}}, {"RECHTS",{1,0}}};

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
    * \pre direction is one of: OMHOOG, LINKS, OMLAAG, RECHTS 
    */
    Move(std::string playername,std::string direction);
    bool properlyInitialized();
    const std::string getPlayerName() const;
    const std::string getDirection() const;
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
    /**
    * \post Constructor must end in properlyInitialized state 
    * \pre  x > 0, y > 0
    **/
    PlayPiece(int x, int y, bool movable);
    bool properlyInitialized();
    /**
    * \brief indicates whether a piece is empty. A piece with coordinates
    * (0,0) as set by the default constructor is considered empty.
    **/
    bool isEmpty();
    /**
    * \brief returns whether the object is movable
    **/
    bool isMovable();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
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
    /**
    * \post Constructor must end in properlyInitialized state 
    * \pre  x > 0, y > 0
    **/
    Player(int x, int y, std::string name);
    bool properlyInitialized();
    std::string getName() const;	
};

class Obstacle:public PlayPiece{
protected:
	Obstacle* _initCheck;
	std::string type;
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Obstacle();
    bool properlyInitialized();
    std::string getType();
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
    * \pre x > 0, y > 0
    */
    Barrel(int x, int y, bool movable);
};

class Wall:public Obstacle{
private:
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    Wall();
    /**
    * \post Constructor must end in properlyInitialized state 
    * \pre x > 0, y > 0
    */
    Wall(int x, int y, bool movable);
};

class Field{
private:
	Field* _initCheck;
	std::string name;
	int length;
	int width;
	PlayPiece*** playfield;
	std::vector<Obstacle*> obstacles;
	std::vector<Player*> players;
        /**
        * \brief        pushes obstacle in direction if possible
        * \param[in]    obstacle        the obstacle to move
        * \param[out]   direction       the direction to move in
        * \param[out]   succes          indicates whether the object was
                                        moved
        * \post         The obstacle is moved if possible
        * \pre          direction is a valid direction
        **/
        bool pushObstacle(Obstacle& obstacle, const std::string& direction);
        /**
        * \brief        checks wheter the given coordinates are an
                        empty square on the field
        * \param[IN]    x       the x coordinate
        * \param[IN]    y       the y coordinate
        * \param[OUT]   empty   indicates whether the square is empty
        * \pre          the coordinates are valid for this field
        **/
        bool isEmpty(int x, int y);
        bool isEmpty(std::pair<int, int>);
        /**
        * \brief        checks whether the given coordinates are valid
                        for this field
        * \param[IN]    x       the x coordinate
        * \param[IN]    y       the y coordinate
        * \param[OUT]   hascoordinates  whether the coordinates are valid
        **/
        bool hasCoordinates(int x, int y) const;
        bool hasCoordinates(std::pair<int, int>) const;
        /**
        * \brief        calculates the coordinates if you go in direction
                        starting from square x,y. These may fall outside
                        the field!
        * \param[IN]    x       the x coordinate
        * \param[IN]    y       the y coordinate
        * \param[IN]    direction       the direction to move
        * \param[OUT]   coordinates     the resulting coordinates
        **/
        std::pair<int, int> getCoordinates(int x, int y, const std::string& direction) const;
        /**
        * \brief        checks whether the given player is on the field
        * \param[IN]    player          the player you want to check for
        * \param[OUT]   found           whether the player was found
        **/
        bool hasPlayer(const Player*);
        Player* getPlayer(std::string playername) const;
        PlayPiece* getPlayPiece(int x, int y) const;
        PlayPiece* getPlayPiece(std::pair<int, int>) const;
public:
        /**
        * \post Constructor must end in properlyInitialized state 
        */
	Field();
        /**
        * \post Constructor must end in properlyInitialized state 
        * \pre name must not be an empty string
        * \pre length > 0, width > 0
        */
	Field(std::string name, const int length, const int width);
	bool properlyInitialized();
        /** 
        * \brief verplaats een playpieve volgens de opgegeven move.
        * \param[in]	move	De te maken move
	* \param[out]   succes	Geeft weer of de move gelukt is
        **/
        bool doMove(const Move&);
	bool addPlayer(Player*);
	bool addObstacle(Obstacle*);
	std::string getName();
	int getLength();
	int getWidth();
	std::vector<Obstacle*> getObstacles();
	std::vector<Player*> getPlayers();
};

#endif
