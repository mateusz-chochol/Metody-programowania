#include "StackImplementations.h"
#include <iostream>
#include <stack>

class StackImplementation
{
protected:
	int elementsCount = 0;
	int maxSize = 0;

public:
	StackImplementation(int size) : maxSize(size) { }
	
	virtual void push(int) = 0;
	
	virtual void pop() = 0;
	
	virtual void top() = 0;
	
	virtual int size()
	{
		return elementsCount;
	}

	virtual bool empty() 
	{
		return (elementsCount == 0);
	}
};

class StackOnArray : public StackImplementation
{
private:
	int *numbers;

public:
	StackOnArray(int size) : StackImplementation(size), numbers(new int[maxSize]) { }

	void push(int number)
	{
		if (size() < maxSize)
		{
			std::cout << number << std::endl;
			numbers[elementsCount++] = number;
		}
		else
			std::cout << "Stack overflow" << std::endl;
	}

	void pop()
	{
		if (!empty())
			std::cout << numbers[--elementsCount] << std::endl;
		else
			std::cout << "Stack is empty" << std::endl;
	}

	void top()
	{
		if (!empty())
			std::cout << numbers[elementsCount - 1] << std::endl;
		else
			std::cout << "Stack is empty" << std::endl;
	}
};

class StackOnLinkedList : public StackImplementation
{
private:
	class ListElement 
	{
	public:
		int value;
		ListElement *previous;
	};
	ListElement *head = nullptr;

public:
	StackOnLinkedList(int size) : StackImplementation(size) { }

	void push(int number)
	{
		if (size() < maxSize)
		{
			std::cout << number << std::endl;

			ListElement *newHead = new ListElement;

			if (head == nullptr)
			{
				newHead->value = number;
				newHead->previous = nullptr;
				head = newHead;
				elementsCount++;
			}
			else 
			{
				newHead->value = number;
				newHead->previous = head;
				head = newHead;
				elementsCount++;
			}
		}
		else
			std::cout << "Stack overflow!" << std::endl;
	}

	void pop()
	{
		if (!empty())
		{
			std::cout << head->value << std::endl;

			ListElement *previousHead = head;
			head = head->previous;
			elementsCount--;

			delete(previousHead);
		}
		else
			std::cout << "Stack is empty!" << std::endl;
	}

	void top()
	{
		if (!empty())
			std::cout << head->value << std::endl;
		else
			std::cout << "Stack is empty!" << std::endl;
	}
};

class StackOnSTDSTACK : public StackImplementation
{
private:
	std::stack<int> stack;

public:
	StackOnSTDSTACK(int size) : StackImplementation(size) { }

	void push(int number)
	{
		if (size() < maxSize)
		{
			std::cout << number << std::endl;
			stack.push(number);
		}
		else
			std::cout << "Stack overflow" << std::endl;
	}

	void pop()
	{
		if (!empty())
		{
			std::cout << stack.top() << std::endl;
			stack.pop();
		}
		else
			std::cout << "Stack is empty" << std::endl;
	}

	void top()
	{
		if (!empty())
			std::cout << stack.top() << std::endl;
		else
			std::cout << "Stack is empty" << std::endl;
	}

	int size()
	{
		return stack.size();
	}

	bool empty()
	{
		return stack.empty();
	}
};

void stackDemo(int *numbers, StackImplementationType stackType)
{
	StackImplementation *stack;

	if (stackType == ARRAY)
	{
		std::cout << "Stack implementation type: ARRAY\n\n";
		stack = new StackOnArray(numbers[0] - 1);
	}
	else if (stackType == LIST)
	{
		std::cout << "Stack implementation type: LIST\n\n";
		stack = new StackOnLinkedList(numbers[0] - 1);
	}
	else
	{
		std::cout << "Stack implementation type: STACK\n\n";
		stack = new StackOnSTDSTACK(numbers[0] - 1);
	}

	for (int i = 1; i < numbers[0]; i++)
	{
		std::cout << "Push: ";
		stack->push(numbers[i]);
	}

	stack->push(0);

	std::cout << "\nEmpty: " << stack->empty() << "\n\n";

	while (stack->size() != 0)
	{
		std::cout << "Pop: ";
		stack->pop();
	}

	std::cout << "\nPop: ";
	stack->pop();
	std::cout << "Empty: " << stack->empty() << "\n\n";

	for (int i = 1; i < numbers[0] / 2; i++)
	{
		std::cout << "Push: ";
		stack->push(numbers[i]);
	}

	std::cout << "\nSize: " << stack->size() << "\n\n";

	for (int i = 1; i < stack->size(); i++)
	{
		std::cout << "Top: ";
		stack->top();
	}

	delete(stack);
}