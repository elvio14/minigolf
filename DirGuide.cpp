#include "stdafx.h"
#include "DirGuide.h"

void DirGuide::addRotation(float add) {
	rotation += add;
}

void DirGuide::update(float deltaTime) {
	if (isActive) {
		sprite->SetPosition(position.x, position.y);
		sprite->SetAngle(rotation - quarterPI);
	}
}

void DirGuide::render() const {
	if (isActive) {
		sprite->Draw();
	}
}

void DirGuide::shutdown() {
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}