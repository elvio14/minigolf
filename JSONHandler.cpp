#include "stdafx.h"
#include "JSONHandler.h"
#include <stdexcept>
#include <vector>

std::unordered_map<std::string, TileType> JSONHandler::lookup = {
    { "NPT",                 TileType::NPT },
    { "Wall_L_T_Left",   TileType::Wall_L_T_Left },
    { "Wall_L_T_Top",    TileType::Wall_L_T_Top },
    { "Wall_L_T_Right",    TileType::Wall_L_T_Right },
    { "Wall_L_T_Bottom",    TileType::Wall_L_T_Bottom },

    { "Wall_L_LeftRight",    TileType::Wall_L_LeftRight },
    { "Wall_L_TopBottom",    TileType::Wall_L_TopBottom },

    { "Wall_L_LeftTop",    TileType::Wall_L_LeftTop },
    { "Wall_L_LeftBottom",    TileType::Wall_L_LeftBottom },
    { "Wall_L_RightTop",    TileType::Wall_L_RightTop },
    { "Wall_L_RightBottom",    TileType::Wall_L_RightBottom },

    { "Wall_L_LeftOnly",    TileType::Wall_L_LeftOnly },
    { "Wall_L_TopOnly",    TileType::Wall_L_TopOnly },
    { "Wall_L_RightOnly",    TileType::Wall_L_RightOnly },
    { "Wall_L_BottomOnly",    TileType::Wall_L_BottomOnly },

    { "No_Wall",    TileType::No_Wall },

    { "Wall_D_BottomToRight",    TileType::Wall_D_BottomToRight },
    { "Wall_D_BottomToLeft",    TileType::Wall_D_BottomToLeft },
    { "Wall_D_TopToRight",    TileType::Wall_D_TopToRight },
    { "Wall_D_TopToLeft",    TileType::Wall_D_TopToLeft },

    { "Wall_S_TopHorizontal",    TileType::Wall_S_TopHorizontal },
    { "Wall_S_TopVertical",    TileType::Wall_S_TopVertical }
};


std::string JSONHandler::loadJSONFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file.");
	}

	return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

TileType JSONHandler::parseToTileType(const std::string& str) {

    auto it = JSONHandler::lookup.find(str);
    if (it != JSONHandler::lookup.end()) {
        return it->second;  // Return the corresponding enum
    }

    // Handle unknown strings
    throw std::runtime_error("Unrecognized tile type: " + str);
}

std::string JSONHandler::getStringFromTileType(TileType tt) {
    for (const auto& pair : JSONHandler::lookup) {
        if (pair.second == tt) {
            return pair.first;
        }
    }
    return "";
}

std::vector<TileType> JSONHandler::parseInnerArray(const std::string& jsonString) {
    std::vector<TileType> tileTypes;

    std::ofstream log;
    log.open("loginner.txt");
 
    //Find opening bracket '['
    size_t arrayStart = jsonString.find('[');
    if (arrayStart == std::string::npos) {
        throw std::runtime_error("Invalid JSON: no opening [.");
    }

    //Find closing bracket ']'
    size_t arrayEnd = jsonString.rfind(']');
    if (arrayEnd == std::string::npos || arrayEnd < arrayStart) {
        throw std::runtime_error("Invalid JSON: no closing ].");
    }

    size_t pos = arrayStart;
    while (true) {
        // Find the next opening quote
        size_t firstQuote = jsonString.find('"', pos);
        if (firstQuote == std::string::npos || firstQuote > arrayEnd) {
            break; // No more strings in the array
        }

        // Find the closing quote
        size_t secondQuote = jsonString.find('"', firstQuote + 1);
        if (secondQuote == std::string::npos || secondQuote > arrayEnd) {
            // No closing quote found
            break;
        }

        // Extract the substring
        std::string tileTypeValue = jsonString.substr(
            firstQuote + 1,
            secondQuote - (firstQuote + 1)
        );
        
        log << tileTypeValue + "\n";
        tileTypes.push_back(JSONHandler::parseToTileType(tileTypeValue));

        // Move past this closing quote to search for the next string
        pos = secondQuote + 1;
    }
    for (TileType tt : tileTypes) {
        log << "tt: " +  std::to_string(static_cast<int>(tt)) + "\n";
    }
    log.close();
    return tileTypes;
}

