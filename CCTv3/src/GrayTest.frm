VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "mscomm32.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form GrayTest 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Gamma Measurement"
   ClientHeight    =   4644
   ClientLeft      =   36
   ClientTop       =   312
   ClientWidth     =   7296
   Icon            =   "GrayTest.frx":0000
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4644
   ScaleWidth      =   7296
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog cmdDiag 
      Left            =   8280
      Top             =   4920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   7560
      Top             =   4920
      _ExtentX        =   804
      _ExtentY        =   804
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Frame user_define 
      Caption         =   "Direct Pattern Measurement (T-CON Input for 10 in)"
      Height          =   4185
      Left            =   240
      TabIndex        =   1
      Top             =   0
      Visible         =   0   'False
      Width           =   6315
      Begin VB.Frame Frame4 
         Caption         =   "6. Source Channel"
         Height          =   780
         Left            =   4560
         TabIndex        =   35
         Top             =   2520
         Width           =   1470
         Begin VB.TextBox Text1 
            Alignment       =   2  'Center
            Height          =   264
            Left            =   480
            TabIndex        =   36
            Text            =   "0"
            Top             =   360
            Width           =   612
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "3. Patterns"
         Height          =   1620
         Left            =   480
         TabIndex        =   29
         Top             =   1920
         Width           =   1860
         Begin VB.OptionButton Option3 
            Caption         =   "0 ~ 1023 Pattern"
            Height          =   300
            Left            =   105
            TabIndex        =   33
            Top             =   765
            Width           =   1605
         End
         Begin VB.OptionButton Option2 
            Caption         =   "0 ~ 256 Pattern"
            Height          =   270
            Left            =   120
            TabIndex        =   32
            Top             =   360
            Value           =   -1  'True
            Width           =   1635
         End
         Begin VB.OptionButton Option1 
            Caption         =   "0 ~ 255 Pattern"
            Height          =   285
            Left            =   240
            TabIndex        =   31
            Top             =   1620
            Width           =   1380
         End
         Begin VB.Label Label4 
            Caption         =   "(S/W Inpterpolation)"
            Height          =   210
            Left            =   180
            TabIndex        =   34
            Top             =   1080
            Width           =   1470
         End
      End
      Begin VB.Frame Frame6 
         Caption         =   "5. Color"
         Height          =   2220
         Left            =   4560
         TabIndex        =   7
         Top             =   240
         Width           =   885
         Begin VB.CheckBox Check_W2 
            Caption         =   "W"
            Height          =   255
            Left            =   240
            TabIndex        =   11
            Top             =   360
            Value           =   1  'Checked
            Width           =   510
         End
         Begin VB.CheckBox Check_R2 
            Caption         =   "R"
            Height          =   375
            Left            =   225
            TabIndex        =   10
            Top             =   735
            Width           =   510
         End
         Begin VB.CheckBox Check_G2 
            Caption         =   "G"
            Height          =   255
            Left            =   240
            TabIndex        =   9
            Top             =   1230
            Width           =   480
         End
         Begin VB.CheckBox Check_B2 
            Caption         =   "B"
            Height          =   255
            Left            =   240
            TabIndex        =   8
            Top             =   1680
            Width           =   495
         End
      End
      Begin VB.Frame Frame7 
         Caption         =   "1. LUT"
         Height          =   1065
         Left            =   480
         TabIndex        =   4
         Top             =   600
         Width           =   1275
         Begin VB.OptionButton op_msr_12bit 
            Caption         =   "12 bit"
            Height          =   210
            Left            =   120
            TabIndex        =   6
            Top             =   720
            Value           =   -1  'True
            Width           =   810
         End
         Begin VB.OptionButton op_msr_10bit 
            Caption         =   "10 bit"
            Height          =   240
            Left            =   120
            TabIndex        =   5
            Top             =   360
            Width           =   795
         End
      End
      Begin VB.CommandButton btn_color_list_run 
         Caption         =   "7. Measure"
         Height          =   465
         Left            =   4560
         TabIndex        =   3
         Top             =   3465
         Width           =   1185
      End
      Begin VB.CommandButton btn_LoadTable 
         Caption         =   "4. Load Table"
         Height          =   450
         Left            =   2520
         TabIndex        =   2
         Top             =   2400
         Width           =   1170
      End
      Begin VB.Frame Frame8 
         Caption         =   "Pattern Type"
         Height          =   3660
         Left            =   135
         TabIndex        =   30
         Top             =   240
         Width           =   3870
         Begin VB.Frame Frame9 
            Caption         =   "2. Other"
            Height          =   1095
            Left            =   2040
            TabIndex        =   37
            Top             =   360
            Width           =   1575
            Begin VB.CheckBox chk_256 
               Caption         =   "Gamma256"
               Height          =   330
               Left            =   120
               TabIndex        =   39
               Top             =   240
               Width           =   1215
            End
            Begin VB.CheckBox chk_intp 
               Caption         =   "Interpolation"
               Enabled         =   0   'False
               Height          =   450
               Left            =   120
               TabIndex        =   38
               Top             =   600
               Width           =   1230
            End
         End
      End
   End
   Begin VB.Frame pc_input 
      Caption         =   "Gamma Measurement (PC Input)"
      Height          =   2715
      Left            =   105
      TabIndex        =   12
      Top             =   30
      Width           =   6195
      Begin VB.Frame Frame3 
         Caption         =   "3. Source Channel"
         Height          =   855
         Left            =   4230
         TabIndex        =   27
         Top             =   330
         Width           =   1455
         Begin VB.TextBox TCH 
            Alignment       =   2  'Center
            Height          =   264
            Left            =   480
            TabIndex        =   28
            Text            =   "0"
            Top             =   360
            Width           =   612
         End
      End
      Begin VB.Frame Frame1 
         Caption         =   "1. Gray Level Option"
         Height          =   2205
         Left            =   150
         TabIndex        =   19
         Top             =   315
         Width           =   2415
         Begin VB.TextBox FSL 
            Alignment       =   2  'Center
            Height          =   264
            Left            =   1080
            TabIndex        =   22
            Text            =   "255"
            Top             =   410
            Width           =   612
         End
         Begin VB.TextBox FEL 
            Alignment       =   2  'Center
            Height          =   264
            Left            =   1080
            TabIndex        =   21
            Text            =   "0"
            Top             =   890
            Width           =   612
         End
         Begin VB.TextBox GLS 
            Alignment       =   2  'Center
            Height          =   270
            Left            =   1560
            TabIndex        =   20
            Text            =   "0"
            Top             =   1560
            Width           =   615
         End
         Begin VB.Label Label1 
            Caption         =   "Start Level"
            Height          =   252
            Left            =   240
            TabIndex        =   26
            Top             =   480
            Width           =   1212
         End
         Begin VB.Label Label2 
            Caption         =   "End Level"
            Height          =   255
            Left            =   240
            TabIndex        =   25
            Top             =   960
            Width           =   1215
         End
         Begin VB.Label Label7 
            Caption         =   "2"
            BeginProperty Font 
               Name            =   "新細明體"
               Size            =   10.8
               Charset         =   136
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   1440
            TabIndex        =   24
            Top             =   1800
            Width           =   255
         End
         Begin VB.Label Label3 
            Caption         =   "Gray Level Step"
            Height          =   255
            Left            =   120
            TabIndex        =   23
            Top             =   1560
            Width           =   1215
         End
      End
      Begin VB.CommandButton FRun 
         Caption         =   "4. Measure"
         Height          =   500
         Left            =   4485
         TabIndex        =   18
         Top             =   1440
         Width           =   1095
      End
      Begin VB.Frame Frame5 
         Caption         =   "2. Color"
         Height          =   2175
         Left            =   2790
         TabIndex        =   13
         Top             =   315
         Width           =   975
         Begin VB.CheckBox Check_W 
            Caption         =   "W"
            Height          =   255
            Left            =   240
            TabIndex        =   17
            Top             =   360
            Value           =   1  'Checked
            Width           =   615
         End
         Begin VB.CheckBox Check_R 
            Caption         =   "R"
            Height          =   375
            Left            =   240
            TabIndex        =   16
            Top             =   720
            Width           =   615
         End
         Begin VB.CheckBox Check_G 
            Caption         =   "G"
            Height          =   255
            Left            =   240
            TabIndex        =   15
            Top             =   1200
            Width           =   615
         End
         Begin VB.CheckBox Check_B 
            Caption         =   "B"
            Height          =   255
            Left            =   240
            TabIndex        =   14
            Top             =   1680
            Width           =   615
         End
      End
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      Caption         =   "Copyright (C) 2005. AU Optronics Corp., All Rights Reserved"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Left            =   765
      TabIndex        =   0
      Top             =   2955
      Width           =   4395
   End
