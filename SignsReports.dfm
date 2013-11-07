object frmSignsReports: TfrmSignsReports
  Left = 218
  Top = 112
  BorderStyle = bsDialog
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1090#1095#1105#1090#1072
  ClientHeight = 372
  ClientWidth = 492
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    492
    372)
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 298
    Top = 0
    Width = 193
    Height = 336
    Anchors = [akTop, akRight, akBottom]
    Caption = ' '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1090#1095#1105#1090#1072' '
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 82
      Height = 13
      Caption = #1053#1072#1095#1072#1083#1086' '#1091#1095#1072#1089#1090#1082#1072':'
    end
    object Label2: TLabel
      Left = 10
      Top = 44
      Width = 76
      Height = 13
      Caption = #1050#1086#1085#1077#1094' '#1091#1095#1072#1089#1090#1082#1072':'
    end
    object Label3: TLabel
      Left = 8
      Top = 258
      Width = 120
      Height = 13
      Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1086#1090#1095#1105#1090#1086#1074
    end
    object Label6: TLabel
      Left = 8
      Top = 216
      Width = 87
      Height = 13
      Caption = #1055#1091#1090#1100' '#1076#1083#1103' '#1086#1090#1095#1077#1090#1086#1074
    end
    object Label7: TLabel
      Left = 8
      Top = 72
      Width = 49
      Height = 17
      AutoSize = False
      Caption = #1056#1072#1081#1086#1085' '
      WordWrap = True
    end
    object Label8: TLabel
      Left = 8
      Top = 100
      Width = 65
      Height = 21
      AutoSize = False
      Caption = #1048#1085#1089#1087#1077#1082#1094#1080#1103
      WordWrap = True
    end
    object Label9: TLabel
      Left = 8
      Top = 120
      Width = 81
      Height = 29
      AutoSize = False
      Caption = #1053#1072#1095#1072#1083#1100#1085#1080#1082' '#1080#1085#1089#1087#1077#1082#1094#1080#1080
      WordWrap = True
    end
    object txtStartPosition: TEdit
      Left = 96
      Top = 19
      Width = 89
      Height = 21
      TabOrder = 0
      OnExit = txtStartPositionExit
    end
    object txtEndPosition: TEdit
      Left = 96
      Top = 43
      Width = 89
      Height = 21
      TabOrder = 1
      OnExit = txtEndPositionExit
    end
    object txtFileName: TEdit
      Left = 8
      Top = 276
      Width = 177
      Height = 21
      TabOrder = 2
    end
    object btnOpenReportFile: TButton
      Left = 112
      Top = 300
      Width = 74
      Height = 25
      Caption = #1054#1073#1079#1086#1088' ...'
      TabOrder = 3
      OnClick = btnOpenReportFileClick
    end
    object txtFilePath: TEdit
      Left = 8
      Top = 236
      Width = 177
      Height = 21
      Enabled = False
      TabOrder = 4
    end
    object txtRoadDistr: TEdit
      Left = 72
      Top = 68
      Width = 113
      Height = 21
      TabOrder = 5
    end
    object txtDepDistr: TEdit
      Left = 72
      Top = 96
      Width = 113
      Height = 21
      TabOrder = 6
    end
    object txtDepCheef: TEdit
      Left = 72
      Top = 120
      Width = 113
      Height = 21
      TabOrder = 7
    end
    object groupFormat: TRadioGroup
      Left = 8
      Top = 152
      Width = 177
      Height = 53
      Caption = #1060#1086#1088#1084#1072#1090' '#1086#1090#1095#1077#1090#1072
      ItemIndex = 0
      Items.Strings = (
        #1058#1077#1082#1089#1090#1086#1074#1099#1081' (rtf)'
        'Web '#1089#1090#1088#1072#1085#1080#1094#1072' (html)')
      TabOrder = 8
    end
  end
  object GroupBox2: TGroupBox
    Left = 4
    Top = 88
    Width = 288
    Height = 125
    Caption = ' '#1057#1087#1080#1089#1086#1082' '#1086#1090#1095#1105#1090#1086#1074
    TabOrder = 1
    object ReportsList: TCheckListBox
      Left = 2
      Top = 15
      Width = 284
      Height = 108
      OnClickCheck = ReportsListClickCheck
      Align = alClient
      ItemHeight = 13
      Items.Strings = (
        #1057#1074#1086#1076#1085#1072#1103' '#1074#1077#1076#1086#1084#1086#1089#1090#1100' '#1076#1086#1088#1086#1078#1085#1099#1093' '#1079#1085#1072#1082#1086#1074
        #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1087#1088#1086#1077#1082#1090#1085#1099#1093' '#1079#1085#1072#1082#1086#1074
        #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1091#1089#1090#1072#1085#1086#1074#1082#1080'/'#1091#1076#1072#1083#1077#1085#1080#1103' '#1076#1086#1088#1086#1078#1085#1099#1093' '#1079#1085#1072#1082#1086#1074
        #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1076#1086#1088#1086#1078#1085#1099#1093' '#1079#1085#1072#1082#1086#1074
        #1042#1077#1076#1086#1084#1086#1089#1090#1100' '#1076#1086#1088#1086#1078#1085#1086#1081' '#1088#1072#1079#1084#1077#1090#1082#1080)
      TabOrder = 0
    end
  end
  object btnMake: TButton
    Left = 329
    Top = 342
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 2
    OnClick = btnMakeClick
  end
  object btnClose: TButton
    Left = 409
    Top = 342
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 3
    OnClick = btnCloseClick
  end
  object GroupBox3: TGroupBox
    Left = 4
    Top = 212
    Width = 288
    Height = 125
    Caption = #1048#1089#1090#1086#1095#1085#1080#1082#1080' '#1076#1072#1085#1085#1099#1093
    TabOrder = 4
    object Label4: TLabel
      Left = 8
      Top = 20
      Width = 115
      Height = 13
      Caption = #1055#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1077' '#1079#1085#1072#1082#1080
    end
    object Label5: TLabel
      Left = 8
      Top = 68
      Width = 111
      Height = 13
      Caption = #1057#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1079#1085#1072#1082#1080
    end
    object DesignSourceList: TComboBox
      Left = 8
      Top = 36
      Width = 265
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object ExistSourceList: TComboBox
      Left = 8
      Top = 84
      Width = 265
      Height = 21
      ItemHeight = 13
      TabOrder = 1
    end
  end
  object GroupBox4: TGroupBox
    Left = 4
    Top = 4
    Width = 288
    Height = 81
    Caption = #1058#1080#1090#1091#1083#1100#1085#1099#1081' '#1083#1080#1089#1090
    TabOrder = 5
    object TitulList: TCheckListBox
      Left = 2
      Top = 15
      Width = 284
      Height = 64
      Align = alClient
      ItemHeight = 13
      Items.Strings = (
        #1058#1080#1090#1091#1083#1100#1085#1099#1081' '#1083#1080#1089#1090
        #1055#1086#1103#1089#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1079#1072#1087#1080#1089#1082#1072)
      TabOrder = 0
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'rtf'
    FileName = #1054#1090#1095#1105#1090' '#1087#1086' '#1079#1085#1072#1082#1072#1084'.rtf'
    Filter = 'RTF Documents (*.rtf)|*.rtf'
    Left = 4
    Top = 256
  end
end
