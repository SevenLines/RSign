object frmVisMode: TfrmVisMode
  Left = 240
  Top = 202
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1085#1072#1093#1086#1078#1076#1077#1085#1080#1103' '#1091#1095#1072#1089#1090#1082#1086#1074' '#1074#1080#1076#1080#1084#1086#1089#1090#1080
  ClientHeight = 167
  ClientWidth = 454
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 16
    Width = 92
    Height = 13
    Caption = #1044#1083#1080#1085#1072' '#1091#1095#1072#1089#1090#1082#1072' ('#1084')'
  end
  object Label2: TLabel
    Left = 24
    Top = 48
    Width = 92
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1086' '#1076#1086#1088#1086#1075#1080' ('#1084')'
  end
  object Label3: TLabel
    Left = 24
    Top = 80
    Width = 69
    Height = 13
    Caption = #1050#1086#1085#1077#1094' '#1076#1086#1088#1086#1075#1080
  end
  object Label4: TLabel
    Left = 216
    Top = 16
    Width = 111
    Height = 13
    Caption = #1042#1099#1089#1086#1090#1072' '#1074#1086#1076#1080#1090#1077#1083#1103' ('#1089#1084')'
  end
  object Label5: TLabel
    Left = 216
    Top = 48
    Width = 128
    Height = 13
    Caption = #1042#1099#1089#1086#1090#1072' '#1087#1088#1077#1087#1103#1090#1089#1090#1074#1080#1103' ('#1089#1084')'
  end
  object edPartLen: TEdit
    Left = 128
    Top = 8
    Width = 41
    Height = 21
    TabOrder = 0
    Text = '50'
  end
  object updPartLen: TUpDown
    Left = 169
    Top = 8
    Width = 16
    Height = 21
    Associate = edPartLen
    Min = 10
    Max = 200
    Increment = 10
    Position = 50
    TabOrder = 1
    Wrap = False
  end
  object edStartPos: TEdit
    Left = 128
    Top = 40
    Width = 57
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object edEndPos: TEdit
    Left = 128
    Top = 72
    Width = 57
    Height = 21
    TabOrder = 3
    Text = '0'
  end
  object edDraiverHeight: TEdit
    Left = 360
    Top = 8
    Width = 49
    Height = 21
    TabOrder = 4
    Text = '100'
  end
  object updDriverHeight: TUpDown
    Left = 409
    Top = 8
    Width = 16
    Height = 21
    Associate = edDraiverHeight
    Min = 10
    Max = 200
    Increment = 10
    Position = 100
    TabOrder = 5
    Wrap = False
  end
  object edMarkerHeight: TEdit
    Left = 360
    Top = 40
    Width = 49
    Height = 21
    TabOrder = 6
    Text = '100'
  end
  object updMarkerHeight: TUpDown
    Left = 409
    Top = 40
    Width = 16
    Height = 21
    Associate = edMarkerHeight
    Min = 10
    Max = 200
    Increment = 10
    Position = 100
    TabOrder = 7
    Wrap = False
  end
  object Button1: TButton
    Left = 64
    Top = 112
    Width = 75
    Height = 25
    Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100
    ModalResult = 1
    TabOrder = 8
  end
  object Button2: TButton
    Left = 312
    Top = 112
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 9
  end
end
