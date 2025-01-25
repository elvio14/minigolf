///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <memory>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Ball.h"
#include "GameStateManager.h"
#include "LevelState.h"
#include "HomeState.h"
#include "fstream"


std::unique_ptr<GameStateManager> stateManager;
void Init()
{
	//auto initialLevel = std::make_unique<LevelState>();
	auto initialLevel = std::make_unique<HomeState>();
	stateManager = std::make_unique<GameStateManager>(std::move(initialLevel));
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	stateManager->update(deltaTime);
	if (dynamic_cast<HomeState*>(stateManager->getCurrentState())) {
		if (!stateManager->getCurrentState()->getStatus()) {
			stateManager->pushState(std::make_unique<LevelState>());
		}
	}
}

void Render()
{	
	stateManager->render();

	//Center helper
	//App::DrawLine(0.f, APP_VIRTUAL_HEIGHT / 2.f, APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT / 2.f);
	//App::DrawLine(APP_VIRTUAL_WIDTH / 2.f, 0.f, APP_VIRTUAL_WIDTH / 2.f, APP_VIRTUAL_HEIGHT);
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	stateManager->shutdown();
}