#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class LevelState;

class JSONHandler
{
public:
	JSONHandler(){}

	static std::string loadJSONFile(const std::string& filePath);
	static std::vector<TileType> parseInnerArray(const std::string& jsonData);
	static std::vector<std::vector<TileType>> parseOuterArray(const std::string& jsonString);
	static LevelData loadLevelFromJSON(size_t levelNumber);
    static TileType parseToTileType(const std::string& str);
    static std::string getStringFromTileType(TileType tt);

    static std::unordered_map<std::string, TileType> lookup;
};
