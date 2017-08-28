#ifndef _RGB_H_
#define _RGB_H_

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>

class RGB {
public:
	double r, g, b;
	RGB(double r, double g, double b) : r(r), g(g), b(b) {
	}
	int normal(double x) const {
		return std::min((int)(x * 255), 255);
	}
	RGB() {}
	int to_color() const {
		//std::cout << normal(r) << " " << normal(g) << " " << normal(b) << std::endl;
		return (normal(r) << 16) | (normal(g) << 8) | (normal(b));
	}

	inline RGB friend operator *(const RGB& a, const RGB& b) {
		return RGB(a.r * b.r, a.g * b.g, a.b * b.b);
	}

	inline RGB friend operator *(const RGB& a, double s) {
		return RGB(a.r * s, a.g * s, a.b * s);
	}

	inline RGB friend operator *(double s, const RGB& a) {
		return RGB(a.r * s, a.g * s, a.b * s);
	}

	inline void operator +=(const RGB& o) {
		r += o.r;
		g += o.g;
		b += o.b;
	}
};

#endif
