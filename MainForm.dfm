object frmMain: TfrmMain
  Left = 192
  Top = 131
  Caption = 'SDB to QDB'
  ClientHeight = 420
  ClientWidth = 582
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  TextHeight = 13
  object DBNavigator1: TDBNavigator
    Left = 0
    Top = 0
    Width = 582
    Height = 25
    DataSource = DataSource
    Align = alTop
    TabOrder = 0
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 25
    Width = 582
    Height = 395
    Align = alClient
    DataSource = DataSource
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object ABSTable: TABSTable
    CurrentVersion = '7.95 '
    DatabaseName = 'sdb'
    InMemory = False
    ReadOnly = True
    TableName = 'go_games'
    Exclusive = False
    Left = 360
    Top = 240
  end
  object ABSDatabase: TABSDatabase
    CurrentVersion = '7.95 '
    DatabaseName = 'sdb'
    Exclusive = False
    ReadOnly = True
    MaxConnections = 500
    MultiUser = False
    SessionName = 'Default'
    Left = 296
    Top = 240
  end
  object MainMenu1: TMainMenu
    Left = 56
    Top = 32
    object File1: TMenuItem
      Caption = '&File'
      object OpenFile: TMenuItem
        Caption = '&Open...'
        OnClick = OpenFileClick
      end
      object Convert: TMenuItem
        Caption = 'Convert...'
        OnClick = ConvertClick
      end
      object Export: TMenuItem
        Caption = '&Export'
        OnClick = ExportClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit: TMenuItem
        Caption = 'E&xit'
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'sdb'
    Filter = 'Stonebase Database Files (*.sdb)|*.sdb'
    Left = 272
    Top = 40
  end
  object DataSource: TDataSource
    DataSet = ABSTable
    Left = 144
    Top = 240
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'qdb'
    Filter = 'QDB files (*.qdb)|*.qdb'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 320
    Top = 40
  end
  object FDConnection: TFDConnection
    Params.Strings = (
      'DriverID=SQLite')
    Left = 176
    Top = 152
  end
  object FDPhysSQLiteDriverLink: TFDPhysSQLiteDriverLink
    Left = 280
    Top = 144
  end
end
