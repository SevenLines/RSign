object ConnectionForm: TConnectionForm
  Left = 596
  Top = 251
  Width = 329
  Height = 204
  AutoSize = True
  BorderWidth = 8
  Caption = 'ConnectionForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object grpUserInfo: TGroupBox
    Left = 0
    Top = 22
    Width = 305
    Height = 78
    Align = alTop
    TabOrder = 0
    DesignSize = (
      305
      78)
    object lblUserID: TLabel
      Left = 7
      Top = 23
      Width = 73
      Height = 13
      Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    end
    object lblPassword: TLabel
      Left = 7
      Top = 49
      Width = 38
      Height = 13
      Caption = #1055#1072#1088#1086#1083#1100
    end
    object edtUserID: TEdit
      Left = 91
      Top = 20
      Width = 201
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
    end
    object edtPassword: TEdit
      Left = 91
      Top = 46
      Width = 201
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      PasswordChar = '*'
      TabOrder = 2
    end
    object chkAsLocalUser: TCheckBox
      Left = 7
      Top = 0
      Width = 169
      Height = 14
      Caption = #1044#1086#1074#1077#1088#1080#1090#1077#1083#1100#1085#1086#1077' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1077
      TabOrder = 0
      OnClick = chkAsLocalUserClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 305
    Height = 22
    Align = alTop
    AutoSize = True
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      305
      22)
    object cmbDataSource: TComboBox
      Left = 0
      Top = 1
      Width = 151
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnKeyPress = cmbDataSourceKeyPress
    end
    object btnConnectToSever: TButton
      Left = 155
      Top = 0
      Width = 33
      Height = 20
      Caption = 'X'
      TabOrder = 1
      OnClick = btnConnectToSeverClick
    end
    object edtProvider: TComboBox
      Left = 192
      Top = 1
      Width = 106
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 2
      Items.Strings = (
        'SQLOLEDB.1'
        'MSDASQL.1')
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 100
    Width = 305
    Height = 21
    Align = alTop
    AutoSize = True
    BevelOuter = bvNone
    Caption = 'Panel2'
    TabOrder = 2
    DesignSize = (
      305
      21)
    object cmbInitialCatalog: TComboBox
      Left = 0
      Top = 0
      Width = 305
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 121
    Width = 305
    Height = 33
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 196
      Height = 33
      Align = alLeft
      AutoSize = True
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        196
        33)
      object lblSuccess: TLabel
        Left = 143
        Top = 7
        Width = 53
        Height = 20
        AutoSize = False
      end
      object btnConnect: TButton
        Left = 0
        Top = 7
        Width = 72
        Height = 26
        Anchors = [akLeft, akBottom]
        Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100
        TabOrder = 1
        OnClick = btnConnectClick
      end
      object btnTest: TButton
        Left = 75
        Top = 7
        Width = 61
        Height = 26
        Anchors = [akLeft, akBottom]
        Caption = #1058#1077#1089#1090
        TabOrder = 0
        OnClick = btnTestClick
      end
    end
    object Panel5: TPanel
      Left = 236
      Top = 0
      Width = 69
      Height = 33
      Align = alRight
      AutoSize = True
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        69
        33)
      object btnCancel: TButton
        Left = 0
        Top = 6
        Width = 69
        Height = 26
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
    Left = 144
    Top = 136
  end
end
