object FAutoCADExport: TFAutoCADExport
  Left = 253
  Top = 160
  AutoSize = True
  BorderStyle = bsSingle
  BorderWidth = 1
  Caption = 'AutoCAD'
  ClientHeight = 426
  ClientWidth = 866
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
    Height = 426
    Align = alLeft
    Caption = ' '#1089#1093#1077#1084#1072' '
    TabOrder = 0
    object GroupBox4: TGroupBox
      Left = 2
      Top = 129
      Width = 221
      Height = 105
      Align = alBottom
      Caption = ' '#1048#1089#1090#1086#1095#1085#1080#1082#1080' '#1076#1072#1085#1085#1099#1093' '
      TabOrder = 0
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
    object GroupBox6: TGroupBox
      Left = 2
      Top = 234
      Width = 221
      Height = 76
      Align = alBottom
      Caption = ' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1089#1090#1088#1086#1082#1080' '
      TabOrder = 1
      object Label33: TLabel
        Left = 160
        Top = 48
        Width = 50
        Height = 13
        Caption = '<< '#1076#1086#1088#1086#1075#1072
      end
      object edtTopAddRows: TEdit
        Left = 40
        Top = 16
        Width = 137
        Height = 21
        TabOrder = 0
        OnChange = edtTopAddRowsChange
        OnClick = edtBottomAddRowsClick
        OnDblClick = edtTopAddRowsDblClick
      end
      object btnTopAddRows: TButton
        Left = 184
        Top = 14
        Width = 27
        Height = 25
        Caption = '...'
        TabOrder = 1
        OnClick = btnTopAddRowsClick
      end
      object cmbRoad: TComboBox
        Left = 8
        Top = 44
        Width = 145
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
      end
      object btnShowInfo: TButton
        Left = 8
        Top = 16
        Width = 25
        Height = 25
        Caption = '?'
        TabOrder = 3
        OnClick = btnShowInfoClick
      end
    end
    object GroupBox5: TGroupBox
      Left = 2
      Top = 310
      Width = 221
      Height = 73
      Align = alBottom
      TabOrder = 2
      object Label14: TLabel
        Left = 8
        Top = 40
        Width = 11
        Height = 13
        Caption = #1086#1090
      end
      object Label17: TLabel
        Left = 176
        Top = 40
        Width = 8
        Height = 13
        Caption = #1084
      end
      object Label15: TLabel
        Left = 96
        Top = 40
        Width = 12
        Height = 13
        Caption = #1076#1086
      end
      object edtStart: TEdit
        Left = 32
        Top = 36
        Width = 57
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
        Left = 112
        Top = 36
        Width = 57
        Height = 21
        TabOrder = 2
        Text = '-1'
        OnChange = edtStartChange
        OnClick = edtBottomAddRowsClick
        OnDblClick = edtTopAddRowsDblClick
      end
    end
    object Panel5: TPanel
      Left = 2
      Top = 383
      Width = 221
      Height = 41
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 3
      object Button1: TButton
        Left = 136
        Top = 8
        Width = 75
        Height = 25
        Cancel = True
        Caption = #1086#1090#1084#1077#1085#1072
        ModalResult = 2
        TabOrder = 0
      end
      object btnOk: TButton
        Left = 6
        Top = 8
        Width = 75
        Height = 25
        Caption = #1101#1082#1089#1087#1086#1088#1090
        ModalResult = 1
        TabOrder = 1
        OnClick = btnOkClick
      end
    end
    object Panel6: TPanel
      Left = 2
      Top = 15
      Width = 221
      Height = 114
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 4
      object cbIni: TComboBox
        Left = 4
        Top = 8
        Width = 213
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbIniChange
      end
      object rgOut: TRadioGroup
        Left = 4
        Top = 33
        Width = 173
        Height = 72
        Caption = ' '#1074#1099#1074#1086#1076': '
        ItemIndex = 0
        Items.Strings = (
          #1074' '#1072#1082#1090#1080#1074#1085#1099#1081' '#1076#1086#1082#1091#1084#1077#1085#1090
          #1074' '#1085#1086#1074#1099#1081' '#1076#1086#1082#1091#1084#1077#1085#1090)
        TabOrder = 1
      end
      object Button3: TButton
        Left = 181
        Top = 40
        Width = 33
        Height = 65
        Caption = '>>'
        TabOrder = 2
        OnClick = Button3Click
      end
    end
  end
  object pnlLeft: TPanel
    Left = 225
    Top = 0
    Width = 641
    Height = 426
    Caption = 'pnlLeft'
    TabOrder = 1
    Visible = False
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 224
      Height = 424
      Align = alLeft
      Caption = 'Panel3'
      TabOrder = 0
      object Panel2: TPanel
        Left = 3
        Top = 7
        Width = 213
        Height = 273
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'Panel2'
        TabOrder = 0
        object chkLamps: TCheckBox
          Left = 8
          Top = 248
          Width = 65
          Height = 17
          Caption = #1092#1086#1085#1072#1088#1080
          TabOrder = 0
        end
        object chkSidewalks: TCheckBox
          Left = 72
          Top = 248
          Width = 73
          Height = 17
          Caption = #1090#1088#1086#1090#1091#1072#1088#1099
          TabOrder = 1
        end
        object chkBorders: TCheckBox
          Left = 144
          Top = 248
          Width = 65
          Height = 17
          Caption = #1073#1086#1088#1076#1102#1088#1099
          TabOrder = 2
        end
        object chkMoundHeights: TCheckBox
          Left = 8
          Top = 220
          Width = 169
          Height = 17
          Caption = #1074#1099#1089#1086#1090#1072' '#1085#1072#1089#1099#1087#1077#1081
          TabOrder = 3
        end
        object chkCurves: TCheckBox
          Left = 8
          Top = 204
          Width = 169
          Height = 17
          Caption = #1091#1095#1072#1089#1090#1082#1080' '#1082#1088#1080#1074#1099#1093
          TabOrder = 4
        end
        object chkSlope: TCheckBox
          Left = 8
          Top = 188
          Width = 169
          Height = 17
          Caption = #1091#1095#1072#1089#1090#1082#1080' '#1091#1082#1083#1086#1085#1086#1074
          TabOrder = 5
        end
        object chkRoadSideObjects: TCheckBox
          Left = 8
          Top = 172
          Width = 169
          Height = 17
          Caption = #1087#1083#1086#1097#1072#1076#1082#1080' '#1086#1090#1076#1099#1093#1072
          TabOrder = 6
        end
        object chkBusstops: TCheckBox
          Left = 8
          Top = 156
          Width = 145
          Height = 17
          Caption = #1072#1074#1090#1086#1073#1091#1089#1085#1099#1077' '#1086#1089#1090#1072#1085#1086#1074#1082#1080
          TabOrder = 7
        end
        object chkSignal: TCheckBox
          Left = 8
          Top = 140
          Width = 201
          Height = 17
          Caption = #1087#1077#1088#1080#1083#1072' '#1080' '#1089#1090#1086#1083#1073#1080#1082#1080
          TabOrder = 8
        end
        object chkBridges: TCheckBox
          Left = 8
          Top = 124
          Width = 145
          Height = 17
          Caption = #1084#1086#1089#1090#1099
          TabOrder = 9
        end
        object chkMark: TCheckBox
          Left = 8
          Top = 92
          Width = 145
          Height = 17
          Caption = #1088#1072#1079#1084#1077#1090#1082#1072
          TabOrder = 10
        end
        object chkTubes: TCheckBox
          Left = 8
          Top = 108
          Width = 145
          Height = 17
          Caption = #1090#1088#1091#1073#1099
          TabOrder = 11
        end
        object chkRoadSigns: TCheckBox
          Left = 8
          Top = 76
          Width = 145
          Height = 17
          Caption = #1076#1086#1088#1086#1078#1085#1099#1077' '#1079#1085#1072#1082#1080
          TabOrder = 12
        end
        object chkAttachments: TCheckBox
          Left = 8
          Top = 60
          Width = 145
          Height = 17
          Caption = #1087#1088#1080#1084#1099#1082#1072#1085#1080#1103
          TabOrder = 13
        end
        object chkRoadMetrics: TCheckBox
          Left = 8
          Top = 44
          Width = 145
          Height = 17
          Caption = #1084#1077#1090#1088#1080#1082#1072' '#1076#1086#1088#1086#1075#1080
          TabOrder = 14
        end
        object chkTable: TCheckBox
          Left = 8
          Top = 28
          Width = 145
          Height = 17
          Caption = #1090#1072#1073#1083#1080#1094#1072
          TabOrder = 15
        end
        object chkSignalExistToo: TCheckBox
          Left = 128
          Top = 140
          Width = 73
          Height = 17
          Hint = 
            #1090#1072#1082' '#1082#1072#1082' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102' '#1074#1099#1074#1086#1076#1103#1090#1089#1103' '#1090#1086#1083#1100#1082#1086' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1099#1077' '#1089#1090#1086#1083#1073#1080#1082#1080' '#1101#1090#1072 +
            ' '#1075#1072#1083#1086#1095#1082#1072' '#1087#1086#1079#1074#1086#1083#1080#1090' '#1074#1099#1074#1086#1076#1080#1090#1100' '#1080' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1090#1072#1082#1078#1077
          Caption = #1089#1091#1097'. '#1090#1086#1078#1077
          ParentShowHint = False
          ShowHint = True
          TabOrder = 16
        end
        object chkAll: TCheckBox
          Left = 8
          Top = 8
          Width = 193
          Height = 17
          Caption = '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
          TabOrder = 17
          OnClick = chkAllClick
        end
      end
      object Panel1: TPanel
        Left = 3
        Top = 288
        Width = 213
        Height = 81
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 1
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
      object GroupBox9: TGroupBox
        Left = 3
        Top = 368
        Width = 213
        Height = 49
        Caption = ' '#1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1072#1103' '#1089#1077#1090#1082#1072' '
        TabOrder = 2
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
    end
    object Panel4: TPanel
      Left = 225
      Top = 1
      Width = 415
      Height = 424
      Align = alClient
      Caption = 'Panel4'
      TabOrder = 1
      object GroupBox10: TGroupBox
        Left = 1
        Top = 1
        Width = 413
        Height = 48
        Align = alTop
        Caption = ' '#1085#1072#1089#1090#1088#1086#1081#1082#1080' '
        TabOrder = 0
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
      object PageControl1: TPageControl
        Left = 1
        Top = 49
        Width = 413
        Height = 374
        ActivePage = TabSheet2
        Align = alClient
        MultiLine = True
        TabIndex = 0
        TabOrder = 1
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
          object Label20: TLabel
            Left = 96
            Top = 100
            Width = 39
            Height = 13
            Caption = #1096#1072#1075'('#1089#1084')'
          end
          object Label9: TLabel
            Left = 8
            Top = 132
            Width = 219
            Height = 13
            Caption = #1096#1072#1073#1083#1086#1085' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1086#1085#1085#1086#1075#1086' '#1087#1086#1083#1103' '#1087#1088#1080' '#1087#1077#1095#1072#1090#1080
          end
          object Label26: TLabel
            Left = 8
            Top = 220
            Width = 136
            Height = 13
            Caption = #1074#1099#1089#1086#1090#1072' '#1087#1080#1082#1077#1090#1072#1078#1085#1099#1093' '#1084#1077#1090#1086#1082
          end
          object Label24: TLabel
            Left = 8
            Top = 176
            Width = 317
            Height = 13
            Caption = #1074#1077#1088#1090#1080#1082#1072#1083#1100#1085#1099#1081' '#1087#1080#1082#1077#1090#1072#1078' '#1074' '#1090#1072#1073#1083#1080#1094#1077' '#1077#1089#1083#1080' '#1076#1083#1080#1085#1072' '#1091#1095#1072#1089#1090#1082#1072' '#1084#1077#1085#1100#1096#1077
          end
          object Label16: TLabel
            Left = 8
            Top = 264
            Width = 278
            Height = 13
            Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1072#1103' '#1088#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1084#1077#1078#1076#1091' '#1090#1086#1095#1082#1072#1084#1080' '#1086#1075#1088#1072#1078#1076#1077#1085#1080#1081
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
          object edtStep: TEdit
            Left = 8
            Top = 96
            Width = 81
            Height = 21
            TabOrder = 4
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtInfoTemplate: TEdit
            Left = 8
            Top = 152
            Width = 89
            Height = 21
            TabOrder = 5
          end
          object edtSmallGridMarkHeight: TEdit
            Left = 8
            Top = 240
            Width = 89
            Height = 21
            TabOrder = 6
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtUseVerticalTextIfLess: TEdit
            Left = 8
            Top = 192
            Width = 89
            Height = 21
            TabOrder = 7
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtMinBarrierSegmentLength: TEdit
            Left = 8
            Top = 280
            Width = 89
            Height = 21
            TabOrder = 8
          end
          object chkHideAutoCAD: TCheckBox
            Left = 8
            Top = 320
            Width = 169
            Height = 17
            Caption = #1089#1082#1088#1099#1074#1072#1090#1100' AutoCAD'
            TabOrder = 9
          end
        end
        object TabSheet1: TTabSheet
          Caption = #1089#1090#1088#1086#1082#1080
          object GroupBox2: TGroupBox
            Left = 0
            Top = 153
            Width = 405
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
            Width = 405
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
        end
        object TabSheet3: TTabSheet
          Caption = #1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
          ImageIndex = 2
          object Label27: TLabel
            Left = 216
            Top = 69
            Width = 115
            Height = 13
            Alignment = taRightJustify
            Caption = #1074#1099#1089#1086#1090#1072' '#1089#1090#1088#1086#1082#1080' '#1075#1088#1072#1092#1080#1082
          end
          object Label2: TLabel
            Left = 216
            Top = 45
            Width = 75
            Height = 13
            Alignment = taRightJustify
            Caption = #1074#1099#1089#1086#1090#1072' '#1089#1090#1088#1086#1082#1080
          end
          object Label1: TLabel
            Left = 216
            Top = 21
            Width = 112
            Height = 13
            Alignment = taRightJustify
            Caption = #1088#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1076#1086' '#1094#1077#1085#1090#1088#1072
          end
          object Label12: TLabel
            Left = 7
            Top = 116
            Width = 160
            Height = 13
            Caption = #1082#1086#1076#1099' '#1094#1074#1077#1090#1086#1074' '#1089#1084#1086#1090#1088#1080' '#1074' AutoCAD'
          end
          object Label11: TLabel
            Left = 0
            Top = 100
            Width = 190
            Height = 13
            Caption = #1094#1074#1077#1090' '#1087#1088#1086#1077#1082#1090#1080#1088#1091#1077#1084#1086#1075#1086' '#1086#1073#1098#1077#1082#1090#1072' (0-256)'
          end
          object Label21: TLabel
            Left = 72
            Top = 140
            Width = 118
            Height = 13
            Caption = #1089#1082#1072#1083#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1086' '#1086#1089#1080' Y'
          end
          object Label23: TLabel
            Left = 56
            Top = 164
            Width = 133
            Height = 13
            Caption = #1089#1088#1077#1076#1085#1085#1103' '#1096#1080#1088#1080#1085#1072'  '#1089#1080#1084#1074#1086#1083#1072
          end
          object GroupBox7: TGroupBox
            Left = 0
            Top = 6
            Width = 177
            Height = 89
            Caption = ' '#1047#1072#1075#1086#1083#1086#1074#1086#1082' '
            TabOrder = 0
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
          object edtRowHeight: TEdit
            Left = 336
            Top = 42
            Width = 57
            Height = 21
            TabOrder = 1
          end
          object edtGrphRowHeight: TEdit
            Left = 336
            Top = 66
            Width = 57
            Height = 21
            TabOrder = 2
          end
          object edtRCenter: TEdit
            Left = 336
            Top = 20
            Width = 57
            Height = 21
            TabOrder = 3
          end
          object GroupBox13: TGroupBox
            Left = 0
            Top = 184
            Width = 405
            Height = 162
            Align = alBottom
            Caption = ' '#1064#1090#1088#1080#1093#1086#1092#1082#1072' '
            TabOrder = 4
            object GroupBox12: TGroupBox
              Left = 8
              Top = 112
              Width = 393
              Height = 49
              Caption = ' '#1087#1091#1089#1090#1099#1093' '#1091#1095#1072#1089#1090#1082#1086#1074' '#1090#1072#1073#1083#1080#1094#1099' '
              TabOrder = 0
              object edtTableHatch: TComboBox
                Left = 8
                Top = 20
                Width = 337
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
                Left = 352
                Top = 20
                Width = 33
                Height = 21
                TabOrder = 1
              end
            end
            object GroupBox8: TGroupBox
              Left = 8
              Top = 64
              Width = 393
              Height = 49
              Caption = ' '#1087#1088#1086#1076#1086#1083#1100#1085#1086#1075#1086' '#1087#1088#1086#1092#1080#1083#1103' '
              TabOrder = 1
              object edtProfileHatch: TComboBox
                Left = 8
                Top = 20
                Width = 337
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
                Left = 352
                Top = 20
                Width = 33
                Height = 21
                TabOrder = 1
              end
            end
            object GroupBox11: TGroupBox
              Left = 8
              Top = 16
              Width = 393
              Height = 49
              Caption = ' '#1090#1088#1086#1090#1091#1072#1088#1086#1074' '
              TabOrder = 2
              object edtSidewalksHatch: TComboBox
                Left = 8
                Top = 20
                Width = 337
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
                Left = 352
                Top = 20
                Width = 33
                Height = 21
                TabOrder = 1
              end
            end
          end
          object edtNotExistsColor: TEdit
            Left = 208
            Top = 104
            Width = 185
            Height = 21
            TabOrder = 5
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtScaleY: TEdit
            Left = 208
            Top = 136
            Width = 185
            Height = 21
            TabOrder = 6
            OnClick = edtBottomAddRowsClick
            OnDblClick = edtTopAddRowsDblClick
          end
          object edtAutoShrinkOneLetterWidth: TEdit
            Left = 208
            Top = 160
            Width = 185
            Height = 21
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
