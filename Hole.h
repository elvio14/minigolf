#pragma once
#include "App/SimpleSprite.h"
#include "App/app.h"
class Hole
{
private:
	Vector2 position;
	CSimpleSprite* sprite;
public:
	Hole() : position() {
		sprite = App::CreateSprite(".\\TestData\\Sprites\\hole.png", 1, 1);
		sprite->SetPosition(position.x, position.y);
	}
	Hole(Vector2 pos) : position(pos) {
		sprite = App::CreateSprite(".\\TestData\\Sprites\\hole.png", 1, 1);
		sprite->SetPosition(pos.x, pos.y + 32.f);
	}
	Vector2 getPosition() const { return position; }
	void render() const;
	void shutdown();
};

