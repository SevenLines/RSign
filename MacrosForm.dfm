object frmMacros: TfrmMacros
  Left = 284
  Top = 291
  Width = 740
  Height = 418
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1052#1072#1082#1088#1086#1089#1099
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 233
    Top = 41
    Width = 4
    Height = 309
    Cursor = crHSplit
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 732
    Height = 41
    Align = alTop
    TabOrder = 0
    object btnAddMacro: TSpeedButton
      Left = 8
      Top = 8
      Width = 23
      Height = 22
      Caption = '+'
      OnClick = btnAddMacroClick
    end
    object btnDelMacro: TSpeedButton
      Left = 32
      Top = 8
      Width = 23
      Height = 22
      Caption = '-'
      OnClick = btnDelMacroClick
    end
    object btnWriteMacro: TSpeedButton
      Left = 56
      Top = 8
      Width = 23
      Height = 22
      Caption = 'S'
      OnClick = btnWriteMacroClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 41
    Width = 233
    Height = 309
    Align = alLeft
    Caption = #1057#1087#1080#1089#1086#1082' '#1084#1072#1082#1088#1086#1089#1086#1074
    TabOrder = 1
    object listMacroses: TListBox
      Left = 2
      Top = 15
      Width = 229
      Height = 292
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnClick = listMacrosesClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 350
    Width = 732
    Height = 41
    Align = alBottom
    TabOrder = 2
  end
  object Panel3: TPanel
    Left = 237
    Top = 41
    Width = 495
    Height = 309
    Align = alClient
    TabOrder = 3
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 493
      Height = 72
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 69
        Height = 13
        Caption = #1048#1084#1103' '#1084#1072#1082#1088#1086#1089#1072
      end
      object Label2: TLabel
        Left = 8
        Top = 40
        Width = 88
        Height = 13
        Caption = #1043#1086#1088#1103#1095#1072#1103' '#1082#1083#1072#1074#1080#1096#1072
      end
      object editMacrosName: TEdit
        Left = 88
        Top = 8
        Width = 145
        Height = 21
        TabOrder = 0
      end
      object HotKey: THotKey
        Left = 128
        Top = 40
        Width = 105
        Height = 19
        HotKey = 32833
        InvalidKeys = [hcNone, hcShift]
        Modifiers = [hkAlt]
        TabOrder = 1
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 73
      Width = 493
      Height = 235
      Align = alClient
      Caption = #1058#1077#1082#1089#1090' '#1084#1072#1082#1088#1086#1089#1072
      TabOrder = 1
      object memoMacrosText: TMemo
        Left = 2
        Top = 15
        Width = 489
        Height = 218
        Align = alClient
        TabOrder = 0
      end
    end
  end
end
