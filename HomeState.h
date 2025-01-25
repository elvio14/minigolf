#pragma once
#include "GameState.h"
#include "Camera.h"

class HomeState : public GameState
{
private:
	bool status = true;
public:
	void update(float deltaTime) override;
	void render() override;
	bool getStatus() override { return status;}
	void shutdown() override;
};

