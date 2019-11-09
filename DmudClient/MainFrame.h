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

	//wxFont style(int &Style);

	void loop();

	wxTextCtrl *m_textCtrl1 = nullptr;
	wxTextCtrl *m_textCtrl3 = nullptr;

	wxDialog *connectionDialog = nullptr;

	wxMenuItem* Debug = nullptr;

	wxDialog *debug = nullptr;

	wxArrayString *last;

	wxFont font;
	
	Connection con1;

	wxStaticText* m_staticText3 = nullptr;
	wxTextCtrl* m_textCtrl5 = nullptr;
	wxStaticText* m_staticText6 = nullptr;
	wxTextCtrl* m_textCtrl7 = nullptr;
	wxButton* m_button4 = nullptr;
	wxButton* m_button5 = nullptr;

private:
	void OnExit(wxCommandEvent& event);
	void OnConnect(wxCommandEvent& event);
	void OnConnected(wxCommandEvent & event);
	void OnSend(wxCommandEvent & event);
	void OnClickConnect(wxCommandEvent & event);

	void OnKeyDown(wxKeyEvent &event);

	

	wxDECLARE_EVENT_TABLE();
	
};


