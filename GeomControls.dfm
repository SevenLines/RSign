object frmGeomControls: TfrmGeomControls
  Left = 442
  Top = 212
  Width = 345
  Height = 213
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    337
    186)
  PixelsPerInch = 96
  TextHeight = 13
  object clbCeomControls: TCheckListBox
    Left = 0
    Top = 0
    Width = 337
    Height = 152
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelEdges = []
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = bsNone
    Color = clMenu
    ItemHeight = 13
    TabOrder = 0
  end
  object Button1: TButton
    Left = 66
    Top = 158
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1054#1082
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ModalResult = 1
    ParentFont = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 193
    Top = 158
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ModalResult = 2
    ParentFont = False
    TabOrder = 2
  end
end
