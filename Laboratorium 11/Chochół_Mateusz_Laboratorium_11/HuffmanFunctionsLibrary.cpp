#include "HuffmanFunctionLibrary.h"
#include "InputFunctionsLibrary.h"
#include "Node.h"
#include <string>
#include <fstream>
#include <vector>
#include <memory>

/*
 * Starting with a complete huffman tree saves to a given file all binary representations of every character
 */
void huffmanCoding(std::fstream& file, std::unique_ptr<Node>& node, const std::string& binaryRepresentation)
{
	if (!node->getRepresenation().empty())
	{
		file << node->getRepresenation() << ": " << binaryRepresentation << std::endl;

		if (file.bad())
			exitProgram("Function \"huffmanCoding()\" wasn't given a proper file to write to. \n(Isn't opened? Wrong openmode?)\n");
	}
	else
	{
		auto leftChild = std::move(node->getLeftChild()), rightChild = std::move(node->getRightChild());

		if (leftChild == nullptr || rightChild == nullptr)
			exitProgram("Function \"huffmanCoding\" was given an incomplete huffman tree. \n(Either left or right child of not-final node is set to nullptr)");

		huffmanCoding(file, leftChild, binaryRepresentation + "1");
		huffmanCoding(file, rightChild, binaryRepresentation + "0");
	}
}

/*
 * Creates huffman tree (starts with a vector of unique pointers to Nodes which are representing characters and their frequencies)
 */
std::unique_ptr<Node>& createTree(std::vector<std::unique_ptr<Node>>& nodes)
{
	if (nodes.empty())
		exitProgram("Function \"createTree()\" was given an empty vector of unique_ptr<Node>.");

	while (nodes.size() > 1)
	{
		sortByFrequency(nodes, 0, nodes.size() - 1);
		std::reverse(nodes.begin(), nodes.end());

		std::unique_ptr<Node> node(new Node());
		
		node->setLeftChild(nodes.back()); 
		nodes.pop_back();
		
		node->setRightChild(nodes.back()); 
		nodes.pop_back();
		
		node->setFrequency();
		nodes.push_back(std::move(node));
	}

	return nodes.back();
}

/*
 * Gets characters and their frequencies from the file and returns them as a vector of unique pointers to Nodes
 */
std::vector<std::unique_ptr<Node>> getCharactersAsNodes(std::fstream& file)
{
	std::vector<std::unique_ptr<Node>> nodes;

	while (!file.eof())
	{
		std::string representation, frequencyAsString;
		double frequency;

		try
		{
			file >> representation >> frequencyAsString;

			if (file.fail())
				exitProgram("Function \"getCharactersAsNodes()\" was unable to read from a given file. \n(Wrong openmode? File not opened?)");

			frequency = std::stod(frequencyAsString);

			if (frequency <= 0)
				exitProgram("Function \"getCharactersAsNodes()\" read that frequency of " + representation + " is less than 0 (which is impossible).");
		}
		catch(const std::invalid_argument& exception)
		{
			exitProgram(std::string("Function \"getCharactersAsNodes()\" was given a " + representation + 
				" character frequency in incorrect form. \n(Possible other than digits characters in file or none at all?) \nException message: ") + exception.what());
		}

		nodes.push_back(std::make_unique<Node>(representation, frequency));
	}

	return nodes;
}

/*
 * Sorts unique pointers to Nodes vector by their frequencies
 */
void sortByFrequency(std::vector<std::unique_ptr<Node>>& nodes, const int left, const int right)
{
	auto currentLeft = left, currentRight = right;

	try
	{
		const auto currentMiddle = nodes.at((left + right) / 2)->getFrequency();
		
		do
		{
			while (nodes.at(currentLeft)->getFrequency() < currentMiddle)
				currentLeft++;

			while (nodes.at(currentRight)->getFrequency() > currentMiddle)
				currentRight--;

			if (currentLeft <= currentRight)
			{
				std::swap(nodes.at(currentLeft), nodes.at(currentRight));

				currentLeft++;
				currentRight--;
			}
		} while (currentLeft <= currentRight);
	}
	catch (const std::out_of_range& exception)
	{
		exitProgram(std::string("Function \"sortByFrequency()\" went out of range for a given vector of unique_ptr<Node>.\n Exception message: ") + exception.what());
	}

	if (left < currentRight)
		sortByFrequency(nodes, left, currentRight);

	if (right > currentLeft)
		sortByFrequency(nodes, currentLeft, right);
}