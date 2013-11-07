object frmSetSigns: TfrmSetSigns
  Left = 562
  Top = 422
  Width = 347
  Height = 318
  Caption = #1052#1072#1089#1090#1077#1088' '#1088#1072#1089#1089#1090#1072#1085#1086#1074#1082#1080' '#1079#1085#1072#1082#1086#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    339
    291)
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 339
    Height = 262
    ActivePage = TabSheet1
    Align = alTop
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1056#1072#1089#1089#1090#1072#1085#1086#1074#1082#1072' '#1079#1085#1072#1082#1086#1074
      object TPanel
        Left = 0
        Top = 0
        Width = 331
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
          Width = 87
          Height = 13
          Caption = #1058#1077#1082#1091#1097#1080#1081' '#1086#1073#1098#1077#1082#1090':'
        end
        object Label4: TLabel
          Left = 4
          Top = 36
          Width = 35
          Height = 13
          Caption = #1052#1077#1089#1090#1086':'
        end
        object lblCurrentRoadObjectTitle: TLabel
          Left = 91
          Top = 20
          Width = 3
          Height = 13
        end
        object lblCurrentRoadObjectPlace: TLabel
          Left = 40
          Top = 36
          Width = 3
          Height = 13
        end
        object GroupBox4: TGroupBox
          Left = 1
          Top = 56
          Width = 329
          Height = 112
          Align = alBottom
          Caption = #1047#1085#1072#1082#1080' '#1087#1088#1077#1076#1083#1072#1075#1072#1077#1084#1099#1077' '#1076#1083#1103' '#1091#1089#1090#1072#1085#1086#1074#1082#1080
          TabOrder = 0
          object CurrentObjectSignsList: TCheckListBox
            Left = 2
            Top = 15
            Width = 325
            Height = 95
            Align = alClient
            ItemHeight = 13
            TabOrder = 0
          end
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 169
        Width = 331
        Height = 32
        Align = alTop
        TabOrder = 1
        object btnGoToBegin: TButton
          Left = 3
          Top = 3
          Width = 94
          Height = 25
          Caption = #1042' '#1085#1072#1095#1072#1083#1086' '#1076#1086#1088#1086#1075#1080
          TabOrder = 0
          OnClick = btnGoToBeginClick
        end
        object btnGoToPrev: TButton
          Left = 99
          Top = 3
          Width = 65
          Height = 25
          Caption = #1055#1088#1077#1076'.'
          TabOrder = 1
          OnClick = btnGoToPrevClick
        end
        object btnGoToNext: TButton
          Left = 166
          Top = 3
          Width = 65
          Height = 25
          Caption = #1057#1083#1077#1076'.'
          TabOrder = 2
          OnClick = btnGoToNextClick
        end
        object btnGoToEnd: TButton
          Left = 233
          Top = 3
          Width = 94
          Height = 25
          Caption = #1042' '#1082#1086#1085#1077#1094' '#1076#1086#1088#1086#1075#1080
          TabOrder = 3
          OnClick = btnGoToEndClick
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 201
        Width = 331
        Height = 32
        Align = alTop
        TabOrder = 2
        object btnSetSigns: TButton
          Left = 166
          Top = 3
          Width = 161
          Height = 25
          Caption = #1056#1072#1089#1089#1090#1072#1074#1080#1090#1100' '#1079#1085#1072#1082#1080
          TabOrder = 0
          OnClick = btnSetSignsClick
        end
        object btnCheckSigns: TButton
          Left = 3
          Top = 3
          Width = 161
          Height = 25
          Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1079#1085#1072#1082#1080
          TabOrder = 1
          OnClick = btnCheckSignsClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 331
        Height = 105
        Align = alTop
        Caption = #1040#1085#1072#1083#1080#1079#1080#1088#1091#1077#1084#1099#1077' '#1086#1073#1098#1077#1082#1090#1099
        TabOrder = 0
        object RoadObjectsList: TCheckListBox
          Left = 2
          Top = 15
          Width = 327
          Height = 88
          Align = alClient
          Color = clMenu
          ItemHeight = 13
          Items.Strings = (
            ': '#1087#1088#1080#1084#1099#1082#1072#1085#1080#1103
            ': '#1085#1072#1089#1077#1083#1105#1085#1085#1099#1077' '#1087#1091#1085#1082#1090#1099
            ': '#1084#1086#1089#1090#1099
            ': '#1072#1074#1090#1086#1073#1091#1089#1085#1099#1077' '#1086#1089#1090#1072#1085#1086#1074#1082#1080
            ': '#1087#1077#1088#1077#1077#1079#1076#1099)
          TabOrder = 0
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 105
        Width = 331
        Height = 32
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
      end
    end
  end
  object btnClose: TButton
    Left = 263
    Top = 265
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 1
    OnClick = btnCloseClick
  end
end
