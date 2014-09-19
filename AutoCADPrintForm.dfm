object FAutoCADPrint: TFAutoCADPrint
  Left = 728
  Top = 71
  AutoSize = True
  BorderStyle = bsDialog
  Caption = #1055#1077#1095#1072#1090#1100' '#1080#1079' AutoCAD '
  ClientHeight = 396
  ClientWidth = 771
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  ShowHint = True
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object pnlTop: TPanel
    Left = 346
    Top = 0
    Width = 425
    Height = 388
    Alignment = taLeftJustify
    AutoSize = True
    BevelOuter = bvNone
    BorderWidth = 10
    TabOrder = 0
    Visible = False
    object Label8: TLabel
      Left = 22
      Top = 116
      Width = 53
      Height = 16
      Alignment = taRightJustify
      Caption = #1053#1080#1078#1085'.(3)'
    end
    object Label7: TLabel
      Left = 25
      Top = 78
      Width = 50
      Height = 16
      Alignment = taRightJustify
      Caption = #1062#1085#1090#1088'.(2)'
    end
    object Label6: TLabel
      Left = 25
      Top = 37
      Width = 49
      Height = 16
      Alignment = taRightJustify
      Caption = #1042#1077#1088#1093'.(1)'
    end
    object Label5: TLabel
      Left = 27
      Top = 212
      Width = 42
      Height = 16
      Caption = #1082#1086#1085#1077#1094':'
    end
    object Label4: TLabel
      Left = 21
      Top = 184
      Width = 51
      Height = 16
      Caption = #1085#1072#1095#1072#1083#1086':'
    end
    object Label3: TLabel
      Left = 41
      Top = 153
      Width = 26
      Height = 16
      Caption = #1096#1072#1075':'
    end
    object Label2: TLabel
      Left = 83
      Top = 10
      Width = 79
      Height = 16
      Caption = #1074#1077#1088#1090'. '#1094#1077#1085#1090#1088':'
    end
    object Label1: TLabel
      Left = 225
      Top = 10
      Width = 108
      Height = 16
      Caption = #1074#1080#1076#1086#1074#1099#1077' '#1101#1082#1088#1072#1085#1099
    end
    object Label9: TLabel
      Left = 17
      Top = 248
      Width = 52
      Height = 16
      Caption = #1096#1072#1073#1083#1086#1085':'
    end
    object Label10: TLabel
      Left = 21
      Top = 276
      Width = 320
      Height = 16
      Caption = #1086#1073#1098#1077#1082#1090' '#1090#1077#1082#1089#1090#1072' '#1076#1086#1083#1078#1077#1085' '#1085#1072#1093#1086#1076#1080#1090#1089#1103' '#1085#1072' '#1089#1083#1086#1077' "@info".'
    end
    object Label11: TLabel
      Left = 21
      Top = 297
      Width = 280
      Height = 16
      Caption = #1087#1088#1080#1084#1077#1088': "%i + %i '#1084'" ('#1086#1090#1086#1073#1088#1072#1078#1072#1077#1090#1089#1103' 1 + 500 '#1084')'
    end
    object Label13: TLabel
      Left = 21
      Top = 325
      Width = 82
      Height = 16
      Caption = #1085#1091#1084#1077#1088#1072#1094#1080#1103' '#1089
    end
    object Label14: TLabel
      Left = 179
      Top = 325
      Width = 154
      Height = 16
      Caption = #1089#1090#1088#1072#1085#1080#1094#1099' ('#1089#1083#1086#1081' @page)'
    end
    object Label16: TLabel
      Left = 32
      Top = 357
      Width = 69
      Height = 16
      Caption = 'PDFBinder:'
    end
    object Panel1: TPanel
      Left = 208
      Top = 30
      Width = 139
      Height = 111
      BevelOuter = bvNone
      BorderStyle = bsSingle
      Caption = 'Panel1'
      TabOrder = 0
      object Image1: TImage
        Left = 0
        Top = 0
        Width = 135
        Height = 107
        Align = alClient
        OnMouseDown = Image1MouseDown
      end
    end
    object edtTopCenter: TEdit
      Left = 80
      Top = 32
      Width = 80
      Height = 24
      TabOrder = 1
      Text = '42250'
      OnEnter = edtStepEnter
    end
    object edtStep: TEdit
      Left = 80
      Top = 148
      Width = 267
      Height = 24
      TabOrder = 2
      Text = '100000'
      OnEnter = edtStepEnter
      OnKeyDown = edtEndKeyDown
    end
    object edtStart: TEdit
      Left = 80
      Top = 179
      Width = 267
      Height = 24
      TabOrder = 3
      Text = '0'
      OnEnter = edtStepEnter
      OnKeyDown = edtEndKeyDown
    end
    object edtMiddleCenter: TEdit
      Left = 80
      Top = 73
      Width = 80
      Height = 24
      TabOrder = 4
      Text = '0'
      OnEnter = edtStepEnter
    end
    object edtEnd: TEdit
      Left = 80
      Top = 207
      Width = 267
      Height = 24
      TabOrder = 5
      Text = '100000'
      OnEnter = edtStepEnter
      OnKeyDown = edtEndKeyDown
    end
    object edtBottomCenter: TEdit
      Left = 80
      Top = 111
      Width = 80
      Height = 24
      TabOrder = 6
      Text = '-42250'
      OnEnter = edtStepEnter
    end
    object Button6: TButton
      Left = 169
      Top = 110
      Width = 33
      Height = 31
      Caption = 'f'
      TabOrder = 7
      OnClick = Button6Click
    end
    object Button5: TButton
      Left = 169
      Top = 69
      Width = 33
      Height = 31
      Caption = 'f'
      TabOrder = 8
      OnClick = Button5Click
    end
    object Button4: TButton
      Left = 169
      Top = 30
      Width = 33
      Height = 32
      Caption = 'f'
      TabOrder = 9
      OnClick = Button4Click
    end
    object chkInfo: TCheckBox
      Left = 297
      Top = 248
      Width = 50
      Height = 21
      Caption = #1082#1084'.'
      TabOrder = 10
    end
    object edtPattern: TEdit
      Left = 80
      Top = 244
      Width = 208
      Height = 24
      TabOrder = 11
      Text = '%i-%i '#1082#1084'.'
    end
    object edtPage: TEdit
      Left = 113
      Top = 320
      Width = 61
      Height = 24
      TabOrder = 12
    end
    object edtPDFBinder: TEdit
      Left = 113
      Top = 352
      Width = 198
      Height = 24
      TabOrder = 13
    end
    object Button8: TButton
      Left = 318
      Top = 349
      Width = 30
      Height = 29
      Caption = '...'
      TabOrder = 14
      OnClick = Button8Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 346
    Height = 396
    Align = alLeft
    Caption = 'Panel3'
    TabOrder = 1
    object pnlBottom: TPanel
      Left = 1
      Top = 159
      Width = 344
      Height = 248
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object chkOnly: TCheckBox
        Left = 10
        Top = 4
        Width = 218
        Height = 21
        Caption = #1090#1086#1083#1100#1082#1086' '#1091#1082#1072#1079#1072#1085#1085#1099#1081' '#1087#1088#1086#1084#1077#1078#1091#1090#1086#1082
        TabOrder = 0
      end
      object cmdPrint: TButton
        Left = 9
        Top = 49
        Width = 326
        Height = 80
        Caption = #1087#1077#1095#1072#1090#1100' '#1074' PDF'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -23
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = cmdPrintClick
      end
      object Button9: TButton
        Left = 9
        Top = 138
        Width = 326
        Height = 80
        Caption = #1074#1099#1074#1086#1076' '#1074' DWG'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -23
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = Button9Click
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 52
      Width = 344
      Height = 107
      Align = alTop
      TabOrder = 1
      object edtPos2: TEdit
        Left = 187
        Top = 22
        Width = 110
        Height = 24
        ReadOnly = True
        TabOrder = 0
        Text = '0'
        OnEnter = edtStepEnter
        OnKeyDown = edtPosKeyDown
      end
      object Button3: TButton
        Left = 305
        Top = 20
        Width = 31
        Height = 30
        Caption = '>>|'
        TabOrder = 1
        OnClick = Button3Click
      end
      object edtPos: TEdit
        Left = 49
        Top = 22
        Width = 100
        Height = 24
        TabOrder = 2
        Text = '0'
        OnChange = edtPosChange
        OnEnter = edtStepEnter
        OnKeyDown = edtPosKeyDown
      end
      object Button7: TButton
        Left = 10
        Top = 20
        Width = 31
        Height = 30
        Caption = '|<<'
        TabOrder = 3
        OnClick = Button7Click
      end
      object tbPos: TTrackBar
        Left = 5
        Top = 49
        Width = 336
        Height = 41
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 4
        ThumbLength = 15
        TickMarks = tmBoth
        TickStyle = tsAuto
        OnChange = tbPosChange
      end
    end
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 344
      Height = 51
      Align = alTop
      BevelOuter = bvNone
      Caption = 'Panel2'
      TabOrder = 2
      object lblActiveName: TLabel
        Left = 108
        Top = 17
        Width = 189
        Height = 16
        AutoSize = False
      end
      object Button2: TButton
        Left = 10
        Top = 10
        Width = 90
        Height = 31
        Caption = #1040#1082#1090#1080#1074#1085#1099#1081
        TabOrder = 0
        OnClick = Button2Click
      end
      object Button12: TButton
        Left = 305
        Top = 10
        Width = 33
        Height = 31
        Caption = '-->'
        TabOrder = 1
        OnClick = Button12Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Title = #1042#1099#1073#1080#1088#1077#1090#1077' '#1087#1072#1087#1082#1091' '#1080' '#1087#1088#1077#1092#1080#1082#1089' '#1080#1084#1077#1085#1080
    Left = 40
    Top = 40
  end
  object OpenDialog1: TOpenDialog
    Left = 8
    Top = 40
  end
  object OpenDialog2: TOpenDialog
    Left = 208
    Top = 8
  end
end
