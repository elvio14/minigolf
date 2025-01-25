#include "stdafx.h"
#include "PowerBar.h"
#include <iostream>
#include <cmath>

std::ofstream PowerBar::log;
float PowerBar::getPressDuration() {
    return elapsedTime;
}

void PowerBar::update(float deltaTime, bool isCurrentlyPressed){    
    // Handle press event
    if (isCurrentlyPressed) {
        if (!isPressed) {
            isPressed = true;
        }
        elapsedTime = (((elapsedTime + deltaTime) < (maxP)) ? (elapsedTime + deltaTime) : (maxP)); 
    }
    
    // Handle release event
    if (!isCurrentlyPressed && isPressed) {
        isPressed = false;
        released = true;
    }

    log << "elapsedTime: " + std::to_string(elapsedTime) + "\n";
}

void PowerBar::render() {
    powerbar->Draw();
    float pressLevel = elapsedTime / maxP;
    int sqCount = 60 - static_cast<int>(pressLevel * 60.f);
    
    float xOffset = 0.f;
    for (int i = 0; i < sqCount; i++) {
        powersq->SetPosition(40.f + static_cast<float>(i) * 16.f, 12.f);
        powersq->Draw();
    }

    log << ", pressLevel: " + std::to_string(pressLevel);
}

void PowerBar::reset() {
    isPressed = false;
    released = false;
    elapsedTime = 0.f;
}

void PowerBar::shutdown() {
    if (powerbar) {
        delete powerbar;
        powerbar = nullptr;
    }
    if (powersq) {
        delete powersq;
        powersq = nullptr;
    }

    log.close();
}