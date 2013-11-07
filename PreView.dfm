object PreViewFrm: TPreViewFrm
  Left = 489
  Top = 296
  Width = 635
  Height = 416
  Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 627
    Height = 33
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 56
      Top = 8
      Width = 48
      Height = 13
      Caption = #1057#1090#1088#1072#1085#1080#1094#1072
    end
    object Label2: TLabel
      Left = 240
      Top = 8
      Width = 46
      Height = 13
      Caption = #1052#1072#1089#1096#1090#1072#1073
    end
    object SpeedButton1: TSpeedButton
      Left = 4
      Top = 4
      Width = 23
      Height = 22
      Hint = #1053#1072#1087#1077#1095#1072#1090#1072#1090#1100' '#1090#1077#1082#1091#1097#1091#1102' '#1089#1090#1088#1072#1085#1080#1094#1091
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
        0003377777777777777308888888888888807F33333333333337088888888888
        88807FFFFFFFFFFFFFF7000000000000000077777777777777770F8F8F8F8F8F
        8F807F333333333333F708F8F8F8F8F8F9F07F333333333337370F8F8F8F8F8F
        8F807FFFFFFFFFFFFFF7000000000000000077777777777777773330FFFFFFFF
        03333337F3FFFF3F7F333330F0000F0F03333337F77773737F333330FFFFFFFF
        03333337F3FF3FFF7F333330F00F000003333337F773777773333330FFFF0FF0
        33333337F3F37F3733333330F08F0F0333333337F7337F7333333330FFFF0033
        33333337FFFF7733333333300000033333333337777773333333}
      NumGlyphs = 2
      OnClick = SpeedButton1Click
    end
    object PageList: TComboBox
      Left = 113
      Top = 7
      Width = 118
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = PageListChange
    end
    object MsList: TComboBox
      Left = 293
      Top = 7
      Width = 117
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 3
      TabOrder = 1
      Text = '100%'
      OnChange = PageListChange
      Items.Strings = (
        '800%'
        '400%'
        '200%'
        '100%'
        '75%'
        '50%'
        '25%'
        '10%')
    end
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 33
    Width = 627
    Height = 356
    Align = alClient
    TabOrder = 1
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 623
      Height = 352
      Align = alClient
      Center = True
    end
  end
end
