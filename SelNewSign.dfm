object AddSignFrm: TAddSignFrm
  Left = 410
  Top = 175
  Width = 513
  Height = 396
  BorderIcons = [biSystemMenu]
  Caption = #1042#1099#1073#1086#1088' '#1076#1086#1088#1086#1078#1085#1086#1075#1086' '#1079#1085#1072#1082#1072
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 500
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 369
    Top = 0
    Width = 8
    Height = 362
    Cursor = crHSplit
    OnMoved = Splitter1Moved
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 229
    Height = 362
    Align = alLeft
    TabOrder = 0
    DesignSize = (
      229
      362)
    object Label1: TLabel
      Left = 13
      Top = 13
      Width = 52
      Height = 13
      Caption = #1058#1080#1087' '#1079#1085#1072#1082#1072
    end
    object Image1: TImage
      Left = 13
      Top = 228
      Width = 202
      Height = 85
      Center = True
      Stretch = True
    end
    object Label3: TLabel
      Left = 13
      Top = 169
      Width = 70
      Height = 13
      Caption = #1050#1086#1076' '#1087#1086' '#1043#1054#1057#1058#1091
    end
    object ListTypes: TListBox
      Left = 13
      Top = 33
      Width = 202
      Height = 124
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListTypesClick
    end
    object Button1: TButton
      Left = 16
      Top = 328
      Width = 78
      Height = 26
      Anchors = [akLeft, akBottom]
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
    end
    object Button2: TButton
      Left = 130
      Top = 328
      Width = 66
      Height = 26
      Anchors = [akLeft, akBottom]
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      ModalResult = 2
      TabOrder = 2
    end
    object GOSTCode: TEdit
      Left = 13
      Top = 189
      Width = 202
      Height = 21
      Enabled = False
      TabOrder = 3
    end
  end
  object Panel2: TPanel
    Left = 229
    Top = 0
    Width = 140
    Height = 362
    Align = alLeft
    TabOrder = 1
    object Label2: TLabel
      Left = 1
      Top = 1
      Width = 138
      Height = 13
      Align = alTop
      Alignment = taCenter
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1079#1085#1072#1082#1072
    end
    object ListKinds: TListBox
      Left = 1
      Top = 14
      Width = 138
      Height = 347
      Style = lbOwnerDrawVariable
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListKindsClick
      OnDrawItem = ListKindsDrawItem
      OnMeasureItem = VariantListMeasureItem
    end
  end
  object Panel3: TPanel
    Left = 377
    Top = 0
    Width = 128
    Height = 362
    Align = alClient
    TabOrder = 2
    object Label4: TLabel
      Left = 1
      Top = 1
      Width = 126
      Height = 13
      Align = alTop
      Alignment = taCenter
      Caption = #1053#1072#1095#1077#1088#1090#1072#1085#1080#1077' '#1079#1085#1072#1082#1072
    end
    object VariantList: TListBox
      Left = 1
      Top = 14
      Width = 126
      Height = 347
      Style = lbOwnerDrawVariable
      Align = alClient
      ItemHeight = 32
      TabOrder = 0
      OnClick = VariantListClick
      OnDrawItem = VariantListDrawItem
      OnMeasureItem = VariantListMeasureItem
    end
  end
end
