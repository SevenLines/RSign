object OpenSourceDialog: TOpenSourceDialog
  Left = 521
  Top = 300
  BorderStyle = bsDialog
  Caption = #1048#1089#1090#1086#1095#1085#1080#1082#1080' '#1076#1072#1085#1085#1099#1093
  ClientHeight = 242
  ClientWidth = 611
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
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 611
    Height = 205
    Align = alClient
    DataSource = DataSource1
    TabOrder = 0
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
        Title.Caption = #1053#1086#1084#1077#1088' '
        Width = 46
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'FullTitle'
        Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
        Width = 225
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Executor'
        Title.Caption = #1048#1089#1087#1086#1083#1085#1080#1090#1077#1083#1100
        Width = 95
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Examiner'
        Title.Caption = #1055#1088#1086#1074#1077#1088#1103#1102#1097#1080#1081
        Width = 97
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DateCreate'
        Title.Caption = #1042#1088#1077#1084#1103' '#1089#1086#1079#1076#1072#1085#1080#1103
        Width = 92
        Visible = True
      end>
  end
  object Panel1: TPanel
    Left = 0
    Top = 205
    Width = 611
    Height = 37
    Align = alBottom
    Anchors = [akLeft]
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 12
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 92
      Top = 8
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      Default = True
      ModalResult = 2
      TabOrder = 1
    end
  end
  object ADODataSet1: TADODataSet
    Connection = MainForm.Connection
    CommandText = 'select * from ListDataSources order by id_'
    FieldDefs = <
      item
        Name = 'id_'
        Attributes = [faReadonly, faFixed]
        DataType = ftAutoInc
      end
      item
        Name = 'FullTitle'
        Attributes = [faFixed]
        DataType = ftFixedChar
        Size = 100
      end
      item
        Name = 'NumRoad'
        Attributes = [faFixed]
        DataType = ftInteger
      end
      item
        Name = 'NumType'
        Attributes = [faFixed]
        DataType = ftInteger
      end
      item
        Name = 'NumOrganization'
        Attributes = [faFixed]
        DataType = ftInteger
      end
      item
        Name = 'Executor'
        Attributes = [faFixed]
        DataType = ftFixedChar
        Size = 100
      end
      item
        Name = 'Examiner'
        Attributes = [faFixed]
        DataType = ftFixedChar
        Size = 100
      end
      item
        Name = 'DateCreate'
        Attributes = [faFixed]
        DataType = ftDateTime
      end
      item
        Name = 'DateBegin'
        Attributes = [faFixed]
        DataType = ftDateTime
      end
      item
        Name = 'DateEnd'
        Attributes = [faFixed]
        DataType = ftDateTime
      end>
    Parameters = <>
    StoreDefs = True
    Left = 32
    Top = 88
  end
  object DataSource1: TDataSource
    DataSet = ADODataSet1
    Left = 80
    Top = 88
  end
end
