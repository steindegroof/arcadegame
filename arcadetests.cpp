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
	Obstacle obstacle;

};

/**
Tests the default constructor.
*/
TEST_F(ArcadeTest, ObstacleConstructor) {
	EXPECT_TRUE(obstacle.properlyInitialized());
	// verify post-condition
}
