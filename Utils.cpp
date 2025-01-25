#include "stdafx.h"

#include "Utils.h"

namespace Utils {
	float simplifyAngle(float angle) {
		angle = std::fmod(angle, Utils::TWO_PI);
		if (angle > Utils::_PI) {
			angle -= Utils::TWO_PI;
		}
		else if (angle < -Utils::_PI) {
			angle += Utils::TWO_PI;
		}
		return angle;
	}
}
