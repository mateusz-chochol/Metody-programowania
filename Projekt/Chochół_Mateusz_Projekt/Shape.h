#ifndef SHAPE_H
#define SHAPE_H

#include "Display.h"

class Shape
{
protected:
	Display* _display;

public:
	explicit Shape(Display* w) : _display(w) { }

	virtual void draw() = 0;

	void changeDisplay(Display* newDisplay) { _display = newDisplay; }
};

#endif // !SHAPE_H