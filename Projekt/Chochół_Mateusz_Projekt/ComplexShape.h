#ifndef COMPLEXSHAPE_H
#define COMPLEXSHAPE_H

#include "Shape.h"
#include <queue>

class ComplexShape : public Shape
{
	std::queue<Shape*> _shapesCollection;

public:
	explicit ComplexShape(Display* w) : Shape(w) { }

	void draw() override
	{
		while (!_shapesCollection.empty())
		{
			_shapesCollection.front()->draw();
			_shapesCollection.pop();
		}
	}

	bool add(Shape* o)
	{
		if (_shapesCollection.size() > 4)
			return false;

		_shapesCollection.push(o);
		return true;
	}
};

#endif // !COMPLEXSHAPE_H