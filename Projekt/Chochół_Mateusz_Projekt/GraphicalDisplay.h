#ifndef GRAPHICALDISPLAY_H
#define GRAPHICALDISPLAY_H

#include "Display.h"
#include <iostream>

class GraphicalDisplay : public Display
{
	static bool isInsideTriangle(const int p1, const int p2, const int a1, const int a2, const int b1, const int b2)
	{
		const double divider = a1 * b2 - a2 * b1;

		const auto firstEgde = (p1 * b2 - p2 * b1) / divider;
		const auto secondEgde = (p2 * a1 - p1 * a2) / divider;
		const auto thirdEdge = firstEgde + secondEgde;

		return firstEgde >= 0 && secondEgde >= 0 && thirdEdge <= 1;
	}

public:
	void drawTriangle(const int a1, const int a2, const int b1, const int b2) override
	{
		if (a1 < 0 || a2 < 0 || b1 < 0 || b2 > 0)
			exitProgram("Incorrect triangle vectors values.");

		for (auto i = a2; i >= b2; i--) 
		{
			for (auto j = 0; j <= (a1 > b1 ? a1 : b1); j++) 
			{
				if (isInsideTriangle(j, i, a1, a2, b1, b2))
					std::cout << 't';
				else
					std::cout << ' ';
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	void drawCircle(const int r) override
	{
		if (r < 0)
			exitProgram("Circle radius cannot be less than 0.");

		for (auto i = -r; i <= r; i++)
		{
			for (auto j = -r; j <= r; j++)
			{
				if (j * j + i * i <= r * r)
					std::cout << 'c';
				else
					std::cout << ' ';
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	void drawParallelogram(const int a1, const int a2, const int b1, const int b2) override
	{
		if (a1 < 0 || a2 < 0 || b1 < 0 || b2 > 0)
			exitProgram("Incorrect parallelogram vectors values.");

		const auto c1 = a1 + b1, c2 = a2 + b2;

		for (auto i = a2; i >= b2; i--) 
		{
			for (auto j = 0; j <= c1; j++) 
			{
				if (isInsideTriangle(j, i, a1, a2, c1, c2) || isInsideTriangle(j, i, b1, b2, c1, c2))
					std::cout << 'p';
				else
					std::cout << ' ';
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
};

#endif // !GRAPHICALDISPLAY_H