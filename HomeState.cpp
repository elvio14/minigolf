#include "stdafx.h"
#include "HomeState.h"
#include "App/app.h"

void HomeState::update(float deltaTime) {
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true)) {
		status = false;
	}
}

void HomeState::render() {
	App::Print(500.f, 500.f, "Welcome!");
	App::Print(500.f, 450.f, "How to play:");
	App::Print(500.f, 430.f, "[SPACE] Hold and release to hit the ball.");
	App::Print(500.f, 410.f, "[A] / [D] Hold to aim.");
	App::Print(500.f, 370.f, "Hit [ENTER] to start!");
}

void HomeState::shutdown() {

}