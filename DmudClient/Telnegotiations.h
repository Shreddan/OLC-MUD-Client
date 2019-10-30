#pragma once
#include <vector>
#include <tuple>
#include "Telnet.h"
class Telnegotiations
{
public:
	Telnegotiations();
	~Telnegotiations();

	std::vector<std::string> singulars;
	std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> Negotiations;

};

