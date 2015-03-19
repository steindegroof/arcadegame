#ifndef MOVESPARSER_H_
#define MOVESPARSER_H_

#include "../arcade.h"
#include "AbstractParser.h"
#include "../tinyxml/tinyxml.h"

/*
 * \class MovesParser
 * This Parser is a subclass of an AbstractParser, it can therefore load any XML file.
 * However it is meant to parse Moves by using the parseFile method.
 */
class MovesParser: public AbstractParser{
private:
	std::vector<Move*>* moves;
	MovesParser* _initCheck;
    	friend std::ostream& operator<<(std::ostream&, const MovesParser&);
public:
	MovesParser();
	bool properlyInitialized() const;
	virtual ~MovesParser();
	/*
	 * Parses an xml file into a vector of Move*'s
	 */
	bool parseFile();
	/*
	 * Writes the Moves to a file
	 */
	bool writeFile(std::string filename);

	/*
	 * Returns a pointer to the parsed vector of Move*'s
	 */
	std::vector<Move*>* getMoves();
};

#endif /* FIELDPARSER_H_ */
