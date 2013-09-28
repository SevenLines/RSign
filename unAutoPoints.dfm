object FAutoPoints: TFAutoPoints
  Left = 369
  Top = 218
  BorderStyle = bsToolWindow
  Caption = 'auto points'
  ClientHeight = 35
  ClientWidth = 138
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnMouseWheel = FormMouseWheel
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 4
    Width = 28
    Height = 13
    Caption = #1090#1086#1095#1082#1072
  end
  object Label2: TLabel
    Left = 120
    Top = 12
    Width = 8
    Height = 13
    Caption = #1084
  end
  object Label3: TLabel
    Left = 4
    Top = 18
    Width = 40
    Height = 13
    Caption = #1082#1072#1078#1076#1099#1077
  end
  object edtFreq: TCSpinEdit
    Left = 56
    Top = 8
    Width = 57
    Height = 22
    MaxValue = 100
    MinValue = 1
    ReadOnly = True
    TabOrder = 0
  end
end
