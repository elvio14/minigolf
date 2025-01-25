#pragma once
#include "GameState.h"
#include "Camera.h"
#include "Structs.h"
#include "TileManager.h"
#include "JSONHandler.h"
#include "MiniMap.h"
#include "Ball.h"
#include "Hole.h"
#include "DirGuide.h"
#include "PowerBar.h"
#include "TilePhysics.h"
#include "fstream"

class LevelState : public GameState
{
private:
	size_t curLevel;
	static constexpr std::size_t MAX_SIZE = 15;
	LevelData activeLevel;
	std::array<std::array<CSimpleSprite*, MAX_SIZE>, MAX_SIZE> sprites;
	MiniMap miniMap;
	Ball ball;
	Hole hole;
	float mapWid;
	float mapHei;
	DirGuide dirGuide;
	PowerBar powerbar;
	int strokes = 1;
	bool isWon = false;
public:
	LevelState() : GameState(Vector2(0.f, 0.f)), miniMap(0), powerbar()
	{
		if (!log.is_open()) {
			log.open("logLevelState.txt", std::ios::trunc);
		}
		loadLevel(1);
	}
	LevelState(size_t level) : GameState(Vector2(0.f, 0.f)), miniMap(0), powerbar(), curLevel(level)
	{
		if (!log.is_open()) {
			log.open("logLevelState.txt", std::ios::trunc);
		}
		loadLevel(level);
	}

	bool getStatus() override { return !isWon; }
	void update(float deltaTime) override;
	void render() override;

	void loadLevel(size_t level);
	
	void shutdown() override;

	static std::ofstream log;
private:
	void handleHitBall(float deltaTime);
	void handleInput(float deltaTime);
};

