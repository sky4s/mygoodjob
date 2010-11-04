object GamutSetupForm: TGamutSetupForm
  Left = 710
  Top = 263
  Width = 191
  Height = 355
  Caption = 'Gamut Setup'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 169
    Height = 129
    Caption = 'Source Panel'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 32
      Width = 8
      Height = 13
      Caption = 'R'
    end
    object Label2: TLabel
      Left = 8
      Top = 56
      Width = 8
      Height = 13
      Caption = 'G'
    end
    object Label3: TLabel
      Left = 8
      Top = 80
      Width = 7
      Height = 13
      Caption = 'B'
    end
    object Label4: TLabel
      Left = 8
      Top = 104
      Width = 36
      Height = 13
      Caption = 'Gamma'
    end
    object Label5: TLabel
      Left = 40
      Top = 16
      Width = 5
      Height = 13
      Caption = 'x'
    end
    object Label6: TLabel
      Left = 88
      Top = 16
      Width = 5
      Height = 13
      Caption = 'y'
    end
    object Label7: TLabel
      Left = 136
      Top = 16
      Width = 7
      Height = 13
      Caption = 'Y'
    end
    object Edit_SourceRx: TEdit
      Left = 24
      Top = 32
      Width = 41
      Height = 21
      TabOrder = 0
    end
    object Edit_SourceRy: TEdit
      Left = 72
      Top = 32
      Width = 41
      Height = 21
      TabOrder = 1
    end
    object Edit_SourceRLv: TEdit
      Left = 120
      Top = 32
      Width = 41
      Height = 21
      TabOrder = 2
    end
    object Edit_SourceGx: TEdit
      Left = 24
      Top = 56
      Width = 41
      Height = 21
      TabOrder = 3
    end
    object Edit_SourceGy: TEdit
      Left = 72
      Top = 56
      Width = 41
      Height = 21
      TabOrder = 4
    end
    object Edit_SourceGLv: TEdit
      Left = 120
      Top = 56
      Width = 41
      Height = 21
      TabOrder = 5
    end
    object Edit_SourceBx: TEdit
      Left = 24
      Top = 80
      Width = 41
      Height = 21
      TabOrder = 6
    end
    object Edit_SourceBy: TEdit
      Left = 72
      Top = 80
      Width = 41
      Height = 21
      TabOrder = 7
    end
    object Edit_SourceBLv: TEdit
      Left = 120
      Top = 80
      Width = 41
      Height = 21
      TabOrder = 8
    end
    object Edit_SourceGamma: TEdit
      Left = 56
      Top = 104
      Width = 41
      Height = 21
      TabOrder = 9
      Text = '2.2'
    end
    object Button1: TButton
      Left = 104
      Top = 104
      Width = 33
      Height = 17
      Caption = 'Test'
      TabOrder = 10
      OnClick = Button1Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 144
    Width = 169
    Height = 145
    Caption = 'Target Panel'
    TabOrder = 1
    object Label8: TLabel
      Left = 8
      Top = 48
      Width = 8
      Height = 13
      Caption = 'R'
    end
    object Label9: TLabel
      Left = 8
      Top = 72
      Width = 8
      Height = 13
      Caption = 'G'
    end
    object Label10: TLabel
      Left = 8
      Top = 96
      Width = 7
      Height = 13
      Caption = 'B'
    end
    object Label11: TLabel
      Left = 8
      Top = 120
      Width = 36
      Height = 13
      Caption = 'Gamma'
    end
    object Label12: TLabel
      Left = 40
      Top = 32
      Width = 5
      Height = 13
      Caption = 'x'
    end
    object Label13: TLabel
      Left = 88
      Top = 32
      Width = 5
      Height = 13
      Caption = 'y'
    end
    object Label14: TLabel
      Left = 136
      Top = 32
      Width = 7
      Height = 13
      Caption = 'Y'
    end
    object Edit_TargetRx: TEdit
      Left = 24
      Top = 48
      Width = 41
      Height = 21
      TabOrder = 0
    end
    object Edit_TargetRy: TEdit
      Left = 72
      Top = 48
      Width = 41
      Height = 21
      TabOrder = 1
    end
    object Edit_TargetRLv: TEdit
      Left = 120
      Top = 48
      Width = 41
      Height = 21
      TabOrder = 2
    end
    object Edit_TargetGx: TEdit
      Left = 24
      Top = 72
      Width = 41
      Height = 21
      TabOrder = 3
    end
    object Edit_TargetGy: TEdit
      Left = 72
      Top = 72
      Width = 41
      Height = 21
      TabOrder = 4
    end
    object Edit_TargetGLv: TEdit
      Left = 120
      Top = 72
      Width = 41
      Height = 21
      TabOrder = 5
    end
    object Edit_TargetBx: TEdit
      Left = 24
      Top = 96
      Width = 41
      Height = 21
      TabOrder = 6
    end
    object Edit_TargetBy: TEdit
      Left = 72
      Top = 96
      Width = 41
      Height = 21
      TabOrder = 7
    end
    object Edit_TargetBLv: TEdit
      Left = 120
      Top = 96
      Width = 41
      Height = 21
      TabOrder = 8
    end
    object Edit_TargetGamma: TEdit
      Left = 56
      Top = 120
      Width = 41
      Height = 21
      TabOrder = 9
      Text = '2.2'
    end
    object CheckBox_sRGB: TCheckBox
      Left = 8
      Top = 16
      Width = 65
      Height = 17
      Caption = 'sRGB'
      TabOrder = 10
      OnClick = CheckBox_sRGBClick
    end
  end
  object Button_Setup: TButton
    Left = 56
    Top = 296
    Width = 65
    Height = 25
    Caption = 'Setup'
    TabOrder = 2
    OnClick = Button_SetupClick
  end
end
