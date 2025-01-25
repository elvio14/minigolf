#include "stdafx.h"
#include "Segment.h"

void Segment::follow(const Vector2& target) {
	Vector2 diff = position - target;

	angle = std::atan2(diff.y, diff.x);

	position = target + (diff.normalize() * length);
}