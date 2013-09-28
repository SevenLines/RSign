object PrnParam: TPrnParam
  Left = 503
  Top = 137
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1087#1077#1095#1072#1090#1080' '#1076#1080#1089#1083#1086#1082#1072#1094#1080#1080
  ClientHeight = 343
  ClientWidth = 314
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
  object Label2: TLabel
    Left = 16
    Top = 44
    Width = 77
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1081' '#1082#1084'.'
  end
  object Label3: TLabel
    Left = 16
    Top = 76
    Width = 70
    Height = 13
    Caption = #1050#1086#1085#1077#1095#1085#1099#1081' '#1082#1084'.'
  end
  object Label4: TLabel
    Left = 16
    Top = 172
    Width = 72
    Height = 13
    Caption = #1084#1072#1089#1096#1090#1072#1073' '#1087#1086' L '
  end
  object Label5: TLabel
    Left = 16
    Top = 204
    Width = 71
    Height = 13
    Caption = #1052#1072#1089#1096#1090#1072#1073' '#1087#1086' X'
  end
  object Label7: TLabel
    Left = 16
    Top = 108
    Width = 68
    Height = 13
    Caption = #1057#1090#1088#1072#1085#1080#1094#1072' '#1082#1084'.'
  end
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 97
    Height = 29
    AutoSize = False
    Caption = #1053#1072#1095#1072#1090#1100' '#1085#1091#1084#1077#1088#1072#1094#1080#1102' '#1089#1086' '#1089#1090#1088#1072#1085#1080#1094#1099
    WordWrap = True
  end
  object Edit2: TEdit
    Left = 120
    Top = 44
    Width = 48
    Height = 21
    TabOrder = 0
    Text = '0'
  end
  object Edit3: TEdit
    Left = 120
    Top = 76
    Width = 48
    Height = 21
    TabOrder = 1
    Text = '0'
  end
  object MinKm: TUpDown
    Left = 168
    Top = 44
    Width = 15
    Height = 21
    Associate = Edit2
    Min = 0
    Position = 0
    TabOrder = 2
    Wrap = False
  end
  object MaxKm: TUpDown
    Left = 168
    Top = 76
    Width = 15
    Height = 21
    Associate = Edit3
    Min = 0
    Position = 0
    TabOrder = 3
    Wrap = False
  end
  object Edit7: TEdit
    Left = 120
    Top = 108
    Width = 48
    Height = 21
    TabOrder = 4
    Text = '1'
    OnChange = Edit7Change
  end
  object PLen: TUpDown
    Left = 168
    Top = 108
    Width = 15
    Height = 21
    Associate = Edit7
    Min = 0
    Max = 200
    Position = 1
    TabOrder = 5
    Wrap = False
  end
  object ScaleL: TComboBox
    Left = 112
    Top = 172
    Width = 97
    Height = 21
    ItemHeight = 13
    TabOrder = 6
    Text = '4000'
    OnChange = ScaleLChange
    Items.Strings = (
      '2000'
      '4000'
      '8000'
      '10000'
      '12000'
      '20000'
      '25000'
      '50000')
  end
  object ScaleX: TComboBox
    Left = 112
    Top = 204
    Width = 97
    Height = 21
    ItemHeight = 13
    ItemIndex = 2
    TabOrder = 7
    Text = '1000'
    Items.Strings = (
      '200'
      '500'
      '1000'
      '2000'
      '5000')
  end
  object Button1: TButton
    Left = 16
    Top = 301
    Width = 75
    Height = 25
    Caption = #1053#1072#1087#1077#1095#1072#1090#1072#1090#1100
    ModalResult = 1
    TabOrder = 8
  end
  object Button2: TButton
    Left = 136
    Top = 301
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 9
  end
  object Button3: TButton
    Left = 16
    Top = 236
    Width = 193
    Height = 25
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1087#1088#1080#1085#1090#1077#1088#1072
    TabOrder = 10
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 16
    Top = 268
    Width = 193
    Height = 25
    Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
    TabOrder = 11
    OnClick = Button4Click
  end
  object AutoScale: TCheckBox
    Left = 16
    Top = 148
    Width = 206
    Height = 17
    Caption = #1040#1074#1090#1086#1086#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1084#1072#1089#1096#1090#1072#1073#1072' '#1087#1086' L'
    Checked = True
    State = cbChecked
    TabOrder = 12
  end
  object Edit1: TEdit
    Left = 120
    Top = 16
    Width = 48
    Height = 21
    TabOrder = 13
    Text = '1'
  end
  object StartPage: TUpDown
    Left = 168
    Top = 16
    Width = 15
    Height = 21
    Associate = Edit1
    Min = 1
    Max = 1000
    Position = 1
    TabOrder = 14
    Wrap = False
  end
  object Edit4: TEdit
    Left = 188
    Top = 108
    Width = 45
    Height = 21
    TabOrder = 15
    Text = '0'
    OnChange = Edit7Change
  end
  object PLenM: TUpDown
    Left = 233
    Top = 108
    Width = 15
    Height = 21
    Associate = Edit4
    Min = 0
    Max = 1000
    Increment = 50
    Position = 0
    TabOrder = 16
    Wrap = False
  end
  object Edit5: TEdit
    Left = 188
    Top = 44
    Width = 45
    Height = 21
    TabOrder = 17
    Text = '0'
  end
  object MinKmM: TUpDown
    Left = 233
    Top = 44
    Width = 15
    Height = 21
    Associate = Edit5
    Min = 0
    Max = 1000
    Increment = 50
    Position = 0
    TabOrder = 18
    Wrap = False
  end
  object Edit6: TEdit
    Left = 188
    Top = 76
    Width = 45
    Height = 21
    TabOrder = 19
    Text = '0'
  end
  object MaxKmM: TUpDown
    Left = 233
    Top = 76
    Width = 15
    Height = 21
    Associate = Edit6
    Min = 0
    Max = 1000
    Increment = 50
    Position = 0
    TabOrder = 20
    Wrap = False
  end
  object PrintDialog1: TPrintDialog
    Left = 8
    Top = 228
  end
end
