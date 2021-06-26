#include "myApp.h"

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;
    if (command_line_mode)
    {
        wxMessageBox("finish task!");
        exit(0);
    }
    MyFrame *frame = new MyFrame();
    frame->Show(true);

    return true;
}

void MyApp::OnInitCmdLine(wxCmdLineParser &parser)
{
    parser.SetDesc(g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars(wxT("-"));
}

int MyApp::OnExit()
{
    // clean up
    return 0;
}

int MyApp::OnRun()
{
    int exitcode = wxApp::OnRun();
    if (exitcode != 0)
        return exitcode;
    return 0;
}

bool MyApp::OnCmdLineParsed(wxCmdLineParser &parser)
{
    wxString input_file, output_file;
    long mode;
    command_line_mode = parser.Found("i", &input_file);
    if (parser.Found("i", &input_file))
    {
        hashCalculator *my_hash = nullptr;
        if (parser.Found("m", &mode))
        {
            switch (mode)
            {
                case 512:
                    my_hash = new hashCalculator(SHA512);
                    break;
                case 384:
                    my_hash = new hashCalculator(SHA384);
                    break;
                case 256:
                    my_hash = new hashCalculator(SHA256);
                    break;
                case 224:
                    my_hash = new hashCalculator(SHA224);
                    break;
                default:
                    my_hash = new hashCalculator();

            }
        } else
        {
            my_hash = new hashCalculator();
        }
        my_hash->set_print_round(parser.Found("s"));
        if (parser.Found("o", &output_file))
        {
            my_hash->hash_file(input_file, output_file);
        } else
        {
            my_hash->hash_file(input_file);
        }
        cout << my_hash->get_length() << endl;
    }
    return true;
}