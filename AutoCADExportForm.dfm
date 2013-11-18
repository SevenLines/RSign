object FAutoCADExport: TFAutoCADExport
  Left = 428
  Top = 9
  AutoSize = True
  BorderStyle = bsSingle
  BorderWidth = 1
  Caption = 'AutoCAD'
  ClientHeight = 672
  ClientWidth = 637
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 225
    Height = 672
    Align = alLeft
    Caption = ' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077' '
    TabOrder = 0
    object Bevel1: TBevel
      Left = 4
      Top = 14
      Width = 213
      Height = 267
      Shape = bsFrame
    end
    object chkTable: TCheckBox
      Left = 8
      Top = 36
      Width = 145
      Height = 17
      Caption = #1090#1072#1073#1083#1080#1094#1072
      TabOrder = 0
    end
    object chkMark: TCheckBox
      Left = 8
      Top = 100
      Width = 145
      Height = 17
      Caption = #1088#1072#1079#1084#1077#1090#1082#1072
      TabOrder = 1
    end
    object chkRoadMetrics: TCheckBox
      Left = 8
      Top = 52
      Width = 145
      Height = 17
      Caption = #1084#1077#1090#1088#1080#1082#1072' '#1076#1086#1088#1086#1075#1080
      TabOrder = 2
    end
    object chkRoadSideObjects: TCheckBox
      Left = 8
      Top = 180
      Width = 169
      Height = 17
      Caption = #1087#1083#1086#1097#1072#1076#1082#1080' '#1086#1090#1076#1099#1093#1072
      TabOrder = 3
    end
    object chkRoadSigns: TCheckBox
      Left = 8
      Top = 84
      Width = 145
      Height = 17
      Caption = #1076#1086#1088#1086#1078#1085#1099#1077' '#1079#1085#1072#1082#1080
      TabOrder = 4
    end
    object chkSlope: TCheckBox
      Left = 8
      Top = 196
      Width = 169
      Height = 17
      Caption = #1091#1095#1072#1089#1090#1082#1080' '#1091#1082#1083#1086#1085#1086#1074
      TabOrder = 5
    end
    object chkTubes: TCheckBox
      Left = 8
      Top = 116
      Width = 145
      Height = 17
      Caption = #1090#1088#1091#1073#1099
      TabOrder = 6
    end
    object chkSignal: TCheckBox
      Left = 8
      Top = 148
      Width = 201
      Height = 17
      Caption = #1087#1077#1088#1080#1083#1072' '#1080' '#1089#1090#1086#1083#1073#1080#1082#1080
      TabOrder = 7
    end
    object Button3: TButton
      Left = 181
      Top = 424
      Width = 33
      Height = 65
      Caption = '>>'
      TabOrder = 8
      OnClick = Button3Click
    end
    object chkAll: TCheckBox
      Left = 8
      Top = 16
      Width = 201
      Height = 17
      Caption = '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
      TabOrder = 9
      OnClick = chkAllClick
    end
    object chkAttachments: TCheckBox
      Left = 8
      Top = 68
      Width = 145
      Height = 17
      Caption = #1087#1088#1080#1084#1099#1082#1072#1085#1080#1103
      TabOrder = 10
    end
    object chkBridges: TCheckBox
      Left = 8
      Top = 132
      Width = 145
      Height = 17
      Caption = #1084#1086#1089#1090#1099
      TabOrder = 11
    end
    object chkBusstops: TCheckBox
      Left = 8
      Top = 164
      Width = 145
      Height = 17
      Caption = #1072#1074#1090#1086#1073#1091#1089#1085#1099#1077' '#1086#1089#1090#1072#1085#1086#1074#1082#1080
      TabOrder = 12
    end
    object chkCurves: TCheckBox
      Left = 8
      Top = 212
      Width = 169
      Height = 17
      Caption = #1091#1095#1072#1089#1090#1082#1080' '#1082#1088#1080#1074#1099#1093
      TabOrder = 13
    end
    object Button1: TButton
      Left = 136
      Top = 524
      Width = 75
      Height = 25
      Cancel = True
      Caption = #1086#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 14
    end
    object btnOk: TButton
      Left = 8
      Top = 524
      Width = 75
      Height = 25
      Caption = 'OK'
      ModalResult = 1
      TabOrder = 15
      OnClick = btnOkClick
    end
    object rgOut: TRadioGroup
      Left = 4
      Top = 418
      Width = 173
      Height = 72
      Caption = ' '#1074#1099#1074#1086#1076': '
      ItemIndex = 0
      Items.Strings = (
        #1074' '#1072#1082#1090#1080#1074#1085#1099#1081' '#1076#1086#1082#1091#1084#1077#1085#1090
        #1074' '#1085#1086#1074#1099#1081' '#1076#1086#1082#1091#1084#1077#1085#1090)
      TabOrder = 16
    end
    object chkMoundHeights: TCheckBox
      Left = 8
      Top = 228
      Width = 169
      Height = 17
      Caption = #1074#1099#1089#1086#1090#1072' '#1085#1072#1089#1099#1087#1077#1081
      TabOrder = 17
    end
    object GroupBox4: TGroupBox
      Left = 4
      Top = 556
      Width = 213
      Height = 105
      Caption = ' '#1048#1089#1090#1086#1095#1085#1080#1082#1080' '#1076#1072#1085#1085#1099#1093' '
      TabOrder = 18
      object Label7: TLabel
        Left = 16
        Top = 16
        Width = 122
        Height = 13
        Caption = #1089#1091#1097#1077#1089#1090#1074#1091#1077#1097#1080#1077' '#1086#1073#1098#1077#1082#1090#1099
      end
      object Label8: TLabel
        Left = 16
        Top = 56
        Width = 127
        Height = 13
        Caption = #1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1077' '#1086#1073#1098#1077#1082#1090#1099
      end
      object cbCurList: TComboBox
        Left = 8
        Top = 32
        Width = 201
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        Text = 'cbCurList'
        OnChange = cbCurListChange
      end
      object cbPrjList: TComboBox
        Left = 8
        Top = 72
        Width = 201
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = 'cbPrjList'
        OnChange = cbPrjListChange
      end
    end
    object chkLamps: TCheckBox
      Left = 8
      Top = 252
      Width = 169
      Height = 17
      Caption = #1092#1086#1085#1072#1088#1080
      TabOrder = 19
    end
    object chkSidewalks: TCheckBox
      Left = 72
      Top = 252
      Width = 73
      Height = 17
      Caption = #1090#1088#1086#1090#1091#1072#1088#1099
      TabOrder = 20
    end
    object chkBorders: TCheckBox
      Left = 144
      Top = 252
      Width = 65
      Height = 17
      Caption = #1073#1086#1088#1076#1102#1088#1099
      TabOrder = 21
    end
    object GroupBox9: TGroupBox
      Left = 4
      Top = 368
      Width = 213
      Height = 49
      Caption = ' '#1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1072#1103' '#1089#1077#1090#1082#1072' '
      TabOrder = 22
      object Label22: TLabel
        Left = 104
        Top = 24
        Width = 48
        Height = 13
        Caption = #1096#1072#1075' '#1074' '#1089#1084'.'
      end
      object edtGridStep: TEdit
        Left = 24
        Top = 20
        Width = 73
        Height = 21
        TabOrder = 0
        OnClick = edtBottomAddRowsClick
        OnDblClick = edtTopAddRowsDblClick
      end
      object chkGridStep: TCheckBox
        Left = 8
        Top = 22
        Width = 17
        Height = 17
        TabOrder = 1
      end
    end
    object cbIni: TComboBox
      Left = 4
      Top = 496
      Width = 213
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 23
      OnChange = cbIniChange
    end
    object Panel1: TPanel
      Left = 4
      Top = 288
      Width = 213
      Height = 81
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 24
      object chkTown: TCheckBox
        Left = 8
        Top = 56
        Width = 121
        Height = 17
        Caption = #1085#1072#1089#1083#1077#1085#1085#1099#1077' '#1087#1091#1085#1082#1090#1099
        TabOrder = 0
      end
      object chkCommunications: TCheckBox
        Left = 104
        Top = 40
        Width = 97
        Height = 17
        Caption = #1082#1086#1084#1084#1091#1085#1080#1082#1072#1094#1080#1080
        TabOrder = 1
      end
      object chkPlan: TCheckBox
        Left = 128
        Top = 56
        Width = 73
        Height = 17
        Caption = #1089#1080#1090#1091#1072#1094#1080#1103
        TabOrder = 2
      end
      object chkProfile: TCheckBox
        Left = 8
        Top = 24
        Width = 169
        Height = 17
        Caption = #1087#1088#1086#1076#1086#1083#1100#1085#1099#1081' '#1087#1088#1086#1092#1080#1083#1100
        TabOrder = 3
      end
      object chkSurface: TCheckBox
        Left = 8
        Top = 40
        Width = 89
        Height = 17
        Caption = #1090#1080#1087' '#1087#1086#1082#1088#1099#1090#1080#1103
        TabOrder = 4
      end
      object chkAllPlan: TCheckBox
        Left = 8
        Top = 4
        Width = 201
        Height = 17
        Caption = '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-'
        TabOrder = 5
        OnClick = chkAllClick
      end
    end
    object chkSignalExistToo: TCheckBox
      Left = 128
      Top = 148
      Width = 81
      Height = 17
      Hint = 
        #1090#1072#1082' '#1082#1072#1082' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102' '#1074#1099#1074#1086#1076#1103#1090#1089#1103' '#1090#1086#1083#1100#1082#1086' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1077' '#1089#1090#1086#1083#1073#1080#1082#1080' '#1101#1090#1072 +
        ' '#1075#1072#1083#1086#1095#1082#1072' '#1087#1086#1079#1074#1086#1083#1080#1090' '#1074#1099#1074#1086#1076#1080#1090#1100' '#1080' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1090#1072#1082#1078#1077
      Caption = #1089#1091#1097'. '#1090#1086#1078#1077
      ParentShowHint = False
      ShowHint = True
      TabOrder = 25
    end
  end
  object pnlLeft: TPanel
    Left = 225
    Top = 0
    Width = 412
    Height = 669
    Caption = 'pnlLeft'
    TabOrder = 1
    Visible = False
    object PageControl1: TPageControl
      Left = 1
      Top = 49
      Width = 410
      Height = 619
      ActivePage = TabSheet1
      MultiLine = True
      TabIndex = 1
      TabOrder = 0
      TabPosition = tpRight
      object TabSheet2: TTabSheet
        Caption = #1086#1073#1097#1080#1077
        ImageIndex = 1
        object Label5: TLabel
          Left = 96
          Top = 12
          Width = 141
          Height = 13
          Caption = #1088#1072#1079#1084#1077#1088' '#1087#1086#1076#1087#1080#1089#1077#1081' '#1088#1072#1079#1084#1077#1090#1082#1080
        end
        object Label6: TLabel
          Left = 96
          Top = 36
          Width = 178
          Height = 13
          Caption = #1089#1076#1074#1080#1075' '#1087#1086' '#1086#1089#1080' Y '#1087#1086#1076#1087#1080#1089#1077#1081' '#1088#1072#1079#1084#1077#1090#1082#1080
        end
        object Label11: TLabel
          Left = 96
          Top = 100
          Width = 190
          Height = 13
          Caption = #1094#1074#1077#1090' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1086#1075#1086' '#1086#1073#1098#1077#1082#1090#1072' (0-256)'
        end
        object Label12: TLabel
          Left = 111
          Top = 116
          Width = 160
          Height = 13
          Caption = #1082#1086#1076#1099' '#1094#1074#1077#1090#1086#1074' '#1089#1084#1086#1090#1088#1080' '#1074' AutoCAD'
        end
        object Label20: TLabel
          Left = 96
          Top = 140
          Width = 39
          Height = 13
          Caption = #1096#1072#1075'('#1089#1084')'
        end
        object Label21: TLabel
          Left = 152
          Top = 172
          Width = 118
          Height = 13
          Caption = #1089#1082#1072#1083#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1086' '#1086#1089#1080' Y'
        end
        object Label23: TLabel
          Left = 152
          Top = 216
          Width = 133
          Height = 13
          Caption = #1089#1088#1077#1076#1085#1085#1103' '#1096#1080#1088#1080#1085#1072'  '#1089#1080#1084#1074#1086#1083#1072
        end
        object Label24: TLabel
          Left = 8
          Top = 296
          Width = 317
          Height = 13
          Caption = #1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1087#1080#1082#1077#1090#1072#1078' '#1074' '#1090#1072#1073#1083#1080#1094#1077' '#1077#1089#1083#1080' '#1076#1083#1080#1085#1072' '#1091#1095#1072#1089#1090#1082#1072' '#1084#1077#1085#1100#1096#1077
        end
        object Label25: TLabel
          Left = 104
          Top = 340
          Width = 8
          Height = 13
          Caption = #1084
        end
        object Label26: TLabel
          Left = 8
          Top = 340
          Width = 136
          Height = 13
          Caption = #1074#1099#1089#1086#1090#1072' '#1087#1080#1082#1077#1090#1072#1078#1085#1099#1093' '#1084#1077#1090#1086#1082
        end
        object Label9: TLabel
          Left = 8
          Top = 384
          Width = 219
          Height = 13
          Caption = #1096#1072#1073#1083#1086#1085' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1086#1085#1085#1086#1075#1086' '#1087#1086#1083#1103' '#1087#1088#1080' '#1087#1077#1095#1072#1090#1080
        end
        object edtUnderTextHeight: TEdit
          Left = 8
          Top = 8
          Width = 81
          Height = 21
          TabOrder = 0
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object edtUnderTextYOffset: TEdit
          Left = 8
          Top = 32
          Width = 81
          Height = 21
          TabOrder = 1
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object chkAuto6_13: TCheckBox
          Left = 8
          Top = 56
          Width = 201
          Height = 17
          Caption = #1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080' '#1089#1076#1074#1080#1075#1072#1090#1100' '#1079#1085#1072#1082' 6.13 '
          Checked = True
          State = cbChecked
          TabOrder = 2
        end
        object edtNotExistsColor: TEdit
          Left = 8
          Top = 104
          Width = 81
          Height = 21
          TabOrder = 4
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object chkLeftValueOnly6_13: TCheckBox
          Left = 8
          Top = 72
          Width = 241
          Height = 17
          Caption = #1090#1086#1083#1100#1082#1086' '#1082#1080#1083#1086#1084#1077#1090#1088#1072#1078' '#1076#1086' '#1095#1077#1088#1090#1099' ('#1079#1085#1072#1082' 6.13)'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object GroupBox5: TGroupBox
          Left = 8
          Top = 168
          Width = 137
          Height = 121
          TabOrder = 6
          object Label16: TLabel
            Left = 112
            Top = 68
            Width = 8
            Height = 13
            Caption = #1084
          end
          object Label14: TLabel
            Left = 8
            Top = 40
            Width = 11
            Height = 13
            Caption = #1086#1090
          end
          object Label17: TLabel
            Left = 112
            Top = 40
            Width = 8
            Height = 13
            Caption = #1084
          end
          object Label15: TLabel
            Left = 8
            Top = 68
            Width = 12
            Height = 13
            Caption = #1076#1086
          end
          object edtStart: TEdit
            Left = 32
            Top = 36
            Width = 73
            Height = 21
            TabOrder = 1
            Text = '-1'
            OnChange = edtStartChange
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object chkSection: TCheckBox
            Left = 8
            Top = 14
            Width = 113
            Height = 17
            Caption = #1074#1099#1074#1086#1076#1080#1090#1100' '#1091#1095#1072#1089#1090#1086#1082
            TabOrder = 0
          end
          object edtEnd: TEdit
            Left = 32
            Top = 64
            Width = 73
            Height = 21
            TabOrder = 2
            Text = '-1'
            OnChange = edtStartChange
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object Button4: TButton
            Left = 8
            Top = 88
            Width = 113
            Height = 25
            Caption = #1089#1073#1088#1086#1089#1080#1090#1100
            TabOrder = 3
            OnClick = Button4Click
          end
        end
        object edtStep: TEdit
          Left = 8
          Top = 136
          Width = 81
          Height = 21
          TabOrder = 5
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object edtScaleY: TEdit
          Left = 152
          Top = 192
          Width = 89
          Height = 21
          TabOrder = 7
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object edtAutoShrinkOneLetterWidth: TEdit
          Left = 152
          Top = 232
          Width = 89
          Height = 21
          TabOrder = 8
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object edtUseVerticalTextIfLess: TEdit
          Left = 8
          Top = 312
          Width = 89
          Height = 21
          TabOrder = 9
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object edtSmallGridMarkHeight: TEdit
          Left = 8
          Top = 360
          Width = 89
          Height = 21
          TabOrder = 10
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object GroupBox13: TGroupBox
          Left = 0
          Top = 434
          Width = 383
          Height = 177
          Align = alBottom
          Caption = ' '#1064#1090#1088#1080#1093#1086#1092#1082#1072' '
          TabOrder = 11
          object GroupBox12: TGroupBox
            Left = 8
            Top = 120
            Width = 369
            Height = 49
            Caption = ' '#1087#1091#1089#1090#1099#1093' '#1091#1095#1072#1089#1090#1082#1086#1074' '#1090#1072#1073#1083#1080#1094#1099' '
            TabOrder = 0
            object edtTableHatch: TComboBox
              Left = 8
              Top = 20
              Width = 305
              Height = 21
              ItemHeight = 13
              Sorted = True
              TabOrder = 0
              Items.Strings = (
                ''
                'ANGLE'
                'ANSI31'
                'ANSI32'
                'ANSI33'
                'ANSI34'
                'ANSI35'
                'ANSI36'
                'ANSI37'
                'ANSI38'
                'AR-B816'
                'AR-B816'#1057
                'AR-B88'
                'AR-BRELM'
                'AR-BRSTD'
                'AR-CONC'
                'AR-HBONE'
                'AR-PARQ1'
                'AR-RROOF'
                'AR-RSHAKE'
                'AR-SAND'
                'BOX'
                'BRASS'
                'BRICK'
                'BRSTONE'
                'CLAY'
                'CORK'
                'CROSS'
                'DASH'
                'DOLMIT'
                'DOTS'
                'EARTH'
                'ESCHER'
                'FLEX'
                'GOST_GLASS'
                'GOST_GROUND'
                'GOST_WOOD'
                'GRASS'
                'GRATE'
                'GRAVEL'
                'HEX'
                'HONEY'
                'HOUND'
                'INSUL'
                'JIS_LC_10'
                'JIS_LC_15'
                'JIS_LC_18'
                'JIS_LC_20'
                'JIS_LC_20A'
                'JIS_LC_30'
                'JIS_LC_8'
                'JIS_LC_8A'
                'JIS_STN_1E'
                'JIS_STN_2.5'
                'JIS_WOOD'
                'LINE'
                'MUDST'
                'NET'
                'NET3'
                'PLAST'
                'PLASTI'
                'SACNCR'
                'SOLID'
                'SQUARE'
                'STARS'
                'STEEL'
                'SWAMP'
                'TRANS'
                'TRIANG'
                'ZIGZAG')
            end
            object edtTableHatchScale: TEdit
              Left = 328
              Top = 20
              Width = 33
              Height = 21
              TabOrder = 1
            end
          end
          object GroupBox8: TGroupBox
            Left = 8
            Top = 72
            Width = 369
            Height = 49
            Caption = ' '#1087#1088#1086#1076#1086#1083#1100#1085#1086#1075#1086' '#1087#1088#1086#1092#1080#1083#1103' '
            TabOrder = 1
            object edtProfileHatch: TComboBox
              Left = 8
              Top = 20
              Width = 305
              Height = 21
              ItemHeight = 13
              Sorted = True
              TabOrder = 0
              Items.Strings = (
                ''
                'ANGLE'
                'ANSI31'
                'ANSI32'
                'ANSI33'
                'ANSI34'
                'ANSI35'
                'ANSI36'
                'ANSI37'
                'ANSI38'
                'AR-B816'
                'AR-B816'#1057
                'AR-B88'
                'AR-BRELM'
                'AR-BRSTD'
                'AR-CONC'
                'AR-HBONE'
                'AR-PARQ1'
                'AR-RROOF'
                'AR-RSHAKE'
                'AR-SAND'
                'BOX'
                'BRASS'
                'BRICK'
                'BRSTONE'
                'CLAY'
                'CORK'
                'CROSS'
                'DASH'
                'DOLMIT'
                'DOTS'
                'EARTH'
                'ESCHER'
                'FLEX'
                'GOST_GLASS'
                'GOST_GROUND'
                'GOST_WOOD'
                'GRASS'
                'GRATE'
                'GRAVEL'
                'HEX'
                'HONEY'
                'HOUND'
                'INSUL'
                'JIS_LC_10'
                'JIS_LC_15'
                'JIS_LC_18'
                'JIS_LC_20'
                'JIS_LC_20A'
                'JIS_LC_30'
                'JIS_LC_8'
                'JIS_LC_8A'
                'JIS_STN_1E'
                'JIS_STN_2.5'
                'JIS_WOOD'
                'LINE'
                'MUDST'
                'NET'
                'NET3'
                'PLAST'
                'PLASTI'
                'SACNCR'
                'SOLID'
                'SQUARE'
                'STARS'
                'STEEL'
                'SWAMP'
                'TRANS'
                'TRIANG'
                'ZIGZAG')
            end
            object edtProfileHatchScale: TEdit
              Left = 328
              Top = 20
              Width = 33
              Height = 21
              TabOrder = 1
            end
          end
          object GroupBox11: TGroupBox
            Left = 8
            Top = 24
            Width = 369
            Height = 49
            Caption = ' '#1090#1088#1086#1090#1091#1072#1088#1086#1074' '
            TabOrder = 2
            object edtSidewalksHatch: TComboBox
              Left = 8
              Top = 20
              Width = 305
              Height = 21
              ItemHeight = 13
              Sorted = True
              TabOrder = 0
              Items.Strings = (
                ''
                'ANGLE'
                'ANSI31'
                'ANSI32'
                'ANSI33'
                'ANSI34'
                'ANSI35'
                'ANSI36'
                'ANSI37'
                'ANSI38'
                'AR-B816'
                'AR-B816'#1057
                'AR-B88'
                'AR-BRELM'
                'AR-BRSTD'
                'AR-CONC'
                'AR-HBONE'
                'AR-PARQ1'
                'AR-RROOF'
                'AR-RSHAKE'
                'AR-SAND'
                'BOX'
                'BRASS'
                'BRICK'
                'BRSTONE'
                'CLAY'
                'CORK'
                'CROSS'
                'DASH'
                'DOLMIT'
                'DOTS'
                'EARTH'
                'ESCHER'
                'FLEX'
                'GOST_GLASS'
                'GOST_GROUND'
                'GOST_WOOD'
                'GRASS'
                'GRATE'
                'GRAVEL'
                'HEX'
                'HONEY'
                'HOUND'
                'INSUL'
                'JIS_LC_10'
                'JIS_LC_15'
                'JIS_LC_18'
                'JIS_LC_20'
                'JIS_LC_20A'
                'JIS_LC_30'
                'JIS_LC_8'
                'JIS_LC_8A'
                'JIS_STN_1E'
                'JIS_STN_2.5'
                'JIS_WOOD'
                'LINE'
                'MUDST'
                'NET'
                'NET3'
                'PLAST'
                'PLASTI'
                'SACNCR'
                'SOLID'
                'SQUARE'
                'STARS'
                'STEEL'
                'SWAMP'
                'TRANS'
                'TRIANG'
                'ZIGZAG')
            end
            object edtSidewalksHatchScale: TEdit
              Left = 328
              Top = 20
              Width = 33
              Height = 21
              TabOrder = 1
            end
          end
        end
        object edtInfoTemplate: TEdit
          Left = 8
          Top = 400
          Width = 89
          Height = 21
          TabOrder = 12
        end
      end
      object TabSheet1: TTabSheet
        Caption = #1090#1072#1073#1083#1080#1094#1072
        object Label1: TLabel
          Left = 168
          Top = 525
          Width = 112
          Height = 13
          Alignment = taRightJustify
          Caption = #1088#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1076#1086' '#1094#1077#1085#1090#1088#1072
        end
        object Label2: TLabel
          Left = 168
          Top = 565
          Width = 75
          Height = 13
          Alignment = taRightJustify
          Caption = #1074#1099#1089#1086#1090#1072' '#1089#1090#1088#1086#1082#1080
        end
        object Label27: TLabel
          Left = 256
          Top = 565
          Width = 115
          Height = 13
          Alignment = taRightJustify
          Caption = #1074#1099#1089#1086#1090#1072' '#1089#1090#1088#1086#1082#1080' '#1075#1088#1072#1092#1080#1082
        end
        object GroupBox2: TGroupBox
          Left = 0
          Top = 153
          Width = 383
          Height = 168
          Align = alTop
          Caption = #1085#1080#1078#1085#1103#1103' '#1090#1072#1073#1083#1080#1094#1072'  ('#1089#1087#1088#1072#1074#1072') '
          TabOrder = 0
          object Label4: TLabel
            Left = 80
            Top = 27
            Width = 50
            Height = 13
            Caption = #1086#1090' '#1086#1089#1077#1074#1086#1081
          end
          object edtLinesBottom: TCSpinEdit
            Left = 16
            Top = 22
            Width = 57
            Height = 22
            MaxValue = 100
            TabOrder = 0
          end
          object listBottomRows: TCheckListBox
            Left = 168
            Top = 16
            Width = 201
            Height = 145
            DragMode = dmAutomatic
            ItemHeight = 13
            Items.Strings = (
              #1090#1080#1087' '#1087#1086#1082#1088#1099#1090#1080#1103
              #1088#1072#1079#1084#1077#1090#1082#1072' '#1086#1089#1077#1074#1072#1103
              #1088#1072#1079#1084#1077#1090#1082#1072' '#1086#1090' '#1086#1089#1077#1074#1086#1081
              #1082#1088#1080#1074#1099#1077' '#1074' '#1087#1083#1072#1085#1077
              #1087#1088#1086#1076#1086#1083#1100#1085#1099#1077' '#1091#1082#1083#1086#1085#1099
              #1076#1086#1088#1086#1078#1085#1099#1077' '#1086#1075#1088#1072#1078#1076#1077#1085#1080#1103' '#1080' '#1085#1072#1087#1088#1072#1074#1083#1103#1102#1097#1080#1077' '#1091#1089#1090#1088'-'#1074#1072
              #1074#1099#1089#1086#1090#1099' '#1085#1072#1089#1099#1087#1080
              #1090#1088#1086#1090#1091#1072#1088#1099
              #1080#1089#1082#1091#1089#1089#1090#1074#1077#1085#1085#1099#1077' '#1089#1086#1086#1088#1091#1078#1077#1085#1080#1103
              #1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1089#1090#1088#1086#1082#1080)
            TabOrder = 1
            OnDragOver = listBottomRowsDragOver
          end
        end
        object GroupBox3: TGroupBox
          Left = 0
          Top = 0
          Width = 383
          Height = 153
          Align = alTop
          Caption = ' '#1074#1077#1088#1093#1085#1103#1103' '#1090#1072#1073#1083#1080#1094#1072' ('#1089#1083#1077#1074#1072') '
          TabOrder = 1
          object Label3: TLabel
            Left = 72
            Top = 27
            Width = 50
            Height = 13
            Caption = #1086#1090' '#1086#1089#1077#1074#1086#1081
          end
          object edtLinesTop: TCSpinEdit
            Left = 8
            Top = 22
            Width = 57
            Height = 22
            MaxValue = 100
            TabOrder = 0
          end
          object chkRuler: TCheckBox
            Left = 8
            Top = 48
            Width = 137
            Height = 17
            Caption = #1083#1080#1085#1077#1081#1082#1072
            TabOrder = 1
          end
          object listTopRows: TCheckListBox
            Left = 168
            Top = 16
            Width = 201
            Height = 129
            DragMode = dmAutomatic
            ItemHeight = 13
            Items.Strings = (
              #1090#1088#1086#1090#1091#1072#1088#1099
              #1074#1099#1089#1086#1090#1099' '#1085#1072#1089#1099#1087#1080
              #1076#1086#1088#1086#1078#1085#1099#1077' '#1086#1075#1088#1072#1078#1076#1077#1085#1080#1103' '#1080' '#1085#1072#1087#1088#1072#1074#1083#1103#1102#1097#1080#1077' '#1091#1089#1090#1088'-'#1074#1072
              #1088#1072#1079#1084#1077#1090#1082#1072' '#1086#1090' '#1086#1089#1077#1074#1086#1081
              #1088#1072#1079#1084#1077#1090#1082#1072' '#1086#1089#1077#1074#1072#1103
              #1087#1088#1086#1076#1086#1083#1100#1085#1099#1081' '#1087#1088#1086#1092#1080#1083#1100
              #1082#1088#1080#1074#1099#1077' '#1074' '#1087#1083#1072#1085#1077
              #1087#1088#1086#1076#1086#1083#1100#1085#1099#1077' '#1091#1082#1083#1086#1085#1099
              #1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1089#1090#1088#1086#1082#1080)
            TabOrder = 2
            OnDragOver = listBottomRowsDragOver
          end
          object chkTopAddRowsWithoutData: TCheckBox
            Left = 8
            Top = 64
            Width = 161
            Height = 17
            Hint = 
              #1045#1089#1083#1080' '#1087#1086#1090#1072#1074#1080#1090#1100' '#1075#1072#1083#1086#1095#1082#1091' '#1076#1072#1085#1085#1099#1077' '#1076#1083#1103' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1093' '#1089#1090#1088#1086#1082' '#1074#1099#1074#1076#1080#1090#1100#1089#1103' ' +
              #1085#1077' '#1073#1091#1076#1091#1090
            Caption = #1076#1086#1087' '#1089#1090#1088#1086#1082#1080': '#1074#1099#1082#1083'. '#1076#1072#1085#1085#1099#1077
            TabOrder = 3
          end
          object chkGraphic: TCheckBox
            Left = 8
            Top = 82
            Width = 153
            Height = 17
            Caption = #1089#1090#1091#1087#1077#1085#1095#1072#1090#1099#1081' '#1075#1088#1072#1092#1080#1082
            TabOrder = 4
          end
        end
        object edtRCenter: TEdit
          Left = 168
          Top = 540
          Width = 57
          Height = 21
          TabOrder = 2
        end
        object edtRowHeight: TEdit
          Left = 168
          Top = 580
          Width = 57
          Height = 21
          TabOrder = 3
        end
        object GroupBox6: TGroupBox
          Left = 0
          Top = 321
          Width = 383
          Height = 200
          Align = alTop
          Caption = ' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1089#1090#1088#1086#1082#1080' '
          TabOrder = 4
          object Label18: TLabel
            Left = 8
            Top = 96
            Width = 183
            Height = 13
            Caption = #1074#1085#1091#1090#1088#1080' '#1084#1086#1075#1091#1090' '#1085#1072#1093#1086#1076#1080#1090#1100#1089#1103' '#1090#1088#1080' '#1087#1072#1087#1082#1080':'
          end
          object Label19: TLabel
            Left = 8
            Top = 160
            Width = 43
            Height = 13
            Caption = #1055#1088#1080#1084#1077#1088':'
          end
          object Label29: TLabel
            Left = 8
            Top = 144
            Width = 300
            Height = 13
            Caption = #1087#1072#1087#1082#1080' '#1089' '#1092#1072#1081#1083#1072#1084#1080' '#1074#1080#1076#1072': ['#1085#1086#1084#1077#1088' '#1089#1090#1088#1086#1082#1080']_['#1079#1072#1075#1086#1083#1086#1074#1086#1082' '#1089#1090#1088#1086#1082#1080']'
          end
          object Label30: TLabel
            Left = 8
            Top = 112
            Width = 287
            Height = 13
            Caption = '>> top '#8212' '#1076#1083#1103' '#1074#1077#1088#1093#1085#1080#1093' '#1089#1090#1088#1086#1082' >> bottom '#8212' '#1076#1083#1103' '#1085#1080#1078#1085#1080#1093' '#1089#1090#1088#1086#1082
          end
          object Label31: TLabel
            Left = 8
            Top = 128
            Width = 196
            Height = 13
            Caption = '>> graphic '#8212' '#1076#1083#1103' '#1089#1090#1091#1087#1077#1085#1095#1072#1090#1086#1075#1086' '#1075#1088#1072#1092#1080#1082#1072
          end
          object Label32: TLabel
            Left = 8
            Top = 176
            Width = 350
            Height = 13
            Caption = 
              #1080#1084#1103' '#1092#1072#1081#1083#1072': 7_'#1085#1072#1089#1099#1087#1100' >> '#1092#1086#1088#1084#1072#1090' '#1076#1072#1085#1085#1099#1093': ['#1085#1072#1095#1072#1083#1086'] ['#1082#1086#1085#1077#1094'] ['#1079#1085#1072#1095#1077#1085#1080#1077 +
              ']'
          end
          object Label33: TLabel
            Left = 272
            Top = 44
            Width = 50
            Height = 13
            Caption = '<< '#1076#1086#1088#1086#1075#1072
          end
          object edtTopAddRows: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
            OnChange = edtTopAddRowsChange
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object btnTopAddRows: TButton
            Left = 336
            Top = 14
            Width = 27
            Height = 25
            Caption = '...'
            TabOrder = 1
            OnClick = btnTopAddRowsClick
          end
          object cmbRoad: TComboBox
            Left = 8
            Top = 40
            Width = 257
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 2
          end
        end
        object GroupBox7: TGroupBox
          Left = 0
          Top = 520
          Width = 161
          Height = 89
          Caption = ' '#1047#1072#1075#1086#1083#1086#1074#1086#1082' '
          TabOrder = 5
          object Label10: TLabel
            Left = 72
            Top = 40
            Width = 30
            Height = 13
            Caption = #1076#1083#1080#1085#1072
          end
          object Label13: TLabel
            Left = 73
            Top = 64
            Width = 77
            Height = 13
            Caption = #1074#1099#1089#1086#1090#1072' '#1090#1077#1082#1089#1090#1072' '
          end
          object chkMakeHeader: TCheckBox
            Left = 8
            Top = 16
            Width = 137
            Height = 17
            Caption = #1074#1099#1074#1086#1076#1080#1090#1100
            TabOrder = 0
          end
          object edtHeaderWidth: TEdit
            Left = 8
            Top = 36
            Width = 57
            Height = 21
            TabOrder = 1
          end
          object edtHeaderTextHeight: TEdit
            Left = 8
            Top = 60
            Width = 57
            Height = 21
            TabOrder = 2
          end
        end
        object edtGrphRowHeight: TEdit
          Left = 256
          Top = 580
          Width = 57
          Height = 21
          TabOrder = 6
        end
      end
    end
    object GroupBox10: TGroupBox
      Left = 1
      Top = 1
      Width = 410
      Height = 48
      Align = alTop
      Caption = ' '#1085#1072#1089#1090#1088#1086#1081#1082#1080' '
      TabOrder = 1
      object Label28: TLabel
        Left = 160
        Top = 23
        Width = 38
        Height = 13
        Caption = #1096#1072#1073#1083#1086#1085
      end
      object Button6: TButton
        Left = 8
        Top = 17
        Width = 105
        Height = 25
        Caption = #1089#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082'...'
        TabOrder = 0
        OnClick = Button6Click
      end
      object edtPath: TComboBox
        Left = 208
        Top = 19
        Width = 193
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'dwt|*.dwt|dwg|*.dwg|All Files|*.*'
    Left = 144
    Top = 48
  end
  object OpenDialog2: TOpenDialog
    Filter = '(ini - '#1092#1072#1081#1083#1099')|*.ini'
    Left = 144
    Top = 80
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'ini'
    Filter = '(ini - '#1092#1072#1081#1083#1099')|*.ini'
    Left = 168
    Top = 80
  end
end
