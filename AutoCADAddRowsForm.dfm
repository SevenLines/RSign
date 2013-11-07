object FAddRows: TFAddRows
  Left = 613
  Top = 312
  Width = 295
  Height = 149
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 65
    Width = 287
    Height = 50
    Align = alClient
    Alignment = taCenter
    Layout = tlCenter
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 287
    Height = 65
    Align = alTop
    TabOrder = 0
    object Button1: TButton
      Left = 248
      Top = 6
      Width = 27
      Height = 25
      Caption = '...'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Edit2: TEdit
      Left = 8
      Top = 8
      Width = 233
      Height = 21
      TabOrder = 1
    end
    object Button2: TButton
      Left = 32
      Top = 32
      Width = 73
      Height = 25
      Caption = 'ok'
      ModalResult = 1
      TabOrder = 2
    end
    object Button3: TButton
      Left = 112
      Top = 32
      Width = 73
      Height = 25
      Caption = #1086#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 3
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 8
    Top = 8
  end
end
