#ifndef SHA512_FRAMES_H
#define SHA512_FRAMES_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>

#endif

#include <wx/filepicker.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include "hashCalculator.h"


class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnFile(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

    void OnHashButtonClick(wxCommandEvent &event);

    void calculate_hash_with_string();

    void OnRcvRez(wxCommandEvent &event);

    hashCalculator my_hash;
    wxStaticText *hash_value_text;
    wxStaticText *time_used;
    wxTextCtrl *string_to_hash;

};

#endif //SHA512_FRAMES_H
