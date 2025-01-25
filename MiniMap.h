#pragma once
#include "App/SimpleSprite.h"
#include "App/app.h"

class MiniMap
{
private:
	size_t level;
	CSimpleSprite* sprite;
	Vector2 position;
	Vector2 ballPos;

public:
	MiniMap(size_t level) : level(level) {
		initMiniMap(level);
	}
	void initMiniMap(size_t level);
	void update(float deltaTime);
	void render() const;
	void shutdown();
};

