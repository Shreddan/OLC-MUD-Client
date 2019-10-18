#pragma once

#include <iostream>
#include <sstream>
#include <wx/wx.h>
#include <wx/socket.h>

class Connection : public wxSocketClient
{
public:
	Connection();
	~Connection();


	void initialise();

	void read(wxSocketClient * sockConn, std::vector<wxString>& recv, int & aob, std::string rec);


	wxSocketClient *sockConn;

	std::string rec;

	int aob;
};

