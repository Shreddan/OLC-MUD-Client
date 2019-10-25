#pragma once

#include <vector>

#include "EscSeq.h"
struct Element
{
	std::vector<uint8_t> Colours;
	std::vector<char> text;
};
class Ansi
{
public:
	Ansi();
	~Ansi();

	uint32_t handleSeq();
	

	std::vector<Element> textElements;
};

