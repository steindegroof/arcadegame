#ifndef ABSTRACTPARSER_H_
#define ABSTRACTPARSER_H_

#include <iostream>
#include <string>
#include "../tinyxml/tinyxml.h"

/**
 * \class AbstractParser
 * This class is meant as a superclass for classes that can load parse xml files.
 * The abstract parsers can load any xml file into a TinyXML document (TiXmlDocument)
 * and remembers the first element (aka the root) in that document.
 */
class AbstractParser {
private:
	TiXmlElement * root;
	TiXmlDocument doc;
public:
/**
 * \post Constructor must end in properlyInitialized state
 */
	AbstractParser();
	bool properlyInitialized();
	virtual ~AbstractParser();

/**
 * Returns the first element (aka the root) of the loaded XML Document.
 * Root is returned as a TiXmlElement
 * \pre AbstractParser must be initialized when calling getRoot.
 */
	TiXmlElement* getRoot();

/**
 * Loads any XML file. Returns true when loading the file was succesfull.
 * Returns false, when something went wrong during loading.
 * \pre AbstractParser must be initialized when calling loadFile.
 */
	bool loadFile(std::string filename);
/**
 * Returns name of the root.
 * \pre AbstractParser must be initialized when calling getRootName.
 */
	std::string getRootName();
};

#endif /* ABSTRACTPARSER_H_ */
