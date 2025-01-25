#include "stdafx.h"
#include "Camera.h"

void Camera::move(Vector2 destination, float mapWidth, float mapHeight) {
    position.x = Utils::clampF(position.x + destination.x, APP_VIRTUAL_WIDTH / 2.f, mapWidth - (APP_VIRTUAL_WIDTH / 2.f));
    position.y = Utils::clampF(position.y + destination.y, APP_VIRTUAL_HEIGHT / 2.f, mapHeight - (APP_VIRTUAL_HEIGHT / 2.f));
}

void Camera::setPosition(Vector2 newPos, float mapWidth, float mapHeight)
{
    position.x = Utils::clampF(newPos.x, APP_VIRTUAL_WIDTH / 2.f, mapWidth - APP_VIRTUAL_WIDTH / 2.f);
    position.y = Utils::clampF(newPos.y, APP_VIRTUAL_HEIGHT / 2.f, mapHeight - APP_VIRTUAL_HEIGHT / 2.f);
}

bool Camera::isVisible(Vector2 objPos, float objWidth, float objHeight) const {
    // Compute object's bottom-left
    float bottomLeftX = objPos.x - objWidth * 0.5f;
    float bottomLeftY = objPos.y - objHeight * 0.5f;

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;

    // Add a little buffer to the check
    float buffer = 100.0f;

    // Check if the object is within the camera's (center-based) bounds.
    // If any of these conditions is true, it's outside the visible area.
    if (bottomLeftX + objWidth < (position.x - halfW - buffer)) return false; // Left of camera
    if (bottomLeftX > (position.x + halfW + buffer)) return false; // Right of camera
    if (bottomLeftY > (position.y + halfH + buffer)) return false; // Above camera
    if (bottomLeftY + objHeight < (position.y - halfH - buffer)) return false; // Below camera

    return true;
}