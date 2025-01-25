#include "stdafx.h"
#include "GameStateManager.h"
#include "LevelState.h"

void GameStateManager::pushState(std::unique_ptr<GameState> state) {
	states.push(std::move(state));
}

void GameStateManager::popState() {
	if (!states.empty()) {
		states.pop();
	}
}

GameState* GameStateManager::getCurrentState() {
	if (states.empty()) {
		return nullptr;
	}

	return states.top().get();
}

void GameStateManager::pushLevel(size_t number) {
	auto level = std::make_unique<LevelState>();
	level->loadLevel(number);

	pushState(std::move(level));
};

void GameStateManager::update(float deltaTime) {
	if (!states.empty()) {
		states.top()->update(deltaTime);
	}
}

void GameStateManager::render() {
	if (!states.empty()) {
		states.top()->render();
	}
}

void GameStateManager::shutdown() {
	while (!states.empty()) {
		states.top()->shutdown();
		popState();
	}
}