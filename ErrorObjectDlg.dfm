object ErrorObjectDialog: TErrorObjectDialog
  Left = 193
  Top = 103
  BorderStyle = bsDialog
  Caption = #1057#1086#1086#1073#1097#1077#1085#1080#1077
  ClientHeight = 159
  ClientWidth = 263
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object labelMessage: TLabel
    Left = 8
    Top = 8
    Width = 241
    Height = 49
    Alignment = taCenter
    AutoSize = False
    WordWrap = True
  end
  object Label1: TLabel
    Left = 4
    Top = 68
    Width = 121
    Height = 13
    Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1086#1073#1098#1077#1082#1090#1072
  end
  object Label2: TLabel
    Left = 4
    Top = 84
    Width = 75
    Height = 13
    Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077
  end
  object labelObjName: TLabel
    Left = 136
    Top = 68
    Width = 3
    Height = 13
  end
  object labelPosition: TLabel
    Left = 135
    Top = 84
    Width = 5
    Height = 13
  end
  object btnCancel: TButton
    Left = 4
    Top = 128
    Width = 75
    Height = 25
    Caption = #1055#1088#1086#1087#1091#1089#1090#1080#1090#1100
    ModalResult = 2
    TabOrder = 0
    OnClick = btnCancelClick
  end
  object btnDelete: TButton
    Left = 88
    Top = 128
    Width = 75
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    ModalResult = 1
    TabOrder = 1
    OnClick = btnDeleteClick
  end
  object btnMark: TButton
    Left = 172
    Top = 128
    Width = 75
    Height = 25
    Caption = #1055#1086#1084#1077#1090#1080#1090#1100
    ModalResult = 1
    TabOrder = 2
    OnClick = btnMarkClick
  end
  object checkApplyToAll: TCheckBox
    Left = 4
    Top = 104
    Width = 249
    Height = 17
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100' '#1082#1086' '#1074#1089#1077#1084' '#1086#1073#1098#1077#1082#1090#1072#1084
    TabOrder = 3
  end
end
