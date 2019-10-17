#include "DmudClient.h"

wxIMPLEMENT_APP(DmudClient);

bool DmudClient::OnInit()
{
	MainFrame *frame = new MainFrame();
	frame->Show(true);
	std::cout << "Welcome to the Official OLC Mud Client!!!" << std::endl;
	return true;
}

