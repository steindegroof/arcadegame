#ifndef ARCADE_H_
#define ARCADE_H_

#include <string>
#include <vector>
#include <map>
#include "playpieces.h"

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
    bool properlyInitialized() const;
    const std::string getPlayerName() const;
    const std::string getDirection() const;
};


class Field{
protected:
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
    bool pushObstacle(PlayPiece* obstacle, const std::string& direction);
public:
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
	/**
    * \brief        returns the playpiece on a given coordinate.
    * \param[IN]    x          the x coordinate of the playpiece
	* \param[IN]    y          the y coordinate of the playpiece
    * \param[OUT]   PlayPiece   pointer to the playpiece on the given position. If no playpiece was found returns nullptr.
    **/
    PlayPiece* getPlayPiece(int x, int y) const;
    PlayPiece* getPlayPiece(std::pair<int, int>) const;
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
	/** 
    * \brief Geeft terug of het veld goed geinitialiseerd is..
	* \param[out]   succes	Geeft weer de klasse goed is geinitialiseerd.
    **/
    bool properlyInitialized() const;
    /** 
    * \brief verplaats een playpiece volgens de opgegeven move.
    * \param[in]	move	De te maken move
	* \param[out]   succes	Geeft weer of de move gelukt is
	* \pre          properlyInitialized
	* \pre          Player must have nonempty name.
    **/
    bool doMove(const Move&);
	/** 
    * \brief Voeg een speler toe aan het veld
    * \param[in]	player	De speler die je wil toevoegen
	* \param[out]   succes	Geeft weer of het toevoegen gelukt is.
	* \pre          De speler heeft geen negatieve coordinaten
	* \post         De speler werd aan het veld toegevoegd indien succes true was.
    **/
	bool addPlayer(Player*);
	/** 
    * \brief Voeg een obstakel toe aan het veld
    * \param[in]	obstacle	Het toe te voegen obstakel
	* \param[out]   succes	Geeft weer of het toevoegen gelukt is.
    * \pre          Het obstakel heeft geen negatieve coordinaten
	* \post         Het obstakel werd aan het veld toegevoegd indien succes true was.
    **/
	bool addObstacle(Obstacle*);
	/** 
    * \brief Geeft de naam van het veld terug.
	* \param[out]   name	de naam van het veld
    **/
	std::string getName();
	/** 
    * \brief Geeft de lengte van het veld terug.
	* \param[out]   lengte	de lengte van het veld
    **/
	int getLength();
	/** 
    * \brief Geeft de breedte van het veld terug.
	* \param[out]   breedte	de breedte van het veld
    **/
	int getWidth();
	/** 
    * \brief Geeft een pointer terug naar de speler met een bepaalde naam
	* \param[in]	playername	De naam van de te zoeken speler
	* \param[out]   player	het Player object met de gegeven naam. Of indien niet gevonden nullptr
    **/
    Player* getPlayer(std::string playername) const;
	/** 
    * \brief Geeft vector met alle obstakels op het veld terug.
	* \param[out]   vector<Obstacle*>	De vector met alle obstakels van het veld.
    **/
	std::vector<Obstacle*> getObstacles();
	/** 
    * \brief Geeft vector met alle spelers op het veld terug.
	* \param[out]   vector<Player*>	De vector met alle players van het veld.
    **/
	std::vector<Player*> getPlayers();
};

#endif
