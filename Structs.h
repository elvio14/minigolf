#pragma once
#include <cmath>
#include <vector>
class Ball;

struct Vector2 {
	float x;
	float y;

	Vector2(float x = 0, float y = 0) : x(x), y(y){}

	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	} 

	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator*(Vector2 factor) const {
		return Vector2(x * factor.x, y * factor.y);
	}

	Vector2 operator/(float scalar) const {
		if (scalar == 0) {
			return Vector2(0.f, 0.f);
		}

		return Vector2(x / scalar, y / scalar);
	}

	Vector2 normalize() const {
		float length = std::sqrt(x * x + y * y);

		if (length == 0) return Vector2(0.f, 0.f);

		return *this / length;
	}

	float dotProduct(Vector2 other) const {
		return x * other.x + y * other.y;
	}

	float magnitude() const {
		return std::sqrt(x * x + y * y);
	}

	float distance(Vector2 other) const {
		return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}
};
enum class TileType {
	//Non-Playable
	NPT,				//0

	// L: Linear,
	// Three walls:
	Wall_L_T_Left,		//1
	Wall_L_T_Top,		//2
	Wall_L_T_Right,		//3
	Wall_L_T_Bottom,	//4
	//	Two walls:
	//Apart:
	Wall_L_LeftRight,	//5
	Wall_L_TopBottom,	//6
	//Corner:
	Wall_L_LeftTop,		//7
	Wall_L_LeftBottom,	//8
	Wall_L_RightTop,	//9
	Wall_L_RightBottom,	//10
	
	// One wall:
	Wall_L_LeftOnly,	//11
	Wall_L_TopOnly,		//12
	Wall_L_RightOnly,	//13
	Wall_L_BottomOnly,	//14
	// No wall:
	No_Wall,			//15

	// D: diagonal
	Wall_D_BottomToRight,	//16
	Wall_D_BottomToLeft,	//17	
	Wall_D_TopToRight,		//18
	Wall_D_TopToLeft,		//19

	// S: Stacked
	Wall_S_TopHorizontal,	//20
	Wall_S_TopVertical		//21

	// G: Gap, No ground, has minimum velocity to pass through, no friction ?

};


struct LevelData {
	static constexpr size_t LDMax = 15;
	int mapWidth; //Number of tiles
	int mapHeight; //Number of tiles
	float tileWidth;
	float tileHeight;
	//starting positions:
	Vector2 ball;
	Vector2 hole;

	std::array<std::array<TileType, LDMax>, LDMax> map{TileType::NPT};
	
	LevelData() : mapWidth(0), mapHeight(0), tileWidth(0), tileHeight(0), ball(), hole() {};

	LevelData(int width, int height)
		: mapWidth(width), mapHeight(height), tileWidth(0), tileHeight(0), ball(), hole() {
	}
};

struct TileAddress {
	int x;
	int y;

	TileAddress(int x, int y) : x(x), y(y) {}
};

struct PhysicsData {
	Ball& ball;
	TileType tt;
	TileAddress ad;
	float tileWidth;
	float tileHeight;
	Vector2 relPos; //Position of ball relative to the tile
	Vector2 ballVel; //Velocity of ball
	float radius; //Radius of ball
	float deltaTime;

	PhysicsData(Ball& ball, TileType tt, TileAddress ad, float tileWidth, float tileHeight, Vector2 relPos, Vector2 ballVel, float radius, float dt) :
		ball(ball), tt(tt), ad(ad), tileWidth(tileWidth), tileHeight(tileHeight), relPos(relPos), ballVel(ballVel), radius(radius), deltaTime(dt) {}
};
