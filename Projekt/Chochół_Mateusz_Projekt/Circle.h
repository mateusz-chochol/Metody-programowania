#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape
{
	int _radius;

public:
	Circle(Display* w, const int r) : Shape(w), _radius(r) { }

	void draw() override
	{
		_display->drawCircle(_radius);
	}
};

#endif // !CIRCLE_H