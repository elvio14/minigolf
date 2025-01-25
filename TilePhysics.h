#pragma once
#include "Structs.h"
#include "Ball.h"
#include <fstream>

class TilePhysics {
private:
	static float loss;
	static float buffer;
	static float quarterPI;
	static float damping;
public:

	static TileAddress getTileAddressFromPos(Vector2 pos, const LevelData& data);
	static TileType getTileTypeFromAddress(TileAddress address, const LevelData& data);
	static Vector2 getRelativeBallPos(Vector2 pos, TileAddress ad, const LevelData& data);
	static Vector2 getNormalizedWallNormal(Vector2 p1, Vector2 p2, bool leftSide);//leftSide determines which side of the wall is active
	static void handleDiagonal(PhysicsData pd,float rotation);

	static void handleNPT(PhysicsData pd);
	static void handleNoWalls(PhysicsData pd);
	static void handleOneWall(PhysicsData pd);
	static void handleTwoWalls(PhysicsData pd);
	static void handleThreeWalls(PhysicsData pd);
	static void handleDiagonalWall(PhysicsData pd);
	static void handleStackedWalls(PhysicsData pd);

	static void handleLeftWall(PhysicsData pd);
	static void handleTopWall(PhysicsData pd);
	static void handleRightWall(PhysicsData pd);
	static void handleBottomWall(PhysicsData pd);
	static void update(Ball& ball, const LevelData& data, float deltaTime);
};