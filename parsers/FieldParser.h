#ifndef FIELDPARSER_H_
#define FIELDPARSER_H_

#include "../arcade.h"
#include "AbstractParser.h"
#include "../tinyxml/tinyxml.h"


/*
 * \class FieldParser
 * This Parser is a subclass of an AbstractParser, it can therefore load any XML file.
 * However it is meant to parse Fields by using the parseField method.
 */
class FieldParser: public AbstractParser{
private:
	Field* field;

public:
	FieldParser();
	virtual ~FieldParser();

	/*
	 * This method expects the TiXmlElement that is passed as a parameter to represent an entire catalog of CDs.
	 * It will then parse said catalog and return it as a pointer to a vector of CD*'s.
	 */
	void parseFile(TiXmlElement* elem);
	
	bool writeFile(std::string filename);

	/*
	 * Returns a pointer to the parsed vector of CD*'s
	 */
	Field* getField();
};

#endif /* FIELDPARSER_H_ */
