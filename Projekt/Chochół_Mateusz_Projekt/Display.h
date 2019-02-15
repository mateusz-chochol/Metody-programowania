#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>

class Display
{
protected:
	virtual void exitProgram(const std::string& message)
	{
		std::cerr << message << std::endl;
		getchar();
		exit(0);
	}

public:
	virtual void drawTriangle(int a1, int a2, int b1, int b2) = 0;

	virtual void drawCircle(int r) = 0;

	virtual void drawParallelogram(int a1, int a2, int b1, int b2) = 0;
};

#endif // !DISPLAY_H