std::vector<std::vector<TileType>> JSONHandler::parseOuterArray(const std::string& jsonString) {
    std::vector<std::vector<TileType>> allRows;
    std::ofstream log;
    log.open("log.txt");
    log << jsonString;
    
    std::string lastSubStr;
    size_t mapPos = jsonString.find("\"map\"");
    if (mapPos == std::string::npos) {
        log << "No map";
        throw std::runtime_error("Invalid JSON: no map.");
    }
    size_t outerArrayStart = jsonString.find("[", mapPos);
    if (outerArrayStart == std::string::npos) {
        log << "No opening [";
        throw std::runtime_error("Invalid JSON: no opening [.");
    }

    size_t pos = outerArrayStart + 1;
    while (true) {
        // Skip whitespace
        while (pos < jsonString.size() && std::isspace(static_cast<unsigned char>(jsonString[pos]))) {
            pos++;
        }

        if (pos >= jsonString.size() || jsonString[pos] == ']') {
            break;
        }

        // Find the next sub-array
        if (jsonString[pos] != '[') {
            break;
        }

        size_t subStart = pos;
        int bracketLevel = 0;
        for (; pos < jsonString.size(); ++pos) {
            if (jsonString[pos] == '[') bracketLevel++;
            else if (jsonString[pos] == ']') {
                bracketLevel--;
                if (bracketLevel == 0) {
                    // Found the matching ']'
                    size_t subEnd = pos;
                    std::string subStr = jsonString.substr(subStart, (subEnd - subStart + 1));
                    std::vector<TileType> vec = parseInnerArray(subStr);
                    allRows.push_back(std::move(vec));
                    pos++; // move past this ']'
                    break;
                }
            }
        }

        // After finishing the subarray, we should skip optional commas
        while (pos < jsonString.size() &&
            (std::isspace((unsigned char)jsonString[pos]) || jsonString[pos] == ',')) {
            pos++;
        }
    }
    log << "LAST SUBSTRING: \n";
    log << lastSubStr;

    log.close();

    return allRows;
}

LevelData JSONHandler::loadLevelFromJSON(size_t levelNumber) {
    std::ofstream log;
    log.open("logload.txt");

	LevelData level;
	//Get file path according to level number
	std::string path = ".\\TestData\\Levels\\Level_" + std::to_string(levelNumber) + ".json";
	std::string jsonString = JSONHandler::loadJSONFile(path);

    std::cout << jsonString;

	//Parse the jsonString to LevelData
	size_t widthPos = jsonString.find("\"mapWidth\"");

	level.mapWidth = std::stoi(jsonString.substr(jsonString.find(":", widthPos) + 1));

	size_t heightPos = jsonString.find("\"mapHeight\"");
	level.mapHeight = std::stoi(jsonString.substr(jsonString.find(":", heightPos) + 1));

    size_t tileWPos = jsonString.find("\"tileWidth\"");
    level.tileWidth = std::stof(jsonString.substr(jsonString.find(":", tileWPos) + 1));

    size_t tileHPos = jsonString.find("\"tileHeight\"");
    level.tileHeight = std::stof(jsonString.substr(jsonString.find(":", tileHPos) + 1));

    size_t bxPos = jsonString.find("\"ballX\"");
    float ballX = std::stof(jsonString.substr(jsonString.find(":", bxPos) + 1));

    size_t byPos = jsonString.find("\"ballY\"");
    float ballY = std::stof(jsonString.substr(jsonString.find(":", byPos) + 1));

    size_t hxPos = jsonString.find("\"holeX\"");
    float holeX = std::stof(jsonString.substr(jsonString.find(":", hxPos) + 1));

    size_t hyPos = jsonString.find("\"holeY\"");
    float holeY = std::stof(jsonString.substr(jsonString.find(":", hyPos) + 1));

    level.ball = Vector2(ballX, ballY);
    level.hole = Vector2(holeX, holeY);
    //level.map.resize(level.mapWidth);
    std::vector<std::vector<TileType>> mapVector = parseOuterArray(jsonString);

    for (size_t i = 0; i < mapVector.size(); i++) {
        for (size_t j = 0; j < mapVector[i].size(); j++) {
            level.map[i][j] = mapVector[i][j];
        }
    }


    log << jsonString;
    log << "\nWIDTH: " + std::to_string(level.mapWidth);
    log << "\nHeight: " + std::to_string(level.mapHeight);
    log << "\ntileW: " + std::to_string(level.tileWidth);
    log << "\ntileH: " + std::to_string(level.tileHeight);
    log.close();

	return level;
}