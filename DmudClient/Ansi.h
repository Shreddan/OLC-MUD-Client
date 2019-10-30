#pragma once

#include <vector>
#include <sstream>

#include "EscSeq.h"
struct Element
{
	std::vector<std::string> Colours;
	std::vector<std::string> text;
};
class Ansi
{
public:
	Ansi();
	~Ansi();

	void handleSeq(std::vector<uint8_t>& Colours, std::vector<Element>& textElements, std::stringstream & s1);

	std::vector<uint8_t> Colours;

	std::stringstream s1;
	
	std::vector<Element> textElements;
};
