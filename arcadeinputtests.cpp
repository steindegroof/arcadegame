#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>


#include "arcade.h"
#include "parsers/FieldParser.h"
#include "parsers/MovesParser.h"
#include "arcadeUtils.h"

class ArcadeInputTest: public ::testing::Test {
protected:
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

/**
virtual void SetUp() will be called before each test is run.  You
should define it if you need to initialize the variables.
Otherwise, this can be skipped.
*/
	virtual void SetUp() {
	}

/**
virtual void TearDown() will be called after each test is run.
You should define it if there is cleanup work to do.  Otherwise,
you don't have to provide it.
*/
	virtual void TearDown() {
	}

/**
Declares the variables your tests want to use.
*/
	MovesParser movesparser;
	FieldParser fieldparser;
    
};

/**
Test of de MovesParser faalt wanneer er een bestand opgegeven wordt dat niet bestaat.
*/
TEST_F(ArcadeInputTest, MovesParser_NonExistingFile){
	ASSERT_TRUE(DirectoryExists("testOutput"));
	EXPECT_FALSE(FileExists("testOutput/nonExistingFile.xml"));
	EXPECT_FALSE(movesparser.loadFile("testOutput/nonExistingFile.xml"));
}
/**
Test of de FieldParser faalt wanneer er een bestand opgegeven wordt dat niet bestaat.
*/
TEST_F(ArcadeInputTest, FieldParser_NonExistingFile){
	ASSERT_TRUE(DirectoryExists("testOutput"));
	EXPECT_FALSE(FileExists("testOutput/nonExistingFile.xml"));
	EXPECT_FALSE(fieldparser.loadFile("testOutput/nonExistingFile.xml"));
}
/**
Test of parsen mislukt als een speler geen naam heeft.
*/
TEST_F(ArcadeInputTest, FieldParser_NoName){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_no_playername.xml"));
	EXPECT_FALSE(fieldparser.parseFile());
}

/**
Test of parsen mislukt als er geen veldnaam gegeven is.
*/
TEST_F(ArcadeInputTest, FieldParser_no_fieldname){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_no_fieldname.xml"));
	EXPECT_FALSE(fieldparser.parseFile());
}
/**
Test of parsen mislukt als een entiteit een negatief coordinaat heeft.
*/
TEST_F(ArcadeInputTest, FieldParser_neg_coo){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_neg_coo.xml"));
	EXPECT_FALSE(fieldparser.parseFile());
}
/**
Test of parsen mislukt als een entiteit buiten het veld ligt.
*/
TEST_F(ArcadeInputTest, FieldParser_out_of_range){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_out_of_range.xml"));
	EXPECT_DEATH(fieldparser.parseFile(),"invalid coordinates when calling addObstacle");
}
/**
Test of parsen mislukt als een veld negatieve coordinaten heeft.
*/
TEST_F(ArcadeInputTest, FieldParser_neg_coo_field){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_neg_coo_field.xml"));
	EXPECT_FALSE(fieldparser.parseFile());
}
/**
Test of parsen mislukt als er 2 entiteiten op dezelfde plek willen staan.
*/
TEST_F(ArcadeInputTest, FieldParser_double_position){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_double_position.xml"));
	EXPECT_FALSE(fieldparser.parseFile());
}
/**
Test of parsen mislukt als er een dimensie niet gegeven is.
*/
TEST_F(ArcadeInputTest, FieldParser_missing_dimension){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(fieldparser.loadFile("testInput/speelveld_missing_dimension.xml"));
	EXPECT_FALSE(fieldparser.parseFile());
}
/**
Test of correcte input voor speelveld kan parsen.
*/
TEST_F(ArcadeInputTest, FieldParser_HappyDay){
	ASSERT_TRUE(DirectoryExists("xml_files"));
	EXPECT_TRUE(fieldparser.loadFile("xml_files/Speelveld1.0.xml"));
	EXPECT_TRUE(fieldparser.parseFile());
	Field* field = fieldparser.getField();
	EXPECT_NE(field,nullptr);
}
/**
Test of correcte input voor moves kan parsen.
*/
TEST_F(ArcadeInputTest, MovesParser_HappyDay){
	ASSERT_TRUE(DirectoryExists("xml_files"));
	EXPECT_TRUE(movesparser.loadFile("xml_files/Bewegingen1.0.xml"));
	EXPECT_TRUE(movesparser.parseFile());
	EXPECT_NE(movesparser.getMoves()->size(),0);
}
/**
Test of xml bestand van moves met een ongeldige move in, gewoon parsed, maar deze foutieve move negeert.
*/
TEST_F(ArcadeInputTest, MovesParser_no_playername){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(movesparser.loadFile("testInput/Bewegingen_no_playername.xml"));
	EXPECT_TRUE(movesparser.parseFile());
}
/**
Test of xml bestand van moves met geen enkele geldige move gewoon parsed, maar resulteert in 0 moves.
*/
TEST_F(ArcadeInputTest, MovesParser_no_valid_moves){
	ASSERT_TRUE(DirectoryExists("testInput"));
	EXPECT_TRUE(movesparser.loadFile("testInput/Bewegingen_no_valid_moves.xml"));
	EXPECT_TRUE(movesparser.parseFile());
	std::vector<Move*>* moves = movesparser.getMoves();
	EXPECT_EQ(moves->size(), 0);
}
/**
Test of assertions falen bij overtreden van contract fieldparser
*/
TEST_F(ArcadeInputTest, FieldParser_DesignByContract){
	ASSERT_TRUE(DirectoryExists("xml_files"));
	EXPECT_TRUE(fieldparser.loadFile("xml_files/Bewegingen1.0.xml")); //bewegingen inladen bij fieldparser
	EXPECT_DEATH(fieldparser.parseFile(),"FieldParser verwacht als rootname 'VELD'. Dit werd niet gevonden.");
}
/**
Test of assertions falen bij overtreden van contract movesparser
*/
TEST_F(ArcadeInputTest, MovesParser_DesignByContract){
	ASSERT_TRUE(DirectoryExists("xml_files"));
	EXPECT_TRUE(movesparser.loadFile("xml_files/Speelveld1.0.xml")); //bewegingen inladen bij fieldparser
	EXPECT_DEATH(movesparser.parseFile(),"MovesParser verwacht als rootname 'BEWEGINGEN'. Dit werd niet gevonden.");
}
