#include "Ansi.h"



Ansi::Ansi()
{
}


Ansi::~Ansi()
{
}

void Ansi::handleSeq(std::vector<uint8_t> &Colours, std::vector<Element> &textElements, std::stringstream &s1)
{
	std::string tempte;
	Element e;
	for (size_t i = 0; i < Colours.size(); i++)
	{
		std::getline(s1, tempte);
		switch (Colours[i])
		{
			case FGRed:
			{
				e.Colours.emplace_back("#ff0000");
				break;
			}
			case FGGreen:
			{
				e.Colours.emplace_back("#00ff00");
				break;
			}
			case FGYellow:
			{
				e.Colours.emplace_back("#ffff00");
				break;
			}
			case FGBlue:
			{
				e.Colours.emplace_back("#0000ff");
				break;
			}
			case FGMagenta:
			{
				e.Colours.emplace_back("#ff00ff");
				break;
			}
			case FGCyan:
			{
				e.Colours.emplace_back("#00ffff");
				break;
			}
			case FGWhite:
			{
				e.Colours.emplace_back("#ffffff");
				break;
			}
			default:
			{
				e.Colours.emplace_back("#ffffff");
				break;
			}
		}
		e.text.emplace_back(tempte);
		textElements.emplace_back(e);
	}
}
