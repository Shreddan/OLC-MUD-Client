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
	if (con1.text1.size() > 0)
	{
		for (size_t i = 0; i < con1.text1.size(); i++)
		{
			*m_textCtrl1 << con1.text1[i];
		}
	}
	
	while (con1.sockConn->IsConnected())
	{
		con1.out.clear();
		con1.text1.clear();
		con1.ansi1.textElements.clear();
		con1.ansi1.Colours.clear();
		con1.ansi1.str.clear();
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
					//m_textCtrl1->AppendText("\n");
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
	loop();
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


