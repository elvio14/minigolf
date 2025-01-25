#pragma once
#include "App/app.h"
#include "fstream"

class PowerBar {
public:
    PowerBar() : buttonCode(0), isPressed(false), elapsedTime(0) {
        powerbar = App::CreateSprite(".\\TestData\\Sprites\\powerbar.png", 1, 1);
        powerbar->SetPosition(APP_VIRTUAL_WIDTH / 2.f, 12.f);
        powersq = App::CreateSprite(".\\TestData\\Sprites\\powersq.png", 1, 1);
        powersq->SetPosition(40.f, 12.f);

        if (!log.is_open()) {
            log.open("logpwr.txt", std::ios::trunc);
        }
    }

    void update(float deltaTime, bool isCurrentlyPressed);
    float getPressDuration();
    bool isReleased() const { return released; }
    void reset();
    void render();
    void shutdown();
private:
    int buttonCode = XINPUT_GAMEPAD_A;
    bool isPressed;
    float elapsedTime;
    bool released = false;
    float maxP = 2000.f;
    CSimpleSprite* powerbar;
    CSimpleSprite* powersq;
    static std::ofstream log;
};