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

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	m_textCtrl1->SetMinSize(wxSize(1100, 700));
	m_textCtrl1->SetBackgroundColour("#000000");
	m_textCtrl1->SetForegroundColour("#ffffff");


	font = wxFont(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_CP437);
	m_textCtrl1->SetFont(font);
	m_textCtrl1->SetDefaultStyle(wxTextAttr(wxFONTENCODING_CP437));
	fgSizer1->Add(m_textCtrl1, 0, wxALL, 5);


	fgSizer1->Add(0, 0, 1, wxEXPAND, 5);

	m_textCtrl3 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_textCtrl3->SetMinSize(wxSize(1100, -1));

	fgSizer1->Add(m_textCtrl3, 0, wxALL, 5);

	wxButton *Send = new wxButton(this, 2001, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(Send, 0, wxALL, 5);


	this->SetSizer(fgSizer1);
	this->Layout();

	this->Centre(wxBOTH);


}


MainFrame::~MainFrame()
{
}

void MainFrame::loop(std::vector<wxString>& recv)
{
	con1.initialise();
	if (con1.sockConn->IsConnected())
	{
		*m_textCtrl1 << "Connection Established \n";
	}
	

	con1.read(con1.sockConn, recv, con1.aob, con1.rec);
	if (con1.aob > 0)
	{
		*m_textCtrl1 << con1.aob << "\n";
	}
	for (size_t i = 0; i < recv.size(); i++)
	{
		*m_textCtrl1 << recv[i];
	}
	int size = recv.size();

	recv.clear();

	while (con1.sockConn->IsConnected())
	{
		if (con1.sockConn->Wait())
		{
			con1.read(con1.sockConn, recv, con1.aob, con1.rec);
			if (con1.aob > 0)
			{
				*m_textCtrl1 << con1.aob << "\n";
			}
			for (size_t i = 0; i < recv.size(); i++)
			{
				*m_textCtrl1 << recv[i];
			}
		}
	}

}

void MainFrame::OnExit(wxCommandEvent & event)
{
	Close(true);
}

void MainFrame::OnConnect(wxCommandEvent & event)
{
	loop(recv);
}

void MainFrame::OnSend(wxCommandEvent &event)
{
	if (con1.sockConn->WaitForWrite())
	{
		wxString send = m_textCtrl3->GetValue() += '\n';
		m_textCtrl1->AppendText(send);
		m_textCtrl3->Clear();
		con1.sockConn->Write(send.c_str(), send.size() + 1);
		int sent = con1.LastWriteCount();
		*m_textCtrl1 << sent;
		event.Skip();
	}
}
