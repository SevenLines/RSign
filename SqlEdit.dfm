object SqlEditFrm: TSqlEditFrm
  Left = 222
  Top = 215
  Width = 696
  Height = 480
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1079#1072#1087#1088#1086#1089#1086#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    688
    453)
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 8
    Width = 105
    Height = 113
    Caption = #1042#1080#1076' '#1079#1072#1087#1088#1086#1089#1072
    ItemIndex = 0
    Items.Strings = (
      #1047#1072#1075#1088#1091#1079#1082#1072
      #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077
      #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077
      #1059#1076#1072#1083#1077#1085#1080#1077)
    TabOrder = 0
    OnClick = RadioGroup1Click
  end
  object Memo1: TMemo
    Left = 120
    Top = 8
    Width = 561
    Height = 441
    Anchors = [akLeft, akTop, akRight, akBottom]
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
  end
  object Button1: TButton
    Left = 24
    Top = 136
    Width = 75
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object Button2: TButton
    Left = 24
    Top = 176
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 3
  end
end
