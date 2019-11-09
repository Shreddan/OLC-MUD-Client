#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(1002, MainFrame::OnConnect)
	EVT_MENU(1001, MainFrame::OnConnected)
	EVT_BUTTON(2001, MainFrame::OnSend)
	EVT_BUTTON(3001, MainFrame::OnClickConnect)
wxEND_EVENT_TABLE()


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "OLCMud-Client", wxDefaultPosition, wxSize(1200, 800))
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxMenuBar *m_menubar3 = new wxMenuBar(0);
	wxMenu *m_menu2 = new wxMenu();
	wxMenuItem* Connect;
	Connect = new wxMenuItem(m_menu2, 1001, wxString(wxT("Connect")), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* AddServ;
	AddServ = new wxMenuItem(m_menu2, 1002, wxString(wxT("Add Server")), wxEmptyString, wxITEM_NORMAL);
	Debug = new wxMenuItem(m_menu2, 1003, wxString(wxT("Debug")), wxEmptyString, wxITEM_CHECK);
	m_menu2->Append(Connect);
	m_menu2->Append(AddServ);
	m_menu2->Append(Debug);
	m_menu2->Append(wxID_EXIT);

	m_menubar3->Append(m_menu2, wxT("File"));

	this->SetMenuBar(m_menubar3);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	m_textCtrl1->SetMinSize(wxSize(1100, 700));
	m_textCtrl1->SetBackgroundColour("#202020");
	m_textCtrl1->SetForegroundColour("#ffffff");
	font = wxFont(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString);
	m_textCtrl1->SetFont(font);
	m_textCtrl1->SetDefaultStyle(wxTextAttr("#ffffff"));
	fgSizer1->Add(m_textCtrl1, 0, wxALL | wxEXPAND, 2);

	
	fgSizer1->Add(0, 0, 1, wxEXPAND, 5);

	m_textCtrl3 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_textCtrl3->SetMinSize(wxSize(1100, -1));
	m_textCtrl3->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnSend), NULL, this);

	fgSizer1->Add(m_textCtrl3, 0, wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND, 4);

	wxButton *Send = new wxButton(this, 2001, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0);
	Send->SetMinSize(wxSize(70, -1));
	fgSizer1->Add(Send, 0, wxALL, 2);


	this->SetSizer(fgSizer1);
	this->Layout();

	this->Centre(wxBOTH);


}


MainFrame::~MainFrame()
{
	m_textCtrl3->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnSend), NULL, this);
}


void MainFrame::loop()
{
	con1.initialise();
	con1.read(con1.sockConn, con1.aob, con1.out);
	con1.Split(con1.out, con1.text1);
	con1.Vectorise(con1.text1, con1.ansi1.str);
	con1.ansi1.handleSeq(con1.ansi1.Colours, con1.ansi1.textElements, con1.ansi1.str);
	if (con1.ansi1.textElements.size() != 0)
	{
		for (size_t i = 0; i < con1.text1.size(); i++)
		{
			if (con1.ansi1.textElements[i].Colours[i].size() > 0)
			{
				m_textCtrl1->SetDefaultStyle(wxTextAttr(con1.ansi1.textElements[i].Colours[i].c_str()));
			}
			*m_textCtrl1 << con1.ansi1.textElements[i].text[i];
		}
	}
	else
	{
		for (size_t j = 0; j < con1.text1.size(); j++)
		{
			*m_textCtrl1 << con1.text1[j];
		}
		
	}

	debug = new wxDialog(this, wxID_ANY, "Debug Console", wxDefaultPosition, wxSize(700, 600));
	wxTextCtrl* debugcon;
	debugcon = new wxTextCtrl(debug, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);

	while (con1.sockConn->IsConnected())
	{
		con1.out.clear();
		con1.text1.clear();
		con1.ansi1.textElements.clear();
		con1.ansi1.Colours.clear();
		con1.ansi1.str.clear();

		if (Debug->IsChecked() && debug->Show() == false)
		{
			debug->Show();
		}

		if (con1.sockConn->WaitForRead())
		{
			con1.read(con1.sockConn, con1.aob, con1.out);
			con1.Split(con1.out, con1.text1);
			con1.Vectorise(con1.text1, con1.Seq);
			con1.ansi1.handleSeq(con1.ansi1.Colours, con1.ansi1.textElements, con1.ansi1.str);
			if (con1.ansi1.textElements.size() > 0)
			{
				//m_textCtrl1->AppendText(std::to_string(con1.ansi1.textElements.size()));
				for (size_t i = 0; i < con1.ansi1.textElements.size(); i++)
				{
					m_textCtrl1->SetDefaultStyle(wxTextAttr(con1.ansi1.textElements[i].Colours[i].c_str()));
					*m_textCtrl1 << con1.ansi1.textElements[i].text[i];
					*debugcon << con1.text1[i];
					//debugcon->AppendText('\n');
				}
			}
		}
	}
}

void MainFrame::OnExit(wxCommandEvent & event)
{
	if (con1.sockConn != nullptr)
	{
		con1.Close();
	}
	Close(true);
}

void MainFrame::OnConnect(wxCommandEvent & event)
{
	connectionDialog = new wxDialog(this, wxID_ANY, "Connection", wxDefaultPosition, wxSize(400, 300));
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText3 = new wxStaticText(connectionDialog, wxID_ANY, wxT("Connection Address"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer2->Add(m_staticText3, 0, wxALL, 5);

	m_textCtrl5 = new wxTextCtrl(connectionDialog, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_textCtrl5, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxALL, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText6 = new wxStaticText(connectionDialog, wxID_ANY, wxT("Port #               "), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	bSizer3->Add(m_staticText6, 0, wxALL, 5);

	m_textCtrl7 = new wxTextCtrl(connectionDialog, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(m_textCtrl7, 0, wxALL, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	m_button4 = new wxButton(connectionDialog, 3001, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button4, 0, wxALL, 5);

	m_button5 = new wxButton(connectionDialog, 3002, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_button5, 0, wxALL, 5);


	bSizer1->Add(bSizer4, 1, wxALIGN_CENTER, 5);

	m_button4->Connect(wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnClickConnect), NULL, this);


	connectionDialog->SetSizer(bSizer1);
	connectionDialog->Layout();

	connectionDialog->Centre(wxBOTH);
	connectionDialog->Show(true);
}

void MainFrame::OnConnected(wxCommandEvent &event)
{
	loop();
}
	


void MainFrame::OnSend(wxCommandEvent &event)
{
	if (con1.sockConn->WaitForWrite())
	{
		wxString send = m_textCtrl3->GetValue() += '\n';
		wxString lastcmd = m_textCtrl3->GetValue();
		//last->Add(lastcmd);
		m_textCtrl1->AppendText('\n');
		m_textCtrl1->AppendText(send);
		m_textCtrl3->Clear();
		con1.sockConn->Write(send.c_str(), send.size() + 1);
		event.Skip();
	}
}

void MainFrame::OnClickConnect(wxCommandEvent &event)
{
	con1.address = m_textCtrl5->GetValue();
	int port1 = wxAtoi(m_textCtrl7->GetValue());
	con1.port = port1;
	m_textCtrl5->Clear();
	m_textCtrl7->Clear();
	connectionDialog->Show(false);
}

void MainFrame::OnKeyDown(wxKeyEvent &event)
{

}