#include "stdafx.h"
#include "Hole.h"

void Hole::render() const {
	sprite->Draw();
}

void Hole::shutdown() {
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}