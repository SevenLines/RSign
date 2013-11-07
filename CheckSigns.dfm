object frmCheckSigns: TfrmCheckSigns
  Left = 608
  Top = 417
  Width = 416
  Height = 323
  Caption = #1052#1072#1089#1090#1077#1088' '#1087#1088#1086#1074#1077#1088#1082#1080' '#1079#1085#1072#1082#1086#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    408
    296)
  PixelsPerInch = 96
  TextHeight = 13
  object btnClose: TButton
    Left = 333
    Top = 269
    Width = 75
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 0
    OnClick = btnCloseClick
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 408
    Height = 265
    ActivePage = TabSheet1
    Align = alTop
    Anchors = [akLeft, akTop, akBottom]
    TabIndex = 0
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1079#1085#1072#1082#1086#1074
      object TPanel
        Left = 0
        Top = 0
        Width = 400
        Height = 169
        Align = alTop
        TabOrder = 0
        object Label1: TLabel
          Left = 3
          Top = 2
          Width = 86
          Height = 13
          Caption = #1058#1077#1082#1091#1097#1072#1103' '#1076#1086#1088#1086#1075#1072':'
        end
        object lblCurrentRoadTitle: TLabel
          Left = 91
          Top = 2
          Width = 5
          Height = 13
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label3: TLabel
          Left = 3
          Top = 19
          Width = 75
          Height = 13
          Caption = #1058#1077#1082#1091#1097#1080#1081' '#1079#1085#1072#1082':'
        end
        object Label4: TLabel
          Left = 4
          Top = 36
          Width = 35
          Height = 13
          Caption = #1052#1077#1089#1090#1086':'
        end
        object lblCurrentSignTitle: TLabel
          Left = 81
          Top = 20
          Width = 3
          Height = 13
        end
        object lblCurrentSignPlace: TLabel
          Left = 42
          Top = 37
          Width = 3
          Height = 13
        end
        object GroupBox2: TGroupBox
          Left = 1
          Top = 55
          Width = 398
          Height = 113
          Align = alBottom
          Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1087#1088#1086#1074#1077#1088#1082#1080':'
          Color = clBtnFace
          ParentColor = False
          TabOrder = 0
          object lblCurrentSignDescription: TLabel
            Left = 2
            Top = 15
            Width = 394
            Height = 96
            Align = alClient
            AutoSize = False
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 169
        Width = 400
        Height = 32
        Align = alTop
        TabOrder = 1
        DesignSize = (
          400
          32)
        object btnGoToBegin: TButton
          Left = 72
          Top = 3
          Width = 94
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1042' '#1085#1072#1095#1072#1083#1086' '#1076#1086#1088#1086#1075#1080
          TabOrder = 0
          OnClick = btnGoToBeginClick
        end
        object btnGoToPrev: TButton
          Left = 168
          Top = 3
          Width = 65
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1055#1088#1077#1076'.'
          TabOrder = 1
          OnClick = btnGoToPrevClick
        end
        object btnGoToNext: TButton
          Left = 235
          Top = 3
          Width = 65
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1057#1083#1077#1076'.'
          TabOrder = 2
          OnClick = btnGoToNextClick
        end
        object btnGoToEnd: TButton
          Left = 302
          Top = 3
          Width = 94
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1042' '#1082#1086#1085#1077#1094' '#1076#1086#1088#1086#1075#1080
          TabOrder = 3
          OnClick = btnGoToEndClick
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 201
        Width = 400
        Height = 32
        Align = alTop
        TabOrder = 2
        DesignSize = (
          400
          32)
        object btnCheckSign: TButton
          Left = 235
          Top = 3
          Width = 161
          Height = 25
          Anchors = [akTop, akRight]
          Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1079#1085#1072#1082
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 400
        Height = 121
        Align = alTop
        Caption = #1040#1085#1072#1083#1080#1079#1080#1088#1091#1077#1084#1099#1077' '#1079#1085#1072#1082#1080
        TabOrder = 0
        object SignsList: TCheckListBox
          Left = 2
          Top = 15
          Width = 396
          Height = 104
          Align = alClient
          Color = clMenu
          ItemHeight = 13
          Items.Strings = (
            ': '#1087#1088#1077#1076#1091#1087#1088#1077#1078#1076#1072#1102#1097#1080#1077' '#1079#1085#1072#1082#1080
            ': '#1079#1085#1072#1082#1080' '#1087#1088#1080#1086#1088#1080#1090#1077#1090#1072
            ': '#1079#1072#1087#1088#1077#1097#1072#1102#1097#1080#1077' '#1079#1085#1072#1082#1080
            ': '#1087#1088#1077#1076#1087#1080#1089#1099#1074#1072#1102#1097#1080#1077' '#1079#1085#1072#1082#1080
            ': '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1086#1085#1085#1086'-'#1091#1082#1072#1079#1072#1090#1077#1083#1100#1085#1099#1077' '#1079#1085#1072#1082#1080
            ': '#1079#1085#1072#1082#1080' '#1089#1077#1088#1074#1080#1089#1072
            ': '#1079#1085#1072#1082#1080' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1086#1081' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080)
          TabOrder = 0
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 121
        Width = 400
        Height = 48
        Align = alTop
        TabOrder = 1
        object AutoCheck: TCheckBox
          Left = 5
          Top = 9
          Width = 321
          Height = 17
          Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080' '#1074#1099#1087#1086#1083#1085#1103#1090#1100' '#1087#1088#1086#1074#1077#1088#1082#1091' '#1088#1072#1089#1089#1090#1072#1085#1086#1074#1082#1080' '#1079#1085#1072#1082#1086#1074
          TabOrder = 0
        end
        object CheckOnlyKnownSigns: TCheckBox
          Left = 5
          Top = 26
          Width = 316
          Height = 17
          Caption = #1055#1088#1086#1074#1077#1088#1103#1090#1100' '#1090#1086#1083#1100#1082#1086' "'#1080#1079#1074#1077#1089#1090#1085#1099#1077'" '#1079#1085#1072#1082#1080
          TabOrder = 1
        end
      end
    end
  end
end
