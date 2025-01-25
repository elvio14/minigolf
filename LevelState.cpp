#include "stdafx.h"

#include "LevelState.h"
#include "../glut/include/GL/freeglut_ext.h"

std::ofstream LevelState::log;

void LevelState::handleInput(float deltaTime) {
	float speed = 0.7f;
	if (App::GetController().GetLeftThumbStickX() > 0.5f)//RIGHT
	{
		dirGuide.addRotation(-0.05f);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)//LEFT
	{
		dirGuide.addRotation(0.05f);
	}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	//{
	//	camera.move(Vector2(0.f, speed * deltaTime),mapWid,mapHei);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	//{
	//	camera.move(Vector2(0.f, -speed * deltaTime), mapWid, mapHei);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	//{
	//	camera.move(Vector2(-speed * deltaTime, 0.f), mapWid, mapHei);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	//{
	//	camera.move(Vector2(speed * deltaTime, 0.f), mapWid, mapHei);
	//}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false)) {
		if (!isWon) {
			powerbar.update(deltaTime, true);
		}
		else {
			//ONLY 2 levels for now

			if (curLevel + 1 < 3) {
				loadLevel(curLevel+1);
				isWon = false;
			}
		}
	}
	else {
		powerbar.update(deltaTime, false);
	};
}

void LevelState::handleHitBall(float deltaTime) {
	if (powerbar.isReleased()) {
		float val = powerbar.getPressDuration();
		float rot = dirGuide.getRotation();
		ball.applyForce({ val * std::cos(rot) * deltaTime / ball.getMass(), val * std::sin(rot) * deltaTime / ball.getMass() });
		powerbar.reset();
		dirGuide.reset();
	}
}


void LevelState::update(float deltaTime) {
	TilePhysics::update(ball, activeLevel, deltaTime);
	
	handleInput(deltaTime);
	handleHitBall(deltaTime);
	ball.update(deltaTime, strokes);
	if (abs(ball.getPosition().distance(hole.getPosition()) < 25.f)) {
		isWon = true;
		ball.setIsActive(false);
	}

	dirGuide.setIsActive(!ball.getIsActive());
	dirGuide.setPosition(ball.getPosition());
	dirGuide.update(deltaTime);
	log << "BallPos: " + std::to_string(ball.getPosition().x) + ", " + std::to_string(ball.getPosition().y) + "  ";
	log << "dirGuide Angle: " + std::to_string(dirGuide.getRotation()) + "\n";

	float mapWid = activeLevel.tileWidth * static_cast<float>(activeLevel.mapWidth);
	float mapHei = activeLevel.tileHeight * static_cast<float>(activeLevel.mapHeight);
	camera.setPosition(ball.getPosition(), mapWid, mapHei);
}

void LevelState::render() {
	//SIMULATING NATIVE COORDS TO CENTER CAMERA
	float glFactorX = 1.f / 512.f;
	float glFactorY = 1.f / 384.f;
	float glAddX = -512.f;
	float glAddY = -1.f;
	glPushMatrix();
	glTranslatef(-((camera.getPosition().x + glAddX ) * glFactorX ), -((camera.getPosition().y  * glFactorY) + glAddY ), 0.0f);

	for (auto& row : sprites) {
		for (auto& sprite : row) {
			Vector2 pos;
			sprite->GetPosition(pos.x, pos.y);
			//if (camera.isVisible(pos, sprite->GetWidth(), sprite->GetHeight())) {
				sprite->Draw();
				std::string print = "(" + std::to_string(static_cast<int>(pos.x)) + "," + std::to_string(static_cast<int>(pos.y)) + ")"; //DEBUG
				App::Print(pos.x, pos.y, print.c_str());
			//}
		}
	}

	hole.render();
	
	if (!isWon) {
		ball.render();
		dirGuide.render();
		powerbar.render();
	}

	glPopMatrix();

	//Outside Camera:
	if(isWon){
		std::string won = "You won with " + std::to_string(strokes) + "strokes!";
		App::Print(500.f, 400.f, won.c_str());
		if (curLevel == 1) {
			std::string level = "Hit SPACE to go to level 2";
			App::Print(500.f, 300.f, level.c_str());
		}
		else if(curLevel == 2) {
			std::string level = "Thanks for Playing! hit SPACE to restart level 1 ";
			App::Print(500.f, 300.f, level.c_str());
		}
	}
	miniMap.render();
	powerbar.render();
}

void LevelState::loadLevel(size_t level) {
	activeLevel = JSONHandler::loadLevelFromJSON(level);
	strokes = 1;
	curLevel = level;
	miniMap.initMiniMap(level);
	ball = Ball(activeLevel.ball);
	//ball = Vector2(1536.f, 1792.f); //DEBUG
	hole = Hole(activeLevel.hole);
	dirGuide = DirGuide(activeLevel.ball);
	mapWid = activeLevel.tileWidth * static_cast<float>(activeLevel.mapWidth);
	mapHei = activeLevel.tileHeight * static_cast<float>(activeLevel.mapHeight);
	camera.setPosition(activeLevel.ball, mapWid, mapHei);

	//camera.setPosition({ 640.f, 640.f }); //DEBUG

	std::ofstream log;
	log.open("loglevel.txt");
	log << "RUNNING\n";
	log << " activeLevel:\n";
	log << "mw: " + std::to_string(activeLevel.mapWidth) + ", ";
	log << "mh: " + std::to_string(activeLevel.mapHeight) + ", ";
	log << "tw: " + std::to_string(activeLevel.tileWidth) + ", ";
	log << "th: " + std::to_string(activeLevel.tileHeight) + ", ";
	
	//Populate Sprites
	for (size_t i = 0; i < activeLevel.map.size(); i++) {
		for (size_t j = 0; j < activeLevel.map[i].size(); j++) {
			log << "i: " + std::to_string(i) + " j:" + std::to_string(j) + "\n";
			TileType tt = activeLevel.map[i][j];
			log << "tt: " + std::to_string(static_cast<int>(tt)) + "\n";
			std::string ttString = JSONHandler::getStringFromTileType(activeLevel.map[i][j]);
			log << "ttString:\n" + ttString;
			std::string path = ".\\TestData\\Sprites\\" + ttString + ".png";
			log << "\npath:\n" + path;
			sprites[i][j] = App::CreateSprite(path.c_str(), 1, 1);
			float x = static_cast<float>(j) * activeLevel.tileWidth + activeLevel.tileWidth / 2.f; //BOTTOM LEFT
			float y = static_cast<float>(i) * activeLevel.tileHeight + activeLevel.tileHeight / 2.f;
			sprites[i][j]->SetPosition(x,y);
			log << "SP: " + std::to_string(x) + ", " + std::to_string(y);
			log << "\n";
		}
	}
	log.close();
}

void LevelState::shutdown() {

	for (auto& row : sprites) {
		for (auto sprite : row) {
			if (sprite) {
				delete sprite;
				sprite = nullptr;
			}
		}
	}
	ball.shutdown();
	dirGuide.shutdown();
	hole.shutdown();
	miniMap.shutdown();
	powerbar.shutdown();

	log.close();
}