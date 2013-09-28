object BmpParam: TBmpParam
  Left = 361
  Top = 92
  BorderStyle = bsDialog
  Caption = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1076#1080#1089#1083#1086#1082#1072#1094#1080#1080' '#1074' '#1088#1072#1089#1090#1088#1086#1074#1086#1084' '#1092#1086#1088#1084#1072#1090#1077
  ClientHeight = 371
  ClientWidth = 229
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 60
    Height = 13
    Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072' '
  end
  object Label2: TLabel
    Left = 40
    Top = 100
    Width = 77
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1081' '#1082#1084'.'
  end
  object Label3: TLabel
    Left = 40
    Top = 132
    Width = 70
    Height = 13
    Caption = #1050#1086#1085#1077#1095#1085#1099#1081' '#1082#1084'.'
  end
  object Label4: TLabel
    Left = 24
    Top = 220
    Width = 72
    Height = 13
    Caption = #1084#1072#1089#1096#1090#1072#1073' '#1087#1086' L '
  end
  object Label5: TLabel
    Left = 24
    Top = 252
    Width = 71
    Height = 13
    Caption = #1052#1072#1089#1096#1090#1072#1073' '#1087#1086' X'
  end
  object Label6: TLabel
    Left = 24
    Top = 284
    Width = 16
    Height = 13
    Caption = 'Dpi'
  end
  object Label7: TLabel
    Left = 40
    Top = 164
    Width = 68
    Height = 13
    Caption = #1057#1090#1088#1072#1085#1080#1094#1072' '#1082#1084'.'
  end
  object Label8: TLabel
    Left = 32
    Top = 64
    Width = 97
    Height = 29
    AutoSize = False
    Caption = #1053#1072#1095#1072#1090#1100' '#1085#1091#1084#1077#1088#1072#1094#1080#1102' '#1089#1086' '#1089#1090#1088#1072#1085#1080#1094#1099
    WordWrap = True
  end
  object FNameEdit: TEdit
    Left = 16
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'Export'
    OnExit = FNameEditExit
  end
  object Edit2: TEdit
    Left = 136
    Top = 100
    Width = 48
    Height = 21
    TabOrder = 1
    Text = '0'
  end
  object Edit3: TEdit
    Left = 136
    Top = 132
    Width = 48
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object Button1: TButton
    Left = 16
    Top = 340
    Width = 75
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    ModalResult = 1
    TabOrder = 3
  end
  object Button2: TButton
    Left = 136
    Top = 340
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 4
  end
  object MinKm: TUpDown
    Left = 184
    Top = 100
    Width = 15
    Height = 21
    Associate = Edit2
    Min = 0
    Position = 0
    TabOrder = 5
    Wrap = False
  end
  object MaxKm: TUpDown
    Left = 184
    Top = 132
    Width = 15
    Height = 21
    Associate = Edit3
    Min = 0
    Position = 0
    TabOrder = 6
    Wrap = False
  end
  object Edit7: TEdit
    Left = 136
    Top = 164
    Width = 48
    Height = 21
    TabOrder = 7
    Text = '1'
    OnChange = Edit7Change
  end
  object PLen: TUpDown
    Left = 184
    Top = 164
    Width = 15
    Height = 21
    Associate = Edit7
    Min = 1
    Max = 200
    Position = 1
    TabOrder = 8
    Wrap = False
  end
  object ScaleL: TComboBox
    Left = 120
    Top = 220
    Width = 89
    Height = 21
    ItemHeight = 13
    ItemIndex = 1
    TabOrder = 9
    Text = '4000'
    OnChange = ScaleLChange
    Items.Strings = (
      '2000'
      '4000'
      '10000'
      '25000'
      '50000')
  end
  object ScaleX: TComboBox
    Left = 120
    Top = 252
    Width = 89
    Height = 21
    ItemHeight = 13
    ItemIndex = 2
    TabOrder = 10
    Text = '1000'
    Items.Strings = (
      '200'
      '500'
      '1000'
      '2000'
      '5000')
  end
  object Dpi: TComboBox
    Left = 120
    Top = 284
    Width = 89
    Height = 21
    ItemHeight = 13
    ItemIndex = 2
    TabOrder = 11
    Text = '300'
    Items.Strings = (
      '72'
      '150'
      '300'
      '600')
  end
  object AutoScale: TCheckBox
    Left = 8
    Top = 188
    Width = 206
    Height = 17
    Caption = #1040#1074#1090#1086#1086#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1084#1072#1089#1096#1090#1072#1073#1072' '#1087#1086' L'
    Checked = True
    State = cbChecked
    TabOrder = 12
  end
  object Button3: TButton
    Left = 144
    Top = 22
    Width = 75
    Height = 25
    Caption = #1054#1073#1079#1086#1088' ...'
    TabOrder = 13
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 16
    Top = 308
    Width = 193
    Height = 25
    Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
    TabOrder = 14
    OnClick = Button4Click
  end
  object Edit1: TEdit
    Left = 136
    Top = 68
    Width = 48
    Height = 21
    TabOrder = 15
    Text = '1'
  end
  object StartPage: TUpDown
    Left = 184
    Top = 68
    Width = 15
    Height = 21
    Associate = Edit1
    Min = 1
    Max = 1000
    Position = 1
    TabOrder = 16
    Wrap = False
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bmp'
    Filter = #1060#1072#1081#1083#1099' '#1088#1072#1089#1090#1088#1086#1074#1086#1081' '#1075#1088#1072#1092#1080#1082#1080'|*.bmp|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Title = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082' ...'
    Left = 8
    Top = 108
  end
end
