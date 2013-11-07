object ProcEdit: TProcEdit
  Left = 253
  Top = 103
  BorderStyle = bsDialog
  Caption = #1055#1088#1086#1094#1077#1076#1091#1088#1099' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103
  ClientHeight = 520
  ClientWidth = 697
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 13
    Top = 7
    Width = 150
    Height = 186
    Caption = #1058#1080#1087' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103
    Items.Strings = (
      #1055#1088#1086#1089#1090#1086#1081' '#1087#1086#1083#1080#1075#1086#1085
      #1055#1088#1086#1089#1090#1072#1103' '#1083#1080#1085#1080#1103
      #1052#1077#1090#1072#1092#1072#1081#1083
      #1052#1086#1089#1090
      #1057#1083#1086#1078#1085#1072#1103' '#1083#1080#1085#1080#1103
      #1051#1080#1085#1080#1103' '#1080#1079' '#1092#1080#1075#1091#1088
      #1047#1072#1075#1086#1075#1091#1083#1080#1089#1090#1072#1103' '#1083#1080#1085#1080#1103
      #1043#1088#1072#1085#1080#1094#1099' '#1086#1073#1098#1077#1082#1090#1072)
    TabOrder = 0
    OnClick = RadioGroup1Click
  end
  object Button1: TButton
    Left = 38
    Top = 230
    Width = 72
    Height = 20
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object Button2: TButton
    Left = 39
    Top = 267
    Width = 74
    Height = 20
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 2
  end
  object GroupBox2: TGroupBox
    Left = 182
    Top = 7
    Width = 241
    Height = 158
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1083#1080#1085#1080#1080
    TabOrder = 3
    object Label1: TLabel
      Left = 13
      Top = 26
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label27: TLabel
      Left = 13
      Top = 48
      Width = 46
      Height = 13
      Caption = #1058#1086#1083#1097#1080#1085#1072
    end
    object Label28: TLabel
      Left = 16
      Top = 72
      Width = 46
      Height = 13
      Caption = #1052#1072#1089#1096#1090#1072#1073
    end
    object Label31: TLabel
      Left = 16
      Top = 104
      Width = 30
      Height = 13
      Caption = #1057#1090#1080#1083#1100
    end
    object Label34: TLabel
      Left = 16
      Top = 128
      Width = 69
      Height = 25
      AutoSize = False
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1083#1080#1085#1080#1080' '#1074' 0.1 '#1084#1084
      WordWrap = True
    end
    object PenNum2: TEdit
      Left = 91
      Top = 20
      Width = 98
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object PenWidth2: TEdit
      Left = 91
      Top = 48
      Width = 98
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object PenScale2: TComboBox
      Left = 91
      Top = 72
      Width = 98
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 2
      Text = #1055#1086' '#1096#1080#1088#1080#1085#1077
      Items.Strings = (
        #1055#1086' '#1096#1080#1088#1080#1085#1077
        #1055#1086' '#1076#1083#1080#1085#1077)
    end
    object PenStyle2: TEdit
      Left = 91
      Top = 104
      Width = 98
      Height = 21
      TabOrder = 3
    end
    object PenOffset2: TEdit
      Left = 92
      Top = 132
      Width = 97
      Height = 21
      TabOrder = 4
      Text = '0'
    end
  end
  object GroupBox1: TGroupBox
    Left = 190
    Top = 168
    Width = 241
    Height = 85
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1087#1086#1083#1080#1075#1086#1085#1072
    TabOrder = 4
    object Label2: TLabel
      Left = 13
      Top = 20
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label3: TLabel
      Left = 13
      Top = 52
      Width = 66
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1082#1080#1089#1090#1080
    end
    object PenNum1: TEdit
      Left = 91
      Top = 13
      Width = 98
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object BrushNum1: TEdit
      Left = 91
      Top = 46
      Width = 98
      Height = 21
      TabOrder = 1
      Text = '1'
    end
  end
  object GroupBox3: TGroupBox
    Left = 154
    Top = 123
    Width = 241
    Height = 294
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1084#1077#1090#1072#1092#1072#1081#1083#1072
    TabOrder = 5
    object Label4: TLabel
      Left = 13
      Top = 20
      Width = 94
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1084#1077#1090#1072#1092#1072#1081#1083#1072
    end
    object Label5: TLabel
      Left = 13
      Top = 76
      Width = 42
      Height = 13
      Caption = #1064#1080#1088#1080#1085#1072' '
    end
    object Label6: TLabel
      Left = 13
      Top = 96
      Width = 38
      Height = 13
      Caption = #1042#1099#1089#1086#1090#1072
    end
    object Label7: TLabel
      Left = 13
      Top = 115
      Width = 111
      Height = 27
      AutoSize = False
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1086#1090' '#1094#1077#1085#1090#1088#1072' '#1087#1086' '#1096#1080#1088#1080#1085#1077
      WordWrap = True
    end
    object Label8: TLabel
      Left = 13
      Top = 148
      Width = 111
      Height = 26
      AutoSize = False
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1086#1090' '#1094#1077#1085#1090#1088#1072' '#1087#1086' '#1074#1099#1089#1086#1090#1077
      WordWrap = True
    end
    object Label33: TLabel
      Left = 8
      Top = 184
      Width = 105
      Height = 73
      AutoSize = False
      Caption = #1055#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082' '#1076#1083#1103' '#1074#1099#1074#1086#1076#1072' '#1090#1077#1082#1089#1090#1072' ('#1083#1077#1074#1086', '#1074#1077#1088#1093', '#1087#1088#1072#1074#1086', '#1085#1080#1079')'
      WordWrap = True
    end
    object Label36: TLabel
      Left = 12
      Top = 44
      Width = 62
      Height = 13
      Caption = #1050#1086#1086#1088#1076#1080#1085#1072#1090#1099
    end
    object MetaNum3: TEdit
      Left = 130
      Top = 13
      Width = 98
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object Width3: TEdit
      Left = 130
      Top = 70
      Width = 98
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object Height3: TEdit
      Left = 130
      Top = 96
      Width = 98
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object DX3: TEdit
      Left = 130
      Top = 122
      Width = 98
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object DY3: TEdit
      Left = 130
      Top = 148
      Width = 98
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object Left3: TEdit
      Left = 130
      Top = 176
      Width = 98
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object Top3: TEdit
      Left = 130
      Top = 200
      Width = 98
      Height = 21
      TabOrder = 6
      Text = '0'
    end
    object Right3: TEdit
      Left = 130
      Top = 224
      Width = 98
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object Bottom3: TEdit
      Left = 130
      Top = 248
      Width = 98
      Height = 21
      TabOrder = 8
      Text = '0'
    end
    object MetaMeasure3: TComboBox
      Left = 100
      Top = 40
      Width = 129
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 9
      Text = #1074' 0.1 '#1084#1084' '#1085#1072' '#1073#1091#1084#1072#1075#1077
      Items.Strings = (
        #1074' 0.1 '#1084#1084' '#1085#1072' '#1073#1091#1084#1072#1075#1077
        #1074' '#1089#1084' '#1085#1072' '#1084#1077#1089#1090#1085#1086#1089#1090#1080)
    end
  end
  object GroupBox4: TGroupBox
    Left = 438
    Top = 210
    Width = 241
    Height = 119
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1084#1086#1089#1090#1072
    TabOrder = 6
    object Label9: TLabel
      Left = 13
      Top = 20
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label10: TLabel
      Left = 13
      Top = 39
      Width = 108
      Height = 13
      Caption = #1044#1083#1080#1085#1072' '#1091#1089#1080#1082#1072' (0.1 '#1084#1084')'
    end
    object Label29: TLabel
      Left = 13
      Top = 64
      Width = 46
      Height = 13
      Caption = #1058#1086#1083#1097#1080#1085#1072
    end
    object Label30: TLabel
      Left = 16
      Top = 88
      Width = 46
      Height = 13
      Caption = #1052#1072#1089#1096#1090#1072#1073
    end
    object PenNum4: TEdit
      Left = 130
      Top = 13
      Width = 98
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object Length4: TEdit
      Left = 130
      Top = 39
      Width = 98
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object PenWidth4: TEdit
      Left = 131
      Top = 64
      Width = 98
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object PenScale4: TComboBox
      Left = 131
      Top = 88
      Width = 98
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 3
      Text = #1055#1086' '#1096#1080#1088#1080#1085#1077
      Items.Strings = (
        #1055#1086' '#1096#1080#1088#1080#1085#1077
        #1055#1086' '#1076#1083#1080#1085#1077)
    end
  end
  object GroupBox5: TGroupBox
    Left = 436
    Top = 7
    Width = 234
    Height = 208
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1083#1086#1078#1085#1086#1081' '#1083#1080#1085#1080#1080
    TabOrder = 7
    object Label11: TLabel
      Left = 13
      Top = 20
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label12: TLabel
      Left = 13
      Top = 39
      Width = 66
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1082#1080#1089#1090#1080
    end
    object Label13: TLabel
      Left = 13
      Top = 59
      Width = 54
      Height = 13
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077
    end
    object Label14: TLabel
      Left = 13
      Top = 78
      Width = 46
      Height = 13
      Caption = #1058#1086#1083#1097#1080#1085#1072
    end
    object Label15: TLabel
      Left = 13
      Top = 98
      Width = 72
      Height = 13
      Caption = #1044#1083#1080#1085#1072' '#1096#1090#1088#1080#1093#1072
    end
    object Label16: TLabel
      Left = 13
      Top = 117
      Width = 83
      Height = 13
      Caption = #1044#1083#1080#1085#1072' '#1087#1088#1086#1095#1077#1088#1082#1072
    end
    object Label17: TLabel
      Left = 13
      Top = 137
      Width = 105
      Height = 26
      AutoSize = False
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1076#1086' '#1085#1072#1095#1072#1083#1072' '#1096#1090#1088#1080#1093#1072
      WordWrap = True
    end
    object PenNum5: TEdit
      Left = 117
      Top = 20
      Width = 98
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object BrushNum5: TEdit
      Left = 117
      Top = 46
      Width = 98
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object Shift5: TEdit
      Left = 117
      Top = 72
      Width = 98
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object Width5: TEdit
      Left = 117
      Top = 98
      Width = 98
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object Dash5: TEdit
      Left = 117
      Top = 124
      Width = 98
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object Space5: TEdit
      Left = 117
      Top = 150
      Width = 98
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object Offset5: TEdit
      Left = 117
      Top = 176
      Width = 98
      Height = 21
      TabOrder = 6
      Text = '0'
    end
  end
  object GroupBox6: TGroupBox
    Left = 156
    Top = 236
    Width = 234
    Height = 257
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1083#1080#1085#1080#1080' '#1080#1079' '#1086#1073#1098#1077#1082#1090#1086#1074
    TabOrder = 8
    object Label18: TLabel
      Left = 13
      Top = 20
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label19: TLabel
      Left = 13
      Top = 39
      Width = 66
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1082#1080#1089#1090#1080
    end
    object Label20: TLabel
      Left = 13
      Top = 156
      Width = 64
      Height = 13
      Caption = #1042#1080#1076' '#1086#1073#1098#1077#1082#1090#1072
    end
    object Label21: TLabel
      Left = 13
      Top = 182
      Width = 39
      Height = 13
      Caption = #1056#1072#1079#1084#1077#1088
    end
    object Label22: TLabel
      Left = 13
      Top = 72
      Width = 54
      Height = 13
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077
    end
    object Label23: TLabel
      Left = 13
      Top = 98
      Width = 63
      Height = 13
      Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '
    end
    object Label24: TLabel
      Left = 13
      Top = 124
      Width = 105
      Height = 26
      AutoSize = False
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1076#1086' '#1085#1072#1095#1072#1083#1072' '#1096#1090#1088#1080#1093#1072
      WordWrap = True
    end
    object Label32: TLabel
      Left = 13
      Top = 208
      Width = 75
      Height = 13
      Caption = #1056#1072#1079#1084#1077#1088' ('#1085#1072#1087#1088'.)'
    end
    object Label35: TLabel
      Left = 12
      Top = 228
      Width = 46
      Height = 13
      Caption = #1052#1072#1089#1096#1090#1072#1073
    end
    object PenNum6: TEdit
      Left = 117
      Top = 20
      Width = 98
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object BrushNum6: TEdit
      Left = 117
      Top = 46
      Width = 98
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object Kind6: TComboBox
      Left = 117
      Top = 150
      Width = 98
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      Items.Strings = (
        #1050#1088#1091#1078#1082#1080
        #1050#1074#1072#1076#1088#1072#1090#1080#1082#1080
        #1058#1088#1077#1091#1075#1086#1083#1100#1085#1080#1082#1080
        #1055#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082#1080)
    end
    object Size6: TEdit
      Left = 117
      Top = 176
      Width = 98
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object Shift6: TEdit
      Left = 117
      Top = 72
      Width = 98
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object Space6: TEdit
      Left = 117
      Top = 98
      Width = 98
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object Offset6: TEdit
      Left = 117
      Top = 124
      Width = 98
      Height = 21
      TabOrder = 6
      Text = '0'
    end
    object OrSize6: TEdit
      Left = 117
      Top = 202
      Width = 98
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object PenScale6: TComboBox
      Left = 115
      Top = 228
      Width = 98
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 8
      Text = #1055#1086' '#1096#1080#1088#1080#1085#1077
      Items.Strings = (
        #1055#1086' '#1096#1080#1088#1080#1085#1077
        #1055#1086' '#1076#1083#1080#1085#1077)
    end
  end
  object GroupBox7: TGroupBox
    Left = 446
    Top = 423
    Width = 243
    Height = 82
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1079#1072#1075#1086#1075#1091#1083#1080#1085#1099
    TabOrder = 9
    object Label25: TLabel
      Left = 13
      Top = 26
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label26: TLabel
      Left = 16
      Top = 48
      Width = 97
      Height = 13
      Caption = #1057#1084#1077#1097#1077#1085#1080#1077' (0.1 '#1084#1084')'
    end
    object PenNum7: TEdit
      Left = 131
      Top = 20
      Width = 102
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object Shift7: TEdit
      Left = 128
      Top = 48
      Width = 105
      Height = 21
      TabOrder = 1
      Text = '100'
    end
  end
  object GroupBox8: TGroupBox
    Left = 408
    Top = 276
    Width = 209
    Height = 137
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1075#1088#1072#1085#1080#1094#1099
    TabOrder = 10
    object Label37: TLabel
      Left = 13
      Top = 26
      Width = 61
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1077#1088#1072
    end
    object Label38: TLabel
      Left = 13
      Top = 50
      Width = 109
      Height = 13
      Caption = #1044#1083#1080#1085#1072' '#1083#1080#1085#1080#1080' (0.1 '#1084#1084')'
    end
    object Label39: TLabel
      Left = 13
      Top = 72
      Width = 52
      Height = 13
      Caption = #1042#1080#1076' '#1083#1080#1085#1080#1080
    end
    object PenNum8: TEdit
      Left = 132
      Top = 20
      Width = 57
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object Length8: TEdit
      Left = 132
      Top = 44
      Width = 57
      Height = 21
      TabOrder = 1
      Text = '1'
    end
    object Kind8: TComboBox
      Left = 72
      Top = 68
      Width = 117
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 3
      TabOrder = 2
      Text = #1074' '#1085#1072#1095#1072#1083#1077' '#1080' '#1082#1086#1085#1094#1077
      Items.Strings = (
        #1085#1077#1090' '#1083#1080#1085#1080#1081
        #1074' '#1085#1072#1095#1072#1083#1077
        #1074' '#1082#1086#1085#1094#1077
        #1074' '#1085#1072#1095#1072#1083#1077' '#1080' '#1082#1086#1085#1094#1077)
    end
  end
end
