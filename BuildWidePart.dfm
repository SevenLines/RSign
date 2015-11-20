object frmWidePartDialog: TfrmWidePartDialog
  Left = 193
  Top = 106
  BorderStyle = bsDialog
  Caption = #1055#1086#1089#1090#1088#1086#1077#1085#1080#1077' '#1091#1095#1072#1089#1090#1082#1086#1074' '#1087#1086' '#1096#1080#1088#1080#1085#1077' '#1080' '#1086#1073#1086#1095#1080#1085
  ClientHeight = 248
  ClientWidth = 575
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label6: TLabel
    Left = 8
    Top = 160
    Width = 117
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1086' '#1091#1095#1072#1089#1090#1082#1072' '#1076#1086#1088#1086#1075#1080
  end
  object Label7: TLabel
    Left = 8
    Top = 180
    Width = 111
    Height = 13
    Caption = #1050#1086#1085#1077#1094' '#1091#1095#1072#1089#1090#1082#1072' '#1076#1086#1088#1086#1075#1080
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 269
    Height = 145
    Caption = #1059#1095#1072#1089#1090#1082#1080' '#1087#1086' '#1096#1080#1088#1080#1085#1077
    TabOrder = 0
    object Label1: TLabel
      Left = 12
      Top = 20
      Width = 165
      Height = 29
      AutoSize = False
      Caption = #1064#1080#1088#1080#1085#1072' '#1087#1086' '#1087#1086#1083#1086#1089#1072#1084
      WordWrap = True
    end
    object Label2: TLabel
      Left = 12
      Top = 56
      Width = 157
      Height = 33
      AutoSize = False
      Caption = #1042#1077#1083#1080#1095#1080#1085#1072' '#1086#1082#1088#1091#1075#1083#1077#1085#1080#1103' '#1096#1080#1088#1080#1085#1099' '#1091#1095#1072#1089#1090#1082#1072' ('#1089#1084')'
      WordWrap = True
    end
    object checkPart: TCheckBox
      Left = 12
      Top = 92
      Width = 229
      Height = 17
      Caption = #1057#1090#1088#1086#1080#1090#1100' '#1091#1095#1072#1089#1090#1082#1080' '#1087#1086' '#1096#1080#1088#1080#1085#1077' '
      TabOrder = 0
    end
    object editPartMaxDev: TEdit
      Left = 188
      Top = 20
      Width = 53
      Height = 21
      TabOrder = 1
      Text = '300'
    end
    object editPartRoundVal: TEdit
      Left = 188
      Top = 60
      Width = 53
      Height = 21
      TabOrder = 2
      Text = '10'
    end
    object updPartMaxDev: TUpDown
      Left = 241
      Top = 20
      Width = 15
      Height = 21
      Associate = editPartMaxDev
      Min = 200
      Max = 400
      Increment = 5
      Position = 300
      TabOrder = 3
      Wrap = False
    end
    object updPartRoundVal: TUpDown
      Left = 241
      Top = 60
      Width = 15
      Height = 21
      Associate = editPartRoundVal
      Min = 1
      Position = 10
      TabOrder = 4
      Wrap = False
    end
    object cbMethod: TComboBox
      Left = 8
      Top = 112
      Width = 241
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 1
      TabOrder = 5
      Text = #1064#1080#1088#1080#1085#1072' '#1087#1086' '#1087#1086#1083#1086#1089#1072#1084
      Items.Strings = (
        #1054#1082#1088#1091#1075#1083#1077#1085#1080#1077' '#1074#1085#1080#1079
        #1064#1080#1088#1080#1085#1072' '#1087#1086' '#1087#1086#1083#1086#1089#1072#1084)
    end
  end
  object GroupBox2: TGroupBox
    Left = 284
    Top = 8
    Width = 285
    Height = 169
    Caption = #1054#1073#1086#1095#1080#1085#1072
    TabOrder = 1
    object Label3: TLabel
      Left = 12
      Top = 20
      Width = 165
      Height = 29
      AutoSize = False
      Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1088#1072#1079#1085#1080#1094#1072' '#1096#1080#1088#1080#1085#1099' '#1085#1072' '#1086#1073#1086#1095#1080#1085#1077' ('#1089#1084')'
      WordWrap = True
    end
    object Label4: TLabel
      Left = 12
      Top = 56
      Width = 157
      Height = 33
      AutoSize = False
      Caption = #1042#1077#1083#1080#1095#1080#1085#1072' '#1086#1082#1088#1091#1075#1083#1077#1085#1080#1103' '#1096#1080#1088#1080#1085#1099' '#1086#1073#1086#1095#1080#1085#1099' ('#1089#1084')'
      WordWrap = True
    end
    object Label5: TLabel
      Left = 12
      Top = 92
      Width = 71
      Height = 13
      Caption = #1042#1080#1076' '#1087#1086#1082#1088#1099#1090#1080#1103
    end
    object checkLeftSide: TCheckBox
      Left = 8
      Top = 144
      Width = 145
      Height = 17
      Caption = #1057#1090#1088#1086#1080#1090#1100' '#1083#1077#1074#1091#1102' '#1086#1073#1086#1095#1080#1085#1091
      TabOrder = 0
    end
    object checkRightSide: TCheckBox
      Left = 8
      Top = 124
      Width = 257
      Height = 17
      Caption = #1057#1090#1088#1086#1080#1090#1100' '#1087#1088#1072#1074#1091#1102' '#1086#1073#1086#1095#1080#1085#1091
      TabOrder = 1
    end
    object editSideMaxDev: TEdit
      Left = 188
      Top = 20
      Width = 53
      Height = 21
      TabOrder = 2
      Text = '20'
    end
    object editSideRountVal: TEdit
      Left = 188
      Top = 60
      Width = 53
      Height = 21
      TabOrder = 3
      Text = '10'
    end
    object comboSideKind: TComboBox
      Left = 124
      Top = 88
      Width = 141
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 1
      TabOrder = 4
      Text = #1065#1077#1073#1077#1085#1086#1095#1085#1086'-'#1075#1088#1072#1074#1080#1081#1085#1086#1077
      Items.Strings = (
        #1058#1074#1077#1088#1076#1086#1077
        #1065#1077#1073#1077#1085#1086#1095#1085#1086'-'#1075#1088#1072#1074#1080#1081#1085#1086#1077
        #1047#1072#1089#1077#1074' '#1090#1088#1072#1074
        #1041#1077#1079' '#1087#1086#1082#1088#1099#1090#1080#1103)
    end
    object updSideMaxDev: TUpDown
      Left = 241
      Top = 20
      Width = 15
      Height = 21
      Associate = editSideMaxDev
      Min = 10
      Increment = 5
      Position = 20
      TabOrder = 5
      Wrap = False
    end
    object updSideRoundVal: TUpDown
      Left = 241
      Top = 60
      Width = 15
      Height = 21
      Associate = editSideRountVal
      Min = 1
      Position = 10
      TabOrder = 6
      Wrap = False
    end
  end
  object editStartPos: TEdit
    Left = 164
    Top = 156
    Width = 93
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object editEndPos: TEdit
    Left = 164
    Top = 180
    Width = 93
    Height = 21
    TabOrder = 3
    Text = '0'
  end
  object Button1: TButton
    Left = 40
    Top = 208
    Width = 75
    Height = 25
    Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 4
  end
  object Button2: TButton
    Left = 456
    Top = 184
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 5
  end
end
