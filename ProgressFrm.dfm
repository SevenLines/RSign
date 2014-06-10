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
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Panel2: TPanel
    Left = 0
    Top = 148
    Width = 463
    Height = 51
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Label: TLabel
      Left = 0
      Top = 0
      Width = 346
      Height = 51
      Align = alClient
      Alignment = taCenter
      AutoSize = False
      Caption = 'hello :D'
      Layout = tlCenter
      WordWrap = True
    end
    object pnlCancel: TPanel
      Left = 346
      Top = 0
      Width = 117
      Height = 51
      Align = alRight
      BevelOuter = bvNone
      Caption = 'pnlCancel'
      TabOrder = 0
      object cmdAbort: TButton
        Left = 15
        Top = 9
        Width = 92
        Height = 32
        Caption = #1086#1090#1084#1077#1085#1072
        TabOrder = 0
        OnClick = cmdAbortClick
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 463
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    BorderWidth = 2
    Caption = 'Panel3'
    TabOrder = 1
    object ProgressBar: TCGauge
      Left = 2
      Top = 2
      Width = 459
      Height = 30
      Align = alClient
      ForeColor = clSkyBlue
    end
  end
  object pnLog: TPanel
    Left = 0
    Top = 34
    Width = 463
    Height = 114
    Align = alClient
    TabOrder = 2
    Visible = False
    object edtLog: TRichEdit
      Left = 1
      Top = 1
      Width = 461
      Height = 112
      Align = alClient
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
end
