#ifndef NODE_H
#define NODE_H

#include "InputFunctionsLibrary.h"
#include <string>
#include <memory>

class Node
{
	double _frequency = 0;
	std::string _characterRepresentaion;
	std::unique_ptr<Node> _leftChild = nullptr;
	std::unique_ptr<Node> _rightChild = nullptr;

public:
	Node() = default;
	Node(std::string character, const double frequency) : _frequency(frequency), _characterRepresentaion(std::move(character)) { }
	
	void setLeftChild(std::unique_ptr<Node>& leftChild) { _leftChild = std::move(leftChild); }

	std::unique_ptr<Node>& getLeftChild() { return _leftChild; }

	void setRightChild(std::unique_ptr<Node>& rightChild) { _rightChild = std::move(rightChild); }

	std::unique_ptr<Node>& getRightChild() { return _rightChild; }

	void setFrequency()
	{
		if (_leftChild == nullptr || _rightChild == nullptr)
			exitProgram("Node class function \"setFrequency()\" attempted to read from a pointer set to nullptr. \n(Node object children haven't been set)");

		_frequency = _leftChild->getFrequency() + _rightChild->getFrequency();
	}

	double getFrequency() const { return _frequency; }

	std::string getRepresenation() const { return _characterRepresentaion; }
};

#endif // !NODE_H