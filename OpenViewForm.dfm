object OpenViewFrm: TOpenViewFrm
  Left = 689
  Top = 117
  Width = 445
  Height = 289
  Caption = #1054#1090#1082#1088#1099#1090#1100' '#1074#1080#1076
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 214
    Width = 437
    Height = 41
    Align = alBottom
    TabOrder = 0
    object ButOk: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 0
      OnClick = ButOkClick
    end
    object ButCancel: TButton
      Left = 96
      Top = 8
      Width = 75
      Height = 25
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 1
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 437
    Height = 214
    Align = alClient
    DataSource = DataSource1
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'id_'
        Title.Caption = #1053#1086#1084#1077#1088
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Title'
        Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1074#1080#1076#1072
        Width = 320
        Visible = True
      end>
  end
  object ADODataSet1: TADODataSet
    Connection = MainForm.Connection
    FieldDefs = <
      item
        Name = 'id_'
        DataType = ftInteger
      end
      item
        Name = 'Title'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'NumRoad'
        DataType = ftInteger
      end>
    Parameters = <>
    StoreDefs = True
    Left = 296
    Top = 8
  end
  object DataSource1: TDataSource
    DataSet = ADODataSet1
    Left = 312
    Top = 80
  end
end
