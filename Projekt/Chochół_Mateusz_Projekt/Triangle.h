#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
	int _a1;
	int _a2;
	int _b1;
	int _b2;

public:
	Triangle(Display* w, const int a1, const int a2, const int b1, const int b2) : Shape(w), _a1(a1), _a2(a2), _b1(b1), _b2(b2) { }

	void draw() override
	{
		_display->drawTriangle(_a1, _a2, _b1, _b2);
	}
};

#endif // !TRIANGLE_H