#ifndef OPERATORCLASS_H
#define OPERATORCLASS_H

#include <map>

enum OperartorConnectivity
{
	LeftSided,
	RightSided
};

enum OperatorType
{
	Assign,
	Relate,
	Addition,
	Multiplication,
	Exponentiation,
	Unary
};

class Operator
{
	char _representation;
	int _priority;
	OperartorConnectivity _connectivity;
	OperatorType _type;

public:
	Operator() : _representation('!'), _priority(10), _connectivity(RightSided), _type(Unary) { }

	Operator(const char representation, const int priority, const OperartorConnectivity connectivity, const OperatorType type)
		: _representation(representation), _priority(priority), _connectivity(connectivity), _type(type) { }

	char getRepresentation() const
	{
		return _representation;
	}

	int getPriority() const
	{
		return _priority;
	}

	OperartorConnectivity getConnectivity() const
	{
		return _connectivity;
	}

	OperatorType getType() const
	{
		return _type;
	}

	static std::map<char, Operator> createCommonOperators()
	{
		std::map<char, Operator> operators;

		operators[')'] = Operator(')', -1, RightSided, Unary);
		operators['('] = Operator('(', -1, RightSided, Unary);
		operators['='] = Operator('=', 0, RightSided, Assign);
		operators['<'] = Operator('<', 1, LeftSided, Relate);
		operators['>'] = Operator('>', 1, LeftSided, Relate);
		operators['+'] = Operator('+', 2, LeftSided, Addition);
		operators['-'] = Operator('-', 2, LeftSided, Addition);
		operators['*'] = Operator('*', 3, LeftSided, Assign);
		operators['/'] = Operator('/', 3, LeftSided, Multiplication);
		operators['%'] = Operator('%', 3, LeftSided, Multiplication);
		operators['^'] = Operator('^', 4, RightSided, Exponentiation);
		operators['~'] = Operator('~', 5, RightSided, Unary);

		return operators;
	}
};

#endif // !OPERATORCLASS_H