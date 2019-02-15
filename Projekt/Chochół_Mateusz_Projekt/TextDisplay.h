#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "Display.h"
#include <iostream>

class TextDisplay : public Display
{
public:
	void drawTriangle(const int a1, const int a2, const int b1, const int b2) override
	{
		std::cout << "Drawing a triangle from vectors (" << a1 << ", " << a2 << "), (" << b1 << ", " << b2 << ")" << std::endl;
	}

	void drawCircle(const int r) override
	{
		std::cout << "Drawing a circle with radius " << r << std::endl;
	}

	void drawParallelogram(const int a1, const int a2, const int b1, const int b2) override
	{
		std::cout << "Drawing a parallelogram from vectors (" << a1 << ", " << a2 << "), (" << b1 << ", " << b2 << ")" << std::endl;
	}
};

#endif // !TEXTDISPLAY_H