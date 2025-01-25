#pragma once
#include "Camera.h"

class GameState
{
public:
	virtual ~GameState() = default;
	Camera camera = 0;

	GameState() {};

	GameState(Vector2 camPos) : camera(camPos) {}

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual bool getStatus() = 0;
	virtual void shutdown() = 0;
};