End
Attribute VB_Name = "GrayTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub btn_color_list_run_Click()
On Error GoTo catch
STime = Time  '''''''''' Timer
Go_ahead = True
'''''''''' Parameter
MainForm.WindowState = 1
GrayTest.visible = False
'EndG = Val(FEL)
'ShowCursor (False)
'Background.BKIGL = 0
'Background.BKA = 0

''''''''' Open Recorder
    Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
          
        sheet.setSheetIndex 1
        sheet.cell(1, 1) = "Gray Level"
        sheet.cell(1, 2) = "W_x"
        sheet.cell(1, 3) = "W_y"
        sheet.cell(1, 4) = "W_Y (nit)"
        sheet.cell(1, 5) = "W_C.T."
        sheet.cell(1, 6) = "ΔUV"
        sheet.cell(1, 7) = "W_R"
        sheet.cell(1, 8) = "W_G"
        sheet.cell(1, 9) = "W_B"
        
        sheet.cell(1, 10) = "R_x"
        sheet.cell(1, 11) = "R_y"
        sheet.cell(1, 12) = "R_Y (nit)"
  
        
        sheet.cell(1, 13) = "G_x"
        sheet.cell(1, 14) = "G_y"
        sheet.cell(1, 15) = "G_Y (nit)"
    
        
        sheet.cell(1, 16) = "B_x"
        sheet.cell(1, 17) = "B_y"
        sheet.cell(1, 18) = "B_Y (nit)"
     

 '''''' Start Test
 objCa.RemoteMode = 1
 objMemory.ChannelNO = TCH
 
    'Row1 = 1
 '   If Check_full.Value = 1 Then
    
     'Row1 = 1
    If (MainForm.op_pc.Value = True) Then
        Background.setShow
    End If
    'Call PatternI(255)
    'Tims (7)
    If chk_256.Value = 1 Then
        num = 257
    Else
        num = 256
    End If
For y = 1 To 4
        
        row1 = 1
         Select Case y
            Case 1
            If Check_W2.Value = 1 Then
            Call PatternRGB(R_value(num - 1), G_value(num - 1), B_value(num - 1))
            'Call Background.BGShow2(StartG, 0, 0)
            Tims (10)
            End If
            Case 2
            If Check_R2.Value = 1 Then
            Call PatternRGB(R_value(num - 1), 0, 0)
            'Call Background.BGShow2(StartG, 0, 0)
            Tims (5)
            End If
            Case 3
            If Check_G2.Value = 1 Then
            Call PatternRGB(0, G_value(num - 1), 0)
            'Call Background.BGShow2(StartG, 0, 0)
            Tims (5)
            End If
            Case 4
            If Check_B2.Value = 1 Then
            Call PatternRGB(0, 0, B_value(num - 1))
            'Call Background.BGShow2(StartG, 0, 0)
            Tims (5)
            End If
        End Select
   
   
   
   If (MainForm.op_pc.Value = True) Then
        Background.setShow
    End If
 
    row1 = 1
    
 For x = num - 1 To 0 Step -1
            X2 = x


    
           'Gray
            If y = 1 Then
                If Check_W2.Value = 1 Then
                
                    Call PatternRGB(R_value(X2), G_value(X2), B_value(X2))
                    'Call RGBcal.CADataCT2102(Cx, Cy, Yx, CT, UV)
                    Call RGBcal.CADataCT210(Cx, Cy, Yx, CT, uv, LR, LG, LB)
                    'Call Background.BGShow2(X2, Yx, 0)
                    row1 = row1 + 1
                    sheet.cell(row1, 1) = X2
                    sheet.cell(row1, 2) = Cx
                    sheet.cell(row1, 3) = Cy
                    sheet.cell(row1, 4) = Yx
                    sheet.cell(row1, 5) = CT
                    sheet.cell(row1, 6) = uv
                    sheet.cell(row1, 7) = LR
                    sheet.cell(row1, 8) = LG
                    sheet.cell(row1, 9) = LB
                
                ''*******interpolation
                    If ((chk_intp.Value = 1) And (X2 > 0)) Then
                        For cc = 3 To 1 Step -1
                            X3 = X2 - 1 + cc / 4
                            row1 = row1 + 1
                            temp_r = R_value(X2 - 1) + Fix((R_value(X2) - R_value(X2 - 1)) / 4 * cc)
                            temp_g = G_value(X2 - 1) + Fix((G_value(X2) - G_value(X2 - 1)) / 4 * cc)
                            temp_b = B_value(X2 - 1) + Fix((B_value(X2) - B_value(X2 - 1)) / 4 * cc)
                            Call PatternRGB(temp_r, temp_g, temp_b)
                            Call RGBcal.CADataCT210(Cx, Cy, Yx, CT, uv, LR, LG, LB)
                            sheet.cell(row1, 1) = X3
                            sheet.cell(row1, 2) = Cx
                            sheet.cell(row1, 3) = Cy
                            sheet.cell(row1, 4) = Yx
                            sheet.cell(row1, 5) = CT
                            sheet.cell(row1, 6) = uv
                            sheet.cell(row1, 7) = LR
                            sheet.cell(row1, 8) = LG
                            sheet.cell(row1, 9) = LB
                            
                        Next cc
                    End If
                
                End If
            End If
               
            If y = 2 Then            'Red
                If Check_R2.Value = 1 Then
                
                     Call PatternRGB(R_value(X2), 0, 0)
                     Call RGBcal.CA210(Cx, Cy, Yx)
                    ' Call Background.BGShow2(X2, Yx, 0)
                     row1 = row1 + 1
                     sheet.cell(row1, 10) = Cx
                     sheet.cell(row1, 11) = Cy
                     sheet.cell(row1, 12) = Yx
                     If ((chk_intp.Value = 1) And (X2 > 0)) Then
                        For cc = 3 To 1 Step -1
                           
                            temp_r = R_value(X2 - 1) + Fix((R_value(X2) - R_value(X2 - 1)) / 4 * cc)
                            'temp_g = G_value(X2 - 1) + (G_value(X2) - G_value(X2 - 1)) / 4 * cc
                            'temp_b = B_value(X2 - 1) + (B_value(X2) - B_value(X2 - 1)) / 4 * cc
                            Call PatternRGB(temp_r, 0, 0)
                             Call RGBcal.CA210(Cx, Cy, Yx)
                            row1 = row1 + 1
                            sheet.cell(row1, 10) = Cx
                            sheet.cell(row1, 11) = Cy
                            sheet.cell(row1, 12) = Yx
            
                            
                        Next cc
                    End If
                    
                End If
           End If
                
                
            If y = 3 Then
                 If Check_G2.Value = 1 Then
                'Green
                    Call PatternRGB(0, G_value(X2), 0)
                    Call RGBcal.CA210(Cx, Cy, Yx)
                    'Call Background.BGShow2(X2, Yx, 0)
                    row1 = row1 + 1
                    sheet.cell(row1, 13) = Cx
                    sheet.cell(row1, 14) = Cy
                    sheet.cell(row1, 15) = Yx
                    If ((chk_intp.Value = 1) And (X2 > 0)) Then
                        For cc = 3 To 1 Step -1
                            'temp_r = R_value(X2 - 1) + (R_value(X2) - R_value(X2 - 1)) / 4 * cc
                            temp_g = G_value(X2 - 1) + Fix((G_value(X2) - G_value(X2 - 1)) / 4 * cc)
                            'temp_b = B_value(X2 - 1) + (B_value(X2) - B_value(X2 - 1)) / 4 * cc
                            Call PatternRGB(0, temp_g, 0)
                             Call RGBcal.CA210(Cx, Cy, Yx)
                            row1 = row1 + 1
                            sheet.cell(row1, 13) = Cx
                            sheet.cell(row1, 14) = Cy
                            sheet.cell(row1, 15) = Yx
            
                            
                        Next cc
                    End If
                End If
            End If
                
            If y = 4 Then
                'Blue
                If Check_B2.Value = 1 Then
                    Call PatternRGB(0, 0, B_value(X2))
                    Call RGBcal.CA210(Cx, Cy, Yx)
                    'Call Background.BGShow2(X2, Yx, 0)
                    row1 = row1 + 1
                    sheet.cell(row1, 16) = Cx
                    sheet.cell(row1, 17) = Cy
                    sheet.cell(row1, 18) = Yx
                    If ((chk_intp.Value = 1) And (X2 > 0)) Then
                            For cc = 3 To 1 Step -1
                                'temp_r = R_value(X2 - 1) + (R_value(X2) - R_value(X2 - 1)) / 4 * cc
                                'temp_g = G_value(X2 - 1) + (G_value(X2) - G_value(X2 - 1)) / 4 * cc
                                temp_b = B_value(X2 - 1) + Fix((B_value(X2) - B_value(X2 - 1)) / 4 * cc)
                                Call PatternRGB(0, 0, temp_b)
                                 Call RGBcal.CA210(Cx, Cy, Yx)
                                row1 = row1 + 1
                                sheet.cell(row1, 16) = Cx
                                sheet.cell(row1, 17) = Cy
                                sheet.cell(row1, 18) = Yx
                
                                
                            Next cc
                     End If
    
                    End If
             End If
        Next x
    Next y
    

            'sheet.setVisible True
             Utils.changeFontAnd (sheet)
        
'If Check_full.Value = 1 Then
   If (MainForm.op_pc.Value = True) Then Unload Background
    
'Else
 '   Unload Background2
'End If
GrayTest.visible = True
'Unload Me
'MainForm.Show
'ShowCursor (True)
ETime = Time  '''''''''' Timer
MsgBox "Start Time - End Time : " & STime & " - " & ETime
Exit Sub
catch:
    Call Utils.catch
