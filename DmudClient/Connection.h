#pragma once

#include <iostream>
#include <wx/wx.h>
#include <wx/socket.h>
#include "Ansi.h"
#include "Telnegotiations.h"

class Connection : public wxSocketClient
{
public:
	Connection();
	~Connection();


	void initialise();

	void read(wxSocketClient * sockConn, int & aob, std::string &out);

	void Split(std::string &out, std::vector<std::string>& text);

	void Vectorise(std::vector<std::string>& text1, std::vector<std::string> &Seq);

	int ParseSeq(std::string &par);

	Telnegotiations tel1;
	Ansi ansi1;

	std::vector<std::string> text1;
	std::vector<std::string> Seq;
	std::string temp;

	std::string out;
	   
	wxSocketClient *sockConn;

	wxString address;

	int port;

	int aob;
};

