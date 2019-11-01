#pragma once

#include <wx/richtext/richtextctrl.h>

#include "Connection.h"


enum cmd
{
	ID_Connect = 1
};

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

	wxFont style(int &Style);

	void loop();

	wxTextCtrl *m_textCtrl1 = nullptr;
	wxTextCtrl *m_textCtrl3 = nullptr;


	wxFont font;
	
	Connection con1;

private:
	void OnExit(wxCommandEvent& event);
	void OnConnect(wxCommandEvent& event);
	void OnSend(wxCommandEvent & event);

	

	wxDECLARE_EVENT_TABLE();
	
};


