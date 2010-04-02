object OptionsFrame: TOptionsFrame
  Left = 0
  Top = 0
  Width = 218
  Height = 297
  TabOrder = 0
  object GroupBox5: TGroupBox
    Left = -1
    Top = -1
    Width = 217
    Height = 297
    Caption = 'Options'
    TabOrder = 0
    object GroupBox6: TGroupBox
      Left = 8
      Top = 24
      Width = 201
      Height = 169
      Caption = 'Bit Depth'
      TabOrder = 2
      object GroupBox8: TGroupBox
        Left = 8
        Top = 24
        Width = 57
        Height = 137
        Caption = 'IN'
        TabOrder = 0
        object RadioButton_In6: TRadioButton
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = '6'
          TabOrder = 0
        end
        object RadioButton_In8: TRadioButton
          Left = 8
          Top = 64
          Width = 40
          Height = 17
          Caption = '8'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object RadioButton_In10: TRadioButton
          Left = 8
          Top = 104
          Width = 40
          Height = 17
          Caption = '10'
          TabOrder = 2
        end
      end
      object GroupBox9: TGroupBox
        Left = 72
        Top = 24
        Width = 57
        Height = 137
        Caption = 'LUT'
        TabOrder = 1
        object RadioButton_Lut10: TRadioButton
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = '10'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton_Lut12: TRadioButton
          Left = 8
          Top = 64
          Width = 40
          Height = 17
          Caption = '12'
          TabOrder = 1
        end
      end
      object GroupBox10: TGroupBox
        Left = 136
        Top = 24
        Width = 57
        Height = 137
        Caption = 'OUT'
        TabOrder = 2
        object RadioButton_Out6: TRadioButton
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = '6'
          TabOrder = 0
        end
        object RadioButton_Out8: TRadioButton
          Left = 8
          Top = 64
          Width = 40
          Height = 17
          Caption = '8'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object RadioButton_Out10: TRadioButton
          Left = 8
          Top = 104
          Width = 40
          Height = 17
          Caption = '10'
          Enabled = False
          TabOrder = 2
        end
      end
    end
    object CheckBox_Gamma256: TCheckBox
      Left = 112
      Top = 184
      Width = 97
      Height = 25
      Caption = 'Gamma 256'
      TabOrder = 0
    end
    object CheckBox_AvoidNoise: TCheckBox
      Left = 8
      Top = 232
      Width = 137
      Height = 25
      Caption = 'Avoid FRC Noise'
      TabOrder = 1
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 8
      Top = 200
      Width = 153
      Height = 25
      Caption = 'Keep Max Luminance'
      TabOrder = 3
    end
  end
end
