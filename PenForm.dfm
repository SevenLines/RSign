object PenEdit: TPenEdit
  Left = 408
  Top = 143
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1077#1088#1072
  ClientHeight = 261
  ClientWidth = 217
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 7
    Top = 59
    Width = 57
    Height = 13
    Caption = #1057#1090#1080#1083#1100' '#1087#1077#1088#1072
  end
  object Label2: TLabel
    Left = 117
    Top = 7
    Width = 49
    Height = 13
    Caption = #1058#1086#1083#1097#1080#1085#1072' '
  end
  object Label3: TLabel
    Left = 7
    Top = 7
    Width = 28
    Height = 13
    Caption = #1062#1074#1077#1090' '
  end
  object Shape1: TShape
    Left = 7
    Top = 26
    Width = 78
    Height = 20
    OnMouseUp = Shape1MouseUp
  end
  object PBox: TPaintBox
    Left = 7
    Top = 207
    Width = 195
    Height = 26
    OnPaint = PBoxPaint
  end
  object Label4: TLabel
    Left = 8
    Top = 112
    Width = 75
    Height = 13
    Caption = #1042#1080#1076' '#1086#1082#1086#1085#1095#1072#1085#1080#1081
  end
  object Label5: TLabel
    Left = 8
    Top = 160
    Width = 82
    Height = 13
    Caption = #1042#1080#1076' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1081
  end
  object ComboBox1: TComboBox
    Left = 13
    Top = 78
    Width = 176
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 0
    Text = '------------- '#1057#1087#1083#1086#1096#1085#1072#1103' '#1083#1080#1085#1080#1103
    OnChange = Edit1Change
    Items.Strings = (
      '------------- '#1057#1087#1083#1086#1096#1085#1072#1103' '#1083#1080#1085#1080#1103
      '--   --  --  --  '#1064#1090#1088#1080#1093#1080
      '- - - - - - - -  '#1055#1091#1085#1082#1090#1080#1088
      '--  -  --  -  -- '#1064#1090#1088#1080#1093'-'#1087#1091#1085#1082#1090#1080#1088
      '--  -  -  --  - - '#1044#1074#1086#1081#1085#1086#1081' '#1087#1091#1085#1082#1090#1080#1088
      '                    '#1053#1077#1090' '#1083#1080#1085#1080#1080' ')
  end
  object Edit1: TEdit
    Left = 117
    Top = 26
    Width = 46
    Height = 24
    TabOrder = 1
    Text = '0'
    OnChange = Edit1Change
  end
  object UpDown1: TUpDown
    Left = 163
    Top = 26
    Width = 20
    Height = 20
    Associate = Edit1
    Min = 0
    Position = 0
    TabOrder = 2
    Wrap = False
  end
  object Button1: TButton
    Left = 7
    Top = 238
    Width = 60
    Height = 20
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object Button2: TButton
    Left = 145
    Top = 238
    Width = 60
    Height = 20
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 4
  end
  object ComboBox2: TComboBox
    Left = 8
    Top = 128
    Width = 185
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 5
    Text = #1047#1072#1082#1088#1091#1075#1083#1077#1085#1080#1103
    Items.Strings = (
      #1047#1072#1082#1088#1091#1075#1083#1077#1085#1080#1103
      #1050#1074#1072#1076#1088#1072#1090#1099
      #1054#1073#1088#1077#1079#1082#1072)
  end
  object ComboBox3: TComboBox
    Left = 8
    Top = 176
    Width = 185
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 6
    Text = #1047#1072#1082#1088#1091#1075#1083#1077#1085#1080#1103
    Items.Strings = (
      #1047#1072#1082#1088#1091#1075#1083#1077#1085#1080#1103
      'PS_BEVEL'
      'PS_MITER')
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 184
    Top = 64
  end
end
