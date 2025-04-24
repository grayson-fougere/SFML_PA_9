#pragma once

class Mathf {
public:
	static float clamp(float n, const float& min, const float& max) {
		if (n < min) n = min;
		else if (n > max) n = max;
		return n;
	}
};