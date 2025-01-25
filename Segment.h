#pragma once
#include "Structs.h"
#include "Utils.h"
class Segment
{
public:
	Segment() {
		position = Vector2(10.f, 10.f);
		angle = 0.f;
		length = 25.f;
		radius = 30.f;
	}
	Segment(Vector2 origin, float angle, float length, float radius) 
		:
		position(origin), angle(angle), length(length), radius(radius)
	{}

	void setPosition(float x, float y) { position.x = x; position.y = y; }
	void setPosition(Vector2 newpos) { position.x = newpos.x; position.y = newpos.y;}
	Vector2 getPosition() const { return position; }
	float getAngle() const { return angle; }
	void addAngle(float add) { angle += add; }

	void follow(const Vector2& target);
private:
	Vector2 position;
	float angle;
	float length;
	float radius;
	float angleConstraint = Utils::_PI / 6;
};

