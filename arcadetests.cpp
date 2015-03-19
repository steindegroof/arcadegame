#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>


#include "arcade.h"

class ArcadeTest: public ::testing::Test {
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
        Move move;
        PlayPiece playpiece;
        Obstacle obstacle;
        Barrel barrel;
        Wall wall;
        Player player;
        Field field;


};

/**
Tests the default constructors.
*/
TEST_F(ArcadeTest, MoveConstructor) {
	EXPECT_TRUE(move.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(move.getPlayerName(), "");
	EXPECT_EQ(move.getDirection(), "");
}
TEST_F(ArcadeTest, PlayPieceConstructor) {
	EXPECT_TRUE(playpiece.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(playpiece.getX(), 0);
	EXPECT_EQ(playpiece.getY(), 0);
	EXPECT_FALSE(playpiece.isMovable());
}
TEST_F(ArcadeTest, ObstacleConstructor) {
	EXPECT_TRUE(obstacle.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(obstacle.getType(), "");
	EXPECT_EQ(obstacle.getX(), 0);
	EXPECT_EQ(obstacle.getY(), 0);

}

TEST_F(ArcadeTest, BarrelConstructor) {
	EXPECT_TRUE(barrel.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(barrel.getType(), "ton");
	EXPECT_EQ(barrel.getX(), 0);
	EXPECT_EQ(barrel.getY(), 0);
    EXPECT_TRUE(barrel.isMovable());
}
TEST_F(ArcadeTest, wallConstructor) {
	EXPECT_TRUE(wall.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(wall.getType(), "muur");
	EXPECT_EQ(wall.getX(), 0);
	EXPECT_EQ(wall.getY(), 0);
	EXPECT_FALSE(wall.isMovable());
}
TEST_F(ArcadeTest, PlayerConstructor) {
	EXPECT_TRUE(player.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(player.getX(), 0);
	EXPECT_EQ(player.getY(), 0);
	EXPECT_EQ(player.getName(), "");
	EXPECT_TRUE(player.isMovable());
}
TEST_F(ArcadeTest, FieldConstructor) {
	EXPECT_TRUE(field.properlyInitialized());
	EXPECT_EQ(field.getLength(), 0);
	EXPECT_EQ(field.getWidth(), 0);
	EXPECT_EQ(field.getName(), "");
	Field field2("naam", 5, 10);
	EXPECT_TRUE(field.properlyInitialized());
	EXPECT_EQ(field2.getLength(), 5);
	EXPECT_EQ(field2.getWidth(), 10);
	EXPECT_EQ(field2.getName(), "naam");
}
TEST_F(ArcadeTest, addPlayer) {
    Field field2("veld", 5, 10);
	Player player2(1, 3, "speler");
	//Player player3(2, 4, "speler"); // invalid: duplicate name
	Player player4(1, 3, "speelster"); // invalid: square occupied
	Player player5(2, 3, "speelster"); // valid
	//Player player6(-1, 3, "valsspeler"); // invalid: negative x
	Player player7(2, 10, "fluitspeler"); // invalid: y too high
    EXPECT_TRUE(field2.addPlayer(&player2));
    EXPECT_FALSE(field2.addPlayer(&player2)); // can't add again
	EXPECT_EQ(field2.getPlayers().size(), 1);
	EXPECT_EQ(field2.getPlayer("speler"), &player2);
    //EXPECT_FALSE(field2.addPlayer(&player3));
    EXPECT_FALSE(field2.addPlayer(&player4));
    EXPECT_TRUE(field2.addPlayer(&player5));
    //EXPECT_FALSE(field2.addPlayer(&player6));
    EXPECT_FALSE(field2.addPlayer(&player7));
	EXPECT_EQ(field2.getPlayers().size(), 2);
	EXPECT_EQ(field2.getPlayer("speelster")->getX(), 2);
    EXPECT_EQ(field2.getPlayer("valsspeler"), nullptr);
}
TEST_F(ArcadeTest, addObstacle) {
    Field field2("veld", 5, 10);
	Barrel barrel2(1, 3, true);
	Barrel barrel3(1, 3, true); // invalid: square occupied
	Barrel barrel4(2, 3, true); // valid
	Barrel barrel5(2, 10, true); // invalid: y too high
    EXPECT_TRUE(field2.addObstacle(&barrel2));
    EXPECT_FALSE(field2.addObstacle(&barrel2)); // can't add again
	EXPECT_EQ(field2.getObstacles().size(), 1);
    EXPECT_FALSE(field2.addObstacle(&barrel3));
    EXPECT_TRUE(field2.addObstacle(&barrel4));
    EXPECT_FALSE(field2.addObstacle(&barrel5));
	EXPECT_EQ(field2.getObstacles().size(), 2);
}

TEST_F(ArcadeTest, DoMove) {
    Field field3("veld", 5, 10);
	Player player3(0, 3, "speler");
	field3.addPlayer(&player3);
	// succesful move
	Move moveUP("speler", "OMHOOG");
	Move moveDOWN("speler", "OMLAAG");
	Move moveLEFT("speler", "LINKS");
	Move moveRIGHT("speler", "RECHTS");
    EXPECT_TRUE(field3.doMove(moveUP));
	EXPECT_EQ(player3.getX(), 0);
	EXPECT_EQ(player3.getY(), 4);
    // try to move off the left, then top, then bottomn then right
    EXPECT_FALSE(field3.doMove(moveLEFT));
   	EXPECT_EQ(player3.getX(), 0);
	EXPECT_EQ(player3.getY(), 4);
    EXPECT_FALSE(field3.doMove(moveUP));
   	EXPECT_EQ(player3.getX(), 0);
	EXPECT_EQ(player3.getY(), 4);
    for (int i = 0; i < 11; i++) {
	    field3.doMove(moveDOWN);
		field3.doMove(moveRIGHT);
	}
   	EXPECT_EQ(player3.getX(), 9);
	EXPECT_EQ(player3.getY(), 0);
    // and now with some obstacles
	Barrel barrel2(8, 0, true);
	Barrel barrel3(9, 1, true); 
	Barrel barrel4(9, 2, true);
	field3.addObstacle(&barrel2);
	field3.addObstacle(&barrel3);
	field3.addObstacle(&barrel4);
	EXPECT_FALSE(field3.doMove(moveUP)); // moving into double barrel
    EXPECT_TRUE(field3.doMove(moveLEFT)); // moving into single barrel
    EXPECT_TRUE(field3.doMove(moveUP)); 
    // moving into barrel blocked by edge
	EXPECT_FALSE(field3.doMove(moveRIGHT));
}
TEST_F(ArcadeTest, FieldSquareIsEmpty) {
    Field field1("veld",2,8);
    EXPECT_TRUE(field1.isEmpty(0,0));
    EXPECT_TRUE(field1.isEmpty(7,1));
    Player player1(7, 1, "speler");
    field1.addPlayer(&player1);
    Barrel barrel1(0, 0, true);
    field1.addObstacle(&barrel1);
    EXPECT_FALSE(field1.isEmpty(0,0));
    EXPECT_FALSE(field1.isEmpty(7,1));
}

TEST_F(ArcadeTest, FieldHasCoordinates) {
    Field field1("veld",1,88);
    EXPECT_TRUE(field1.hasCoordinates(0,0));
    EXPECT_TRUE(field1.hasCoordinates(87,0));
    EXPECT_TRUE(field1.hasCoordinates(10,0)); 
    EXPECT_FALSE(field1.hasCoordinates(0,1));  
    EXPECT_FALSE(field1.hasCoordinates(100,0));
    EXPECT_FALSE(field1.hasCoordinates(-10,0));
}
TEST_F(ArcadeTest, FieldGetCoordinates) {
    Field field1("veld",10,8);
    EXPECT_EQ(field1.getCoordinates(0,0,"OMHOOG"),std::make_pair(0,1));
    EXPECT_EQ(field1.getCoordinates(100,100,"OMHOOG"),std::make_pair(100,101));
    EXPECT_EQ(field1.getCoordinates(0,0,"OMLAAG"),std::make_pair(0,-1));
    EXPECT_EQ(field1.getCoordinates(0,0,"LINKS"),std::make_pair(-1,0));
    EXPECT_EQ(field1.getCoordinates(-1,-10,"RECHTS"),std::make_pair(0,-10));
}