End Sub

Private Sub btn_LoadTable_Click()
Dim fm As String, fnum As Integer, fname As String
    'Dim iCheck As Integer
    
    'iCheck = MsgBox("Are you sure to load file to CA-210", vbOKCancel)
    
    'If iCheck = 2 Then
    'Exit Sub
    'End If
    
    On Error Resume Next
    cmdDiag.CancelError = True
    cmdDiag.filename = "*.xls"
    
    cmdDiag.FilterIndex = 2
    cmdDiag.Action = 1
    If Err.Number = cdlCancel Then
        Exit Sub
    Else
        fm = cmdDiag.filename
        fm = Mid$(fm, 1, InStr(1, fm, ".")) + "xls"
    End If
    
    fname = Dir$(fm, vbNormal Or vbReadOnly)
    If fname = "" Then
        MsgBox "No File", vbOKOnly
        Exit Sub
    Else
    End If
    
    Dim xlApp As Excel.Application '定義EXCEL類
    Dim xlBook As Excel.workbook '定義工件簿類
    Dim xlsheet As Excel.Worksheet '定義工作表類

    Set xlApp = CreateObject("Excel.Application") '創建EXCEL應用類
    xlApp.visible = False '設置EXCEL不可見
    Set xlBook = xlApp.Workbooks.Open(fm) '打開EXCEL工作簿
    Set xlsheet = xlBook.Worksheets(1) '打開EXCEL工作表
    xlsheet.Activate '啟動工作表
    'Dim R, G, B As Single
      
    
    If chk_256.Value = 1 Then
        num = 257
    Else
        num = 256
    End If
    If op_msr_10bit.Value = True Then
        gain = 4
    Else
        gain = 1
    End If
    For i = 1 To num
        R_value(i - 1) = xlsheet.Cells(i + 1, 2) * gain
        G_value(i - 1) = xlsheet.Cells(i + 1, 3) * gain
        B_value(i - 1) = xlsheet.Cells(i + 1, 4) * gain
    Next i
        
      
  
    xlBook.Close
    xlApp.Quit
