object VPatFrm: TVPatFrm
  Left = 352
  Top = 157
  Width = 606
  Height = 532
  BorderIcons = [biSystemMenu]
  Caption = #1042#1099#1073#1086#1088' '#1096#1072#1073#1083#1086#1085#1072' '#1089#1090#1088#1072#1085#1080#1094#1099
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 215
    Top = 0
    Width = 383
    Height = 469
    Align = alClient
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077' '#1096#1072#1073#1083#1086#1085#1072
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 215
    Height = 469
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 215
      Height = 49
      Align = alTop
      Caption = #1058#1077#1082#1091#1097#1080#1081' '#1096#1072#1073#1083#1086#1085
      TabOrder = 0
      object Edit1: TEdit
        Left = 8
        Top = 16
        Width = 193
        Height = 24
        Enabled = False
        TabOrder = 0
        OnChange = Edit1Change
      end
    end
    object ListBox1: TListBox
      Left = 0
      Top = 49
      Width = 215
      Height = 420
      Align = alClient
      ItemHeight = 13
      TabOrder = 1
      OnClick = ListBox1Click
      OnDblClick = ListBox1DblClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 469
    Width = 598
    Height = 36
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      598
      36)
    object Button1: TButton
      Left = 8
      Top = 5
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      Enabled = False
      ModalResult = 1
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 129
      Top = 5
      Width = 76
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      ModalResult = 2
      TabOrder = 1
    end
    object Button3: TButton
      Left = 231
      Top = 5
      Width = 244
      Height = 25
      Anchors = [akLeft, akRight, akBottom]
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1096#1072#1073#1083#1086#1085#1072
      TabOrder = 2
      OnClick = Button3Click
    end
  end
end
