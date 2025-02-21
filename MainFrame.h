#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	
private:
	void OnButtonClicked(wxCommandEvent& evt);
	void OnSaveClicked(wxCommandEvent& evt);
	int times_clicked = 0;
};

