object Form4: TForm4
  Left = 290
  Top = 175
  Width = 434
  Height = 119
  Caption = 'Form4'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefaultSizeOnly
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 78
    Height = 13
    Caption = 'Table Step used'
  end
  object sg_table_step: TStringGrid
    Left = 8
    Top = 24
    Width = 289
    Height = 49
    ColCount = 9
    DefaultColWidth = 30
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
    OnKeyDown = sg_table_stepKeyDown
  end
  object btn_set_new_table_step: TButton
    Left = 304
    Top = 40
    Width = 65
    Height = 25
    Caption = 'Done'
    TabOrder = 1
    OnClick = btn_set_new_table_stepClick
  end
end
