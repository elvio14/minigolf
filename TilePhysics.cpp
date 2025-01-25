#include "stdafx.h"

#include "TilePhysics.h"

float TilePhysics::loss = 3.f;

float TilePhysics::buffer = 0.f;

float TilePhysics::quarterPI = 1.57079632675f;

float TilePhysics::damping = 23.f;

void TilePhysics::handleLeftWall(PhysicsData pd){
	if (pd.relPos.x <= pd.radius) {
		pd.ball.addPosX(pd.radius);
		pd.ball.setVel(Vector2(-pd.ball.getVel().x, pd.ball.getVel().y));
		//pd.ball.setFriction(damping);
	}
}
void TilePhysics::handleTopWall(PhysicsData pd) {
	if (pd.tileHeight - pd.relPos.y <= pd.radius) {
		pd.ball.addPosY(-pd.radius);
		pd.ball.setVel(Vector2(pd.ball.getVel().x, -pd.ball.getVel().y));
		//pd.ball.setFriction(damping); 
	}
}

void TilePhysics::handleRightWall(PhysicsData pd) {
	if (pd.tileWidth - pd.relPos.x <= pd.radius) {
		pd.ball.addPosX(-pd.radius);
		pd.ball.setVel(Vector2(-pd.ball.getVel().x, pd.ball.getVel().y));
		//pd.ball.setFriction(damping);
	}

}

void TilePhysics::handleBottomWall(PhysicsData pd) {
	if (pd.relPos.y <= pd.radius) {
		pd.ball.addPosY(pd.radius);
		pd.ball.setVel(Vector2(pd.ball.getVel().x, -pd.ball.getVel().y));
		//pd.ball.setFriction(damping);
	}
}


TileAddress TilePhysics::getTileAddressFromPos(Vector2 pos, const LevelData& data) {
	int x = static_cast<int>(pos.x / data.tileWidth);
	int y = static_cast<int>(pos.y / data.tileHeight);

	return TileAddress(x, y);
}

TileType TilePhysics::getTileTypeFromAddress(TileAddress address, const LevelData& data) {
	return data.map[address.y][address.x];
}

Vector2 TilePhysics::getRelativeBallPos(Vector2 pos, TileAddress ad, const LevelData& data) {
	float x = pos.x - static_cast<float>(ad.x * data.tileWidth);
	float y = pos.y - static_cast<float>(ad.y * data.tileHeight);

	return Vector2(x, y);
}

Vector2 TilePhysics::getNormalizedWallNormal(Vector2 p1, Vector2 p2, bool leftSide) { //p1, p2: End Points of Diagonal Wall
	Vector2 wall = p2 - p1;
	Vector2 wallNormal;
	if(leftSide){
		wallNormal= Vector2(wall.y, -wall.x);
	}
	else {
		wallNormal = Vector2(-wall.y, wall.x);
	}
	return wallNormal.normalize();
}

void TilePhysics::handleDiagonal(PhysicsData pd, float rotation) {
	std::ofstream log;
	log.open("logTP.txt");
	//Rotate vector and diagonal wall to simulate a horizontal wall, reflect y velocity, and then rotate it back
	float mag = pd.ball.getVel().magnitude();											
	float angle = atan2(pd.ball.getVel().y, pd.ball.getVel().x);							
	float virtualAngle = angle - rotation;										
	Vector2 virtualVel = { mag * cos(virtualAngle), mag * sin(virtualAngle) };	

	float newAngle = atan2(-virtualVel.y, virtualVel.x);						
	Vector2 newVel = { mag * cos(newAngle), mag * sin(newAngle) };				

	pd.ball.setVel(newVel);
	//pd.ball.setFriction(damping);

	log << "mag: " + std::to_string(mag) + " | ";
	log << "angle: " + std::to_string(angle) + " | ";
	log << "virtualAngle: " + std::to_string(virtualAngle) + " | ";
	log << "vel before: " + std::to_string(pd.ball.getVel().x) + "," + std::to_string(pd.ball.getVel().y) + " | ";
	log << "newAngle: " + std::to_string(newAngle) + " | ";
	log << "newVel: " + std::to_string(newVel.x) + "," + std::to_string(newVel.y) + "\n";
	log.close();
}


