//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <vector>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", frmMain);
#include "MainForm.h"
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try {
        Application->Initialize();

        std::vector<UnicodeString> nonSwitchArgs;
        UnicodeString currentSwitch;
        UnicodeString qdbFilePath;
        UnicodeString sgfDirPath;
        bool bGui = false;
        // Parsing command line arguments
        for (int i = 1; i <= ParamCount(); i++) {
            UnicodeString arg = ParamStr(i);
            // Check if the argument is a switch
            auto leadingStr = arg.SubString(0, 2);
            if (leadingStr == L"--") {
                auto param = arg.SubString(3, arg.Length() - 2);
                int pos = param.Pos("=");
                if (pos > 0) {
                    currentSwitch = param.SubString(0, pos - 1);
                    if (currentSwitch == L"export") {
                        sgfDirPath =
                            param.SubString(pos + 1, param.Length() - pos);
                    } else if (currentSwitch == L"convert") {
                        qdbFilePath =
                            param.SubString(pos + 1, param.Length() - pos);
                    }
                } else {
                    if (param == L"gui") {
                        bGui = true;
                    }
                }
            } else {
                // It's a non-switch argument
                nonSwitchArgs.push_back(arg);
            }
        }

        bool showForm = false;
        if (!bGui && nonSwitchArgs.size() != 1) {
            return 1;
        }

        Application->MainFormOnTaskBar = true;
        Application->CreateForm(__classid(TfrmMain), &frmMain);
        frmMain->Visible = bGui;
        if (!qdbFilePath.IsEmpty()) {
            UnicodeString &sdbFilePath = nonSwitchArgs.at(0);
            frmMain->openSDB(sdbFilePath);
            frmMain->convertSDBToQDB(qdbFilePath);
            return 0;
        }
        if (!sgfDirPath.IsEmpty()) {
            UnicodeString &sdbFilePath = nonSwitchArgs.at(0);
            frmMain->openSDB(sdbFilePath);
            frmMain->exportSDBToDirectory(sgfDirPath);
            return 0;
        }
        Application->Run();
    } catch (Exception &exception) {
        Application->ShowException(&exception);
    } catch (...) {
        try {
            throw Exception("");
        } catch (Exception &exception) {
            Application->ShowException(&exception);
        }
    }
    return 0;
}
//---------------------------------------------------------------------------

