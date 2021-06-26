
#ifndef SHA512_MYAPP_H
#define SHA512_MYAPP_H

#include "frames.h"
#include <wx/cmdline.h>
//------


class MyApp : public wxApp
{
public:
    virtual bool OnInit();

    virtual int OnExit();

    virtual int OnRun();

    virtual void OnInitCmdLine(wxCmdLineParser &parser);

    virtual bool OnCmdLineParsed(wxCmdLineParser &parser);

private:
    bool command_line_mode;
};

static const wxCmdLineEntryDesc g_cmdLineDesc[] =
        {
                {wxCMD_LINE_SWITCH, "h", "help",     "displays help on the command line parameters",
                                                                                                                                                             wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP},
                {wxCMD_LINE_OPTION, "o", "output",   "output file"},
                {wxCMD_LINE_OPTION, "i", "input",    "input file"},
                {wxCMD_LINE_OPTION, "m", "mode",     "hash mode, options: 512, 384, 256, 224, enter 384 if you want to calculate sha384, sha512 by default", wxCMD_LINE_VAL_NUMBER},
                {wxCMD_LINE_SWITCH, "s", "separate", "separate mode"},

                {wxCMD_LINE_NONE}
        };

DECLARE_APP(MyApp)

#endif //SHA512_MYAPP_H
