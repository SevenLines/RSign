object FAutoCADPrint: TFAutoCADPrint
  Left = 728
  Top = 71
  AutoSize = True
  BorderStyle = bsDialog
  Caption = #1055#1077#1095#1072#1090#1100' '#1080#1079' AutoCAD '
  ClientHeight = 322
  ClientWidth = 626
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  ShowHint = True
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnlTop: TPanel
    Left = 281
    Top = 0
    Width = 289
    Height = 322
    Alignment = taLeftJustify
    AutoSize = True
    BevelOuter = bvNone
    BorderWidth = 10
    TabOrder = 0
    Visible = False
    object Label8: TLabel
      Left = 14
      Top = 96
      Width = 43
      Height = 13
      Alignment = taRightJustify
      Caption = #1053#1080#1078#1085'.(3)'
    end
    object Label7: TLabel
      Left = 17
      Top = 65
      Width = 40
      Height = 13
      Alignment = taRightJustify
      Caption = #1062#1085#1090#1088'.(2)'
    end
    object Label6: TLabel
      Left = 17
      Top = 32
      Width = 39
      Height = 13
      Alignment = taRightJustify
      Caption = #1042#1077#1088#1093'.(1)'
    end
    object Label5: TLabel
      Left = 18
      Top = 174
      Width = 33
      Height = 13
      Caption = #1082#1086#1085#1077#1094':'
    end
    object Label4: TLabel
      Left = 13
      Top = 152
      Width = 38
      Height = 13
      Caption = #1085#1072#1095#1072#1083#1086':'
    end
    object Label3: TLabel
      Left = 29
      Top = 126
      Width = 22
      Height = 13
      Caption = #1096#1072#1075':'
    end
    object Label2: TLabel
      Left = 63
      Top = 10
      Width = 61
      Height = 13
      Caption = #1074#1077#1088#1090'. '#1094#1077#1085#1090#1088':'
    end
    object Label1: TLabel
      Left = 179
      Top = 10
      Width = 85
      Height = 13
      Caption = #1074#1080#1076#1086#1074#1099#1077' '#1101#1082#1088#1072#1085#1099
    end
    object Label9: TLabel
      Left = 10
      Top = 204
      Width = 41
      Height = 13
      Caption = #1096#1072#1073#1083#1086#1085':'
    end
    object Label10: TLabel
      Left = 13
      Top = 226
      Width = 255
      Height = 13
      Caption = #1086#1073#1098#1077#1082#1090' '#1090#1077#1082#1089#1090#1072' '#1076#1086#1083#1078#1077#1085' '#1085#1072#1093#1086#1076#1080#1090#1089#1103' '#1085#1072' '#1089#1083#1086#1077' "@info".'
    end
    object Label11: TLabel
      Left = 13
      Top = 243
      Width = 228
      Height = 13
      Caption = #1087#1088#1080#1084#1077#1088': "%i + %i '#1084'" ('#1086#1090#1086#1073#1088#1072#1078#1072#1077#1090#1089#1103' 1 + 500 '#1084')'
    end
    object Label13: TLabel
      Left = 13
      Top = 266
      Width = 64
      Height = 13
      Caption = #1085#1091#1084#1077#1088#1072#1094#1080#1103' '#1089
    end
    object Label14: TLabel
      Left = 141
      Top = 266
      Width = 120
      Height = 13
      Caption = #1089#1090#1088#1072#1085#1080#1094#1099' ('#1089#1083#1086#1081' @page)'
    end
    object Label16: TLabel
      Left = 22
      Top = 292
      Width = 54
      Height = 13
      Caption = 'PDFBinder:'
    end
    object Panel1: TPanel
      Left = 165
      Top = 26
      Width = 113
      Height = 91
      BevelOuter = bvNone
      BorderStyle = bsSingle
      Caption = 'Panel1'
      TabOrder = 0
      object Image1: TImage
        Left = 0
        Top = 0
        Width = 109
        Height = 87
        Align = alClient
        OnMouseDown = Image1MouseDown
      end
    end
    object edtTopCenter: TEdit
      Left = 61
      Top = 28
      Width = 65
      Height = 24
      TabOrder = 1
      Text = '42250'
      OnEnter = edtStepEnter
    end
    object edtStep: TEdit
      Left = 61
      Top = 122
      Width = 217
      Height = 24
      TabOrder = 2
      Text = '100000'
      OnEnter = edtStepEnter
      OnKeyDown = edtEndKeyDown
    end
    object edtStart: TEdit
      Left = 61
      Top = 147
      Width = 217
      Height = 24
      TabOrder = 3
      Text = '0'
      OnEnter = edtStepEnter
      OnKeyDown = edtEndKeyDown
    end
    object edtMiddleCenter: TEdit
      Left = 61
      Top = 61
      Width = 65
      Height = 24
      TabOrder = 4
      Text = '0'
      OnEnter = edtStepEnter
    end
    object edtEnd: TEdit
      Left = 61
      Top = 170
      Width = 217
      Height = 24
      TabOrder = 5
      Text = '100000'
      OnEnter = edtStepEnter
      OnKeyDown = edtEndKeyDown
    end
    object edtBottomCenter: TEdit
      Left = 61
      Top = 92
      Width = 65
      Height = 24
      TabOrder = 6
      Text = '-42250'
      OnEnter = edtStepEnter
    end
    object Button6: TButton
      Left = 133
      Top = 91
      Width = 27
      Height = 26
      Caption = 'f'
      TabOrder = 7
      OnClick = Button6Click
    end
    object Button5: TButton
      Left = 133
      Top = 58
      Width = 27
      Height = 25
      Caption = 'f'
      TabOrder = 8
      OnClick = Button5Click
    end
    object Button4: TButton
      Left = 133
      Top = 26
      Width = 27
      Height = 26
      Caption = 'f'
      TabOrder = 9
      OnClick = Button4Click
    end
    object chkInfo: TCheckBox
      Left = 237
      Top = 204
      Width = 41
      Height = 17
      Caption = #1082#1084'.'
      TabOrder = 10
    end
    object edtPattern: TEdit
      Left = 61
      Top = 200
      Width = 169
      Height = 24
      TabOrder = 11
      Text = '%i-%i '#1082#1084'.'
    end
    object edtPage: TEdit
      Left = 88
      Top = 262
      Width = 49
      Height = 24
      TabOrder = 12
    end
    object edtPDFBinder: TEdit
      Left = 88
      Top = 288
      Width = 161
      Height = 24
      TabOrder = 13
    end
    object Button8: TButton
      Left = 254
      Top = 286
      Width = 25
      Height = 23
      Caption = '...'
      TabOrder = 14
      OnClick = Button8Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 281
    Height = 322
    Align = alLeft
    Caption = 'Panel3'
    TabOrder = 1
    object pnlBottom: TPanel
      Left = 1
      Top = 129
      Width = 279
      Height = 202
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object chkOnly: TCheckBox
        Left = 8
        Top = 3
        Width = 177
        Height = 17
        Caption = #1090#1086#1083#1100#1082#1086' '#1091#1082#1072#1079#1072#1085#1085#1099#1081' '#1087#1088#1086#1084#1077#1078#1091#1090#1086#1082
        TabOrder = 0
      end
      object cmdPrint: TButton
        Left = 7
        Top = 40
        Width = 265
        Height = 65
        Caption = #1087#1077#1095#1072#1090#1100' '#1074' PDF'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = cmdPrintClick
      end
      object Button9: TButton
        Left = 7
        Top = 112
        Width = 265
        Height = 65
        Caption = #1074#1099#1074#1086#1076' '#1074' DWG'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = Button9Click
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 42
      Width = 279
      Height = 87
      Align = alTop
      TabOrder = 1
      object edtPos2: TEdit
        Left = 152
        Top = 18
        Width = 89
        Height = 24
        ReadOnly = True
        TabOrder = 0
        Text = '0'
        OnEnter = edtStepEnter
        OnKeyDown = edtPosKeyDown
      end
      object Button3: TButton
        Left = 248
        Top = 16
        Width = 25
        Height = 25
        Caption = '>>|'
        TabOrder = 1
        OnClick = Button3Click
      end
      object edtPos: TEdit
        Left = 40
        Top = 18
        Width = 81
        Height = 24
        TabOrder = 2
        Text = '0'
        OnChange = edtPosChange
        OnEnter = edtStepEnter
        OnKeyDown = edtPosKeyDown
      end
      object Button7: TButton
        Left = 8
        Top = 16
        Width = 25
        Height = 25
        Caption = '|<<'
        TabOrder = 3
        OnClick = Button7Click
      end
      object tbPos: TTrackBar
        Left = 4
        Top = 40
        Width = 273
        Height = 33
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
      Width = 279
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      Caption = 'Panel2'
      TabOrder = 2
      object lblActiveName: TLabel
        Left = 88
        Top = 14
        Width = 153
        Height = 13
        AutoSize = False
      end
      object Button2: TButton
        Left = 8
        Top = 8
        Width = 73
        Height = 25
        Caption = #1040#1082#1090#1080#1074#1085#1099#1081
        TabOrder = 0
        OnClick = Button2Click
      end
      object Button12: TButton
        Left = 248
        Top = 8
        Width = 27
        Height = 25
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
