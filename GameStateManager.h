#pragma once
#include <stack>
#include "GameState.h"

class GameStateManager
{
private:
	std::stack<std::unique_ptr<GameState>> states;

public:
	GameStateManager(std::unique_ptr<GameState> initialState) {
		pushState(std::move(initialState));
	}

	void pushState(std::unique_ptr<GameState> state);
	void popState();
	GameState* getCurrentState();

	void pushLevel(size_t number);

	void update(float deltaTime);
	void render();
	void shutdown();
};