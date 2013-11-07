object frmConstHelp: TfrmConstHelp
  Left = 396
  Top = 105
  Width = 517
  Height = 325
  Caption = #1057#1087#1088#1072#1074#1082#1072' '#1087#1086' '#1082#1086#1085#1089#1090#1072#1085#1090#1072#1084
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 509
    Height = 298
    ActivePage = TabSheet2
    Align = alClient
    TabIndex = 2
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1054#1073#1098#1077#1082#1090#1099
      object listObjects: TListView
        Left = 0
        Top = 41
        Width = 501
        Height = 229
        Align = alClient
        Columns = <
          item
            Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1086#1073#1098#1077#1082#1090#1072
            Width = 320
          end
          item
            Caption = #1053#1086#1084#1077#1088
          end>
        GridLines = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnChange = listObjectsChange
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 501
        Height = 41
        Align = alTop
        TabOrder = 1
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1061#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080
      ImageIndex = 2
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 501
        Height = 41
        Align = alTop
        TabOrder = 0
      end
      object listPropertys: TListView
        Left = 0
        Top = 41
        Width = 501
        Height = 229
        Align = alClient
        Columns = <
          item
            Caption = #1053#1072#1079#1074#1072#1085#1080#1077
            Width = 200
          end
          item
            Caption = #1053#1086#1084#1077#1088
          end
          item
            Caption = #1050#1088#1072#1090#1082#1086#1077' '#1085#1072#1079#1074#1072#1085#1080#1077
            Width = 100
          end
          item
            Caption = #1048#1084#1103' '#1089#1074#1086#1081#1089#1090#1074#1072
            Width = 100
          end
          item
            Caption = #1058#1080#1087
            Width = 80
          end>
        GridLines = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
        OnChange = listPropertysChange
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1047#1085#1072#1095#1077#1085#1080#1103' '#1093#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082
      ImageIndex = 1
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 501
        Height = 41
        Align = alTop
        TabOrder = 0
      end
      object listValues: TListView
        Left = 0
        Top = 41
        Width = 501
        Height = 229
        Align = alClient
        Columns = <
          item
            Caption = #1058#1077#1082#1089#1090
            Width = 300
          end
          item
            Caption = #1053#1086#1084#1077#1088
          end
          item
            Caption = #1050#1088#1072#1090#1082#1080#1081' '#1090#1077#1082#1089#1090
            Width = 100
          end>
        GridLines = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
      end
    end
  end
end
