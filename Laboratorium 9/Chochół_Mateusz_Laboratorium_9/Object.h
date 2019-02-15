#ifndef OBJECT_H
#define OBJECT_H

class Object
{
	int _price = 0;
	int _weight = 0;
	double _priceWeightRatio = 0;

public:
	Object(const int price, const int weight) 
		: _price(price), _weight(weight), _priceWeightRatio(double(price) / weight) { }

	int getPrice() const { return _price; }

	int getWeight() const { return _weight; }

	double getPriceWeightRatio() const { return _priceWeightRatio; }
};

#endif // !OBJECT_H