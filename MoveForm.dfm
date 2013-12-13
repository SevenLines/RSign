object moveDialog: TmoveDialog
  Left = 192
  Top = 114
  BorderStyle = bsDialog
  Caption = #1055#1077#1088#1077#1084#1077#1097#1077#1085#1080#1077' '#1086#1073#1098#1077#1082#1090#1086#1074
  ClientHeight = 222
  ClientWidth = 251
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 108
    Height = 13
    Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1074' '#1084#1077#1090#1088#1072#1093
  end
  object edLength: TEdit
    Left = 136
    Top = 8
    Width = 89
    Height = 21
    TabOrder = 0
    Text = '0'
  end
  object rgKind: TRadioGroup
    Left = 8
    Top = 40
    Width = 161
    Height = 73
    Caption = #1055#1077#1088#1077#1084#1077#1097#1072#1090#1100' '#1086#1073#1098#1077#1082#1100#1099
    ItemIndex = 0
    Items.Strings = (
      #1053#1080#1082#1072#1082#1080#1077
      #1042#1099#1073#1088#1072#1085#1085#1099#1077
      #1042#1089#1077)
    TabOrder = 1
  end
  object cbVideo: TCheckBox
    Left = 8
    Top = 120
    Width = 217
    Height = 17
    Caption = #1055#1077#1088#1077#1084#1077#1097#1072#1090#1100' '#1087#1088#1080#1074#1103#1079#1082#1091' '#1074#1080#1076#1077#1086
    TabOrder = 2
  end
  object cbGeometry: TCheckBox
    Left = 8
    Top = 144
    Width = 241
    Height = 17
    Caption = #1055#1077#1088#1077#1084#1077#1097#1072#1090#1100' '#1075#1077#1086#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
    TabOrder = 3
  end
  object Button1: TButton
    Left = 8
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 4
  end
  object Button2: TButton
    Left = 160
    Top = 176
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 5
  end
end
