#include "MainFrame.h"
#include <wx/wx.h>
#include "json.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include "Main.cpp"
using namespace std;
using json = nlohmann::json;
string typedText;
int number_keys = 0;
int selected_pasta = 1;
int id_selected_pasta;

std::string filename = "Copy_pasta.JSON"; 
namespace current_folder = std::filesystem;

static bool CheckDataExists(std::string& file) {
	return current_folder::exists(file);
}

static json ReadData() {
	std::ifstream f(filename);
	json file_data = json::parse(f);
	return file_data;
}


static json SaveData(string x, string typedText) {
	json file_data = ReadData();
	file_data[x]["content"] = typedText;
	std::ofstream file("Copy_Pasta.JSON");
	file << file_data;
	return file_data;
}

static json LoadData(string x) {
	json file_data = ReadData();
	file_data = file_data[x]["content"];
	return file_data;
}


int ReadNumberKeys() {
	json file_data = ReadData();
	for (auto key = file_data.begin(); key != file_data.end(); key++) {
		number_keys++;

	}
	return number_keys;

}

static json NewData(int number_keys) {
	SaveData(std::to_string(number_keys + 1 ), "Paste your pasta here...");
	return number_keys;
}

static json DeleteData(int key) {
	json file_data = ReadData();
	file_data.erase(std::to_string(key));
	int increment = 1;
	json replacement_data;
	for (auto it = file_data.begin(); it != file_data.end(); it++) {
		replacement_data[std::to_string(increment)]["content"] = file_data[it.key()]["content"];
		increment++;
		std::ofstream file2("Test.JSON"); // This file is for debugging
		file2 << replacement_data;
	}
	std::ofstream file("Copy_Pasta.JSON");
	file << replacement_data;
	return replacement_data;
}

