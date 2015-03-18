#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>


#include "arcade.h"
#include "arcadeUtils.h"
#include "parsers/FieldParser.h"
#include "parsers/MovesParser.h"

class ArcadeOutputTest: public ::testing::Test {
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
	FieldParser fieldparser;
	MovesParser movesparser;
    
};

// Tests the compare files (overgenomen uit het TicTacToevoorbeeld)
TEST_F(ArcadeOutputTest, FileCompare) {
	ASSERT_TRUE(DirectoryExists("testOutput"));

	std::ofstream myfile;
	myfile.open("testOutput/file1.txt");
	myfile.close();
	myfile.open("testOutput/file2.txt");
	myfile.close();

	EXPECT_TRUE(FileExists("testOutput/file1.txt"));
	EXPECT_TRUE(FileExists("testOutput/file2.txt"));
	EXPECT_TRUE(FileIsEmpty("testOutput/file1.txt"));
	EXPECT_TRUE(FileIsEmpty("testOutput/file2.txt"));


	//compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
	//EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	//EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare an empty and a non-empty files
	myfile.open("testOutput/file1.txt");
	myfile << "xxx" << std::endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileExists("testOutput/file1.txt"));
	EXPECT_FALSE(FileIsEmpty("testOutput/file1.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare two equal files
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << std::endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileExists("testOutput/file2.txt"));
	EXPECT_FALSE(FileIsEmpty("testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare 2 non-empty files which are off by a character in the middle
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << std::endl << "xyy";
	myfile.close();
	EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare 2 non-empty files where one is one character shorter than the other
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << std::endl << "yy";
	myfile.close();
	EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare existing against non existing file
	EXPECT_FALSE(
			FileCompare("testOutput/file1.txt", "testOutput/nonexisting.txt"));
	EXPECT_FALSE(
			FileCompare("testOutput/nonexisting.txt", "testOutput/file1.txt"));
}
/**
Test de output van het "happy day" scenario voor de FieldParser. Waar het ingelezen veld correct wordt weggeschreven (de manier waarop we het verwachten).
*/
TEST_F(ArcadeOutputTest, FieldParserOutput_HappyDay){
	ASSERT_TRUE(DirectoryExists("testOutput/expected_output"));
	//if directory doesn't exist then no need in proceeding with the test
	EXPECT_TRUE(fieldparser.loadFile("xml_files/Speelveld1.0.xml"));
	EXPECT_TRUE(fieldparser.parseFile());
	EXPECT_TRUE(fieldparser.writeFile("testOutput/speelveld.txt"));
	EXPECT_TRUE(FileCompare("testOutput/speelveld.txt","testOutput/expected_output/speelveld_template.txt"));
}
/**
Test de output van het "happy day" scenario voor de MovesParser. Waar de ingelezen moves correct worden weggeschreven (de manier waarop we het verwachten).
*/
TEST_F(ArcadeOutputTest, MovesParserOutput_HappyDay){
	ASSERT_TRUE(DirectoryExists("testOutput/expected_output"));
	//if directory doesn't exist then no need in proceeding with the test
	EXPECT_TRUE(movesparser.loadFile("xml_files/Bewegingen1.0.xml"));
	EXPECT_TRUE(movesparser.parseFile());
	EXPECT_TRUE(movesparser.writeFile("testOutput/ResterendeBewegingen.txt"));
	EXPECT_TRUE(FileCompare("testOutput/ResterendeBewegingen.txt","testOutput/expected_output/ResterendeBewegingen_template.txt"));
}

/**
Test of het verkregen veld na de moves hetgeen is wat we verwachten.
*/
TEST_F(ArcadeOutputTest, FieldParser_FieldAfterMoves){
	ASSERT_TRUE(DirectoryExists("testOutput/expected_output"));
	//if directory doesn't exist then no need in proceeding with the test
	EXPECT_TRUE(movesparser.loadFile("xml_files/Bewegingen1.0.xml"));
	EXPECT_TRUE(movesparser.parseFile());
	EXPECT_TRUE(fieldparser.loadFile("xml_files/Speelveld1.0.xml"));
	EXPECT_TRUE(fieldparser.parseFile());
	Field* field = fieldparser.getField();
	std::vector<Move*>* moves = movesparser.getMoves();
	std::vector<Move*>::iterator it;
	for( it = moves->begin(); it!=moves->end(); it++){
		field->doMove(**it);
	}
	EXPECT_TRUE(fieldparser.writeFile("testOutput/field_after_moves.txt"));
	EXPECT_TRUE(FileCompare("testOutput/field_after_moves.txt","testOutput/expected_output/field_after_moves_template.txt"));
}
/**
Test of de vector met moves leeg is na het uitvoeren van alle moves.
*/
TEST_F(ArcadeOutputTest, MovesParser_MovesAfterMoves){
	ASSERT_TRUE(DirectoryExists("testOutput/expected_output"));
	//if directory doesn't exist then no need in proceeding with the test
	EXPECT_TRUE(movesparser.loadFile("xml_files/Bewegingen1.0.xml"));
	EXPECT_TRUE(movesparser.parseFile());
	EXPECT_TRUE(fieldparser.loadFile("xml_files/Speelveld1.0.xml"));
	EXPECT_TRUE(fieldparser.parseFile());
	Field* field = fieldparser.getField();
	std::vector<Move*>* moves = movesparser.getMoves();
	std::vector<Move*>::iterator it;
	while(!moves->empty()){
		it = moves->begin();
		field->doMove(**it);
		moves->erase(it);	
	}
	EXPECT_TRUE(movesparser.writeFile("testOutput/moves_after_moves.txt"));
	EXPECT_TRUE(FileCompare("testOutput/moves_after_moves.txt","testOutput/expected_output/moves_after_moves_template.txt"));
}

