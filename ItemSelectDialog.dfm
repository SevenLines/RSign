object ItemSelectDialogForm: TItemSelectDialogForm
  Left = 319
  Top = 146
  AutoSize = True
  BorderStyle = bsDialog
  BorderWidth = 4
  Caption = 'ItemSelectDialogForm'
  ClientHeight = 91
  ClientWidth = 330
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object lblMessage: TLabel
    Left = 0
    Top = 0
    Width = 330
    Height = 26
    Align = alClient
    Alignment = taCenter
  end
  object Panel1: TPanel
    Left = 0
    Top = 50
    Width = 330
    Height = 41
    Align = alBottom
    AutoSize = True
    BevelOuter = bvNone
    BevelWidth = 4
    BorderWidth = 8
    TabOrder = 0
    object Button1: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Ok'
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 88
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 26
    Width = 330
    Height = 24
    Align = alBottom
    AutoSize = True
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      330
      24)
    object cmbOptions: TComboBox
      Left = 0
      Top = 0
      Width = 327
      Height = 24
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 16
      TabOrder = 0
      Text = 'cmbOptions'
    end
  end
end