End Sub



Private Sub chk_256_Click()
chk_intp.Enabled = True
End Sub

 
 
 

Private Sub Form_Load()
If MainForm.op_pc.Value = True Then
    GrayTest.FSL.Text = 255
    GrayTest.op_msr_10bit.Enabled = False
    GrayTest.op_msr_12bit.Enabled = False
    'GTable.GSL.Text = 255
    GrayTest.user_define.visible = False
Else
    GrayTest.FSL.Text = 4095
    GrayTest.op_msr_12bit.Value = True
    GrayTest.op_msr_10bit.Enabled = True
    GrayTest.op_msr_12bit.Enabled = True
    GrayTest.user_define.visible = True
End If

'X = MsgBox("If the panel is wide color gamut(over than NTSC72%), please do Matrix Calibration for CS-1000 or SR-3 to get more accurate measuring data!", vbExclamation + vbOKOnly)
End Sub
 


Private Sub FRun_Click()
On Error GoTo catch

STime = Time  '''''''''' Timer
Go_ahead = True
'''''''''' Parameter
MainForm.WindowState = 1

GLS = Val(GLS.Text)
If (MainForm.op_pc.Value = True) Then
    If GLS > 0 And Val(FSL) = 255 Then
        StartG = Val(FSL) + 1
        EndG = Val(FEL)
        
    Else
        StartG = Val(FSL)
        EndG = Val(FEL)
    End If
