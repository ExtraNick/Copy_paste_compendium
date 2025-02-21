#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include "json.hpp"
wxIMPLEMENT_APP(App);


bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Copy Paste Compendium");
	mainFrame->SetClientSize(800, 400);
	mainFrame->SetPosition(wxGetMousePosition());
	mainFrame->Show();
	return true;
}