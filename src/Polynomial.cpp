#include "raytrace/Polynomial.hpp"
#include <algorithm>
#include <cmath>

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) {
		return false;
	} else if (discr == 0) {
		x0 = x1 = - 0.5 * b / a;
	} else {
		float q = (b > 0) ?
		-0.5 * (b + sqrtf(discr)) :
		-0.5 * (b - sqrtf(discr));
		x0 = q / a;
		x1 = c / q;
	}

	if (x0 > x1) {
		std::swap(x0, x1);
	}		

	return true;
} 