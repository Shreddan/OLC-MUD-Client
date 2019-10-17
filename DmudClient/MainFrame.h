#pragma once

#include <wx/wx.h>

enum cmd
{
	ID_Connect = 1
};

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

	
	

private:
	void OnExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
	
};