//-----------------------------------------------------------------------------------------------------------------------
void TilePhysics::handleNPT(PhysicsData pd) {

};
void TilePhysics::handleThreeWalls(PhysicsData pd) {
	if (pd.tt == TileType::Wall_L_T_Left) {
		handleLeftWall(pd);
		handleTopWall(pd);
		handleBottomWall(pd);
	}
};
void TilePhysics::handleTwoWalls(PhysicsData pd) {
	if (pd.tt == TileType::Wall_L_LeftRight) {
		handleLeftWall(pd);
		handleRightWall(pd);
	}
	if (pd.tt == TileType::Wall_L_TopBottom) {
		handleTopWall(pd);
		handleBottomWall(pd);
	}
	if (pd.tt == TileType::Wall_L_LeftTop) {
		handleLeftWall(pd);
		handleTopWall(pd);
	}
	if (pd.tt == TileType::Wall_L_LeftBottom) {
		handleLeftWall(pd);
		handleBottomWall(pd);
	}
	if (pd.tt == TileType::Wall_L_RightTop) {
		handleRightWall(pd);
		handleTopWall(pd);
	}
	if (pd.tt == TileType::Wall_L_RightBottom) {
		handleRightWall(pd);
		handleBottomWall(pd);
	}
};
void TilePhysics::handleOneWall(PhysicsData pd) {

	if (pd.tt == TileType::Wall_L_LeftOnly) {
		handleLeftWall(pd);
	}

	if (pd.tt == TileType::Wall_L_TopOnly) {
		handleTopWall(pd);
	}

	if (pd.tt == TileType::Wall_L_RightOnly) {
		handleRightWall(pd);
	}

	if (pd.tt == TileType::Wall_L_BottomOnly) {
		handleBottomWall(pd);
	}
};
void TilePhysics::handleNoWalls(PhysicsData pd) {

};

void TilePhysics::handleDiagonalWall(PhysicsData pd) {

	if (pd.tt == TileType::Wall_D_TopToLeft) {
		if (pd.relPos.x + buffer > pd.relPos.y) {
			pd.ball.addPosition({ -pd.radius, pd.radius });
			handleDiagonal(pd, quarterPI);
		}
	}
	if (pd.tt == TileType::Wall_D_BottomToRight) {
		if (pd.relPos.x < pd.relPos.y) {
			pd.ball.addPosition({ pd.radius, -pd.radius });
			handleDiagonal(pd, quarterPI);
		}
	}

	if (pd.tt == TileType::Wall_D_TopToRight) {
		float check = (pd.tileHeight * pd.relPos.x / pd.tileWidth) + pd.relPos.y - pd.tileHeight;
		if (check < 0.f) {
			pd.ball.addPosition({ pd.radius, pd.radius });
			handleDiagonal(pd, -quarterPI);
		}
	}
		
		
	if(pd.tt == TileType::Wall_D_BottomToLeft) {
		float check = (pd.tileHeight * pd.relPos.x / pd.tileWidth) + pd.relPos.y - pd.tileHeight;
		if (check > 0.f) {
			pd.ball.addPosition({ -pd.radius, -pd.radius });
			handleDiagonal(pd,-quarterPI);
		}
	}

};
void TilePhysics::handleStackedWalls(PhysicsData pd) {

	if (abs(pd.ball.getVel().y) > abs(pd.ball.getVel().x)) {
		handleLeftWall(pd);
		handleRightWall(pd);
		if (pd.tt == TileType::Wall_S_TopHorizontal) {
			pd.ball.setRender(false);
		}
	}
	else {
		handleTopWall(pd);
		handleBottomWall(pd);
		if (pd.tt == TileType::Wall_S_TopVertical) {
			pd.ball.setRender(false);
		}
	}

};
//------------------------------------------------------------------------------------------------------------------------

void TilePhysics::update(Ball& ball, const LevelData& data, float deltaTime) {
	TileAddress ad = getTileAddressFromPos(ball.getPosition(), data);
	TileType tt = getTileTypeFromAddress(ad, data);

	Vector2 relPos = getRelativeBallPos(ball.getPosition(), ad, data);
	Vector2 ballVel = ball.getVel();
	float radius = ball.getRadius();
	PhysicsData pd = PhysicsData(ball, tt, ad, data.tileWidth, data.tileHeight, relPos, ballVel, radius, deltaTime);

	

	int value = static_cast<int>(tt);

	if (value == 0) {
		handleNPT(pd);
		ball.setNPTError(true);
		ball.setPosition(data.ball);
		ball.setVel({ 0.f,0.f });
	}
	else if (value > 0 && value <= 4) {
		handleThreeWalls(pd);
	}
	else if (value <= 10) {
		handleTwoWalls(pd);
	}
	else if (value <= 14) {
		handleOneWall(pd);
	}
	else if (value == 15) {
		handleNoWalls(pd);
	}
	else if (value <= 19) {
		handleDiagonalWall(pd);
	}
	else {
		handleStackedWalls(pd);
	}

	Vector2 pos = ball.getPosition();
	if (pos.x + buffer > data.tileWidth * static_cast<float>(data.mapWidth) ||
		pos.y + buffer > data.tileHeight * static_cast<float>(data.mapHeight) ||
		pos.x - buffer < 0.f ||
		pos.y - buffer < 0.f
		) {
		ball.setIsActive(false);
		ball.setNPTError(true);
		ball.setPosition(data.ball);
		ball.setVel({ 0.f,0.f });
	}
}