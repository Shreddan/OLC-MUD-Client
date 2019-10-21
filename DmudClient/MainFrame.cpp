#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(1001, MainFrame::OnConnect)
	EVT_BUTTON(2001, MainFrame::OnSend)
wxEND_EVENT_TABLE()


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "OLCMud-Client", wxDefaultPosition, wxSize(1200, 800))
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxMenuBar *m_menubar3 = new wxMenuBar(0);
	wxMenu *m_menu2 = new wxMenu();
	wxMenuItem* Connect;
	Connect = new wxMenuItem(m_menu2, 1001, wxString(wxT("Connect")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(Connect);

	m_menu2->Append(wxID_EXIT);

	m_menubar3->Append(m_menu2, wxT("File"));

	this->SetMenuBar(m_menubar3);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	m_textCtrl1->SetMinSize(wxSize(1100, 700));
	m_textCtrl1->SetBackgroundColour("#000000");
	m_textCtrl1->SetForegroundColour("#ffffff");
	font = wxFont(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString);
	m_textCtrl1->SetFont(font);
	m_textCtrl1->SetDefaultStyle(wxTextAttr("#ffffff"));
	fgSizer1->Add(m_textCtrl1, 0, wxALL | wxEXPAND, 5);

	


	fgSizer1->Add(0, 0, 1, wxEXPAND, 5);

	m_textCtrl3 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_textCtrl3->SetMinSize(wxSize(1100, -1));
	m_textCtrl3->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnSend), NULL, this);

	fgSizer1->Add(m_textCtrl3, 0, wxALL, 5);

	wxButton *Send = new wxButton(this, 2001, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(Send, 0, wxALL, 5);


	this->SetSizer(fgSizer1);
	this->Layout();

	this->Centre(wxBOTH);


}


MainFrame::~MainFrame()
{
	m_textCtrl3->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnSend), NULL, this);
}

void MainFrame::FilterSeq(std::vector<std::string> &recv, std::vector<std::string> &esc)
{
	for (size_t i = 0; i < recv.size(); i++)
	{
		for (int j = 0; j < recv[i].size(); j++)
		{
			if (recv[i][j] == '[')
			{
				esc.push_back(recv[i].substr(0, 6));
				recv[i].erase(0, 6);
			}
		}
		
	}
	
}

void MainFrame::loop(std::vector<std::string> &recv, std::vector<std::string> &esc)
{
	con1.initialise();
	
	con1.read(con1.sockConn, con1.cb, con1.aob, con1.textrecv, recv);
	for (int i = 0; i < recv.size(); i++)
	{
		*m_textCtrl1 << recv[i];
	}

	
	
	while (con1.sockConn->IsConnected())
	{
		recv.clear();
		if (con1.sockConn->Wait())
		{
			con1.read(con1.sockConn, con1.cb, con1.aob, con1.textrecv, recv);
			FilterSeq(recv, esc);
			AnsiEsc(esc);
			//for (size_t a = 0; a < esc.size(); a++)
			//{
			//	*m_textCtrl1 << esc[a];
			//}
			for (int i = 0; i < recv.size(); i++)
			{
				if (esc.size() > 0)
				{
					m_textCtrl1->SetDefaultStyle(wxTextAttr(esc[i].c_str()));
				}
				*m_textCtrl1 << recv[i];
			}
		}
		esc.clear();
	}
	
}
                                   


void MainFrame::AnsiEsc(std::vector<std::string>& esc)
{
	for (size_t i = 0; i < esc.size(); i++)
	{
		if (esc[i] == "[0;31m" || esc[i] == "[1;31m")
		{
			esc[i] = "#ff0000";
		}
		else if (esc[i] == "[0;32m" || esc[i] == "[1;32m")
		{
			esc[i] = "#00ff00";
		}
		else if (esc[i] == "[0;33m" || esc[i] == "[1;33m")
		{
			esc[i] = "#ffff00";
		}
		else if (esc[i] == "[0;34m" || esc[i] == "[1:34m")
		{
			esc[i] = "#0000ff";
		}
		else if (esc[i] == "[0;35m" || esc[i] == "[1:35m")
		{
			esc[i] = "#ff00ff";
		}
		else if (esc[i] == "[0;36m" || esc[i] == "[1:36m")
		{
			esc[i] = "#00ffff";
		}
		else if (esc[i] == "[0;37m" || esc[i] == "[1;37m")
		{
			esc[i] = "#ffffff";
		}
		
		
	}
}



void MainFrame::OnExit(wxCommandEvent & event)
{
	con1.sockConn->Close();
	Close(true);
}

void MainFrame::OnConnect(wxCommandEvent & event)
{
	loop(recv, esc);
}

void MainFrame::OnSend(wxCommandEvent &event)
{
	if (con1.sockConn->WaitForWrite())
	{
		wxString send = m_textCtrl3->GetValue() += '\n';
		m_textCtrl1->AppendText('\n');
		m_textCtrl1->AppendText(send);
		m_textCtrl3->Clear();
		con1.sockConn->Write(send.c_str(), send.size() + 1);
		event.Skip();
	}
}


