object AddProjectForm: TAddProjectForm
  Left = 489
  Top = 103
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1088#1086#1077#1082#1090' '#1076#1080#1089#1083#1086#1082#1072#1094#1080#1080' '#1076#1086#1088#1086#1078#1085#1099#1093' '#1079#1085#1072#1082#1086#1074
  ClientHeight = 313
  ClientWidth = 377
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 112
    Width = 345
    Height = 49
    Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1080
    TabOrder = 1
    object OrgName: TDBLookupComboBox
      Left = 8
      Top = 16
      Width = 321
      Height = 21
      ListSource = DataSource1
      TabOrder = 0
      OnClick = ProjNameChange
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 168
    Width = 345
    Height = 49
    Caption = #1048#1084#1103' '#1080#1089#1087#1086#1083#1085#1080#1090#1077#1083#1103
    TabOrder = 2
    object ExecName: TEdit
      Left = 8
      Top = 16
      Width = 321
      Height = 21
      TabOrder = 0
      OnChange = ProjNameChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 224
    Width = 345
    Height = 49
    Caption = #1055#1088#1086#1074#1077#1088#1103#1102#1097#1080#1081
    TabOrder = 3
    object ExamName: TEdit
      Left = 8
      Top = 16
      Width = 321
      Height = 21
      TabOrder = 0
      OnChange = ProjNameChange
    end
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 0
    Width = 345
    Height = 49
    Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1076#1086#1088#1086#1075#1080
    TabOrder = 4
    object RoadName: TEdit
      Left = 8
      Top = 16
      Width = 321
      Height = 21
      Enabled = False
      TabOrder = 0
    end
  end
  object Button1: TButton
    Left = 24
    Top = 280
    Width = 75
    Height = 25
    Caption = #1057#1086#1079#1076#1072#1090#1100
    Default = True
    Enabled = False
    ModalResult = 1
    TabOrder = 5
  end
  object Button2: TButton
    Left = 248
    Top = 280
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 6
  end
  object GroupBox5: TGroupBox
    Left = 8
    Top = 56
    Width = 345
    Height = 49
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1087#1088#1086#1077#1082#1090#1072
    TabOrder = 0
    object ProjName: TEdit
      Left = 8
      Top = 16
      Width = 321
      Height = 21
      TabOrder = 0
      OnChange = ProjNameChange
    end
  end
  object DataSource1: TDataSource
    DataSet = ADODataSet1
    Left = 136
    Top = 280
  end
  object ADODataSet1: TADODataSet
    Connection = MainForm.Connection
    Parameters = <>
    Left = 168
    Top = 280
  end
end
