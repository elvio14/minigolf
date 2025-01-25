#include "stdafx.h"
#include "MiniMap.h"

void MiniMap::initMiniMap(size_t level) {
	std::string path = ".\\TestData\\Sprites\\minimap_" + std::to_string(level) + ".png";
	sprite = App::CreateSprite(path.c_str(), 1, 1);
	sprite->SetScale(0.8);
	sprite->SetPosition(135.f,155.f);
}

void MiniMap::update(float deltaTime) {

}

void MiniMap::render() const {
	sprite->Draw();
}

void MiniMap::shutdown() {
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
}