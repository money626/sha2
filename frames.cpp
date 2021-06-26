#include "frames.h"

enum
{
    ID_File = SHA512 + 1,
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "sha-2")
{
    auto *menuFile = new wxMenu;
    menuFile->Append(ID_File, "&Select File...\tCtrl-F", "Select a file to calculate");
    auto *menuHashMode = new wxMenu;
    menuHashMode->AppendRadioItem(SHA512, "SHA512...", "SHA512");
    menuHashMode->AppendRadioItem(SHA384, "SHA384...", "SHA384");
    menuHashMode->AppendRadioItem(SHA256, "SHA256...", "SHA256");
    menuHashMode->AppendRadioItem(SHA224, "SHA224...", "SHA224");
    menuFile->AppendSubMenu(menuHashMode, "Hash Mode...", "Select hash mode");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);


    auto *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    auto *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnFile, this, ID_File);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MyFrame::OnHashButtonClick, this, wxID_ANY);
    Bind(wxEVT_MENU, &MyFrame::OnRcvRez, this, SHA512);
    Bind(wxEVT_MENU, &MyFrame::OnRcvRez, this, SHA384);
    Bind(wxEVT_MENU, &MyFrame::OnRcvRez, this, SHA256);
    Bind(wxEVT_MENU, &MyFrame::OnRcvRez, this, SHA224);

    // panel
    auto *panel = new wxPanel(this, wxID_ANY);
    auto defaultString = "example";
    string_to_hash = new wxTextCtrl(panel, wxID_ANY, defaultString, wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE | wxTE_PROCESS_ENTER);
    hash_value_text = new wxStaticText(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(50, 100));
    time_used = new wxStaticText(panel, wxID_ANY, "0");
    calculate_hash_with_string();
    auto *calculate_hash = new wxButton(panel, wxID_ANY, "HASH", wxPoint(10, 10), wxSize(50, 8));
    auto *panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(string_to_hash, 10, wxEXPAND);
    panelSizer->Add(calculate_hash, 2, wxEXPAND);
    panelSizer->Add(hash_value_text, 5, wxEXPAND);
    panelSizer->Add(time_used, 5, wxEXPAND);
    panel->SetSizer(panelSizer);

    // Set up the sizer for the frame and resize the frame
    // according to its contents
    auto *topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->SetMinSize(1000, 50);
    topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(topSizer);
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a sha2 hash tool", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnFile(wxCommandEvent &event)
{
    auto fileName = wxFileSelector();
    if (!fileName.empty())
    {
        auto t1 = high_resolution_clock::now();
        my_hash.process_file_data(fileName);
        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        hash_value_text->SetLabel(my_hash.get_hash());
        stringstream ss;
        ss << fileName << endl;
        ss << ms_int.count() << "ms used. " << endl;
        ss << "performance: " << my_hash.get_length() << "bytes processed." << endl;
        if (ms_int.count())
        {
            ss << my_hash.get_length() * 1000 / ms_int.count() << "bytes/s";
        }
        time_used->SetLabel(ss.str());
    }
}

void MyFrame::OnHashButtonClick(wxCommandEvent &event)
{
    calculate_hash_with_string();
}

void MyFrame::calculate_hash_with_string()
{
    auto t1 = high_resolution_clock::now();
    auto s = string_to_hash->GetValue();
    auto hash = my_hash.hash(s.ToStdString());
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    hash_value_text->SetLabel(hash);
    stringstream ss;
    ss << s << endl;
    ss << ms_int.count() << "ms used. " << endl;
    ss<< "performance: " << my_hash.get_length() << "bytes processed." << endl;
    if (ms_int.count())
    {
        ss << my_hash.get_length() * 1000 / ms_int.count() << "bytes/s";
    }
    time_used->SetLabel(ss.str());
}

void MyFrame::OnRcvRez(wxCommandEvent &event)
{
    my_hash.set_hash_mode(event.GetId());
    switch (event.GetId())
    {
        case SHA512:
            wxMessageBox("SHA512");
            break;
        case SHA384:
            wxMessageBox("SHA384");
            break;
        case SHA256:
            wxMessageBox("SHA256");
            break;
        case SHA224:
            wxMessageBox("SHA224");
            break;
    }
}