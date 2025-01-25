#pragma once
#include <memory>
#include "App/SimpleSprite.h"
#include "App/app.h"
#include "fstream"

class Ball
{
private:
	float radius = 15.f;
	CSimpleSprite* sprite;
	Vector2 position;
	Vector2 vel; //velocity
	float friction = 15.f; 
	float elapsedTime = 0.f;
	float k = 0.1f;
	float mass = 1000.f;

	bool isActive;
	bool NPTError = false;
	bool toRender;
public:
	Ball(): position(), vel(0),toRender(true), isActive(false) {
		sprite = App::CreateSprite(".\\TestData\\Sprites\\Ball.bmp", 1, 1);
	}
	Ball(Vector2 position) : position(position), vel(0), toRender(true), isActive(false) {
		sprite = App::CreateSprite(".\\TestData\\Sprites\\Ball.bmp", 1, 1);

		if (!log.is_open()) {
			log.open("logball.txt", std::ios::trunc);
		}
		sprite->SetPosition(position.x, position.y);
	}
	~Ball() {
	}

	void render();
	void update(float deltaTime, int& strokes);

	float getRadius() const { return radius; }
	Vector2 getPosition() const { return position; }
	bool getIsActive() const { return isActive; }
	float getMass() const { return mass; }
	void setPosition(Vector2 pos) { position = pos; }
	void addPosition(Vector2 addPos) { position = position + addPos; }
	void addPosX(float addx) { position.x += addx; };
	void addPosY(float addy) { position.y += addy; };
	void addVel(Vector2 addVel) { vel = vel + addVel; }
	void setVel(Vector2 newVel) { vel = newVel; }
	Vector2 getVel() const { return vel; }
	void setIsActive(bool status) { isActive = status;}
	void setNPTError(bool status) { NPTError = status; }

	void applyForce(Vector2 force);
	void applyFriction(float amount, float deltaTime);
	void setFriction(float newf) { friction = newf; };
	void clampVel();
	void setRender(bool val) { toRender = val; }
	
	void shutdown();
	static std::ofstream log;
private:
	void updatePos(float deltaTime);
};

