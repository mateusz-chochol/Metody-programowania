#ifndef NODE_H
#define NODE_H

#include "InputFunctionsLibrary.h"
#include "Object.h"
#include <vector>

class Node
{
	static std::vector<Object> _allObjects;
	static int _maxValue;
	static int _maxWeight;

	int _value = 0;
	int _weight = 0;
	int _bound = 0;
	int _totalWeight = 0;
	int _indexToAdd = 0;
	int _indexToOverflow = 0;

	bool _promising = true;
	Node* _leftChild = nullptr;
	Node* _rightChild = nullptr;

public:
	Node(const std::vector<Object> &allObjects, const int maxWeight)
	{
		_maxValue = 0;
		_maxWeight = maxWeight;
		_allObjects = allObjects;
	}

	Node(const int indexToAdd, const int price, const int weight)
	{
		if (_allObjects.empty() || _maxWeight < 0)
			exitProgram();

		_weight = weight;
		_value = price;
		_indexToAdd = indexToAdd;

		if (weight > _maxWeight)
			_promising = false;
		else
		{
			if (price > _maxValue)
				_maxValue = price;

			_indexToOverflow = getIndexToOverflow();
			_bound = getBound(_indexToOverflow, _indexToAdd);

			if (_bound <= _maxValue)
				_promising = false;
			else
				_indexToAdd++;
		}
	}

	double getBound(const int indexToOverflow, const int indexToAdd)
	{
		auto priceSum = _value;
		_totalWeight = _weight;

		for (auto i = indexToAdd + 1; i < indexToOverflow; i++)
		{
			priceSum += _allObjects.at(i).getPrice();
			_totalWeight += _allObjects.at(i).getWeight();
		}

		if (indexToOverflow < _allObjects.size())
			return priceSum + (_maxWeight - _totalWeight) * _allObjects.at(indexToOverflow).getPriceWeightRatio();

		return priceSum;
	}

	int getIndexToOverflow() const
	{
		auto fictionalWeight = _weight, indexToOverflow = _indexToAdd;

		while (indexToOverflow < _allObjects.size() && fictionalWeight <= _maxWeight)
			fictionalWeight += _allObjects.at(indexToOverflow++).getWeight();

		if (fictionalWeight < _maxWeight)
			indexToOverflow = _allObjects.size();

		return indexToOverflow;
	}

	std::string getNodeData() const
	{
		std::string nodeData;

		nodeData += "Max value: " + std::to_string(_maxValue) + ", max weight: " + std::to_string(_maxWeight);
		nodeData += ", value: " + std::to_string(_value) + ", weight: " + std::to_string(_weight);
		nodeData += ", index to add (i): " + std::to_string(_indexToAdd) + ", index to overflow (k): " + std::to_string(_indexToOverflow);
		nodeData += ", total weight: " + std::to_string(_totalWeight) + ", bound: " + std::to_string(_bound);
		nodeData += ", is promising: " + std::to_string(_promising) + "\n";

		return nodeData;
	}

	void setLeftChild() { _leftChild = new Node(_indexToAdd, _value + _allObjects.at(_indexToAdd).getPrice(), _weight + _allObjects.at(_indexToAdd).getWeight()); }

	Node* getLeftChild() const { return _leftChild; }

	void setRightChild() { _rightChild = new Node(_indexToAdd, _value, _weight); }

	Node* getRightChild() const { return _rightChild; }

	static int getMaxValue() { return _maxValue; }

	bool isPromising() const { return _promising; }
};

#endif // !NODE_H