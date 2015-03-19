#ifndef FIELDPARSER_H_
#define FIELDPARSER_H_

#include "../arcade.h"
#include "AbstractParser.h"
#include "../tinyxml/tinyxml.h"


/*
 * \class FieldParser
 * This Parser is a subclass of an AbstractParser, it can therefore load any XML file.
 * However it is meant to parse Fields by using the parseFile method.
 */
class FieldParser: public AbstractParser{
private:
	FieldParser* _initCheck;
	Field* field;
	friend std::ostream& operator<<(std::ostream&, const FieldParser&);
public:
	FieldParser();
	bool properlyInitialized() const;
	virtual ~FieldParser();

	/*
	 * Parses an xml file into a field object
	 */
	bool parseFile();
	/*
	 * Writes the field to a file
	 */
	bool writeFile(std::string filename);

	/*
	 * Returns a pointer to the field
	 */
	Field* getField();
};

#endif /* FIELDPARSER_H_ */
