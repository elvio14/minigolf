#pragma once
#include "App/App.h"

class DirGuide
{
private:
	CSimpleSprite* sprite;
	Vector2 position;
	bool isActive = true;
	float rotation = 0.f;
	float quarterPI = 1.57079632675f;
public:
	DirGuide() {
		sprite = App::CreateSprite(".\\TestData\\Sprites\\dirguide.png", 1, 1);
	}

	DirGuide(Vector2 pos) : position(pos) {
		sprite = App::CreateSprite(".\\TestData\\Sprites\\dirguide.png", 1, 1);
		sprite->SetPosition(pos.x, pos.y);
	}
	void setPosition(Vector2 newPos) { position = newPos; }
	void setIsActive(bool status) { isActive = status; }
	void addRotation(float add);
	void reset() { rotation = 0.f; }
	float getRotation() { return rotation; }
	void update(float deltaTime);
	void render() const;
	void shutdown();
};

