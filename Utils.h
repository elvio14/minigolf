#pragma once

namespace Utils {
	constexpr float _PI = 3.1415926535f;
	constexpr float TWO_PI = 6.28318530718f;

	float simplifyAngle(float angle);

	static float clampF(float value, float min, float max) {
		return (value < min) ? min : (value > max ? max : value);
	}

	static float distanceSq(Vector2 a, Vector2 b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;

		return dx * dx + dy * dy;
	}
}