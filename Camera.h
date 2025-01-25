#pragma once
#include "App/AppSettings.h"

class Camera
{
private:
	Vector2 position; //CENTER
	float width = APP_VIRTUAL_WIDTH;
	float height = APP_VIRTUAL_HEIGHT;
public:
	Camera(Vector2 bottomLeft) :
		position(bottomLeft) { }

	void setPosition(Vector2 pos, float mapWidth, float mapHeight);
	Vector2 getPosition()const { return position; }
	void move(Vector2 destination, float mapWidth, float mapHeight);
	bool isVisible(Vector2 objPos, float objWidth, float objHeight) const;
};

