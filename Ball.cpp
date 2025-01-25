#include "stdafx.h"
#include <cmath>
#include "Ball.h"
std::ofstream Ball::log;

void Ball::applyForce(Vector2 addForce) {
	if (!isActive) {
		isActive = true;
	}
	vel = vel + addForce;
}


void Ball::updatePos(float deltaTime) {
	position = position + (vel * elapsedTime / mass);
	sprite->SetPosition(position.x, position.y);
	if (isActive) {
		log << "Active\n";
		log << "elapsedTime: " + std::to_string(elapsedTime);
		log << "divided: " + std::to_string(elapsedTime / 1000.f) + "\n";
		log << "deltaTime: " + std::to_string(deltaTime) + "\n";
		log << "vel: " + std::to_string(vel.x) + ", " + std::to_string(vel.y) + "\n";
		log << "pos: " + std::to_string(position.x) + ", " + std::to_string(position.y) + "\n\n";
	}
	else {
		log << "|";
	}
}
void Ball::applyFriction(float amount, float deltaTime) {
	float angle = atan2(vel.y, vel.x);
	applyForce({ -(amount * cos(angle) * deltaTime / mass), -(amount * sin(angle) * deltaTime / mass) });
}

void Ball::clampVel() {
	if (vel.magnitude() > 60.f) {
		vel.normalize();
		vel * 59.f;
	}
}

void Ball::update(float deltaTime, int& strokes) {
	if (NPTError) {
		isActive = false;
		NPTError = false;
	}
	if (isActive) {
		applyFriction(friction, deltaTime);
		clampVel();
		updatePos(deltaTime);
		elapsedTime += deltaTime;
	}
	else {
		elapsedTime = 0.f;
	}

	if (abs(vel.x) < 1.5f && abs(vel.y) < 1.5f && isActive) {
		isActive = false;
		vel = Vector2();
		strokes++;
	}

	//reset friction
	//friction = 0.75f;

}

void Ball::render() {
	if (toRender) {
		sprite->Draw();
	}
	else {
		toRender = true;
	}

}

void Ball::shutdown() {
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}

	log.close();
}