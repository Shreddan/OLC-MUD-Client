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

	void loop(std::vector<char>& recv);

	wxTextCtrl *m_textCtrl1 = nullptr;

	std::vector<char> recv;

	wxFont font;
	

private:
	void OnExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
	
};


