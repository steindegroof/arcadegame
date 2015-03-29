#ifndef PLAYPIECES_H_
#define PLAYPIECES_H_


#include <string>


class Field;
class PlayPiece{ 
protected:
    PlayPiece* _initCheck;
    int x;
    int y;
    bool movable;
	Field* field;
public:
    /**
    * \post Constructor must end in properlyInitialized state 
    */
    PlayPiece();
    /**
    * \post Constructor must end in properlyInitialized state 
    * \pre  x >= 0, y >= 0
    **/
    PlayPiece(int x, int y, bool movable, Field* field);
    bool properlyInitialized() const;
    /**
    * \brief returns whether the object is movable
    **/
    bool isMovable();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    void move(std::string direction);
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
    * \pre  x >= 0, y >= 0
    **/
    Player(int x, int y, std::string name);
    bool properlyInitialized() const;
    std::string getName() const;	
    void setName(std::string);
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
    bool properlyInitialized() const;
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
    * \pre x >= 0, y >= 0
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
    * \pre x >= 0, y >= 0
    */
    Wall(int x, int y, bool movable);
};
#endif
