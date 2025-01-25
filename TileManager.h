#pragma once
#include "Structs.h"
#include "App/SimpleSprite.h"
#include "App/app.h"
#include "JSONHandler.h"
#include "Camera.h"

class TileManager
{
private:
	static constexpr std::size_t MAX_SIZE = 15;
	//std::vector<std::vector<TileType>> tiles;
	//std::vector<std::vector<CSimpleSprite*>> sprites;
	//std::array<std::array<TileType, MAX_SIZE>, MAX_SIZE> tiles;
	//std::array<std::array<CSimpleSprite*, MAX_SIZE>, MAX_SIZE> sprites;
	CSimpleSprite* tile;
	int rows;
	int cols;
public:
	TileManager() : rows(MAX_SIZE), cols(MAX_SIZE) {}
	TileManager(const LevelData& levelData ) : rows(MAX_SIZE), cols(MAX_SIZE) {
		//updateTiles(levelData);
		//updateSprites(levelData);
	}
	//void initManager(const LevelData& levelData);
	//void updateTiles(const LevelData& levelData);
	//void updateSprites(const LevelData& levelData);
	/*void reinitialize(const std::unique_ptr<LevelData>& levelData);*/

	void render(const Camera& camera) const;
}; 