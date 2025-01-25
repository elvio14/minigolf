#include "stdafx.h"
#include "TileManager.h"

//void TileManager::updateSprites(const LevelData& levelData) {
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			std::string ttString = JSONHandler::getStringFromTileType(tiles[i][j]);
//			std::string path = ".\\TestData\\Sprites\\" + ttString + ".png";
//			sprites[i][j] = App::CreateSprite(path.c_str(), 1, 1);
//			float x = static_cast<float>(j) * levelData.tileWidth + levelData.tileWidth / 2.f;
//			float y = static_cast<float>(i) * levelData.tileHeight + levelData.tileHeight / 2.f;
//			sprites[i][j]->SetPosition(x,y);
//		}
//	}
//}

//void TileManager::initManager(const LevelData& levelData) {
//	tiles = levelData.map;
//	updateSprites(levelData);
//}
//
//
//void TileManager::updateTiles(const LevelData& levelData) {
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			tiles[i][j] = levelData.map[i][j];
//		}
//	}
//}

//void TileManager::render(const Camera& camera) const {
//	//for (int i = 0; i < rows; ++i) {
//	//	for (int j = 0; j < cols; ++j) {
//	//		//Vector2 pos;
//	//		//sprites[i][j]->GetPosition(pos.x, pos.y);
//	//		//float wid = sprites[i][j]->GetWidth();
//	//		//float hei = sprites[i][j]->GetHeight();
//	//		//if (camera.isVisible(pos,wid,hei)){
//	//		//	sprites[i][j]->Draw();
//	//		//}
//	//		sprites[i][j]->Draw();
//	//	}
//	//}
//	sprites[0][1]->Draw();
//}

//void TileManager::reinitialize(const std::unique_ptr<LevelData>& levelData) {
//	rows = levelData->mapWidth;
//	cols = levelData->mapHeight;
//	tiles = levelData->map;
//	sprites.clear();
//	for (int i = 0; i < rows; ++i) {
//		for (int j = 0; j < cols; ++j) {
//			std::string ttString = JSONHandler::getStringFromTileType(tiles[i][j]);
//			std::string path = ".\\TestData\\Sprites\\" + ttString + ".png";
//
//			sprites[i][j] = std::unique_ptr<CSimpleSprite>(App::CreateSprite(path.c_str(), 1, 1));
//
//			if (!sprites[i][j]) {
//				throw std::runtime_error("Failed to create sprite for tile: " + ttString);
//			}
//
//			sprites[i][j]->SetPosition(
//				static_cast<float>(j * levelData->tileWidth + levelData->tileWidth / 2.f),
//				static_cast<float>(i * levelData->tileHeight + levelData->tileHeight / 2.f)
//			);
//		}
//	}
//}