object FrmSetting: TFrmSetting
  Left = 193
  Top = 106
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 217
  ClientWidth = 269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object RadioCopy: TRadioGroup
    Left = 8
    Top = 8
    Width = 250
    Height = 65
    Caption = #1057#1087#1086#1089#1086#1073' '#1082#1086#1087#1080#1088#1086#1074#1072#1085#1080#1103
    ItemIndex = 1
    Items.Strings = (
      #1047#1072#1084#1077#1085#1103#1090#1100' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1086#1073#1098#1077#1082#1090#1099
      #1055#1088#1086#1087#1091#1089#1082#1072#1090#1100' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1086#1073#1098#1077#1082#1090#1099)
    TabOrder = 0
  end
  object Button1: TButton
    Left = 8
    Top = 187
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object Button2: TButton
    Left = 184
    Top = 187
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 2
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 78
    Width = 250
    Height = 40
    Caption = #1055#1088#1080#1085#1090#1077#1088
    TabOrder = 3
    object RopMode: TCheckBox
      Left = 7
      Top = 20
      Width = 234
      Height = 13
      Caption = #1055#1086#1076#1076#1077#1088#1078#1082#1072' '#1089#1084#1077#1096#1077#1085#1080#1103' '#1094#1074#1077#1090#1086#1074
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 124
    Width = 250
    Height = 53
    Caption = #1042#1080#1076#1077#1086
    TabOrder = 4
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 74
      Height = 13
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' ('#1084'.)'
    end
    object Edit1: TEdit
      Left = 96
      Top = 20
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object updownVideoOffset: TUpDown
      Left = 145
      Top = 20
      Width = 15
      Height = 21
      Associate = Edit1
      Min = -100
      Position = 0
      TabOrder = 1
      Wrap = False
    end
  end
end
