#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>


#include "arcade.h"

class ArcadeTest: public ::testing::Test {
protected:
	friend class Obstacle;
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
}
TEST_F(ArcadeTest, ObstacleConstructor) {
	EXPECT_TRUE(obstacle.properlyInitialized());
	// verify post-condition
}
TEST_F(ArcadeTest, PlayPieceConstructor) {
	EXPECT_TRUE(playpiece.properlyInitialized());
	// verify post-condition
}
TEST_F(ArcadeTest, BarrelConstructor) {
	EXPECT_TRUE(barrel.properlyInitialized());
	// verify post-condition
}
TEST_F(ArcadeTest, wallConstructor) {
	EXPECT_TRUE(wall.properlyInitialized());
	// verify post-condition
}
TEST_F(ArcadeTest, PlayerConstructor) {
	EXPECT_TRUE(player.properlyInitialized());
	// verify post-condition
}
TEST_F(ArcadeTest, FieldConstructor) {
	EXPECT_TRUE(obstacle.properlyInitialized());
	// verify post-condition
}
