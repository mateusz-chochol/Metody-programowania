#ifndef OBJECT_H
#define OBJECT_H
#include <string>

class Object
{
	std::string _name;
	int _price;
	int _mass;
	double _priceMassRatio;

public:
	Object(std::string name, const int price, const int mass)
		: _name(std::move(name)), _price(price), _mass(mass), _priceMassRatio(double(price) / mass) { }

	std::string getName() const
	{
		return _name;
	}

	int getPrice() const
	{
		return _price;
	}

	int getMass() const
	{
		return _mass;
	}

	double getPriceMassRatio() const
	{
		return _priceMassRatio;
	}
};

#endif // !OBJECT_H