object frmBuildSlopes: TfrmBuildSlopes
  Left = 435
  Top = 127
  BorderStyle = bsDialog
  Caption = #1055#1086#1089#1090#1088#1086#1077#1085#1080#1077' '#1087#1088#1086#1076#1086#1083#1100#1085#1099#1093' '#1091#1082#1083#1086#1085#1086#1074
  ClientHeight = 281
  ClientWidth = 324
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox6: TGroupBox
    Left = 4
    Top = 8
    Width = 313
    Height = 85
    Caption = #1055#1086#1089#1090#1088#1086#1077#1085#1080#1077' '#1091#1082#1083#1086#1085#1086#1074
    TabOrder = 0
    object Label2: TLabel
      Left = 20
      Top = 24
      Width = 166
      Height = 13
      Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1072#1103' '#1076#1083#1080#1085#1072' '#1091#1095#1072#1089#1090#1082#1072' ('#1084'.)'
    end
    object Label3: TLabel
      Left = 20
      Top = 52
      Width = 188
      Height = 13
      Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1081' '#1088#1072#1079#1073#1088#1086#1089' '#1091#1082#1083#1086#1085#1086#1074'  (%)'
    end
    object Edit2: TEdit
      Left = 228
      Top = 20
      Width = 53
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object ProfMinLen: TUpDown
      Left = 281
      Top = 20
      Width = 15
      Height = 21
      Associate = Edit2
      Min = 0
      Max = 1000
      Increment = 50
      Position = 0
      TabOrder = 1
      Wrap = False
    end
    object Edit3: TEdit
      Left = 228
      Top = 48
      Width = 53
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object ProfMaxDev: TUpDown
      Left = 281
      Top = 48
      Width = 15
      Height = 21
      Associate = Edit3
      Min = 0
      Increment = 10
      Position = 0
      TabOrder = 3
      Wrap = False
    end
  end
  object GroupBox7: TGroupBox
    Left = 4
    Top = 96
    Width = 313
    Height = 77
    Caption = #1043#1088#1072#1076#1072#1094#1080#1103' '#1091#1082#1083#1086#1085#1086#1074
    TabOrder = 1
    object Label4: TLabel
      Left = 20
      Top = 20
      Width = 89
      Height = 13
      Caption = #1053#1077#1079#1085#1072#1095#1080#1090#1077#1083#1100#1085#1099#1077' '
    end
    object Label5: TLabel
      Left = 20
      Top = 48
      Width = 65
      Height = 13
      Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1099#1077
    end
    object Edit4: TEdit
      Left = 128
      Top = 16
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object Edit5: TEdit
      Left = 128
      Top = 44
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object ProfVal1: TUpDown
      Left = 177
      Top = 16
      Width = 15
      Height = 21
      Associate = Edit4
      Min = 0
      Position = 0
      TabOrder = 2
      Wrap = False
    end
    object ProfVal2: TUpDown
      Left = 177
      Top = 44
      Width = 15
      Height = 21
      Associate = Edit5
      Min = 0
      Position = 0
      TabOrder = 3
      Wrap = False
    end
  end
  object Button1: TButton
    Left = 28
    Top = 252
    Width = 75
    Height = 25
    Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object Button2: TButton
    Left = 224
    Top = 252
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 4
    Top = 176
    Width = 313
    Height = 69
    Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1091#1082#1083#1086#1085#1099' '#1085#1072' '#1091#1095#1072#1089#1090#1082#1077
    TabOrder = 4
    object Label1: TLabel
      Left = 20
      Top = 16
      Width = 57
      Height = 13
      Caption = #1053#1072#1095#1072#1083#1086' ('#1084'.)'
    end
    object Label6: TLabel
      Left = 20
      Top = 44
      Width = 51
      Height = 13
      Caption = #1050#1086#1085#1077#1094' ('#1084'.)'
    end
    object edtStartPos: TEdit
      Left = 124
      Top = 16
      Width = 81
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object edtEndPos: TEdit
      Left = 124
      Top = 40
      Width = 81
      Height = 21
      TabOrder = 1
      Text = '0'
    end
  end
end
