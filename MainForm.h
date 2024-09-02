//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <DBCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "ABSMain.hpp"
#include <Data.DbxSqlite.hpp>
#include <Data.SqlExpr.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Phys.SQLiteWrapper.Stat.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
  __published: // IDE-managed Components
    TABSTable* ABSTable;
    TABSDatabase* ABSDatabase;
    TMainMenu* MainMenu1;
    TOpenDialog* OpenDialog;
    TMenuItem* File1;
    TMenuItem* OpenFile;
    TMenuItem* N1;
    TMenuItem* Exit;
    TDataSource* DataSource;
    TSaveDialog* SaveDialog;
    TMenuItem* Convert;
    TMenuItem* Export;
    TFDConnection* FDConnection;
    TFDPhysSQLiteDriverLink* FDPhysSQLiteDriverLink;
    TDBNavigator* DBNavigator1;
    TDBGrid* DBGrid1;
    void __fastcall OpenFileClick(TObject* Sender);
    void __fastcall ConvertClick(TObject* Sender);
    void __fastcall ExportClick(TObject* Sender);
  private: // User declarations
  public: // User declarations
    __fastcall TfrmMain(TComponent* Owner);
    int convertSDBToQDB(const UnicodeString &qdbFilePath);
    int exportSDBToDirectory(const UnicodeString &dirPath);
    void openSDB(const UnicodeString &sdbFilePath);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain* frmMain;
//---------------------------------------------------------------------------
#endif

