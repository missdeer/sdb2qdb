//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ABSMain"
#pragma resource "*.dfm"
TfrmMain* frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
int TfrmMain::convertSDBToQDB(const UnicodeString &qdbFilePath)
{
    int count = 0;
    FDConnection->Params->Values["Database"] = qdbFilePath;
    FDConnection->Open();
    FDConnection->ExecSQL(
        "CREATE TABLE IF NOT EXISTS go_games (ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "DISPLAYID INTEGER,"
        "CATEGORY TEXT,"
        "EVENTNAME TEXT,"
        "GAMENAME TEXT,"
        "BLACKNAME TEXT,"
        "BLACKRANK TEXT,"
        "BLACKLAYOUT TEXT,"
        "WHITENAME TEXT,"
        "WHITERANK TEXT,"
        "WHITELAYOUT TEXT,"
        "GAMEDATETIME TEXT,"
        "GAMERESULT TEXT,"
        "HANDICAP TEXT,"
        "KOMI TEXT,"
        "MOVECOUNT INTEGER,"
        "BOARDSIZE INTEGER,"
        "GAMEFORMAT INTEGER,"
        "READCOUNT INTEGER,"
        "LASTTIME TEXT,"
        "SIGNATURE TEXT,"
        "RATE TEXT,"
        "COMMENTED INTEGER,"
        "TAG INTEGER,"
        "PREVIEW BLOB,"
        "GAMEDATA BLOB)");
    TFDQuery* query = new TFDQuery(nullptr);
    query->Connection = FDConnection;
    query->SQL->Text =
        "INSERT into go_games (DISPLAYID, CATEGORY, EVENTNAME, GAMENAME, BLACKNAME, BLACKRANK, BLACKLAYOUT, WHITENAME, WHITERANK, WHITELAYOUT, GAMEDATETIME, GAMERESULT, HANDICAP, KOMI, MOVECOUNT, BOARDSIZE, GAMEFORMAT, READCOUNT, LASTTIME, SIGNATURE, RATE, COMMENTED, TAG, PREVIEW, GAMEDATA) "
        "VALUES (:DISPLAYID, :CATEGORY, :EVENTNAME, :GAMENAME, :BLACKNAME, :BLACKRANK, :BLACKLAYOUT, :WHITENAME, :WHITERANK, :WHITELAYOUT, :GAMEDATETIME, :GAMERESULT, :HANDICAP, :KOMI, :MOVECOUNT, :BOARDSIZE, :GAMEFORMAT, :READCOUNT, :LASTTIME, :SIGNATURE, :RATE, :COMMENTED, :TAG, :PREVIEW, :GAMEDATA);";
    FDConnection->StartTransaction();
    ABSTable->First();
    while (!ABSTable->Eof) {
        int id = ABSTable->FieldByName("ID")->AsInteger;

        query->ParamByName("DISPLAYID")->AsInteger =
            ABSTable->FieldByName("DISPLAYID")->AsInteger;
        query->ParamByName("CATEGORY")->AsString =
            ABSTable->FieldByName("CATEGORY")->AsString;
        query->ParamByName("EVENTNAME")->AsString =
            ABSTable->FieldByName("EVENTNAME")->AsString;
        query->ParamByName("GAMENAME")->AsString =
            ABSTable->FieldByName("GAMENAME")->AsString;
        query->ParamByName("BLACKNAME")->AsString =
            ABSTable->FieldByName("BLACKNAME")->AsString;
        query->ParamByName("BLACKRANK")->AsString =
            ABSTable->FieldByName("BLACKRANK")->AsString;
        query->ParamByName("BLACKLAYOUT")->AsString =
            ABSTable->FieldByName("BLACKLAYOUT")->AsString;
        query->ParamByName("WHITENAME")->AsString =
            ABSTable->FieldByName("WHITENAME")->AsString;
        query->ParamByName("WHITERANK")->AsString =
            ABSTable->FieldByName("WHITERANK")->AsString;
        query->ParamByName("WHITELAYOUT")->AsString =
            ABSTable->FieldByName("WHITELAYOUT")->AsString;
        query->ParamByName("GAMEDATETIME")->AsString =
            ABSTable->FieldByName("GAMEDATETIME")->AsString;
        query->ParamByName("GAMERESULT")->AsString =
            ABSTable->FieldByName("GAMERESULT")->AsString;
        query->ParamByName("HANDICAP")->AsString =
            ABSTable->FieldByName("HANDICAP")->AsString;
        query->ParamByName("KOMI")->AsString =
            ABSTable->FieldByName("KOMI")->AsString;
        query->ParamByName("MOVECOUNT")->AsInteger =
            ABSTable->FieldByName("MOVECOUNT")->AsInteger;
        query->ParamByName("BOARDSIZE")->AsInteger =
            ABSTable->FieldByName("BOARDSIZE")->AsInteger;
        query->ParamByName("GAMEFORMAT")->AsInteger =
            ABSTable->FieldByName("GAMEFORMAT")->AsInteger;
        query->ParamByName("READCOUNT")->AsInteger =
            ABSTable->FieldByName("READCOUNT")->AsInteger;
        query->ParamByName("LASTTIME")->AsString =
            ABSTable->FieldByName("LASTTIME")->AsString;
        query->ParamByName("SIGNATURE")->AsString =
            ABSTable->FieldByName("SIGNATURE")->AsString;
        query->ParamByName("RATE")->AsString =
            ABSTable->FieldByName("RATE")->AsString;
        query->ParamByName("TAG")->AsInteger =
            ABSTable->FieldByName("TAG")->AsInteger;
        query->ParamByName("COMMENTED")->AsInteger =
            ABSTable->FieldByName("COMMENTED")->AsBoolean ? 1 : 0;

        TStream* pPreviewStream = ABSTable->CreateBlobStream(
            ABSTable->FieldByName("PREVIEW"), bmRead);
        TMemoryStream* pPreviewDataMemoryStream = new TMemoryStream;
        pPreviewDataMemoryStream->CopyFrom(
            pPreviewStream, pPreviewStream->Size);
        auto* pPreviewField = query->ParamByName("PREVIEW");
        pPreviewField->LoadFromStream(pPreviewDataMemoryStream, ftBlob);

        TStream* pGameDataStream = ABSTable->CreateBlobStream(
            ABSTable->FieldByName("GAMEDATA"), bmRead);
        TMemoryStream* pGameDataMemoryStream = new TMemoryStream;
        pGameDataMemoryStream->CopyFrom(pGameDataStream, pGameDataStream->Size);
        auto* pGameDataField = query->ParamByName("GAMEDATA");
        pGameDataField->LoadFromStream(pGameDataMemoryStream, ftBlob);

        // insert record to qdb database
        query->ExecSQL();

        delete pPreviewStream;
        delete pPreviewDataMemoryStream;
        delete pGameDataStream;
        delete pGameDataMemoryStream;

        ABSTable->Next();
        count++;
    }
    FDConnection->Commit();
    FDConnection->Close();
    return count;
}
//---------------------------------------------------------------------------
int TfrmMain::exportSDBToDirectory(const UnicodeString &dirPath)
{
    if (!TDirectory::Exists(dirPath)) {
        TDirectory::CreateDirectory(dirPath);
    }
    int count = 0;
    while (!ABSTable->Eof) {
        TStream* pStream = ABSTable->CreateBlobStream(
            ABSTable->FieldByName("GAMEDATA"), bmRead);
        int id = ABSTable->FieldByName("ID")->AsInteger;
        TFileStream* pFileStream =
            new TFileStream(dirPath + "/" + IntToStr(id) + ".sgf", fmCreate);
        pFileStream->CopyFrom(pStream, pStream->Size);
        delete pStream;
        delete pFileStream;
        ABSTable->Next();
        count++;
    }
    return count;
}
//---------------------------------------------------------------------------
void TfrmMain::openSDB(const UnicodeString &sdbFilePath)
{
    ABSDatabase->Close();
    ABSDatabase->DatabaseFileName = sdbFilePath;
    ABSDatabase->Open();
    ABSTable->Close();
    ABSTable->TableName = "go_games";
    ABSTable->Open();
}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::OpenFileClick(TObject* Sender)
{
    if (!OpenDialog->Execute())
        return;
    openSDB(OpenDialog->FileName);
    this->Caption = OpenDialog->FileName + " - SDB to QDB";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ConvertClick(TObject* Sender)
{
    if (!SaveDialog->Execute())
        return;
    int count = convertSDBToQDB(SaveDialog->FileName);
    Application->MessageBox(
        (IntToStr(count) + L" SGF files have been inserted into " +
            SaveDialog->FileName)
            .c_str(),
        L"Notice");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ExportClick(TObject* Sender)
{
    if (!ABSDatabase->Connected) {
        Application->MessageBox(L"Database is not opened.", L"Error");
        return;
    }
    auto sourceFilePath = ABSDatabase->DatabaseFileName;
    if (!TFile::Exists(sourceFilePath)) {
        Application->MessageBox(
            (sourceFilePath + L" does not exist.").c_str(), L"Error");
        return;
    }
    auto dirPath = TPath::Combine(ExtractFilePath(sourceFilePath),
        TPath::GetFileNameWithoutExtension(sourceFilePath));
    int count = exportSDBToDirectory(dirPath);
    Application->MessageBox(
        (IntToStr(count) + L" SGF files have been exported to " + dirPath)
            .c_str(),
        L"Notice");
}
//---------------------------------------------------------------------------

