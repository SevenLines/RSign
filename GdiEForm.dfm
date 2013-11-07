object MainForm: TMainForm
  Left = 225
  Top = 312
  Width = 826
  Height = 595
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1085#1072#1089#1090#1088#1086#1077#1082
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 818
    Height = 541
    ActivePage = TabSheet2
    Align = alClient
    TabIndex = 2
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1054#1073#1098#1077#1082#1090#1099' '#1080' '#1093#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080
      object Splitter1: TSplitter
        Left = 196
        Top = 0
        Width = 6
        Height = 513
        Cursor = crHSplit
      end
      object Splitter2: TSplitter
        Left = 410
        Top = 0
        Width = 7
        Height = 513
        Cursor = crHSplit
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 196
        Height = 513
        Align = alLeft
        Caption = #1057#1087#1080#1089#1086#1082' '#1086#1073#1098#1077#1082#1090#1086#1074
        TabOrder = 0
        object ObjTree: TTreeView
          Left = 2
          Top = 15
          Width = 192
          Height = 496
          Align = alClient
          HideSelection = False
          Indent = 19
          TabOrder = 0
          OnChange = ObjTreeChange
        end
      end
      object GroupBox2: TGroupBox
        Left = 202
        Top = 0
        Width = 208
        Height = 513
        Align = alLeft
        Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1087#1086' '#1086#1073#1098#1077#1082#1090#1091
        TabOrder = 1
        DesignSize = (
          208
          513)
        object Label1: TLabel
          Left = 13
          Top = 59
          Width = 78
          Height = 13
          Caption = #1041#1072#1079#1086#1074#1099#1081' '#1082#1083#1072#1089#1089
        end
        object Label2: TLabel
          Left = 13
          Top = 20
          Width = 50
          Height = 13
          Caption = #1053#1072#1079#1074#1072#1085#1080#1077
        end
        object Label3: TLabel
          Left = 13
          Top = 98
          Width = 79
          Height = 13
          Caption = #1060#1083#1072#1075#1080' '#1086#1073#1098#1077#1082#1090#1072
        end
        object Label4: TLabel
          Left = 13
          Top = 177
          Width = 161
          Height = 13
          Caption = #1054#1090#1086#1073#1088#1072#1078#1072#1077#1084#1072#1103' '#1093#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1072
        end
        object Label5: TLabel
          Left = 13
          Top = 216
          Width = 128
          Height = 13
          Caption = #1061#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080' '#1086#1073#1098#1077#1082#1090#1072
        end
        object Label11: TLabel
          Left = 13
          Top = 136
          Width = 94
          Height = 13
          Caption = #1054#1089#1085#1086#1074#1085#1072#1103' '#1090#1072#1073#1083#1080#1094#1072
        end
        object ClassList: TComboBox
          Left = 13
          Top = 72
          Width = 183
          Height = 21
          Style = csDropDownList
          Anchors = [akLeft, akTop, akRight]
          ItemHeight = 0
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          OnChange = ClassListChange
        end
        object ObjName: TEdit
          Left = 13
          Top = 33
          Width = 183
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 1
        end
        object ObjFlags: TEdit
          Left = 13
          Top = 111
          Width = 183
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 2
        end
        object MainChar: TComboBox
          Left = 13
          Top = 190
          Width = 183
          Height = 21
          Style = csDropDownList
          Anchors = [akLeft, akTop, akRight]
          ItemHeight = 0
          TabOrder = 3
        end
        object CharList: TCheckListBox
          Left = 13
          Top = 232
          Width = 183
          Height = 212
          Anchors = [akLeft, akTop, akRight, akBottom]
          ItemHeight = 13
          TabOrder = 4
        end
        object Button1: TButton
          Left = 32
          Top = 450
          Width = 145
          Height = 25
          Anchors = [akLeft, akRight, akBottom]
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
          TabOrder = 5
          OnClick = Button1Click
        end
        object Button4: TButton
          Left = 32
          Top = 480
          Width = 145
          Height = 25
          Anchors = [akLeft, akTop, akRight]
          Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1079#1072#1087#1088#1086#1089#1099
          TabOrder = 6
          OnClick = Button4Click
        end
        object MainTable: TEdit
          Left = 13
          Top = 149
          Width = 183
          Height = 21
          TabOrder = 7
        end
      end
      object GroupBox3: TGroupBox
        Left = 417
        Top = 0
        Width = 393
        Height = 513
        Align = alClient
        Caption = #1044#1086#1089#1090#1091#1087#1085#1099#1077' '#1093#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080
        TabOrder = 2
        object PropList: TListBox
          Left = 2
          Top = 15
          Width = 389
          Height = 504
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
          OnDblClick = PropListDblClick
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1061#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080
      ImageIndex = 2
      DesignSize = (
        810
        513)
      object GroupBox7: TGroupBox
        Left = 407
        Top = 7
        Width = 353
        Height = 426
        Anchors = [akTop, akRight]
        Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077
        TabOrder = 0
        object Label6: TLabel
          Left = 13
          Top = 20
          Width = 50
          Height = 13
          Caption = #1053#1072#1079#1074#1072#1085#1080#1077
        end
        object Label7: TLabel
          Left = 13
          Top = 59
          Width = 121
          Height = 13
          Caption = #1057#1086#1082#1088#1072#1097#1077#1085#1085#1086#1077' '#1085#1072#1079#1074#1072#1085#1080#1077
        end
        object Label8: TLabel
          Left = 13
          Top = 138
          Width = 111
          Height = 13
          Caption = #1048#1084#1103' '#1089#1074#1086#1081#1089#1090#1074#1072' '#1082#1083#1072#1089#1089#1072
        end
        object Label9: TLabel
          Left = 13
          Top = 177
          Width = 59
          Height = 13
          Caption = #1058#1080#1087' '#1076#1072#1085#1085#1099#1093
        end
        object Label10: TLabel
          Left = 13
          Top = 98
          Width = 168
          Height = 13
          Caption = #1048#1084#1103' '#1087#1086#1083#1103' '#1074' '#1090#1072#1073#1083#1080#1094#1077' '#1080#1083#1080' '#1079#1072#1087#1088#1086#1089#1077
        end
        object PropName: TEdit
          Left = 13
          Top = 33
          Width = 332
          Height = 21
          TabOrder = 0
        end
        object PropShort: TEdit
          Left = 13
          Top = 72
          Width = 156
          Height = 21
          TabOrder = 1
        end
        object PropClass: TEdit
          Left = 13
          Top = 151
          Width = 156
          Height = 21
          TabOrder = 2
        end
        object PropType: TComboBox
          Left = 13
          Top = 190
          Width = 156
          Height = 21
          Style = csDropDownList
          ItemHeight = 0
          TabOrder = 3
        end
        object Button2: TButton
          Left = 14
          Top = 398
          Width = 156
          Height = 20
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
          TabOrder = 4
          OnClick = Button2Click
        end
        object PropField: TEdit
          Left = 13
          Top = 112
          Width = 156
          Height = 21
          TabOrder = 5
        end
        object ValList: TListBox
          Left = 13
          Top = 224
          Width = 332
          Height = 161
          ItemHeight = 13
          TabOrder = 6
          Visible = False
          OnMouseDown = ValListMouseDown
          OnMouseMove = ValListMouseMove
          OnMouseUp = ValListMouseUp
        end
      end
      object GroupBox8: TGroupBox
        Left = 7
        Top = 7
        Width = 376
        Height = 474
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = #1057#1087#1080#1089#1086#1082' '#1093#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082
        TabOrder = 1
        object ProperList: TListBox
          Left = 2
          Top = 15
          Width = 372
          Height = 457
          Align = alClient
          ItemHeight = 13
          TabOrder = 0
          OnClick = ProperListClick
          OnMouseDown = ProperListMouseDown
          OnMouseMove = ProperListMouseMove
          OnMouseUp = ProperListMouseUp
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1054#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
      ImageIndex = 1
      object Splitter4: TSplitter
        Left = 163
        Top = 0
        Width = 7
        Height = 513
        Cursor = crHSplit
      end
      object Splitter5: TSplitter
        Left = 320
        Top = 0
        Width = 6
        Height = 513
        Cursor = crHSplit
      end
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 163
        Height = 513
        Align = alLeft
        Caption = #1043#1088#1072#1092#1080#1095#1077#1089#1082#1080#1077' '#1086#1073#1098#1077#1082#1090#1099
        TabOrder = 0
        object Splitter3: TSplitter
          Left = 2
          Top = 163
          Width = 159
          Height = 7
          Cursor = crVSplit
          Align = alTop
        end
        object GroupBox5: TGroupBox
          Left = 2
          Top = 15
          Width = 159
          Height = 148
          Align = alTop
          Caption = #1055#1077#1088#1100#1103
          TabOrder = 0
          object GDIPens: TListBox
            Left = 2
            Top = 15
            Width = 155
            Height = 131
            Style = lbOwnerDrawFixed
            Align = alClient
            Color = clSilver
            ExtendedSelect = False
            ItemHeight = 24
            PopupMenu = Popup1
            TabOrder = 0
            OnDblClick = GDIPensDblClick
            OnDrawItem = GDIPensDrawItem
          end
        end
        object GroupBox6: TGroupBox
          Left = 2
          Top = 170
          Width = 159
          Height = 341
          Align = alClient
          Caption = #1050#1080#1089#1090#1080
          TabOrder = 1
          object GDIBrushs: TListBox
            Left = 2
            Top = 15
            Width = 155
            Height = 324
            Style = lbOwnerDrawFixed
            Align = alClient
            Color = clSilver
            ExtendedSelect = False
            ItemHeight = 32
            PopupMenu = Popup1
            TabOrder = 0
            OnDblClick = GDIBrushsDblClick
            OnDrawItem = GDIBrushsDrawItem
          end
        end
      end
      object GroupBox9: TGroupBox
        Left = 170
        Top = 0
        Width = 150
        Height = 513
        Align = alLeft
        Caption = #1055#1088#1086#1094#1077#1076#1091#1088#1099' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103
        TabOrder = 1
        object VisList: TListBox
          Left = 2
          Top = 15
          Width = 146
          Height = 496
          Style = lbOwnerDrawFixed
          Align = alClient
          ItemHeight = 64
          PopupMenu = Popup1
          TabOrder = 0
          OnClick = VisListClick
          OnDblClick = VisListDblClick
          OnDrawItem = VisListDrawItem
        end
      end
      object GroupBox10: TGroupBox
        Left = 326
        Top = 0
        Width = 484
        Height = 513
        Align = alClient
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103
        TabOrder = 2
        object Splitter6: TSplitter
          Left = 241
          Top = 15
          Width = 5
          Height = 401
          Cursor = crHSplit
        end
        object GroupBox11: TGroupBox
          Left = 2
          Top = 416
          Width = 480
          Height = 95
          Align = alBottom
          Caption = #1042#1080#1076' '#1086#1073#1098#1077#1082#1090#1072
          TabOrder = 0
          DesignSize = (
            480
            95)
          object VisBox: TPaintBox
            Left = 73
            Top = 13
            Width = 288
            Height = 78
            Anchors = [akLeft, akTop, akRight, akBottom]
            OnDblClick = VisBoxDblClick
            OnPaint = VisBoxPaint
          end
          object Radio1: TRadioButton
            Left = 20
            Top = 13
            Width = 46
            Height = 14
            Caption = '--1--'
            Checked = True
            TabOrder = 0
            TabStop = True
            OnClick = Radio1Click
          end
          object Radio2: TRadioButton
            Left = 20
            Top = 33
            Width = 46
            Height = 13
            Caption = '--2--'
            TabOrder = 1
            OnClick = Radio1Click
          end
          object Radio3: TRadioButton
            Left = 20
            Top = 52
            Width = 46
            Height = 14
            Caption = '--3--'
            TabOrder = 2
            OnClick = Radio1Click
          end
          object Radio4: TRadioButton
            Left = 20
            Top = 72
            Width = 46
            Height = 13
            Caption = '--4--'
            TabOrder = 3
            OnClick = Radio1Click
          end
          object Check1: TCheckBox
            Left = 7
            Top = 13
            Width = 13
            Height = 14
            TabOrder = 4
            OnClick = Check1Click
          end
          object Check2: TCheckBox
            Left = 7
            Top = 33
            Width = 13
            Height = 13
            TabOrder = 5
            OnClick = Check2Click
          end
          object Check3: TCheckBox
            Left = 7
            Top = 52
            Width = 13
            Height = 14
            TabOrder = 6
            OnClick = Check3Click
          end
          object Check4: TCheckBox
            Left = 7
            Top = 72
            Width = 13
            Height = 13
            TabOrder = 7
            OnClick = Check4Click
          end
          object Button3: TButton
            Left = 379
            Top = 11
            Width = 78
            Height = 20
            Anchors = [akRight, akBottom]
            Caption = #1047#1072#1087#1086#1084#1085#1080#1090#1100
            TabOrder = 8
            OnClick = Button3Click
          end
          object Edit1: TEdit
            Left = 420
            Top = 60
            Width = 33
            Height = 21
            TabOrder = 9
            Text = '0'
            OnChange = Edit1Change
          end
          object UpDown1: TUpDown
            Left = 453
            Top = 60
            Width = 15
            Height = 21
            Associate = Edit1
            Min = 0
            Max = 8
            Position = 0
            TabOrder = 10
            Wrap = False
          end
          object ShowGrid: TCheckBox
            Left = 380
            Top = 36
            Width = 97
            Height = 17
            Caption = #1055#1086#1083#1086#1078#1077#1085#1080#1077' '
            TabOrder = 11
            OnClick = ShowGridClick
          end
        end
        object Panel1: TPanel
          Left = 246
          Top = 15
          Width = 236
          Height = 401
          Align = alClient
          TabOrder = 1
          object Splitter7: TSplitter
            Left = 1
            Top = 77
            Width = 234
            Height = 8
            Cursor = crVSplit
            Align = alTop
          end
          object PagesList: TCheckListBox
            Left = 1
            Top = 1
            Width = 234
            Height = 76
            Align = alTop
            ItemHeight = 13
            TabOrder = 0
          end
          object VisPropList: TListBox
            Left = 1
            Top = 85
            Width = 234
            Height = 315
            Align = alClient
            ItemHeight = 13
            PopupMenu = Popup1
            TabOrder = 1
            OnClick = VisPropListClick
          end
        end
        object Panel2: TPanel
          Left = 2
          Top = 15
          Width = 239
          Height = 401
          Align = alLeft
          TabOrder = 2
          object VisObjTree: TTreeView
            Left = 1
            Top = 46
            Width = 237
            Height = 354
            Align = alClient
            HideSelection = False
            Indent = 19
            TabOrder = 0
            OnChange = VisObjTreeChange
          end
          object GroupBox12: TGroupBox
            Left = 1
            Top = 1
            Width = 237
            Height = 45
            Align = alTop
            TabOrder = 1
            DesignSize = (
              237
              45)
            object CurPage: TComboBox
              Left = 4
              Top = 12
              Width = 229
              Height = 21
              Style = csDropDownList
              Anchors = [akLeft, akTop, akRight]
              ItemHeight = 13
              TabOrder = 0
            end
          end
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 96
    Top = 32
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N2: TMenuItem
        Caption = #1048#1084#1087#1086#1088#1090
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1069#1082#1089#1087#1086#1088#1090
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N5Click
      end
    end
    object N6: TMenuItem
      Caption = #1048#1085#1089#1090#1088#1091#1084#1077#1085#1090#1099
      object N7: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1085#1077#1080#1089#1087#1086#1083#1100#1079#1091#1077#1084#1099#1077' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103
        OnClick = N7Click
      end
    end
  end
  object Connection: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=victo' +
      'ry_istu'
    LoginPrompt = False
    Provider = 'MSDASQL.1'
    Left = 160
    Top = 16
  end
  object Popup1: TPopupMenu
    Left = 208
    Top = 24
    object P1: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1077#1088#1086
      OnClick = P1Click
    end
    object P2: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1080#1089#1090#1100
      OnClick = P2Click
    end
    object P3: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
      OnClick = P3Click
    end
    object P4: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1087#1077#1088#1086
      OnClick = P4Click
    end
    object P5: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1082#1080#1089#1090#1100
      OnClick = P5Click
    end
    object P6: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
      OnClick = P6Click
    end
    object N8: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1091#1089#1083#1086#1074#1080#1077
      OnClick = N8Click
    end
    object N9: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1091#1089#1083#1086#1074#1080#1077
      OnClick = N9Click
    end
  end
end
