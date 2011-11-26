object DCRForm1: TDCRForm1
  Left = 534
  Top = 232
  Width = 746
  Height = 552
  Align = alCustom
  Caption = 'DCR'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 908
    Height = 603
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'DCR Setting'
      object CheckBox1: TCheckBox
        Left = 10
        Top = 12
        Width = 130
        Height = 22
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object GroupBox1: TGroupBox
        Left = 463
        Top = 457
        Width = 434
        Height = 103
        Caption = 'BackLight Gradient Step'
        TabOrder = 1
        object Label3: TLabel
          Left = 12
          Top = 28
          Width = 41
          Height = 16
          Caption = 'Label3'
        end
        object Label32: TLabel
          Left = 12
          Top = 53
          Width = 48
          Height = 16
          Caption = 'Label32'
        end
        object Label35: TLabel
          Left = 12
          Top = 78
          Width = 34
          Height = 16
          Caption = 'Label'
        end
        object CheckBox6: TCheckBox
          Left = 167
          Top = 0
          Width = 200
          Height = 22
          Caption = 'CheckBox6'
          TabOrder = 0
        end
        object ScrollBar3: TScrollBar
          Left = 167
          Top = 25
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 1
        end
        object StaticText3: TStaticText
          Left = 384
          Top = 26
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText3'
          TabOrder = 2
        end
        object ScrollBar28: TScrollBar
          Left = 167
          Top = 50
          Width = 210
          Height = 23
          PageSize = 0
          TabOrder = 3
        end
        object StaticText28: TStaticText
          Left = 384
          Top = 52
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText28'
          TabOrder = 4
        end
        object ScrollBar31: TScrollBar
          Left = 167
          Top = 76
          Width = 208
          Height = 22
          PageSize = 0
          TabOrder = 5
        end
        object StaticText31: TStaticText
          Left = 385
          Top = 76
          Width = 63
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 6
        end
      end
      object GroupBox2: TGroupBox
        Left = 10
        Top = 457
        Width = 445
        Height = 103
        Caption = 'Histogram difference ratio'
        TabOrder = 2
        object Label4: TLabel
          Left = 12
          Top = 27
          Width = 41
          Height = 16
          Caption = 'Label4'
        end
        object ScrollBar4: TScrollBar
          Left = 177
          Top = 25
          Width = 208
          Height = 22
          PageSize = 0
          TabOrder = 0
        end
        object StaticText4: TStaticText
          Left = 394
          Top = 25
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText4'
          TabOrder = 1
        end
        object CheckBox7: TCheckBox
          Left = 207
          Top = 0
          Width = 209
          Height = 22
          Caption = 'CheckBox7'
          TabOrder = 2
        end
        object GroupBox17: TGroupBox
          Left = 4
          Top = 52
          Width = 430
          Height = 40
          Caption = 'Noise Filter'
          TabOrder = 3
          object Label42: TLabel
            Left = 12
            Top = 17
            Width = 34
            Height = 16
            Caption = 'Label'
          end
          object ScrollBar38: TScrollBar
            Left = 174
            Top = 12
            Width = 208
            Height = 22
            PageSize = 0
            TabOrder = 0
          end
          object StaticText38: TStaticText
            Left = 390
            Top = 12
            Width = 63
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 1
          end
        end
      end
      object GroupBox6: TGroupBox
        Left = 463
        Top = 103
        Width = 434
        Height = 277
        Caption = 'Duty Detect'
        TabOrder = 3
        object Label10: TLabel
          Left = 10
          Top = 59
          Width = 48
          Height = 16
          Caption = 'Label10'
        end
        object Label11: TLabel
          Left = 10
          Top = 86
          Width = 48
          Height = 16
          Caption = 'Label11'
        end
        object Label81: TLabel
          Left = 10
          Top = 30
          Width = 48
          Height = 16
          Caption = 'Label81'
        end
        object ScrollBar10: TScrollBar
          Left = 167
          Top = 59
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 0
        end
        object StaticText10: TStaticText
          Left = 384
          Top = 60
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText10'
          TabOrder = 1
        end
        object ScrollBar11: TScrollBar
          Left = 167
          Top = 87
          Width = 210
          Height = 23
          PageSize = 0
          TabOrder = 2
        end
        object StaticText11: TStaticText
          Left = 384
          Top = 86
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText11'
          TabOrder = 3
        end
        object CheckBox5: TCheckBox
          Left = 167
          Top = 0
          Width = 208
          Height = 22
          Caption = 'CheckBox5'
          TabOrder = 4
        end
        object GroupBox3: TGroupBox
          Left = 4
          Top = 112
          Width = 424
          Height = 160
          Caption = 'PWM Frequency Setting'
          TabOrder = 5
          object Label5: TLabel
            Left = 12
            Top = 52
            Width = 41
            Height = 16
            Caption = 'Label5'
          end
          object Label14: TLabel
            Left = 12
            Top = 25
            Width = 48
            Height = 16
            Caption = 'Label14'
          end
          object ComboBox1: TComboBox
            Left = 167
            Top = 20
            Width = 151
            Height = 24
            ItemHeight = 16
            TabOrder = 0
            Text = 'ComboBox1'
          end
          object ScrollBar5: TScrollBar
            Left = 167
            Top = 49
            Width = 210
            Height = 22
            PageSize = 0
            TabOrder = 1
          end
          object StaticText5: TStaticText
            Left = 384
            Top = 49
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText5'
            TabOrder = 2
          end
          object GroupBox7: TGroupBox
            Left = 4
            Top = 74
            Width = 418
            Height = 80
            Caption = 'PWM_Coefficient'
            TabOrder = 3
            object Label13: TLabel
              Left = 10
              Top = 52
              Width = 48
              Height = 16
              Caption = 'Label13'
            end
            object Label12: TLabel
              Left = 10
              Top = 25
              Width = 48
              Height = 16
              Caption = 'Label12'
            end
            object ScrollBar12: TScrollBar
              Left = 164
              Top = 23
              Width = 209
              Height = 23
              PageSize = 0
              TabOrder = 0
            end
            object ScrollBar13: TScrollBar
              Left = 164
              Top = 52
              Width = 209
              Height = 22
              PageSize = 0
              TabOrder = 1
            end
            object StaticText12: TStaticText
              Left = 380
              Top = 25
              Width = 77
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText12'
              TabOrder = 2
            end
            object StaticText13: TStaticText
              Left = 380
              Top = 50
              Width = 77
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText13'
              TabOrder = 3
            end
            object CheckBox9: TCheckBox
              Left = 170
              Top = 0
              Width = 197
              Height = 22
              Caption = 'CheckBox9'
              TabOrder = 4
            end
          end
        end
        object ComboBox13: TComboBox
          Left = 167
          Top = 25
          Width = 258
          Height = 24
          ItemHeight = 16
          TabOrder = 6
          Text = 'ComboBox13'
        end
      end
      object CheckBox12: TCheckBox
        Left = 10
        Top = 46
        Width = 120
        Height = 22
        Caption = 'CheckBox12'
        TabOrder = 4
      end
      object GroupBox32: TGroupBox
        Left = 10
        Top = 121
        Width = 445
        Height = 339
        Caption = 'BL_IDX/ PWM modulation'
        TabOrder = 5
        object GroupBox31: TGroupBox
          Left = 10
          Top = 16
          Width = 426
          Height = 80
          Caption = 'Modulation Select '
          TabOrder = 0
          object Label1: TLabel
            Left = 10
            Top = 49
            Width = 41
            Height = 16
            Caption = 'Label1'
          end
          object Label80: TLabel
            Left = 10
            Top = 21
            Width = 48
            Height = 16
            Caption = 'Label80'
          end
          object ScrollBar1: TScrollBar
            Left = 167
            Top = 49
            Width = 210
            Height = 22
            PageSize = 0
            TabOrder = 0
          end
          object StaticText1: TStaticText
            Left = 384
            Top = 49
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText1'
            TabOrder = 1
          end
          object ComboBox12: TComboBox
            Left = 167
            Top = 15
            Width = 248
            Height = 24
            ItemHeight = 16
            TabOrder = 2
            Text = 'ComboBox12'
          end
        end
        object GroupBox5: TGroupBox
          Left = 10
          Top = 95
          Width = 426
          Height = 127
          Caption = 'Image loading ratio boundary and BL_IDX curve slope setting'
          TabOrder = 1
          object Label8: TLabel
            Left = 10
            Top = 48
            Width = 41
            Height = 16
            Caption = 'Label8'
          end
          object Label9: TLabel
            Left = 10
            Top = 22
            Width = 41
            Height = 16
            Caption = 'Label9'
          end
          object ScrollBar8: TScrollBar
            Left = 167
            Top = 49
            Width = 210
            Height = 22
            PageSize = 0
            TabOrder = 0
          end
          object StaticText8: TStaticText
            Left = 384
            Top = 49
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText8'
            TabOrder = 1
          end
          object ScrollBar9: TScrollBar
            Left = 167
            Top = 20
            Width = 210
            Height = 22
            PageSize = 0
            TabOrder = 2
          end
          object StaticText9: TStaticText
            Left = 384
            Top = 20
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText9'
            TabOrder = 3
          end
          object LabeledEdit1: TLabeledEdit
            Left = 10
            Top = 92
            Width = 90
            Height = 21
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit1'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 4
          end
        end
        object GroupBox18: TGroupBox
          Left = 10
          Top = 220
          Width = 426
          Height = 41
          TabOrder = 2
          object Label41: TLabel
            Left = 12
            Top = 14
            Width = 34
            Height = 16
            Caption = 'Label'
          end
          object ScrollBar37: TScrollBar
            Left = 167
            Top = 12
            Width = 210
            Height = 22
            PageSize = 0
            TabOrder = 0
          end
          object StaticText37: TStaticText
            Left = 384
            Top = 12
            Width = 63
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 1
          end
        end
        object GroupBox4: TGroupBox
          Left = 10
          Top = 260
          Width = 426
          Height = 77
          Caption = 'Power saving mode'
          TabOrder = 3
          object Label33: TLabel
            Left = 10
            Top = 27
            Width = 48
            Height = 16
            Caption = 'Label33'
          end
          object Label34: TLabel
            Left = 10
            Top = 52
            Width = 48
            Height = 16
            Caption = 'Label34'
          end
          object ScrollBar29: TScrollBar
            Left = 167
            Top = 25
            Width = 208
            Height = 22
            PageSize = 0
            TabOrder = 0
          end
          object CheckBox21: TCheckBox
            Left = 167
            Top = 0
            Width = 200
            Height = 22
            Caption = 'CheckBox21'
            TabOrder = 1
          end
          object ScrollBar30: TScrollBar
            Left = 167
            Top = 52
            Width = 208
            Height = 22
            PageSize = 0
            TabOrder = 2
          end
          object StaticText29: TStaticText
            Left = 384
            Top = 26
            Width = 77
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText29'
            TabOrder = 3
          end
          object StaticText30: TStaticText
            Left = 384
            Top = 52
            Width = 77
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText30'
            TabOrder = 4
          end
        end
      end
      object GroupBox42: TGroupBox
        Left = 10
        Top = 76
        Width = 445
        Height = 46
        Caption = 'GLT_Sharpness'
        TabOrder = 6
        object Label2: TLabel
          Left = 10
          Top = 18
          Width = 41
          Height = 16
          Caption = 'Label2'
        end
        object ScrollBar2: TScrollBar
          Left = 177
          Top = 16
          Width = 209
          Height = 22
          PageSize = 0
          TabOrder = 0
        end
        object StaticText2: TStaticText
          Left = 393
          Top = 16
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText2'
          TabOrder = 1
        end
      end
      object GroupBox20: TGroupBox
        Left = 463
        Top = 379
        Width = 434
        Height = 80
        Caption = 'Duty Smooth Change function'
        TabOrder = 7
        object Label43: TLabel
          Left = 12
          Top = 22
          Width = 34
          Height = 16
          Caption = 'Label'
        end
        object Label44: TLabel
          Left = 12
          Top = 47
          Width = 34
          Height = 16
          Caption = 'Label'
        end
        object ScrollBar39: TScrollBar
          Left = 167
          Top = 23
          Width = 208
          Height = 23
          PageSize = 0
          TabOrder = 0
        end
        object StaticText39: TStaticText
          Left = 384
          Top = 25
          Width = 63
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 1
        end
        object ScrollBar40: TScrollBar
          Left = 167
          Top = 52
          Width = 208
          Height = 22
          PageSize = 0
          TabOrder = 2
        end
        object StaticText40: TStaticText
          Left = 384
          Top = 50
          Width = 63
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 3
        end
        object CheckBox22: TCheckBox
          Left = 207
          Top = -1
          Width = 159
          Height = 22
          Caption = 'CheckBox22'
          TabOrder = 4
        end
      end
      object GroupBox44: TGroupBox
        Left = 463
        Top = 66
        Width = 434
        Height = 37
        TabOrder = 8
        object Label84: TLabel
          Left = 10
          Top = 12
          Width = 48
          Height = 16
          Caption = 'Label84'
        end
        object ComboBox16: TComboBox
          Left = 169
          Top = 9
          Width = 256
          Height = 24
          ItemHeight = 16
          TabOrder = 0
          Text = 'ComboBox16'
        end
      end
      object GroupBox46: TGroupBox
        Left = 103
        Top = -2
        Width = 173
        Height = 76
        Caption = 'XOR Operation'
        TabOrder = 9
        object CheckBox2: TCheckBox
          Left = 15
          Top = 15
          Width = 130
          Height = 22
          Caption = 'CheckBox2'
          TabOrder = 0
        end
        object GroupBox33: TGroupBox
          Left = 4
          Top = 34
          Width = 145
          Height = 40
          Caption = 'AND with DCREN pin'
          TabOrder = 1
          object CheckBox17: TCheckBox
            Left = 10
            Top = 15
            Width = 129
            Height = 22
            Caption = 'CheckBox17'
            TabOrder = 0
          end
        end
      end
      object GroupBox47: TGroupBox
        Left = 282
        Top = -2
        Width = 172
        Height = 76
        Caption = 'XOR Operation'
        TabOrder = 10
        object CheckBox3: TCheckBox
          Left = 14
          Top = 16
          Width = 130
          Height = 22
          Caption = 'CheckBox3'
          TabOrder = 0
        end
        object GroupBox48: TGroupBox
          Left = 4
          Top = 34
          Width = 145
          Height = 40
          Caption = 'AND with DCREN pin'
          TabOrder = 1
          object CheckBox18: TCheckBox
            Left = 10
            Top = 15
            Width = 119
            Height = 22
            Caption = 'CheckBox18'
            TabOrder = 0
          end
        end
      end
      object GroupBox12: TGroupBox
        Left = 463
        Top = -2
        Width = 434
        Height = 70
        Caption = 'GLT Demo mode'
        TabOrder = 11
        object Label83: TLabel
          Left = 11
          Top = 18
          Width = 48
          Height = 16
          Caption = 'Label83'
        end
        object CheckBox8: TCheckBox
          Left = 197
          Top = -1
          Width = 159
          Height = 22
          Caption = 'CheckBox8'
          TabOrder = 0
        end
        object ComboBox15: TComboBox
          Left = 10
          Top = 36
          Width = 415
          Height = 24
          ItemHeight = 16
          TabOrder = 1
          Text = 'ComboBox15'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'DCR | HDR Setting'
      ImageIndex = 1
      object GroupBox11: TGroupBox
        Left = 0
        Top = 0
        Width = 889
        Height = 554
        TabOrder = 0
        object GroupBox19: TGroupBox
          Left = 10
          Top = 194
          Width = 406
          Height = 51
          Caption = 'Demo Mode for Display BL'
          TabOrder = 0
          object Label40: TLabel
            Left = 12
            Top = 22
            Width = 34
            Height = 16
            Caption = 'Label'
          end
          object CheckBox20: TCheckBox
            Left = 207
            Top = -1
            Width = 188
            Height = 22
            Caption = 'CheckBox20'
            TabOrder = 0
          end
          object ScrollBar36: TScrollBar
            Left = 167
            Top = 22
            Width = 200
            Height = 22
            PageSize = 0
            TabOrder = 1
          end
          object StaticText36: TStaticText
            Left = 372
            Top = 22
            Width = 63
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 2
          end
        end
        object GroupBox37: TGroupBox
          Left = 591
          Top = 354
          Width = 199
          Height = 131
          Caption = 'interpolation_coeff'
          TabOrder = 1
          object LabeledEdit9: TLabeledEdit
            Left = 10
            Top = 39
            Width = 150
            Height = 21
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit9'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit10: TLabeledEdit
            Left = 10
            Top = 89
            Width = 150
            Height = 21
            EditLabel.Width = 107
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit10'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
        end
        object GroupBox38: TGroupBox
          Left = 10
          Top = 354
          Width = 188
          Height = 131
          Caption = 'section_num'
          TabOrder = 2
          object LabeledEdit2: TLabeledEdit
            Left = 10
            Top = 39
            Width = 150
            Height = 21
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit2'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit3: TLabeledEdit
            Left = 10
            Top = 89
            Width = 150
            Height = 21
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit3'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
        end
        object LabeledEdit4: TLabeledEdit
          Left = 423
          Top = 374
          Width = 151
          Height = 21
          EditLabel.Width = 99
          EditLabel.Height = 19
          EditLabel.Caption = 'LabeledEdit4'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
        end
        object GroupBox39: TGroupBox
          Left = 207
          Top = 354
          Width = 208
          Height = 131
          Caption = 'divide_num'
          TabOrder = 4
          object LabeledEdit5: TLabeledEdit
            Left = 10
            Top = 39
            Width = 150
            Height = 21
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit5'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit6: TLabeledEdit
            Left = 10
            Top = 89
            Width = 150
            Height = 21
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit6'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
        end
        object LabeledEdit7: TLabeledEdit
          Left = 423
          Top = 423
          Width = 151
          Height = 21
          EditLabel.Width = 99
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit7'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 5
        end
        object LabeledEdit8: TLabeledEdit
          Left = 423
          Top = 473
          Width = 151
          Height = 21
          EditLabel.Width = 99
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit8'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 6
        end
        object GroupBox43: TGroupBox
          Left = 10
          Top = 247
          Width = 406
          Height = 99
          Color = clBtnFace
          ParentColor = False
          TabOrder = 7
          object Label15: TLabel
            Left = 14
            Top = 11
            Width = 48
            Height = 16
            Caption = 'Label15'
          end
          object Label16: TLabel
            Left = 14
            Top = 41
            Width = 48
            Height = 16
            Caption = 'Label16'
          end
          object Label17: TLabel
            Left = 14
            Top = 73
            Width = 48
            Height = 16
            Caption = 'Label17'
          end
          object ComboBox2: TComboBox
            Left = 165
            Top = 11
            Width = 234
            Height = 21
            ItemHeight = 0
            TabOrder = 0
            Text = 'ComboBox2'
          end
          object ComboBox3: TComboBox
            Left = 164
            Top = 41
            Width = 234
            Height = 21
            ItemHeight = 0
            TabOrder = 1
            Text = 'ComboBox3'
          end
          object ComboBox4: TComboBox
            Left = 164
            Top = 70
            Width = 234
            Height = 21
            ItemHeight = 0
            TabOrder = 2
            Text = 'ComboBox4'
          end
        end
        object GroupBox21: TGroupBox
          Left = 423
          Top = 10
          Width = 455
          Height = 336
          Caption = 'HDR dedicated'
          TabOrder = 8
          object GroupBox23: TGroupBox
            Left = 14
            Top = 14
            Width = 430
            Height = 36
            TabOrder = 0
            object Label46: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar42: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText42: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox24: TGroupBox
            Left = 14
            Top = 53
            Width = 430
            Height = 37
            TabOrder = 1
            object Label47: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar43: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText43: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox25: TGroupBox
            Left = 14
            Top = 92
            Width = 430
            Height = 37
            TabOrder = 2
            object Label48: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar44: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText44: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox26: TGroupBox
            Left = 14
            Top = 132
            Width = 430
            Height = 37
            TabOrder = 3
            object Label49: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar45: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText45: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox27: TGroupBox
            Left = 14
            Top = 171
            Width = 430
            Height = 37
            TabOrder = 4
            object Label50: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar46: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText46: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox28: TGroupBox
            Left = 14
            Top = 210
            Width = 430
            Height = 37
            TabOrder = 5
            object Label51: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar47: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText47: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox29: TGroupBox
            Left = 14
            Top = 250
            Width = 430
            Height = 37
            TabOrder = 6
            object Label52: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar48: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText48: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox30: TGroupBox
            Left = 14
            Top = 289
            Width = 430
            Height = 37
            TabOrder = 7
            object Label53: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar49: TScrollBar
              Left = 226
              Top = 10
              Width = 160
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText49: TStaticText
              Left = 394
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
        end
        object GroupBox45: TGroupBox
          Left = 10
          Top = 10
          Width = 406
          Height = 40
          TabOrder = 9
          object Label54: TLabel
            Left = 14
            Top = 15
            Width = 48
            Height = 16
            Caption = 'Label54'
          end
          object ComboBox5: TComboBox
            Left = 167
            Top = 10
            Width = 234
            Height = 21
            ItemHeight = 0
            TabOrder = 0
            Text = 'ComboBox5'
          end
        end
        object GroupBox49: TGroupBox
          Left = 10
          Top = 58
          Width = 405
          Height = 129
          Caption = 'BL enhance function'
          TabOrder = 10
          object GroupBox15: TGroupBox
            Left = 10
            Top = 49
            Width = 395
            Height = 37
            TabOrder = 0
            object Label38: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar34: TScrollBar
              Left = 158
              Top = 10
              Width = 199
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText34: TStaticText
              Left = 364
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox14: TGroupBox
            Left = 11
            Top = 14
            Width = 394
            Height = 36
            TabOrder = 1
            object Label37: TLabel
              Left = 12
              Top = 11
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar33: TScrollBar
              Left = 156
              Top = 10
              Width = 200
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText33: TStaticText
              Left = 364
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox16: TGroupBox
            Left = 10
            Top = 85
            Width = 395
            Height = 37
            TabOrder = 2
            object Label39: TLabel
              Left = 12
              Top = 12
              Width = 34
              Height = 16
              Caption = 'Label'
            end
            object ScrollBar35: TScrollBar
              Left = 158
              Top = 10
              Width = 199
              Height = 22
              PageSize = 0
              TabOrder = 0
            end
            object StaticText35: TStaticText
              Left = 364
              Top = 10
              Width = 63
              Height = 20
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'HDR Setting'
      ImageIndex = 3
      object GroupBox34: TGroupBox
        Left = 423
        Top = 0
        Width = 466
        Height = 534
        TabOrder = 0
        object Label55: TLabel
          Left = 10
          Top = 30
          Width = 48
          Height = 16
          Caption = 'Label55'
        end
        object Label56: TLabel
          Left = 10
          Top = 59
          Width = 48
          Height = 16
          Caption = 'Label56'
        end
        object Label57: TLabel
          Left = 10
          Top = 89
          Width = 48
          Height = 16
          Caption = 'Label57'
        end
        object Label58: TLabel
          Left = 10
          Top = 118
          Width = 48
          Height = 16
          Caption = 'Label58'
        end
        object Label59: TLabel
          Left = 10
          Top = 148
          Width = 48
          Height = 16
          Caption = 'Label59'
        end
        object Label60: TLabel
          Left = 10
          Top = 177
          Width = 48
          Height = 16
          Caption = 'Label60'
        end
        object Label61: TLabel
          Left = 10
          Top = 207
          Width = 48
          Height = 16
          Caption = 'Label61'
        end
        object Label62: TLabel
          Left = 10
          Top = 236
          Width = 48
          Height = 16
          Caption = 'Label62'
        end
        object Label63: TLabel
          Left = 10
          Top = 266
          Width = 48
          Height = 16
          Caption = 'Label63'
        end
        object Label64: TLabel
          Left = 10
          Top = 295
          Width = 48
          Height = 16
          Caption = 'Label64'
        end
        object Label65: TLabel
          Left = 10
          Top = 325
          Width = 48
          Height = 16
          Caption = 'Label65'
        end
        object Label66: TLabel
          Left = 10
          Top = 354
          Width = 48
          Height = 16
          Caption = 'Label66'
        end
        object Label67: TLabel
          Left = 10
          Top = 384
          Width = 48
          Height = 16
          Caption = 'Label67'
        end
        object Label68: TLabel
          Left = 10
          Top = 414
          Width = 48
          Height = 16
          Caption = 'Label68'
        end
        object Label69: TLabel
          Left = 10
          Top = 443
          Width = 48
          Height = 16
          Caption = 'Label69'
        end
        object Label70: TLabel
          Left = 10
          Top = 473
          Width = 48
          Height = 16
          Caption = 'Label70'
        end
        object Label71: TLabel
          Left = 9
          Top = 502
          Width = 48
          Height = 16
          Caption = 'Label71'
        end
        object ScrollBar50: TScrollBar
          Left = 210
          Top = 30
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 0
        end
        object ScrollBar51: TScrollBar
          Left = 210
          Top = 59
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar52: TScrollBar
          Left = 210
          Top = 89
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 2
        end
        object ScrollBar53: TScrollBar
          Left = 210
          Top = 118
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 3
        end
        object ScrollBar54: TScrollBar
          Left = 210
          Top = 148
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 4
        end
        object ScrollBar55: TScrollBar
          Left = 210
          Top = 177
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 5
        end
        object ScrollBar56: TScrollBar
          Left = 210
          Top = 207
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 6
        end
        object ScrollBar57: TScrollBar
          Left = 210
          Top = 236
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 7
        end
        object ScrollBar58: TScrollBar
          Left = 210
          Top = 266
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 8
        end
        object ScrollBar59: TScrollBar
          Left = 210
          Top = 295
          Width = 210
          Height = 23
          PageSize = 0
          TabOrder = 9
        end
        object ScrollBar60: TScrollBar
          Left = 210
          Top = 325
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 10
        end
        object ScrollBar61: TScrollBar
          Left = 210
          Top = 354
          Width = 210
          Height = 23
          PageSize = 0
          TabOrder = 11
        end
        object ScrollBar62: TScrollBar
          Left = 210
          Top = 384
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 12
        end
        object ScrollBar63: TScrollBar
          Left = 210
          Top = 414
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 13
        end
        object ScrollBar64: TScrollBar
          Left = 210
          Top = 443
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 14
        end
        object ScrollBar65: TScrollBar
          Left = 210
          Top = 473
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 15
        end
        object ScrollBar66: TScrollBar
          Left = 210
          Top = 502
          Width = 210
          Height = 22
          PageSize = 0
          TabOrder = 16
        end
        object StaticText50: TStaticText
          Left = 427
          Top = 30
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 17
        end
        object StaticText51: TStaticText
          Left = 427
          Top = 59
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 18
        end
        object StaticText53: TStaticText
          Left = 427
          Top = 118
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 19
        end
        object StaticText54: TStaticText
          Left = 427
          Top = 148
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 20
        end
        object StaticText55: TStaticText
          Left = 427
          Top = 177
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 21
        end
        object StaticText56: TStaticText
          Left = 427
          Top = 207
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 22
        end
        object StaticText57: TStaticText
          Left = 427
          Top = 236
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 23
        end
        object StaticText58: TStaticText
          Left = 427
          Top = 266
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 24
        end
        object StaticText59: TStaticText
          Left = 427
          Top = 295
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 25
        end
        object StaticText60: TStaticText
          Left = 426
          Top = 325
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 26
        end
        object StaticText61: TStaticText
          Left = 426
          Top = 354
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 27
        end
        object StaticText62: TStaticText
          Left = 427
          Top = 384
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 28
        end
        object StaticText63: TStaticText
          Left = 427
          Top = 414
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 29
        end
        object StaticText64: TStaticText
          Left = 427
          Top = 443
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 30
        end
        object StaticText65: TStaticText
          Left = 427
          Top = 473
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 31
        end
        object StaticText66: TStaticText
          Left = 427
          Top = 502
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 32
        end
        object StaticText52: TStaticText
          Left = 427
          Top = 89
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText52'
          TabOrder = 33
        end
      end
      object GroupBox35: TGroupBox
        Left = 5
        Top = 169
        Width = 416
        Height = 306
        TabOrder = 1
        object Label72: TLabel
          Left = 10
          Top = 10
          Width = 48
          Height = 16
          Caption = 'Label72'
        end
        object Label73: TLabel
          Left = 10
          Top = 59
          Width = 48
          Height = 16
          Caption = 'Label73'
        end
        object Label74: TLabel
          Left = 10
          Top = 108
          Width = 48
          Height = 16
          Caption = 'Label74'
        end
        object Label75: TLabel
          Left = 10
          Top = 158
          Width = 48
          Height = 16
          Caption = 'Label75'
        end
        object Label76: TLabel
          Left = 10
          Top = 207
          Width = 48
          Height = 16
          Caption = 'Label76'
        end
        object Label77: TLabel
          Left = 10
          Top = 256
          Width = 48
          Height = 16
          Caption = 'Label77'
        end
        object ComboBox6: TComboBox
          Left = 10
          Top = 30
          Width = 396
          Height = 21
          ItemHeight = 0
          TabOrder = 0
          Text = 'ComboBox6'
        end
        object ComboBox7: TComboBox
          Left = 10
          Top = 79
          Width = 396
          Height = 21
          ItemHeight = 0
          TabOrder = 1
          Text = 'ComboBox7'
        end
        object ComboBox8: TComboBox
          Left = 10
          Top = 128
          Width = 396
          Height = 21
          ItemHeight = 0
          TabOrder = 2
          Text = 'ComboBox8'
        end
        object ComboBox9: TComboBox
          Left = 10
          Top = 177
          Width = 396
          Height = 21
          ItemHeight = 0
          TabOrder = 3
          Text = 'ComboBox9'
        end
        object ComboBox10: TComboBox
          Left = 10
          Top = 226
          Width = 396
          Height = 21
          ItemHeight = 0
          TabOrder = 4
          Text = 'ComboBox10'
        end
        object ComboBox11: TComboBox
          Left = 10
          Top = 276
          Width = 396
          Height = 21
          ItemHeight = 0
          TabOrder = 5
          Text = 'ComboBox11'
        end
      end
      object GroupBox36: TGroupBox
        Left = 5
        Top = 1
        Width = 416
        Height = 170
        TabOrder = 2
        object LabeledEdit11: TLabeledEdit
          Left = 10
          Top = 39
          Width = 150
          Height = 21
          EditLabel.Width = 107
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit11'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 0
        end
        object LabeledEdit12: TLabeledEdit
          Left = 10
          Top = 89
          Width = 150
          Height = 21
          EditLabel.Width = 107
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit12'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
        end
        object LabeledEdit13: TLabeledEdit
          Left = 10
          Top = 138
          Width = 150
          Height = 21
          EditLabel.Width = 107
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit13'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
        end
        object LabeledEdit14: TLabeledEdit
          Left = 236
          Top = 89
          Width = 150
          Height = 21
          EditLabel.Width = 107
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit14'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
        end
        object LabeledEdit15: TLabeledEdit
          Left = 236
          Top = 138
          Width = 150
          Height = 21
          EditLabel.Width = 107
          EditLabel.Height = 20
          EditLabel.Caption = 'LabeledEdit15'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
        end
      end
      object GroupBox22: TGroupBox
        Left = 6
        Top = 474
        Width = 415
        Height = 60
        TabOrder = 3
        object Label45: TLabel
          Left = 12
          Top = 12
          Width = 34
          Height = 16
          Caption = 'Label'
        end
        object ScrollBar41: TScrollBar
          Left = 10
          Top = 30
          Width = 365
          Height = 22
          PageSize = 0
          TabOrder = 0
        end
        object StaticText41: TStaticText
          Left = 380
          Top = 30
          Width = 63
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 1
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = '&ALS SMBUS'
      ImageIndex = 2
      object GroupBox8: TGroupBox
        Left = 0
        Top = 5
        Width = 436
        Height = 91
        Caption = 'SMBUS'
        TabOrder = 0
        object Label6: TLabel
          Left = 12
          Top = 34
          Width = 41
          Height = 16
          Caption = 'Label6'
        end
        object Label7: TLabel
          Left = 12
          Top = 64
          Width = 41
          Height = 16
          Caption = 'Label7'
        end
        object ScrollBar6: TScrollBar
          Left = 148
          Top = 30
          Width = 199
          Height = 22
          PageSize = 0
          TabOrder = 0
        end
        object StaticText6: TStaticText
          Left = 354
          Top = 30
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText6'
          TabOrder = 1
        end
        object ScrollBar7: TScrollBar
          Left = 148
          Top = 59
          Width = 199
          Height = 22
          PageSize = 0
          TabOrder = 2
        end
        object StaticText7: TStaticText
          Left = 354
          Top = 59
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText7'
          TabOrder = 3
        end
        object CheckBox11: TCheckBox
          Left = 207
          Top = 0
          Width = 111
          Height = 22
          Caption = 'CheckBox11'
          TabOrder = 4
        end
      end
      object GroupBox9: TGroupBox
        Left = 0
        Top = 98
        Width = 887
        Height = 464
        Caption = 'ALS'
        TabOrder = 1
        object Label18: TLabel
          Left = 20
          Top = 59
          Width = 48
          Height = 16
          Caption = 'Label18'
        end
        object Label19: TLabel
          Left = 20
          Top = 98
          Width = 48
          Height = 16
          Caption = 'Label19'
        end
        object Label20: TLabel
          Left = 20
          Top = 138
          Width = 48
          Height = 16
          Caption = 'Label20'
        end
        object Label21: TLabel
          Left = 20
          Top = 177
          Width = 48
          Height = 16
          Caption = 'Label21'
        end
        object Label22: TLabel
          Left = 20
          Top = 217
          Width = 48
          Height = 16
          Caption = 'Label22'
        end
        object Label23: TLabel
          Left = 20
          Top = 256
          Width = 48
          Height = 16
          Caption = 'Label23'
        end
        object Label24: TLabel
          Left = 20
          Top = 295
          Width = 48
          Height = 16
          Caption = 'Label24'
        end
        object Label25: TLabel
          Left = 20
          Top = 335
          Width = 48
          Height = 16
          Caption = 'Label25'
        end
        object Label26: TLabel
          Left = 423
          Top = 59
          Width = 48
          Height = 16
          Caption = 'Label26'
        end
        object Label27: TLabel
          Left = 423
          Top = 98
          Width = 48
          Height = 16
          Caption = 'Label27'
        end
        object Label28: TLabel
          Left = 423
          Top = 138
          Width = 48
          Height = 16
          Caption = 'Label28'
        end
        object Label29: TLabel
          Left = 423
          Top = 177
          Width = 48
          Height = 16
          Caption = 'Label29'
        end
        object Label30: TLabel
          Left = 423
          Top = 217
          Width = 48
          Height = 16
          Caption = 'Label30'
        end
        object Label31: TLabel
          Left = 423
          Top = 256
          Width = 48
          Height = 16
          Caption = 'Label31'
        end
        object Label79: TLabel
          Left = 423
          Top = 295
          Width = 48
          Height = 16
          Caption = 'Label79'
        end
        object CheckBox24: TCheckBox
          Left = 148
          Top = 20
          Width = 120
          Height = 22
          Caption = 'CheckBox24'
          TabOrder = 0
        end
        object CheckBox23: TCheckBox
          Left = 10
          Top = 20
          Width = 120
          Height = 22
          Caption = 'CheckBox23'
          TabOrder = 1
        end
        object ScrollBar14: TScrollBar
          Left = 158
          Top = 59
          Width = 189
          Height = 22
          PageSize = 0
          TabOrder = 2
        end
        object ScrollBar15: TScrollBar
          Left = 158
          Top = 98
          Width = 189
          Height = 23
          PageSize = 0
          TabOrder = 3
        end
        object ScrollBar16: TScrollBar
          Left = 158
          Top = 138
          Width = 189
          Height = 22
          PageSize = 0
          TabOrder = 4
        end
        object ScrollBar17: TScrollBar
          Left = 158
          Top = 177
          Width = 189
          Height = 22
          PageSize = 0
          TabOrder = 5
        end
        object ScrollBar18: TScrollBar
          Left = 158
          Top = 217
          Width = 189
          Height = 22
          PageSize = 0
          TabOrder = 6
        end
        object ScrollBar19: TScrollBar
          Left = 158
          Top = 256
          Width = 189
          Height = 22
          PageSize = 0
          TabOrder = 7
        end
        object ScrollBar20: TScrollBar
          Left = 158
          Top = 295
          Width = 189
          Height = 23
          PageSize = 0
          TabOrder = 8
        end
        object ScrollBar21: TScrollBar
          Left = 158
          Top = 335
          Width = 189
          Height = 22
          PageSize = 0
          TabOrder = 9
        end
        object ScrollBar22: TScrollBar
          Left = 561
          Top = 59
          Width = 190
          Height = 22
          PageSize = 0
          TabOrder = 10
        end
        object ScrollBar23: TScrollBar
          Left = 561
          Top = 98
          Width = 190
          Height = 23
          PageSize = 0
          TabOrder = 11
        end
        object ScrollBar24: TScrollBar
          Left = 561
          Top = 138
          Width = 190
          Height = 22
          PageSize = 0
          TabOrder = 12
        end
        object ScrollBar25: TScrollBar
          Left = 561
          Top = 177
          Width = 190
          Height = 22
          PageSize = 0
          TabOrder = 13
        end
        object ScrollBar26: TScrollBar
          Left = 561
          Top = 217
          Width = 190
          Height = 22
          PageSize = 0
          TabOrder = 14
        end
        object ScrollBar27: TScrollBar
          Left = 561
          Top = 256
          Width = 190
          Height = 22
          PageSize = 0
          TabOrder = 15
        end
        object StaticText14: TStaticText
          Left = 354
          Top = 59
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText14'
          TabOrder = 16
        end
        object StaticText15: TStaticText
          Left = 354
          Top = 98
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText15'
          TabOrder = 17
        end
        object StaticText16: TStaticText
          Left = 354
          Top = 138
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText16'
          TabOrder = 18
        end
        object StaticText17: TStaticText
          Left = 354
          Top = 177
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText17'
          TabOrder = 19
        end
        object StaticText18: TStaticText
          Left = 354
          Top = 217
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText18'
          TabOrder = 20
        end
        object StaticText19: TStaticText
          Left = 354
          Top = 256
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText19'
          TabOrder = 21
        end
        object StaticText20: TStaticText
          Left = 354
          Top = 295
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText20'
          TabOrder = 22
        end
        object StaticText21: TStaticText
          Left = 354
          Top = 335
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText21'
          TabOrder = 23
        end
        object StaticText22: TStaticText
          Left = 758
          Top = 59
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText22'
          TabOrder = 24
        end
        object StaticText23: TStaticText
          Left = 758
          Top = 98
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText23'
          TabOrder = 25
        end
        object StaticText24: TStaticText
          Left = 758
          Top = 138
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText24'
          TabOrder = 26
        end
        object StaticText25: TStaticText
          Left = 758
          Top = 177
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText25'
          TabOrder = 27
        end
        object StaticText26: TStaticText
          Left = 758
          Top = 217
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText26'
          TabOrder = 28
        end
        object StaticText27: TStaticText
          Left = 758
          Top = 256
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText27'
          TabOrder = 29
        end
        object ScrollBar67: TScrollBar
          Left = 561
          Top = 295
          Width = 189
          Height = 21
          PageSize = 0
          TabOrder = 30
        end
        object StaticText67: TStaticText
          Left = 758
          Top = 295
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText67'
          TabOrder = 31
        end
        object GroupBox13: TGroupBox
          Left = 20
          Top = 364
          Width = 406
          Height = 77
          TabOrder = 32
          object Label36: TLabel
            Left = 12
            Top = 52
            Width = 34
            Height = 16
            Caption = 'Label'
          end
          object Label82: TLabel
            Left = 10
            Top = 11
            Width = 48
            Height = 16
            Caption = 'Label82'
          end
          object ScrollBar32: TScrollBar
            Left = 148
            Top = 49
            Width = 219
            Height = 22
            PageSize = 0
            TabOrder = 0
          end
          object StaticText32: TStaticText
            Left = 374
            Top = 49
            Width = 63
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 1
          end
          object ComboBox14: TComboBox
            Left = 148
            Top = 11
            Width = 257
            Height = 21
            ItemHeight = 0
            TabOrder = 2
            Text = 'ComboBox14'
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'DCR LUT'
      ImageIndex = 4
      object GroupBox10: TGroupBox
        Left = 571
        Top = 39
        Width = 277
        Height = 179
        TabOrder = 0
        object btn_dcr_lut_read: TButton
          Left = 30
          Top = 30
          Width = 100
          Height = 51
          Caption = 'R&ead'
          TabOrder = 0
          OnClick = btn_dcr_lut_readClick
        end
        object btn_dcr_lut_write: TButton
          Left = 148
          Top = 30
          Width = 101
          Height = 51
          Caption = '&Write'
          TabOrder = 1
          OnClick = btn_dcr_lut_writeClick
        end
        object btn_dcr_lut_save: TButton
          Left = 30
          Top = 98
          Width = 100
          Height = 52
          Hint = 'Save as ".txt", digit type "Hex"'
          Caption = '&Save File'
          TabOrder = 2
          OnClick = btn_dcr_lut_saveClick
        end
        object btn_dcr_lut_load: TButton
          Left = 148
          Top = 98
          Width = 101
          Height = 52
          Hint = 
            'Load ".txt" file, Number is "Hex"Save as ".txt", digits type "He' +
            'x"'
          Caption = '&Load File'
          TabOrder = 3
          OnClick = btn_dcr_lut_loadClick
        end
        object edt_seq_addr: TLabeledEdit
          Left = 39
          Top = 187
          Width = 91
          Height = 21
          EditLabel.Width = 83
          EditLabel.Height = 16
          EditLabel.Caption = 'Address(Hex)'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clBlack
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 4
          Text = '0'
          Visible = False
        end
      end
    end
  end
  object Btn_DCR_reload: TBitBtn
    Left = 10
    Top = 606
    Width = 91
    Height = 32
    Caption = '&Reload'
    ModalResult = 6
    TabOrder = 1
    OnClick = Btn_DCR_reloadClick
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
  end
  object GroupBox40: TGroupBox
    Left = 482
    Top = 603
    Width = 229
    Height = 38
    Caption = 'hiden'
    TabOrder = 2
    Visible = False
    object CheckBox16: TCheckBox
      Left = 59
      Top = 10
      Width = 121
      Height = 22
      Caption = 'CheckBox16'
      TabOrder = 0
      Visible = False
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 232
    Top = 490
  end
  object SaveDialog1: TSaveDialog
    Left = 184
    Top = 490
  end
end
