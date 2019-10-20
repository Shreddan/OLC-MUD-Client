#pragma once


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

	void loop();

	wxTextCtrl *m_textCtrl1 = nullptr;
	wxTextCtrl *m_textCtrl3 = nullptr;

	//std::vector<char> recv;

	wxFont font;
	
	Connection con1;

private:
	void OnExit(wxCommandEvent& event);
	void OnConnect(wxCommandEvent& event);
	void OnSend(wxCommandEvent & event);

	void AnsiEsc(std::vector<char> &recv);

	//void OnChar(wxKeyEvent & event);

	wxDECLARE_EVENT_TABLE();
	
};


