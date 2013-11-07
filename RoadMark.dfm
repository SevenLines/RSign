object frmMarkParam: TfrmMarkParam
  Left = 622
  Top = 112
  Width = 363
  Height = 346
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1088#1072#1079#1084#1077#1090#1082#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ListKinds: TListBox
    Left = 193
    Top = 0
    Width = 154
    Height = 308
    Style = lbOwnerDrawFixed
    Align = alClient
    ItemHeight = 16
    TabOrder = 0
    OnDrawItem = ListKindsDrawItem
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 193
    Height = 308
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 79
      Height = 13
      Caption = #1053#1072#1095#1072#1083#1086' '#1091#1095#1072#1089#1090#1082#1072
    end
    object Label2: TLabel
      Left = 8
      Top = 32
      Width = 73
      Height = 13
      Caption = #1050#1086#1085#1077#1094' '#1091#1095#1072#1089#1090#1082#1072
    end
    object Label3: TLabel
      Left = 8
      Top = 80
      Width = 75
      Height = 13
      Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077
    end
    object Label5: TLabel
      Left = 8
      Top = 56
      Width = 52
      Height = 13
      Caption = #1042#1080#1076' '#1083#1080#1085#1080#1080
    end
    object Label4: TLabel
      Left = 8
      Top = 104
      Width = 70
      Height = 13
      Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090
    end
    object Label6: TLabel
      Left = 8
      Top = 128
      Width = 60
      Height = 13
      Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077
    end
    object editStart: TEdit
      Left = 88
      Top = 8
      Width = 97
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object editEnd: TEdit
      Left = 88
      Top = 32
      Width = 97
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object comboKind: TComboBox
      Left = 88
      Top = 56
      Width = 97
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 2
      Text = #1044#1088#1091#1075#1086#1077
      OnChange = comboKindChange
      Items.Strings = (
        #1044#1088#1091#1075#1086#1077
        #1054#1089#1100' '#1076#1086#1088#1086#1075#1080
        #1051#1077#1074#1072#1103' '#1082#1088#1072#1077#1074#1072#1103
        #1055#1088#1072#1074#1072#1103' '#1082#1088#1072#1077#1074#1072#1103)
    end
    object comboDirection: TComboBox
      Left = 88
      Top = 80
      Width = 97
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 3
      Text = #1055#1088#1103#1084#1086#1077
      Items.Strings = (
        #1055#1088#1103#1084#1086#1077
        #1054#1073#1088#1072#1090#1085#1086#1077)
    end
    object editK: TEdit
      Left = 104
      Top = 104
      Width = 61
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object editX: TEdit
      Left = 104
      Top = 128
      Width = 61
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object updX: TUpDown
      Left = 165
      Top = 128
      Width = 15
      Height = 21
      Associate = editX
      Min = -1000
      Max = 1000
      Increment = 5
      Position = 0
      TabOrder = 6
      Wrap = False
    end
    object updK: TUpDown
      Left = 165
      Top = 104
      Width = 15
      Height = 21
      Associate = editK
      Min = 0
      Max = 1000
      Increment = 100
      Position = 0
      TabOrder = 7
      Wrap = False
    end
    object Panel2: TPanel
      Left = 0
      Top = 267
      Width = 193
      Height = 41
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 8
      object Button2: TButton
        Left = 108
        Top = 12
        Width = 75
        Height = 25
        Cancel = True
        Caption = #1054#1090#1084#1077#1085#1072
        ModalResult = 2
        TabOrder = 0
      end
      object Button1: TButton
        Left = 4
        Top = 12
        Width = 75
        Height = 25
        Caption = #1054#1082
        Default = True
        TabOrder = 1
        OnClick = Button1Click
      end
    end
  end
end
