object ConnectionForm: TConnectionForm
  Left = 596
  Top = 251
  Width = 375
  Height = 263
  AutoSize = True
  BorderWidth = 8
  Caption = 'ConnectionForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object grpUserInfo: TGroupBox
    Left = 0
    Top = 33
    Width = 341
    Height = 96
    Align = alTop
    TabOrder = 0
    DesignSize = (
      341
      96)
    object lblUserID: TLabel
      Left = 9
      Top = 28
      Width = 95
      Height = 16
      Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    end
    object lblPassword: TLabel
      Left = 9
      Top = 60
      Width = 49
      Height = 16
      Caption = #1055#1072#1088#1086#1083#1100
    end
    object edtUserID: TEdit
      Left = 112
      Top = 25
      Width = 221
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
    end
    object edtPassword: TEdit
      Left = 112
      Top = 57
      Width = 221
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      PasswordChar = '*'
      TabOrder = 2
    end
    object chkAsLocalUser: TCheckBox
      Left = 9
      Top = 0
      Width = 208
      Height = 17
      Caption = #1044#1086#1074#1077#1088#1080#1090#1077#1083#1100#1085#1086#1077' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1077
      TabOrder = 0
      OnClick = chkAsLocalUserClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 341
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      341
      33)
    object cmbDataSource: TComboBox
      Left = 0
      Top = 1
      Width = 145
      Height = 24
      ItemHeight = 16
      TabOrder = 0
      OnKeyPress = cmbDataSourceKeyPress
    end
    object btnConnectToSever: TButton
      Left = 151
      Top = 0
      Width = 40
      Height = 25
      Caption = 'X'
      TabOrder = 1
      OnClick = btnConnectToSeverClick
    end
    object edtProvider: TComboBox
      Left = 200
      Top = 1
      Width = 141
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 16
      TabOrder = 2
      Items.Strings = (
        'SQLOLEDB.1'
        'MSDASQL.1')
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 129
    Width = 341
    Height = 32
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Panel2'
    TabOrder = 2
    DesignSize = (
      341
      32)
    object cmbInitialCatalog: TComboBox
      Left = 8
      Top = 8
      Width = 321
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 16
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 161
    Width = 341
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 217
      Height = 41
      Align = alLeft
      AutoSize = True
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        217
        41)
      object lblSuccess: TLabel
        Left = 168
        Top = 13
        Width = 49
        Height = 24
        AutoSize = False
      end
      object btnConnect: TButton
        Left = 0
        Top = 9
        Width = 89
        Height = 32
        Anchors = [akLeft, akBottom]
        Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100
        TabOrder = 1
        OnClick = btnConnectClick
      end
      object btnTest: TButton
        Left = 92
        Top = 9
        Width = 75
        Height = 32
        Anchors = [akLeft, akBottom]
        Caption = #1058#1077#1089#1090
        TabOrder = 0
        OnClick = btnTestClick
      end
    end
    object Panel5: TPanel
      Left = 256
      Top = 0
      Width = 85
      Height = 41
      Align = alRight
      AutoSize = True
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        85
        41)
      object btnCancel: TButton
        Left = 0
        Top = 7
        Width = 85
        Height = 32
        Anchors = [akRight, akBottom]
        Caption = #1054#1090#1084#1077#1085#1072
        ModalResult = 2
        TabOrder = 0
      end
    end
  end
  object TimerComboInitialCatalog: TTimer
    Interval = 400
    OnTimer = TimerComboInitialCatalogTimer
    Left = 152
    Top = 120
  end
end
