#include "DmudClient.h"


wxIMPLEMENT_APP(DmudClient);

bool DmudClient::OnInit()
{
	MainFrame *frame = new MainFrame();
	frame->Show(true);
	return true;
}

