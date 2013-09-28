object VisCondEdit: TVisCondEdit
  Left = 192
  Top = 107
  Width = 464
  Height = 287
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1091#1089#1083#1086#1074#1080#1077' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnHide = FormHide
  PixelsPerInch = 96
  TextHeight = 13
  object ObjCaption: TLabel
    Left = 0
    Top = 0
    Width = 456
    Height = 25
    Align = alTop
    Alignment = taCenter
    AutoSize = False
    Caption = 'ObjCaption'
  end
  object Splitter1: TSplitter
    Left = 201
    Top = 25
    Width = 8
    Height = 159
    Cursor = crHSplit
  end
  object Panel1: TPanel
    Left = 0
    Top = 184
    Width = 456
    Height = 76
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      456
      76)
    object Button1: TButton
      Left = 16
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Ok'
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 360
      Top = 40
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1084#1077#1085#1072
      ModalResult = 2
      TabOrder = 1
    end
    object CondEdit: TEdit
      Left = 8
      Top = 8
      Width = 441
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      HideSelection = False
      TabOrder = 2
    end
  end
  object PropList: TListBox
    Left = 0
    Top = 25
    Width = 201
    Height = 159
    Align = alLeft
    ItemHeight = 13
    TabOrder = 1
    OnClick = PropListClick
    OnDblClick = PropListDblClick
  end
  object ValList: TListBox
    Left = 209
    Top = 25
    Width = 247
    Height = 159
    Align = alClient
    ItemHeight = 13
    TabOrder = 2
    OnDblClick = ValListDblClick
  end
end
