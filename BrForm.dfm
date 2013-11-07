object BrushEdit: TBrushEdit
  Left = 192
  Top = 116
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1082#1080#1089#1090#1080
  ClientHeight = 133
  ClientWidth = 245
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 13
    Top = 13
    Width = 30
    Height = 13
    Caption = #1057#1090#1080#1083#1100
  end
  object Label2: TLabel
    Left = 13
    Top = 52
    Width = 25
    Height = 13
    Caption = #1062#1074#1077#1090
  end
  object Shape1: TShape
    Left = 59
    Top = 33
    Width = 176
    Height = 52
    OnMouseUp = Shape1MouseUp
  end
  object ComboBox1: TComboBox
    Left = 59
    Top = 7
    Width = 176
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 0
    Text = #1057#1087#1083#1086#1096#1085#1072#1103' '#1079#1072#1083#1080#1074#1082#1072
    OnChange = ComboBox1Change
    Items.Strings = (
      #1057#1087#1083#1086#1096#1085#1072#1103' '#1079#1072#1083#1080#1074#1082#1072
      #1043#1086#1088#1080#1079#1086#1085#1090#1072#1083#1100#1085#1072#1103' '#1096#1090#1088#1080#1093#1086#1074#1082#1072
      #1042#1077#1088#1090#1080#1082#1072#1083#1100#1085#1072#1103' '#1096#1090#1088#1080#1093#1086#1074#1082#1072
      #1044#1080#1072#1075#1086#1085#1072#1083#1100#1085#1072#1103'(\) '#1096#1090#1088#1080#1093#1086#1074#1082#1072
      #1044#1080#1072#1075#1086#1085#1072#1083#1100#1085#1072#1103'(/) '#1096#1090#1088#1080#1093#1086#1074#1082#1072
      #1064#1090#1088#1080#1093#1086#1074#1082#1072' '#1088#1077#1096#1077#1090#1082#1086#1081
      #1064#1090#1088#1080#1093#1086#1074#1082#1072' '#1082#1088#1077#1089#1090#1080#1082#1086#1084)
  end
  object Button1: TButton
    Left = 26
    Top = 104
    Width = 61
    Height = 20
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object Button2: TButton
    Left = 156
    Top = 104
    Width = 61
    Height = 20
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 24
    Top = 88
  end
end
