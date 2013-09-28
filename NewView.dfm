object NewViewDialog: TNewViewDialog
  Left = 192
  Top = 114
  Width = 409
  Height = 266
  Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1089#1090#1086#1095#1085#1080#1082#1080'  '#1076#1072#1085#1085#1099#1093
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 191
    Width = 401
    Height = 41
    Align = alBottom
    TabOrder = 0
    object Button2: TButton
      Left = 92
      Top = 8
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      Default = True
      ModalResult = 2
      TabOrder = 0
    end
    object Button1: TButton
      Left = 12
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
    end
  end
  object SourcesList: TCheckListBox
    Left = 0
    Top = 0
    Width = 401
    Height = 191
    OnClickCheck = SourcesListClickCheck
    Align = alClient
    ItemHeight = 13
    TabOrder = 1
  end
  object DataSource1: TDataSource
    DataSet = ADODataSet1
    Left = 80
    Top = 88
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
end
