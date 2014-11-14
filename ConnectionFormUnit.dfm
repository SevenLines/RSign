object ConnectionForm: TConnectionForm
  Left = 596
  Top = 251
  Width = 387
  Height = 272
  AutoSize = True
  BorderWidth = 4
  Caption = 'ConnectionForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 120
  TextHeight = 16
  object grpUserInfo: TGroupBox
    Left = 0
    Top = 41
    Width = 361
    Height = 96
    Align = alTop
    TabOrder = 0
    DesignSize = (
      361
      96)
    object lblUserID: TLabel
      Left = 8
      Top = 28
      Width = 95
      Height = 16
      Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
    end
    object lblPassword: TLabel
      Left = 8
      Top = 60
      Width = 49
      Height = 16
      Caption = #1055#1072#1088#1086#1083#1100
    end
    object edtUserID: TEdit
      Left = 112
      Top = 24
      Width = 233
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
    end
    object edtPassword: TEdit
      Left = 112
      Top = 56
      Width = 233
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
    end
    object chkAsLocalUser: TCheckBox
      Left = 8
      Top = 0
      Width = 209
      Height = 17
      Caption = #1044#1086#1074#1077#1088#1080#1090#1077#1083#1100#1085#1086#1077' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1077
      TabOrder = 2
      OnClick = chkAsLocalUserClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 361
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      361
      41)
    object cmbDataSource: TComboBox
      Left = 0
      Top = 8
      Width = 200
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 16
      TabOrder = 0
    end
    object edtProvider: TEdit
      Left = 256
      Top = 8
      Width = 105
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Text = 'SQLOLEDB.1'
    end
    object btnConnectToSever: TButton
      Left = 208
      Top = 8
      Width = 41
      Height = 25
      Caption = 'X'
      TabOrder = 2
      OnClick = btnConnectToSeverClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 137
    Width = 361
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Panel2'
    TabOrder = 2
    DesignSize = (
      361
      41)
    object cmbInitialCatalog: TComboBox
      Left = 0
      Top = 9
      Width = 360
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 16
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 178
    Width = 361
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    DesignSize = (
      361
      41)
    object btnCancel: TButton
      Left = 284
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1054#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 0
    end
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 249
      Height = 41
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        249
        41)
      object lblSuccess: TLabel
        Left = 176
        Top = 8
        Width = 65
        Height = 25
        AutoSize = False
      end
      object btnConnect: TButton
        Left = 0
        Top = 8
        Width = 89
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = #1057#1086#1077#1076#1080#1085#1080#1090#1100
        TabOrder = 0
        OnClick = btnConnectClick
      end
      object btnTest: TButton
        Left = 92
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = #1058#1077#1089#1090
        TabOrder = 1
        OnClick = btnTestClick
      end
    end
  end
end
