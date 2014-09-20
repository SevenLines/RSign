object ProgressForm: TProgressForm
  Left = 325
  Top = 182
  Width = 491
  Height = 254
  VertScrollBar.Visible = False
  BorderIcons = []
  BorderWidth = 5
  Caption = 'ProgressForm'
  Color = clBtnFace
  Constraints.MaxHeight = 600
  Constraints.MaxWidth = 800
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 168
    Width = 473
    Height = 42
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Label: TLabel
      Left = 0
      Top = 0
      Width = 378
      Height = 42
      Align = alClient
      Alignment = taCenter
      AutoSize = False
      Caption = 'hello :D'
      Layout = tlCenter
      WordWrap = True
    end
    object pnlCancel: TPanel
      Left = 378
      Top = 0
      Width = 95
      Height = 42
      Align = alRight
      BevelOuter = bvNone
      Caption = 'pnlCancel'
      TabOrder = 0
      object cmdAbort: TButton
        Left = 12
        Top = 7
        Width = 75
        Height = 26
        Caption = #1086#1090#1084#1077#1085#1072
        TabOrder = 0
        OnClick = cmdAbortClick
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 473
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    BorderWidth = 2
    Caption = 'Panel3'
    TabOrder = 1
    object ProgressBar: TCGauge
      Left = 2
      Top = 2
      Width = 469
      Height = 24
      Align = alClient
      ForeColor = clSkyBlue
    end
  end
  object pnLog: TPanel
    Left = 0
    Top = 28
    Width = 473
    Height = 140
    Align = alClient
    TabOrder = 2
    Visible = False
    object edtLog: TRichEdit
      Left = 1
      Top = 1
      Width = 471
      Height = 138
      Align = alClient
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
end
