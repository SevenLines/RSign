object FAutoCADExport: TFAutoCADExport
  Left = 253
  Top = 160
  AutoSize = True
  BorderStyle = bsSingle
  BorderWidth = 1
  Caption = 'AutoCAD'
  ClientHeight = 563
  ClientWidth = 1066
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 277
    Height = 563
    Align = alLeft
    Caption = ' '#1089#1093#1077#1084#1072' '
    TabOrder = 0
    object GroupBox4: TGroupBox
      Left = 2
      Top = 198
      Width = 273
      Height = 129
      Align = alBottom
      Caption = ' '#1048#1089#1090#1086#1095#1085#1080#1082#1080' '#1076#1072#1085#1085#1099#1093' '
      TabOrder = 0
      object Label7: TLabel
        Left = 20
        Top = 20
        Width = 154
        Height = 16
        Caption = #1089#1091#1097#1077#1089#1090#1074#1091#1077#1097#1080#1077' '#1086#1073#1098#1077#1082#1090#1099
      end
      object Label8: TLabel
        Left = 20
        Top = 69
        Width = 163
        Height = 16
        Caption = #1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1077' '#1086#1073#1098#1077#1082#1090#1099
      end
      object cbCurList: TComboBox
        Left = 10
        Top = 39
        Width = 247
        Height = 24
        ItemHeight = 16
        TabOrder = 0
        Text = 'cbCurList'
        OnChange = cbCurListChange
      end
      object cbPrjList: TComboBox
        Left = 10
        Top = 89
        Width = 247
        Height = 24
        ItemHeight = 16
        TabOrder = 1
        Text = 'cbPrjList'
        OnChange = cbPrjListChange
      end
    end
    object GroupBox6: TGroupBox
      Left = 2
      Top = 327
      Width = 273
      Height = 94
      Align = alBottom
      Caption = ' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1089#1090#1088#1086#1082#1080' '
      TabOrder = 1
      object edtTopAddRows: TEdit
        Left = 49
        Top = 20
        Width = 169
        Height = 24
        TabOrder = 0
        OnChange = edtTopAddRowsChange
        OnClick = edtBottomAddRowsClick
        OnDblClick = edtTopAddRowsDblClick
      end
      object btnTopAddRows: TButton
        Left = 226
        Top = 17
        Width = 34
        Height = 31
        Caption = '...'
        TabOrder = 1
        OnClick = btnTopAddRowsClick
      end
      object cmbRoad: TComboBox
        Left = 10
        Top = 54
        Width = 247
        Height = 24
        Style = csDropDownList
        ItemHeight = 16
        TabOrder = 2
      end
      object btnShowInfo: TButton
        Left = 10
        Top = 20
        Width = 31
        Height = 30
        Caption = '?'
        TabOrder = 3
        OnClick = btnShowInfoClick
      end
    end
    object GroupBox5: TGroupBox
      Left = 2
      Top = 421
      Width = 273
      Height = 89
      Align = alBottom
      TabOrder = 2
      object Label14: TLabel
        Left = 10
        Top = 49
        Width = 15
        Height = 16
        Caption = #1086#1090
      end
      object Label17: TLabel
        Left = 217
        Top = 49
        Width = 9
        Height = 16
        Caption = #1084
      end
      object Label15: TLabel
        Left = 118
        Top = 49
        Width = 16
        Height = 16
        Caption = #1076#1086
      end
      object edtStart: TEdit
        Left = 39
        Top = 44
        Width = 71
        Height = 24
        TabOrder = 1
        Text = '-1'
        OnChange = edtStartChange
        OnClick = edtBottomAddRowsClick
        OnDblClick = edtTopAddRowsDblClick
      end
      object chkSection: TCheckBox
        Left = 10
        Top = 17
        Width = 139
        Height = 21
        Caption = #1074#1099#1074#1086#1076#1080#1090#1100' '#1091#1095#1072#1089#1090#1086#1082
        TabOrder = 0
      end
      object edtEnd: TEdit
        Left = 138
        Top = 44
        Width = 70
        Height = 24
        TabOrder = 2
        Text = '-1'
        OnChange = edtStartChange
        OnClick = edtBottomAddRowsClick
        OnDblClick = edtTopAddRowsDblClick
      end
    end
    object Panel5: TPanel
      Left = 2
      Top = 510
      Width = 273
      Height = 51
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 3
      object Button1: TButton
        Left = 167
        Top = 10
        Width = 93
        Height = 31
        Cancel = True
        Caption = #1086#1090#1084#1077#1085#1072
        ModalResult = 2
        TabOrder = 0
      end
      object btnOk: TButton
        Left = 7
        Top = 10
        Width = 93
        Height = 31
        Caption = #1101#1082#1089#1087#1086#1088#1090
        ModalResult = 1
        TabOrder = 1
        OnClick = btnOkClick
      end
    end
    object Panel6: TPanel
      Left = 2
      Top = 18
      Width = 273
      Height = 180
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 4
      object cbIni: TComboBox
        Left = 5
        Top = 10
        Width = 262
        Height = 24
        Style = csDropDownList
        ItemHeight = 16
        TabOrder = 0
        OnChange = cbIniChange
      end
      object rgOut: TRadioGroup
        Left = 5
        Top = 41
        Width = 213
        Height = 88
        Caption = ' '#1074#1099#1074#1086#1076': '
        ItemIndex = 0
        Items.Strings = (
          #1074' '#1072#1082#1090#1080#1074#1085#1099#1081' '#1076#1086#1082#1091#1084#1077#1085#1090
          #1074' '#1085#1086#1074#1099#1081' '#1076#1086#1082#1091#1084#1077#1085#1090)
        TabOrder = 1
      end
      object Button3: TButton
        Left = 223
        Top = 49
        Width = 40
        Height = 80
        Caption = '>>'
        TabOrder = 2
        OnClick = Button3Click
      end
    end
  end
  object pnlLeft: TPanel
    Left = 277
    Top = 0
    Width = 789
    Height = 553
    Caption = 'pnlLeft'
    TabOrder = 1
    Visible = False
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 276
      Height = 551
      Align = alLeft
      Caption = 'Panel3'
      TabOrder = 0
      object Panel2: TPanel
        Left = 4
        Top = 9
        Width = 262
        Height = 360
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'Panel2'
        TabOrder = 0
        object chkLamps: TCheckBox
          Left = 10
          Top = 305
          Width = 80
          Height = 21
          Caption = #1092#1086#1085#1072#1088#1080
          TabOrder = 0
        end
        object chkSidewalks: TCheckBox
          Left = 89
          Top = 305
          Width = 89
          Height = 21
          Caption = #1090#1088#1086#1090#1091#1072#1088#1099
          TabOrder = 1
        end
        object chkBorders: TCheckBox
          Left = 177
          Top = 305
          Width = 80
          Height = 21
          Caption = #1073#1086#1088#1076#1102#1088#1099
          TabOrder = 2
        end
        object chkMoundHeights: TCheckBox
          Left = 10
          Top = 271
          Width = 208
          Height = 21
          Caption = #1074#1099#1089#1086#1090#1072' '#1085#1072#1089#1099#1087#1077#1081
          TabOrder = 3
        end
        object chkCurves: TCheckBox
          Left = 10
          Top = 251
          Width = 208
          Height = 21
          Caption = #1091#1095#1072#1089#1090#1082#1080' '#1082#1088#1080#1074#1099#1093
          TabOrder = 4
        end
        object chkSlope: TCheckBox
          Left = 10
          Top = 231
          Width = 208
          Height = 21
          Caption = #1091#1095#1072#1089#1090#1082#1080' '#1091#1082#1083#1086#1085#1086#1074
          TabOrder = 5
        end
        object chkRoadSideObjects: TCheckBox
          Left = 10
          Top = 212
          Width = 208
          Height = 21
          Caption = #1087#1083#1086#1097#1072#1076#1082#1080' '#1086#1090#1076#1099#1093#1072
          TabOrder = 6
        end
        object chkBusstops: TCheckBox
          Left = 10
          Top = 192
          Width = 178
          Height = 21
          Caption = #1072#1074#1090#1086#1073#1091#1089#1085#1099#1077' '#1086#1089#1090#1072#1085#1086#1074#1082#1080
          TabOrder = 7
        end
        object chkSignal: TCheckBox
          Left = 10
          Top = 172
          Width = 247
          Height = 21
          Caption = #1087#1077#1088#1080#1083#1072' '#1080' '#1089#1090#1086#1083#1073#1080#1082#1080
          TabOrder = 8
        end
        object chkBridges: TCheckBox
          Left = 10
          Top = 153
          Width = 178
          Height = 21
          Caption = #1084#1086#1089#1090#1099
          TabOrder = 9
        end
        object chkMark: TCheckBox
          Left = 10
          Top = 113
          Width = 178
          Height = 21
          Caption = #1088#1072#1079#1084#1077#1090#1082#1072
          TabOrder = 10
        end
        object chkTubes: TCheckBox
          Left = 10
          Top = 133
          Width = 178
          Height = 21
          Caption = #1090#1088#1091#1073#1099
          TabOrder = 11
        end
        object chkRoadSigns: TCheckBox
          Left = 10
          Top = 94
          Width = 178
          Height = 20
          Caption = #1076#1086#1088#1086#1078#1085#1099#1077' '#1079#1085#1072#1082#1080
          TabOrder = 12
        end
        object chkAttachments: TCheckBox
          Left = 10
          Top = 74
          Width = 178
          Height = 21
          Caption = #1087#1088#1080#1084#1099#1082#1072#1085#1080#1103
          TabOrder = 13
        end
        object chkRoadMetrics: TCheckBox
          Left = 10
          Top = 54
          Width = 178
          Height = 21
          Caption = #1084#1077#1090#1088#1080#1082#1072' '#1076#1086#1088#1086#1075#1080
          TabOrder = 14
        end
        object chkTable: TCheckBox
          Left = 10
          Top = 34
          Width = 178
          Height = 21
          Caption = #1090#1072#1073#1083#1080#1094#1072
          TabOrder = 15
        end
        object chkSignalExistToo: TCheckBox
          Left = 158
          Top = 172
          Width = 89
          Height = 21
          Hint = 
            #1090#1072#1082' '#1082#1072#1082' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102' '#1074#1099#1074#1086#1076#1103#1090#1089#1103' '#1090#1086#1083#1100#1082#1086' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1077' '#1089#1090#1086#1083#1073#1080#1082#1080' '#1101#1090#1072 +
            ' '#1075#1072#1083#1086#1095#1082#1072' '#1087#1086#1079#1074#1086#1083#1080#1090' '#1074#1099#1074#1086#1076#1080#1090#1100' '#1080' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1090#1072#1082#1078#1077
          Caption = #1089#1091#1097'. '#1090#1086#1078#1077
          ParentShowHint = False
          ShowHint = True
          TabOrder = 16
        end
        object chkAll: TCheckBox
          Left = 10
          Top = 10
          Width = 237
          Height = 21
          Caption = '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
          TabOrder = 17
          OnClick = chkAllClick
        end
        object chkTrafficLights: TCheckBox
          Left = 10
          Top = 336
          Width = 97
          Height = 17
          Caption = #1089#1074#1077#1090#1086#1092#1086#1088#1099
          TabOrder = 18
        end
        object chkCityObjects: TCheckBox
          Left = 114
          Top = 336
          Width = 119
          Height = 17
          Caption = #1075#1086#1088'. '#1086#1073#1098#1077#1082#1090#1099
          TabOrder = 19
        end
      end
      object Panel1: TPanel
        Left = 4
        Top = 370
        Width = 262
        Height = 100
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 1
        object chkTown: TCheckBox
          Left = 10
          Top = 69
          Width = 149
          Height = 21
          Caption = #1085#1072#1089#1083#1077#1085#1085#1099#1077' '#1087#1091#1085#1082#1090#1099
          TabOrder = 0
        end
        object chkCommunications: TCheckBox
          Left = 128
          Top = 49
          Width = 119
          Height = 21
          Caption = #1082#1086#1084#1084#1091#1085#1080#1082#1072#1094#1080#1080
          TabOrder = 1
        end
        object chkPlan: TCheckBox
          Left = 158
          Top = 69
          Width = 89
          Height = 21
          Caption = #1089#1080#1090#1091#1072#1094#1080#1103
          TabOrder = 2
        end
        object chkProfile: TCheckBox
          Left = 10
          Top = 30
          Width = 208
          Height = 20
          Caption = #1087#1088#1086#1076#1086#1083#1100#1085#1099#1081' '#1087#1088#1086#1092#1080#1083#1100
          TabOrder = 3
        end
        object chkSurface: TCheckBox
          Left = 10
          Top = 49
          Width = 109
          Height = 21
          Caption = #1090#1080#1087' '#1087#1086#1082#1088#1099#1090#1080#1103
          TabOrder = 4
        end
        object chkAllPlan: TCheckBox
          Left = 10
          Top = 5
          Width = 247
          Height = 21
          Caption = '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-'
          TabOrder = 5
          OnClick = chkAllClick
        end
      end
      object GroupBox9: TGroupBox
        Left = 4
        Top = 477
        Width = 262
        Height = 60
        Caption = ' '#1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1072#1103' '#1089#1077#1090#1082#1072' '
        TabOrder = 2
        object Label22: TLabel
          Left = 128
          Top = 30
          Width = 56
          Height = 16
          Caption = #1096#1072#1075' '#1074' '#1089#1084'.'
        end
        object edtGridStep: TEdit
          Left = 30
          Top = 25
          Width = 89
          Height = 24
          TabOrder = 0
          OnClick = edtBottomAddRowsClick
          OnDblClick = edtTopAddRowsDblClick
        end
        object chkGridStep: TCheckBox
          Left = 10
          Top = 27
          Width = 21
          Height = 21
          TabOrder = 1
        end
      end
    end
    object Panel4: TPanel
      Left = 277
      Top = 1
      Width = 511
      Height = 551
      Align = alClient
      Caption = 'Panel4'
      TabOrder = 1
      object GroupBox10: TGroupBox
        Left = 1
        Top = 1
        Width = 509
        Height = 59
        Align = alTop
        Caption = ' '#1085#1072#1089#1090#1088#1086#1081#1082#1080' '
        TabOrder = 0
        object Label28: TLabel
          Left = 197
          Top = 28
          Width = 49
          Height = 16
          Caption = #1096#1072#1073#1083#1086#1085
        end
        object Button6: TButton
          Left = 10
          Top = 21
          Width = 129
          Height = 31
          Caption = #1089#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082'...'
          TabOrder = 0
          OnClick = Button6Click
        end
        object edtPath: TComboBox
          Left = 256
          Top = 23
          Width = 238
          Height = 24
          Style = csDropDownList
          ItemHeight = 16
          TabOrder = 1
        end
      end
      object PageControl1: TPageControl
        Left = 1
        Top = 60
        Width = 509
        Height = 490
        ActivePage = TabSheet2
        Align = alClient
        MultiLine = True
        TabIndex = 0
        TabOrder = 1
        object TabSheet2: TTabSheet
          Caption = #1086#1073#1097#1080#1077
          ImageIndex = 1
          object Label5: TLabel
            Left = 6
            Top = 7
            Width = 181
            Height = 16
            Caption = #1088#1072#1079#1084#1077#1088' '#1087#1086#1076#1087#1080#1089#1077#1081' '#1088#1072#1079#1084#1077#1090#1082#1080
          end
          object Label6: TLabel
            Left = 270
            Top = 7
            Width = 226
            Height = 16
            Caption = #1089#1076#1074#1080#1075' '#1087#1086' '#1086#1089#1080' Y '#1087#1086#1076#1087#1080#1089#1077#1081' '#1088#1072#1079#1084#1077#1090#1082#1080
          end
          object Label20: TLabel
            Left = 6
            Top = 51
            Width = 47
            Height = 16
            Caption = #1096#1072#1075'('#1089#1084')'
          end
          object Label9: TLabel
            Left = 6
            Top = 98
            Width = 285
            Height = 16
            Caption = #1096#1072#1073#1083#1086#1085' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1086#1085#1085#1086#1075#1086' '#1087#1086#1083#1103' '#1087#1088#1080' '#1087#1077#1095#1072#1090#1080
          end
          object Label26: TLabel
            Left = 6
            Top = 191
            Width = 170
            Height = 16
            Caption = #1074#1099#1089#1086#1090#1072' '#1087#1080#1082#1077#1090#1072#1078#1085#1099#1093' '#1084#1077#1090#1086#1082
          end
          object Label24: TLabel
            Left = 6
            Top = 145
            Width = 406
            Height = 16
            Caption = #1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1087#1080#1082#1077#1090#1072#1078' '#1074' '#1090#1072#1073#1083#1080#1094#1077' '#1077#1089#1083#1080' '#1076#1083#1080#1085#1072' '#1091#1095#1072#1089#1090#1082#1072' '#1084#1077#1085#1100#1096#1077
          end
          object Label16: TLabel
            Left = 6
            Top = 237
            Width = 441
            Height = 16
            Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1072#1103' '#1076#1083#1080#1085#1072' '#1101#1083#1077#1084#1077#1085#1090#1072' '#1073#1072#1088#1100#1077#1088#1085#1086#1075#1086' '#1086#1075#1088#1072#1078#1076#1077#1085#1080#1103' ( -1 -- '#1083#1102#1073#1072#1103')'
          end
          object Label18: TLabel
            Left = 6
            Top = 293
            Width = 344
            Height = 16
            Caption = #1055#1088#1077#1092#1080#1082#1089' '#1074' '#1090#1072#1073#1083#1080#1094#1077' '#1076#1083#1103' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1093' '#1086#1075#1088#1072#1078#1076#1077#1085#1080#1081':'
          end
          object edtUnderTextHeight: TEdit
            Left = 10
            Top = 26
            Width = 100
            Height = 24
            TabOrder = 0
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtUnderTextYOffset: TEdit
            Left = 274
            Top = 26
            Width = 100
            Height = 24
            TabOrder = 1
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object chkAuto6_13: TCheckBox
            Left = 2
            Top = 405
            Width = 151
            Height = 21
            Caption = #1089#1076#1074#1080#1075#1072#1090#1100' '#1079#1085#1072#1082' 6.13 '
            Checked = True
            State = cbChecked
            TabOrder = 2
          end
          object chkLeftValueOnly6_13: TCheckBox
            Left = 154
            Top = 405
            Width = 296
            Height = 21
            Caption = #1090#1086#1083#1100#1082#1086' '#1082#1080#1083#1086#1084#1077#1090#1088#1072#1078' '#1076#1086' '#1095#1077#1088#1090#1099' ('#1079#1085#1072#1082' 6.13)'
            Checked = True
            State = cbChecked
            TabOrder = 3
          end
          object edtStep: TEdit
            Left = 10
            Top = 70
            Width = 100
            Height = 24
            TabOrder = 4
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtInfoTemplate: TEdit
            Left = 10
            Top = 115
            Width = 109
            Height = 24
            TabOrder = 5
          end
          object edtSmallGridMarkHeight: TEdit
            Left = 10
            Top = 207
            Width = 109
            Height = 24
            TabOrder = 6
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtUseVerticalTextIfLess: TEdit
            Left = 10
            Top = 164
            Width = 109
            Height = 24
            TabOrder = 7
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtMinBarrierSegmentLength: TEdit
            Left = 10
            Top = 257
            Width = 109
            Height = 24
            TabOrder = 8
          end
          object chkHideAutoCAD: TCheckBox
            Left = 266
            Top = 430
            Width = 208
            Height = 21
            Caption = #1089#1082#1088#1099#1074#1072#1090#1100' AutoCAD'
            TabOrder = 9
          end
          object chkShowAttachmentComments: TCheckBox
            Left = 0
            Top = 432
            Width = 257
            Height = 17
            Caption = #1042#1099#1074#1086#1076#1080#1090#1100' '#1082#1086#1084#1077#1085#1090#1072#1088#1080#1080' '#1087#1088#1080#1084#1099#1082#1072#1085#1080#1081
            TabOrder = 10
          end
          object edtProjectBarrierPrefix: TEdit
            Left = 360
            Top = 289
            Width = 121
            Height = 24
            TabOrder = 11
          end
        end
        object TabSheet1: TTabSheet
          Caption = #1089#1090#1088#1086#1082#1080
          object GroupBox2: TGroupBox
            Left = 0
            Top = 188
            Width = 501
            Height = 207
            Align = alTop
            Caption = #1085#1080#1078#1085#1103#1103' '#1090#1072#1073#1083#1080#1094#1072'  ('#1089#1087#1088#1072#1074#1072') '
            TabOrder = 0
            object Label4: TLabel
              Left = 98
              Top = 33
              Width = 65
              Height = 16
              Caption = #1086#1090' '#1086#1089#1077#1074#1086#1081
            end
            object edtLinesBottom: TCSpinEdit
              Left = 20
              Top = 27
              Width = 70
              Height = 26
              MaxValue = 100
              TabOrder = 0
            end
            object listBottomRows: TCheckListBox
              Left = 207
              Top = 20
              Width = 247
              Height = 178
              DragMode = dmAutomatic
              ItemHeight = 16
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
            Width = 501
            Height = 188
            Align = alTop
            Caption = ' '#1074#1077#1088#1093#1085#1103#1103' '#1090#1072#1073#1083#1080#1094#1072' ('#1089#1083#1077#1074#1072') '
            TabOrder = 1
            object Label3: TLabel
              Left = 89
              Top = 33
              Width = 65
              Height = 16
              Caption = #1086#1090' '#1086#1089#1077#1074#1086#1081
            end
            object edtLinesTop: TCSpinEdit
              Left = 10
              Top = 27
              Width = 70
              Height = 26
              MaxValue = 100
              TabOrder = 0
            end
            object chkRuler: TCheckBox
              Left = 10
              Top = 59
              Width = 168
              Height = 21
              Caption = #1083#1080#1085#1077#1081#1082#1072
              TabOrder = 1
            end
            object listTopRows: TCheckListBox
              Left = 207
              Top = 20
              Width = 247
              Height = 158
              DragMode = dmAutomatic
              ItemHeight = 16
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
              Left = 10
              Top = 79
              Width = 198
              Height = 21
              Hint = 
                #1045#1089#1083#1080' '#1087#1086#1090#1072#1074#1080#1090#1100' '#1075#1072#1083#1086#1095#1082#1091' '#1076#1072#1085#1085#1099#1077' '#1076#1083#1103' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1093' '#1089#1090#1088#1086#1082' '#1074#1099#1074#1076#1080#1090#1100#1089#1103' ' +
                #1085#1077' '#1073#1091#1076#1091#1090
              Caption = #1076#1086#1087' '#1089#1090#1088#1086#1082#1080': '#1074#1099#1082#1083'. '#1076#1072#1085#1085#1099#1077
              TabOrder = 3
            end
            object chkGraphic: TCheckBox
              Left = 10
              Top = 101
              Width = 188
              Height = 21
              Caption = #1089#1090#1091#1087#1077#1085#1095#1072#1090#1099#1081' '#1075#1088#1072#1092#1080#1082
              TabOrder = 4
            end
          end
        end
        object TabSheet3: TTabSheet
          Caption = #1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
          ImageIndex = 2
          object Label27: TLabel
            Left = 261
            Top = 85
            Width = 146
            Height = 16
            Alignment = taRightJustify
            Caption = #1074#1099#1089#1086#1090#1072' '#1089#1090#1088#1086#1082#1080' '#1075#1088#1072#1092#1080#1082
          end
          object Label2: TLabel
            Left = 263
            Top = 55
            Width = 95
            Height = 16
            Alignment = taRightJustify
            Caption = #1074#1099#1089#1086#1090#1072' '#1089#1090#1088#1086#1082#1080
          end
          object Label1: TLabel
            Left = 259
            Top = 26
            Width = 145
            Height = 16
            Alignment = taRightJustify
            Caption = #1088#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1076#1086' '#1094#1077#1085#1090#1088#1072
          end
          object Label12: TLabel
            Left = 9
            Top = 143
            Width = 201
            Height = 16
            Caption = #1082#1086#1076#1099' '#1094#1074#1077#1090#1086#1074' '#1089#1084#1086#1090#1088#1080' '#1074' AutoCAD'
          end
          object Label11: TLabel
            Left = 0
            Top = 123
            Width = 244
            Height = 16
            Caption = #1094#1074#1077#1090' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1086#1075#1086' '#1086#1073#1098#1077#1082#1090#1072' (0-256)'
          end
          object Label21: TLabel
            Left = 89
            Top = 172
            Width = 151
            Height = 16
            Caption = #1089#1082#1072#1083#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1086' '#1086#1089#1080' Y'
          end
          object Label23: TLabel
            Left = 69
            Top = 202
            Width = 168
            Height = 16
            Caption = #1089#1088#1077#1076#1085#1085#1103' '#1096#1080#1088#1080#1085#1072'  '#1089#1080#1084#1074#1086#1083#1072
          end
          object GroupBox7: TGroupBox
            Left = 0
            Top = 7
            Width = 218
            Height = 110
            Caption = ' '#1047#1072#1075#1086#1083#1086#1074#1086#1082' '
            TabOrder = 0
            object Label10: TLabel
              Left = 89
              Top = 49
              Width = 40
              Height = 16
              Caption = #1076#1083#1080#1085#1072
            end
            object Label13: TLabel
              Left = 90
              Top = 79
              Width = 97
              Height = 16
              Caption = #1074#1099#1089#1086#1090#1072' '#1090#1077#1082#1089#1090#1072' '
            end
            object chkMakeHeader: TCheckBox
              Left = 10
              Top = 20
              Width = 168
              Height = 21
              Caption = #1074#1099#1074#1086#1076#1080#1090#1100
              TabOrder = 0
            end
            object edtHeaderWidth: TEdit
              Left = 10
              Top = 44
              Width = 70
              Height = 24
              TabOrder = 1
            end
            object edtHeaderTextHeight: TEdit
              Left = 10
              Top = 74
              Width = 70
              Height = 24
              TabOrder = 2
            end
          end
          object edtRowHeight: TEdit
            Left = 414
            Top = 52
            Width = 70
            Height = 24
            TabOrder = 1
          end
          object edtGrphRowHeight: TEdit
            Left = 414
            Top = 81
            Width = 70
            Height = 24
            TabOrder = 2
          end
          object edtRCenter: TEdit
            Left = 414
            Top = 25
            Width = 70
            Height = 24
            TabOrder = 3
          end
          object GroupBox13: TGroupBox
            Left = 0
            Top = 260
            Width = 501
            Height = 199
            Align = alBottom
            Caption = ' '#1064#1090#1088#1080#1093#1086#1092#1082#1072' '
            TabOrder = 4
            object GroupBox12: TGroupBox
              Left = 10
              Top = 138
              Width = 484
              Height = 60
              Caption = ' '#1087#1091#1089#1090#1099#1093' '#1091#1095#1072#1089#1090#1082#1086#1074' '#1090#1072#1073#1083#1080#1094#1099' '
              TabOrder = 0
              object edtTableHatch: TComboBox
                Left = 10
                Top = 25
                Width = 415
                Height = 24
                ItemHeight = 16
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
                Left = 433
                Top = 25
                Width = 41
                Height = 24
                TabOrder = 1
              end
            end
            object GroupBox8: TGroupBox
              Left = 10
              Top = 79
              Width = 484
              Height = 60
              Caption = ' '#1087#1088#1086#1076#1086#1083#1100#1085#1086#1075#1086' '#1087#1088#1086#1092#1080#1083#1103' '
              TabOrder = 1
              object edtProfileHatch: TComboBox
                Left = 10
                Top = 25
                Width = 415
                Height = 24
                ItemHeight = 16
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
                Left = 433
                Top = 25
                Width = 41
                Height = 24
                TabOrder = 1
              end
            end
            object GroupBox11: TGroupBox
              Left = 10
              Top = 20
              Width = 484
              Height = 60
              Caption = ' '#1090#1088#1086#1090#1091#1072#1088#1086#1074' '
              TabOrder = 2
              object edtSidewalksHatch: TComboBox
                Left = 10
                Top = 25
                Width = 415
                Height = 24
                ItemHeight = 16
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
                Left = 433
                Top = 25
                Width = 41
                Height = 24
                TabOrder = 1
              end
            end
          end
          object edtNotExistsColor: TEdit
            Left = 256
            Top = 128
            Width = 228
            Height = 24
            TabOrder = 5
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtScaleY: TEdit
            Left = 256
            Top = 167
            Width = 228
            Height = 24
            TabOrder = 6
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtAutoShrinkOneLetterWidth: TEdit
            Left = 256
            Top = 197
            Width = 228
            Height = 24
            TabOrder = 7
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
        end
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'dwt|*.dwt|dwg|*.dwg|All Files|*.*'
    Left = 232
    Top = 440
  end
  object OpenDialog2: TOpenDialog
    Filter = '(ini - '#1092#1072#1081#1083#1099')|*.ini'
    Left = 232
    Top = 472
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'ini'
    Filter = '(ini - '#1092#1072#1081#1083#1099')|*.ini'
    Left = 256
    Top = 472
  end
end