static int RefreshFrame(MainFrame *frame){ 
	frame->Layout();
	frame->Update();
	frame->Refresh();
	return 0;
}


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxFRAME_TOOL_WINDOW | /*wxCAPTION |*/ wxMINIMIZE_BOX
	)) {
	//wxPanel* panel = new wxPanel(this);
	if (CheckDataExists(filename)) {
	}
	else {
		std::ofstream created_file(filename);
		//json new_data = ReadData();
		json new_data;
		new_data["1"]["content"] = "Paste your pata here...";
		//std::ofstream created_file(filename);
		created_file << new_data;
	}

	wxPanel* panelRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(650, 100));
	panelRight->SetBackgroundColour(wxColor(32, 32, 32));

	wxScrolled<wxPanel>* panelLeft = new wxScrolled<wxPanel>(this, wxID_ANY, wxDefaultPosition, wxSize(150, 100));
	panelLeft->SetScrollRate(0, FromDIP(10));
	panelLeft->SetBackgroundColour(wxColor(0, 0, 0));

	wxPanel* panelLeftBottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(150, 50));
	panelLeftBottom->SetBackgroundColour(wxColor(10, 10, 10));
	

	

	wxBoxSizer* bottom_left_sizer = new wxBoxSizer(wxVERTICAL);
	bottom_left_sizer->Add(panelLeft, 1, wxEXPAND, FromDIP(10));
	bottom_left_sizer->Add(panelLeftBottom, 0, wxBOTTOM);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(bottom_left_sizer, 0, wxEXPAND, FromDIP(10));
	sizer->Add(panelRight, 1, wxEXPAND);
	
	this->SetSizerAndFit(sizer);
	wxButton* btnSave = new wxButton(panelRight, wxID_ANY, "Save", wxPoint(5, 350), wxSize(100, 50));
	wxButton* btnNew = new wxButton(panelLeftBottom, wxID_ANY, "New", wxPoint(0, 0), wxSize(150, 50));
	wxButton* btnDelete = new wxButton(panelRight, wxID_ANY, "Detele", wxPoint(545, 350), wxSize(100, 50));
	wxButton* btnSearch = new wxButton(panelRight, wxID_ANY, "S", wxPoint(615, 5), wxSize(30, 30));

	wxTextCtrl* txtCopyPasta = new wxTextCtrl(panelRight, wxID_ANY, "Paste your Pasta here.", wxPoint(5, 35), wxSize(640, 315), wxTE_MULTILINE | wxTE_RICH2 | wxTE_NOHIDESEL);
	wxTextCtrl* txtSearchBar = new wxTextCtrl(panelRight, wxID_ANY, "Search pasta... ", wxPoint(5, 5), wxSize(610, 30));

	btnNew->SetBackgroundColour(wxColor(186, 186, 186));
	btnSave->SetBackgroundColour(wxColor(186, 186, 186));
	btnDelete->SetBackgroundColour(wxColor(186, 186, 186));
	btnSearch->SetBackgroundColour(wxColor(186, 186, 186));
	txtCopyPasta->SetBackgroundColour(wxColor(186, 186, 186));
	txtSearchBar->SetBackgroundColour(wxColor(186, 186, 186));

	wxBoxSizer* button_sizer = new wxBoxSizer(wxVERTICAL);
	int number_keys = ReadNumberKeys();
	
	for (int i = 1; i <= number_keys; i++) {
		wxButton* btnPasta = new wxButton(panelLeft, 5999+i, std::to_string(i), wxPoint(0, (50*i)), wxSize(150, 50));
		btnPasta->SetBackgroundColour(wxColor(186, 186, 186));
		button_sizer->Add(btnPasta, 0, wxALIGN_LEFT, FromDIP(10));
		//btnPasta->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
		btnPasta->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
			txtCopyPasta->SetValue(string(LoadData(std::to_string(i))));
			selected_pasta = i;
			id_selected_pasta = 5999 + i;
			});
	}


	panelLeft->SetSizer(button_sizer);



	
	
	txtCopyPasta->SetValue(string(LoadData("1")));
	string typedText = string(txtCopyPasta->GetValue());

	btnSave->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
		SaveData(std::to_string(selected_pasta), string(txtCopyPasta->GetValue()));
	});

	btnDelete->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
		times_clicked = times_clicked - 1;
		DeleteData(selected_pasta);
		if (wxWindow* btnSelected = wxWindow::FindWindowById(id_selected_pasta, this)) 
			btnSelected->Destroy();
			panelLeft->DestroyChildren();
		
		for (int j = 1; j <= number_keys + times_clicked; j++) {
			wxButton* btnPasta = new wxButton(panelLeft, 5999+j, std::to_string(j), wxPoint(0, (50 * j) - 50), wxSize(150, 50));
			btnPasta->SetBackgroundColour(wxColor(186, 186, 186));
			button_sizer->Add(btnPasta, 0, wxALIGN_LEFT, FromDIP(10));
			btnPasta->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
				selected_pasta = j;
				id_selected_pasta = 5999 + j;
				txtCopyPasta->SetValue(string(LoadData(std::to_string(j))));
				});
			RefreshFrame(this);
		}
		});
	btnNew->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
		times_clicked = times_clicked + 1;
		int created_key = number_keys + times_clicked;
		SaveData(std::to_string(created_key), "Type your pasta here...");
		wxButton* btnPasta = new wxButton(panelLeft, wxID_ANY, std::to_string(created_key), wxPoint(0, 5), wxSize(150, 50));
		btnPasta->SetBackgroundColour(wxColor(186, 186, 186));
		button_sizer->Add(btnPasta, 0, wxALIGN_LEFT, FromDIP(10));
		btnPasta->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
			selected_pasta = created_key;
			id_selected_pasta = 5999 + created_key;
			txtCopyPasta->SetValue(string(LoadData(std::to_string(created_key))));
		});
		panelLeft->SetSizer(button_sizer);
		RefreshFrame(this);
		});


	
}
