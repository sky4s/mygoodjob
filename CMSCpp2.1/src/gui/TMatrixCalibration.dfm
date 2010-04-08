object MatrixCalibrationForm: TMatrixCalibrationForm
  Left = 300
  Top = 300
  Width = 538
  Height = 482
  Caption = 'Matrix Calibration'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Label13: TLabel
    Left = 165
    Top = 424
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 176
    Width = 497
    Height = 177
    Caption = 'Matrix Calibration Setting'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 42
      Height = 16
      Caption = 'Pattern'
    end
    object Label2: TLabel
      Left = 72
      Top = 48
      Width = 10
      Height = 16
      Caption = 'R'
    end
    object Label3: TLabel
      Left = 72
      Top = 80
      Width = 10
      Height = 16
      Caption = 'G'
    end
    object Label4: TLabel
      Left = 72
      Top = 112
      Width = 9
      Height = 16
      Caption = 'B'
    end
    object Label5: TLabel
      Left = 72
      Top = 144
      Width = 13
      Height = 16
      Caption = 'W'
    end
    object Label6: TLabel
      Left = 120
      Top = 24
      Width = 6
      Height = 16
      Caption = 'x'
    end
    object Label7: TLabel
      Left = 176
      Top = 24
      Width = 7
      Height = 16
      Caption = 'y'
    end
    object Label8: TLabel
      Left = 224
      Top = 24
      Width = 14
      Height = 16
      Caption = 'Lv'
    end
    object Label9: TLabel
      Left = 272
      Top = 48
      Width = 57
      Height = 16
      Caption = 'Matrix CH'
    end
    object Label10: TLabel
      Left = 272
      Top = 80
      Width = 13
      Height = 16
      Caption = 'ID'
    end
    object Edit_R: TEdit
      Left = 8
      Top = 48
      Width = 49
      Height = 24
      TabOrder = 0
      Text = '255'
    end
    object Edit_G: TEdit
      Left = 8
      Top = 80
      Width = 49
      Height = 24
      TabOrder = 1
      Text = '255'
    end
    object Edit_B: TEdit
      Left = 8
      Top = 112
      Width = 49
      Height = 24
      TabOrder = 2
      Text = '255'
    end
    object Edit_Rx: TEdit
      Left = 96
      Top = 48
      Width = 49
      Height = 24
      TabOrder = 3
      Text = '0'
    end
    object Edit_Gx: TEdit
      Left = 96
      Top = 80
      Width = 49
      Height = 24
      TabOrder = 4
      Text = '0'
    end
    object Edit_Wx: TEdit
      Left = 96
      Top = 144
      Width = 49
      Height = 24
      TabOrder = 5
      Text = '0'
    end
    object Edit_Bx: TEdit
      Left = 96
      Top = 112
      Width = 49
      Height = 24
      TabOrder = 6
      Text = '0'
    end
    object Edit_Ry: TEdit
      Left = 152
      Top = 48
      Width = 49
      Height = 24
      TabOrder = 7
      Text = '0'
    end
    object Edit_Gy: TEdit
      Left = 152
      Top = 80
      Width = 49
      Height = 24
      TabOrder = 8
      Text = '0'
    end
    object Edit_By: TEdit
      Left = 152
      Top = 112
      Width = 49
      Height = 24
      TabOrder = 9
      Text = '0'
    end
    object Edit_Wy: TEdit
      Left = 152
      Top = 144
      Width = 49
      Height = 24
      TabOrder = 10
      Text = '0'
    end
    object Edit_RLv: TEdit
      Left = 208
      Top = 48
      Width = 49
      Height = 24
      TabOrder = 11
      Text = '0'
    end
    object Edit_GLv: TEdit
      Left = 208
      Top = 80
      Width = 49
      Height = 24
      TabOrder = 12
      Text = '0'
    end
    object Edit_BLv: TEdit
      Left = 208
      Top = 112
      Width = 49
      Height = 24
      TabOrder = 13
      Text = '0'
    end
    object Edit_WLv: TEdit
      Left = 208
      Top = 144
      Width = 49
      Height = 24
      TabOrder = 14
      Text = '0'
    end
    object Edit_MatrixChannel: TEdit
      Left = 336
      Top = 48
      Width = 73
      Height = 24
      TabOrder = 15
      Text = '1'
    end
    object Edit_ID: TEdit
      Left = 336
      Top = 80
      Width = 73
      Height = 24
      TabOrder = 16
      Text = ' '
    end
    object Button_Load: TButton
      Left = 272
      Top = 144
      Width = 105
      Height = 25
      Caption = 'Load'
      TabOrder = 17
    end
    object Button_MatrixCalibrate: TButton
      Left = 384
      Top = 144
      Width = 105
      Height = 25
      Caption = 'Matrirx Calibrate'
      TabOrder = 18
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 360
    Width = 497
    Height = 57
    Caption = 'Backup'
    TabOrder = 1
    object Label11: TLabel
      Left = 16
      Top = 24
      Width = 19
      Height = 16
      Caption = 'CH'
    end
    object Label12: TLabel
      Left = 88
      Top = 24
      Width = 33
      Height = 16
      Caption = 'to CH'
    end
    object Edit_BackupStart: TEdit
      Left = 48
      Top = 24
      Width = 33
      Height = 24
      TabOrder = 0
      Text = '0'
    end
    object Edit_BackupEnd: TEdit
      Left = 128
      Top = 24
      Width = 33
      Height = 24
      TabOrder = 1
      Text = '99'
    end
    object Button_SaveToFile: TButton
      Left = 272
      Top = 24
      Width = 105
      Height = 25
      Caption = 'Save To File'
      TabOrder = 2
    end
    object Button_LoadFromFile: TButton
      Left = 384
      Top = 24
      Width = 105
      Height = 25
      Caption = 'Load From File'
      TabOrder = 3
    end
  end
  inline TCA210SettingFrame1: TCA210SettingFrame
    Left = 16
    Top = 16
    Width = 499
    Height = 154
    TabOrder = 2
    inherited GroupBox1: TGroupBox
      inherited Button_Connect: TButton
        OnClick = TCA210SettingFrame1Button_ConnectClick
      end
    end
  end
end