Else
    If GLS > 0 And Val(FSL) = 4095 Then
        StartG = Val(FSL) + 1
        EndG = Val(FEL)
        
    Else
        StartG = Val(FSL)
        EndG = Val(FEL)
    End If

End If

STP = 2 ^ GLS



'StartG = Val(FSL)
'EndG = Val(FEL)
If (MainForm.op_pc.Value = True) Then
Background.BKIGL = 0
Background.BKA = 0
End If
''''''''' Open Recorder
    Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
    
'    Dim Ex As Object
'    Set Ex = CreateObject("Excel.Application")
'        Ex.visible = True
'        Ex.Workbooks.Add
        
        sheet.setSheetIndex 1
        
        sheet.cell(1, 1) = "Gray Level"
        sheet.cell(1, 2) = "W_x"
        sheet.cell(1, 3) = "W_y"
        sheet.cell(1, 4) = "W_Y (nit)"
        sheet.cell(1, 5) = "W_C.T."
        sheet.cell(1, 6) = "ΔUV"
        sheet.cell(1, 7) = "W_R"
        sheet.cell(1, 8) = "W_G"
        sheet.cell(1, 9) = "W_B"
        
        sheet.cell(1, 10) = "R_x"
        sheet.cell(1, 11) = "R_y"
        sheet.cell(1, 12) = "R_Y (nit)"
        'sheet.cell(1, 14) = "R_R"
        'sheet.cell(1, 15) = "R_G"
        'sheet.cell(1, 16) = "R_B"
        
        sheet.cell(1, 13) = "G_x"
        sheet.cell(1, 14) = "G_y"
        sheet.cell(1, 15) = "G_Y (nit)"
        
        sheet.cell(1, 16) = "B_x"
        sheet.cell(1, 17) = "B_y"
        sheet.cell(1, 18) = "B_Y (nit)"
        
    If True = MeasureTool.UseCA210 Then
         '''''' Start Test
        objCa.RemoteMode = 1
        objMemory.ChannelNO = TCH
    End If
 
    row1 = 1
    If (MainForm.op_pc.Value = True) Then Background.setShow
    'Call PatternI(255)
    'Tims (1)
    
    For y = 1 To 4
        
        'row1 = 1
        Select Case y
        Case 1
        If Check_W.Value = 1 Then
        Call PatternRGB(StartG, StartG, StartG)
        Call Background.BGShow2(StartG, 0, 0)
        Tims (2)
        End If
        Case 2
        If Check_R.Value = 1 Then
        Call PatternRGB(StartG, 0, 0)
        Call Background.BGShow2(StartG, 0, 0)
        Tims (5)
        End If
        Case 3
        If Check_G.Value = 1 Then
        Call PatternRGB(0, StartG, 0)
        Call Background.BGShow2(StartG, 0, 0)
        Tims (5)
        End If
        Case 4
        If Check_B.Value = 1 Then
        Call PatternRGB(0, 0, StartG)
        Call Background.BGShow2(StartG, 0, 0)
        Tims (5)
        End If
    End Select
    
        
        'Call RGBcal.CA210(Cx, Cy, Y255)
        
        For x = StartG To EndG Step -STP
            X2 = x
            If (MainForm.op_pc.Value = True) Then
                If X2 > 255 Then X2 = 255
            Else
                If X2 > 4095 Then X2 = 4095
            End If

    
           'Gray
            If y = 1 Then
                If Check_W.Value = 1 Then
                
                Call PatternI(X2)
                If False = MeasureTool.UseCA210 Then
                    GoTo Final
                End If
                Call RGBcal.CADataCT210(Cx, Cy, Yx, CT, uv, LR, LG, LB)
                Call Background.BGShow2(X2, Yx, 0)
                row1 = row1 + 1
                
                'sheet.cell(Row1, 1) = Y255
                sheet.cell(row1, 1) = X2
                sheet.cell(row1, 2) = Cx
                sheet.cell(row1, 3) = Cy
                sheet.cell(row1, 4) = Yx
                sheet.cell(row1, 5) = CT
                sheet.cell(row1, 6) = uv
                sheet.cell(row1, 7) = LR
                sheet.cell(row1, 8) = LG
                sheet.cell(row1, 9) = LB
                'sheet.cell(Row1, 1) = sheet.cell(2, 5)
                End If
            End If
               
            If y = 2 Then            'Red
                 If Check_R.Value = 1 Then
                
                Call PatternRGB(X2, 0, 0)
                Call RGBcal.CA210(Cx, Cy, Yx)
                Call Background.BGShow2(X2, Yx, 0)
                row1 = row1 + 1
                sheet.cell(row1, 10) = Cx
                sheet.cell(row1, 11) = Cy
                sheet.cell(row1, 12) = Yx

                End If
           End If
                
            If y = 3 Then
                 If Check_G.Value = 1 Then
                'Green
                Call PatternRGB(0, X2, 0)
                Call RGBcal.CA210(Cx, Cy, Yx)
                Call Background.BGShow2(X2, Yx, 0)
                row1 = row1 + 1
                sheet.cell(row1, 13) = Cx
                sheet.cell(row1, 14) = Cy
                sheet.cell(row1, 15) = Yx
 
                End If
            End If
                
            If y = 4 Then
                'Blue
                If Check_B.Value = 1 Then
                Call PatternRGB(0, 0, X2)
                Call RGBcal.CA210(Cx, Cy, Yx)
                Call Background.BGShow2(X2, Yx, 0)
                row1 = row1 + 1
                sheet.cell(row1, 16) = Cx
                sheet.cell(row1, 17) = Cy
                sheet.cell(row1, 18) = Yx
                 End If
             End If
        Next x
    Next y
Final:
Utils.changeFontAnd sheet
        
Unload Background
Unload Me
MainForm.Show

ETime = Time  '''''''''' Timer
MsgBox "Start Time - End Time : " & STime & " - " & ETime
'Unload Me
Exit Sub
catch:
    Call Utils.catch
End Sub

Private Sub op_msr_10bit_Click()
chk_intp.Enabled = False
End Sub

Private Sub op_msr_8bit_Click()

End Sub

Private Sub Option1_Click()
chk_256.Value = 0
chk_intp.Value = 0

End Sub

Private Sub Option2_Click()
chk_256.Value = 1
chk_intp.Value = 0
End Sub

Private Sub Option3_Click()
chk_256.Value = 1
chk_intp.Value = 1
End Sub

Private Sub TCHText1_Change()
TCH.Text = Text1.Text
End Sub

 
