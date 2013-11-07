object DumpDialog: TDumpDialog
  Left = 193
  Top = 106
  BorderStyle = bsDialog
  Caption = #1042#1099#1075#1088#1091#1079#1082#1072' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080' '#1074' '#1092#1072#1081#1083
  ClientHeight = 188
  ClientWidth = 486
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
    Left = 8
    Top = 44
    Width = 57
    Height = 13
    Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072
  end
  object Label2: TLabel
    Left = 8
    Top = 76
    Width = 24
    Height = 13
    Caption = #1055#1091#1090#1100
  end
  object Label3: TLabel
    Left = 8
    Top = 8
    Width = 51
    Height = 26
    Caption = #1048#1089#1090#1086#1095#1085#1080#1082' '#1076#1072#1085#1085#1099#1093
    WordWrap = True
  end
  object FileName: TEdit
    Left = 88
    Top = 40
    Width = 333
    Height = 21
    TabOrder = 0
    Text = 'FileName'
  end
  object FilePath: TEdit
    Left = 88
    Top = 68
    Width = 333
    Height = 21
    TabOrder = 1
    Text = 'FilePath'
  end
  object Button1: TButton
    Left = 432
    Top = 68
    Width = 49
    Height = 21
    Caption = '. . .'
    TabOrder = 2
    OnClick = Button1Click
  end
  object SaveGeom: TCheckBox
    Left = 8
    Top = 104
    Width = 377
    Height = 17
    Caption = #1042#1099#1075#1088#1091#1078#1072#1090#1100' '#1075#1077#1086#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object Button2: TButton
    Left = 28
    Top = 156
    Width = 75
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 392
    Top = 156
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 5
  end
  object DataSrcList: TComboBox
    Left = 88
    Top = 8
    Width = 333
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    OnChange = DataSrcListChange
  end
  object SvDialog: TSaveDialog
    DefaultExt = 'dta'
    Filter = #1060#1072#1081#1083#1099' '#1082#1086#1085#1089#1090#1088#1091#1082#1090#1080#1074#1085#1099#1093' '#1101#1083#1077#1084#1077#1085#1090#1086#1074'|*.dta'
    Left = 296
    Top = 28
  end
end
