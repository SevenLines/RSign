object frmEditGeomData: TfrmEditGeomData
  Left = 241
  Top = 126
  Width = 496
  Height = 480
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1075#1077#1086#1084'. '#1087#1086#1082#1072#1079#1072#1090#1077#1083#1077#1081
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    488
    453)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 3
    Width = 79
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1086' '#1091#1095#1072#1089#1090#1082#1072
  end
  object Label2: TLabel
    Left = 0
    Top = 24
    Width = 73
    Height = 13
    Caption = #1050#1086#1085#1077#1094' '#1091#1095#1072#1089#1090#1082#1072
  end
  object Label3: TLabel
    Left = 0
    Top = 48
    Width = 58
    Height = 13
    Caption = #1058#1080#1087' '#1082#1088#1080#1074#1086#1081
  end
  object Label4: TLabel
    Left = 0
    Top = 72
    Width = 86
    Height = 13
    Caption = #1056#1072#1076#1080#1091#1089' '#1087#1086#1074#1086#1088#1086#1090#1072
  end
  object DBGGeomParams: TDBGridEh
    Left = 0
    Top = 120
    Width = 488
    Height = 289
    AllowedOperations = []
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = DataSource
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'MS Sans Serif'
    FooterFont.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = DBGGeomParamsDblClick
  end
  object txtStartPos: TEdit
    Left = 88
    Top = 0
    Width = 278
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 1
  end
  object txtEndPos: TEdit
    Left = 88
    Top = 24
    Width = 278
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 2
  end
  object txtRadius: TEdit
    Left = 88
    Top = 72
    Width = 278
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 3
  end
  object cbType: TComboBox
    Left = 88
    Top = 48
    Width = 278
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    ItemHeight = 13
    TabOrder = 4
  end
  object cmdChange: TButton
    Left = 397
    Top = 32
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = cmdChangeClick
  end
  object Button3: TButton
    Left = 112
    Top = 418
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 285
    Top = 418
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1090#1084#1077#1085#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
  end
  object DataSource: TDataSource
    Left = 16
    Top = 168
  end
end
