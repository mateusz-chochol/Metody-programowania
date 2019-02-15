#include "Shape.h"
#include "Display.h"
#include "TextDisplay.h"
#include "GraphicalDisplay.h"
#include "Triangle.h"
#include "Parallelogram.h"
#include "Circle.h"
#include "ComplexShape.h"

int main()
{
	Display* w1 = new GraphicalDisplay();
	Display* w2 = new TextDisplay();
	Shape* o1 = new Triangle(w1, 3, 2, 2, -2);
	Shape* o2 = new Parallelogram(w1, 3, 2, 2, -2);
	Shape* o3 = new Circle(w1, 5);
	ComplexShape* o4 = new ComplexShape(w1);
	o4->add(o1);
	o4->add(o2);
	o4->add(o3);
	o4->draw();
	o1->draw();
	o2->draw();
	o3->draw();

	o1->changeDisplay(w2);
	o2->changeDisplay(w2);
	o3->changeDisplay(w2);
	o4->changeDisplay(w2);
	o4->draw();
	o1->draw();
	o2->draw();
	o3->draw();

	delete o1;
	delete o2;
	delete o3;
	delete o4;
	delete w2;
	delete w1;

	getchar();
	return 0;
}