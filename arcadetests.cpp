#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>


#include "arcade.h"

class ArcadeTest: public ::testing::Test {
protected:
	friend class Field;
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
	// verify post-condition
	EXPECT_EQ(field.getLength(), 0);
	EXPECT_EQ(field.getWidth(), 0);
	EXPECT_EQ(field.getName(), "");
}
