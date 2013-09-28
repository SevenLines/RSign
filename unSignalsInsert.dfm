object frmSignalsInsert: TfrmSignalsInsert
  Left = 513
  Top = 286
  ActiveControl = edtEvery
  BorderStyle = bsToolWindow
  Caption = #1084#1072#1089#1090#1077#1088' '#1089#1090#1086#1083#1073#1080#1082#1086#1074' ^_^'
  ClientHeight = 206
  ClientWidth = 252
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnMouseWheel = FormMouseWheel
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 12
    Width = 38
    Height = 13
    Caption = #1085#1072#1095#1072#1083#1086':'
  end
  object Label2: TLabel
    Left = 16
    Top = 36
    Width = 33
    Height = 13
    Caption = #1082#1086#1085#1077#1094':'
  end
  object Label3: TLabel
    Left = 8
    Top = 65
    Width = 40
    Height = 13
    Caption = #1082#1072#1078#1076#1099#1077
  end
  object Label4: TLabel
    Left = 120
    Top = 65
    Width = 8
    Height = 13
    Caption = #1084
  end
  object lblCount: TLabel
    Left = 237
    Top = 67
    Width = 3
    Height = 13
    Alignment = taRightJustify
  end
  object Label5: TLabel
    Left = 168
    Top = 147
    Width = 65
    Height = 13
    Caption = #1089#1090#1086#1083#1073#1080#1082#1086#1074'('#1072')'
  end
  object rgMain: TRadioGroup
    Left = 8
    Top = 88
    Width = 145
    Height = 89
    ItemIndex = 0
    Items.Strings = (
      #1087#1086' '#1086#1090#1088#1077#1079#1082#1091
      #1074#1083#1077#1074#1086
      #1074#1087#1088#1072#1074#1086
      #1086#1090' '#1094#1077#1085#1090#1088#1072)
    TabOrder = 5
  end
  object edtBegin: TEdit
    Left = 56
    Top = 8
    Width = 185
    Height = 21
    TabOrder = 0
  end
  object edtEnd: TEdit
    Left = 56
    Top = 32
    Width = 185
    Height = 21
    TabOrder = 1
  end
  object Button1: TButton
    Left = 160
    Top = 61
    Width = 81
    Height = 25
    Caption = #1087#1088#1080#1084#1077#1085#1080#1090#1100
    ModalResult = 1
    TabOrder = 2
    OnClick = Button1Click
  end
  object edtEvery: TCSpinEdit
    Left = 56
    Top = 62
    Width = 57
    Height = 22
    MaxValue = 1000
    MinValue = 1
    TabOrder = 3
    Value = 20
    OnChange = edtEveryChange
  end
  object edtCount: TCSpinEdit
    Left = 96
    Top = 142
    Width = 49
    Height = 22
    MaxValue = 1000
    MinValue = 1
    TabOrder = 4
    Value = 3
    OnChange = edtEveryChange
  end
  object chkAuto: TCheckBox
    Left = 8
    Top = 184
    Width = 225
    Height = 17
    Caption = #1074#1099#1079#1086#1074' '#1090#1086#1083#1100#1082#1086' '#1087#1088#1080' '#1085#1072#1078#1072#1090#1086#1084' Ctrl'
    TabOrder = 6
  end
end
