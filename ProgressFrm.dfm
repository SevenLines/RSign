object ProgressForm: TProgressForm
  Left = 325
  Top = 182
  Width = 416
  Height = 319
  BorderIcons = []
  BorderWidth = 5
  Caption = 'ProgressForm'
  Color = clBtnFace
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
    Top = 230
    Width = 390
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Label: TLabel
      Left = 0
      Top = 0
      Width = 295
      Height = 41
      Align = alClient
      Alignment = taCenter
      AutoSize = False
      Layout = tlCenter
      WordWrap = True
    end
    object pnlCancel: TPanel
      Left = 295
      Top = 0
      Width = 95
      Height = 41
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
    Width = 390
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    BorderWidth = 2
    Caption = 'Panel3'
    TabOrder = 1
    object ProgressBar: TCGauge
      Left = 2
      Top = 2
      Width = 386
      Height = 24
      Align = alClient
      ForeColor = clSkyBlue
    end
  end
  object pnLog: TPanel
    Left = 0
    Top = 28
    Width = 390
    Height = 202
    Align = alClient
    TabOrder = 2
    Visible = False
    object edtLog: TRichEdit
      Left = 1
      Top = 1
      Width = 388
      Height = 200
      Align = alClient
      ReadOnly = True
      TabOrder = 0
    end
  end
end
