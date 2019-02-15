#include "OnpFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"

#pragma region INF do ONP

/*
* Funkcja tworzy stos, nastepnie pobiera liste dostepnych operatorow (w postaci mapy: key = char, value = Operator) wraz z ich parametrami.
* Zlicza tez liczbe otwartych nawiasow by pod koniec wiedziec, czy wszystkie zostaly zamkniete.
* Nastepnie, w petli: jesli to liczba - od razu wyrzuca na wyjscie (przy okazji sprawdzane jest, czy czasem dwoch z rzedu nie bylo - jesli tak: error).
* Jesli to nie liczba to sprawdza czy operator: jesli tak, to zgodnie z zasadami ONP dodaje na stos (przy okazji wyrzucajac inne jesli to konieczne).
* Jesli nie, to sprawdza czy to przecinek lub spacja: jesli tak, to je ignoruje.
* Jesli nie to wyrzuca dla tego przypadku blad.
* Na koniec wypluwa na wyjsciu wszystko co zostalo jeszcze na stosie.
*/
void infixToPostfix(std::string& line, const std::map<char, Operator>& operators)
{
	std::stack<Operator> stack;
	const auto expression = line.substr(5);
	line = "ONP: ";

	auto openedBrackets = 0;
	auto wasPreviousCharacterAnOperand = false;

	for (auto character : expression)
	{
		if (isCharacterOperand(character))
		{
			if (wasPreviousCharacterAnOperand)
			{
				line = "ONP: error";
				return;
			}

			line += character;
			wasPreviousCharacterAnOperand = true;
		}
		else if (isCharacterOperator(character))
		{
			if (!wasPreviousCharacterAnOperand && operators.at(character).getType() != Unary)
			{
				line = "ONP: error";
				return;
			}

			if (character != ')')
			{
				if (character == '(')
					openedBrackets++;

				while (!canOperatorBePushed(stack, operators, character))
				{
					line += stack.top().getRepresentation();
					stack.pop();
				}

				stack.push(operators.at(character));
			}
			else
			{
				if (openedBrackets == 0)
				{
					line = "ONP: error";
					return;
				}

				openedBrackets--;

				while (stack.top().getRepresentation() != '(')
				{
					line += stack.top().getRepresentation();
					stack.pop();
				}

				stack.pop();
			}

			wasPreviousCharacterAnOperand = false;
		}
		else if (character != ' ' && character != ',')
		{
			line = "ONP: error";
			return;
		}
	}

	if (openedBrackets != 0)
	{
		line = "ONP: error";
		return;
	}

	while (!stack.empty())
	{
		line += stack.top().getRepresentation();
		stack.pop();
	}
}

bool canOperatorBePushed(const std::stack<Operator>& stack, const std::map<char, Operator>& operators, const char character)
{
	if (character == '(')
		return true;

	return (stack.empty() || (stack.top().getPriority() < operators.at(character).getPriority()) ||
		(stack.top().getPriority() == operators.at(character).getPriority() && stack.top().getConnectivity() == RightSided));
}

#pragma endregion 

#pragma region ONP do INF

/*
* Funkcja tlumaczaczac z ONP do INF jednoczesnie podlicza liczbe operatorow (innych niz ~) i na jej podstawie wysuwa potem wniosek
* czy dzialanie jest wykonalne.
* Calosc ogolnie dziala na stosie w mniej wiecej takiej samej formie w jakiej czlowiek robilby to w pamieci
* Najpierw zbiera zmienne na ktorych bedzie pracowal a potem stosuje na nich okreslone dzialanie
* A to czy wstawic nawiasy czy nie, okresla na podstawie priorytetu poprzedniego znaku z dzialania
*/
void postfixToInfix(std::string& line, const std::map<char, Operator>& operators)
{
	std::stack<std::string> stack;
	auto expression = line.substr(5);
	line = "INF: ";

	auto operandsCount = 0, operatorsCount = 0, priorityLevelOfPreviousOperator = 10;

	for (auto character : expression)
	{
		if (isCharacterOperand(character))
		{
			operandsCount++;
			stack.push(std::string(1, character));

			priorityLevelOfPreviousOperator = 10;
		}
		else if (isCharacterOperator(character))
		{
			if (character == '~')
			{
				std::string stackContent;

				if (stack.top().size() == 1 || stack.top() == "~")
					stackContent = "~" + stack.top();
				else
					stackContent = "~(" + stack.top() + ")";

				stack.pop();
				stack.push(stackContent);
			}
			else
			{
				operatorsCount++;

				if (stack.size() >= 2)
				{
					const auto lastPart = stack.top();
					stack.pop();

					const auto rest = stack.top();
					stack.pop();

					if (priorityLevelOfPreviousOperator > operators.at(character).getPriority())
						stack.push(rest + std::string(1, character) + lastPart);
					else
					{
						if (priorityLevelOfPreviousOperator < operators.at(character).getPriority())
							stack.push("(" + rest + ")" + std::string(1, character) + "(" + lastPart + ")");
						else
							stack.push(rest + std::string(1, character) + "(" + lastPart + ")");
					}
				}

				priorityLevelOfPreviousOperator = operators.at(character).getPriority();
			}
		}
		else if (character != ' ' && character != ',')
		{
			line += "error";
			return;
		}
	}

	if (operandsCount - 1 == operatorsCount)
		line += stack.top();
	else
		line += "error";
}

#pragma endregion 