VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmGamma 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "GammaAdj"
   ClientHeight    =   5364
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   8292
   Icon            =   "frmGamma.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5364
   ScaleWidth      =   8292
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame9 
      Caption         =   "3. Bit Depth"
      Height          =   2460
      Left            =   225
      TabIndex        =   34
      Top             =   1230
      Width           =   3840
      Begin VB.Frame Frame12 
         Caption         =   "In"
         Height          =   1455
         Left            =   120
         TabIndex        =   44
         Top             =   240
         Width           =   975
         Begin VB.OptionButton op_in_6 
            Caption         =   "6"
            Height          =   255
            Left            =   120
            TabIndex        =   47
            Top             =   240
            Width           =   615
         End
         Begin VB.OptionButton op_in_8 
            Caption         =   "8"
            Height          =   255
            Left            =   120
            TabIndex        =   46
            Top             =   600
            Value           =   -1  'True
            Width           =   615
         End
         Begin VB.OptionButton op_in_10 
            Caption         =   "10"
            Height          =   255
            Left            =   120
            TabIndex        =   45
            Top             =   945
            Width           =   615
         End
      End
      Begin VB.Frame Frame10 
         Caption         =   "LUT"
         Height          =   1455
         Left            =   1155
         TabIndex        =   41
         Top             =   225
         Width           =   1020
         Begin VB.OptionButton op_10bit2 
            Caption         =   "10 bit"
            Height          =   255
            Left            =   120
            TabIndex        =   43
            Top             =   360
            Value           =   -1  'True
            Width           =   735
         End
         Begin VB.OptionButton op_12bit2 
            Caption         =   "12 bit"
            Height          =   255
            Left            =   120
            TabIndex        =   42
            Top             =   840
            Width           =   735
         End
      End
      Begin VB.Frame Frame11 
         Caption         =   "Out"
         Height          =   1455
         Left            =   2250
         TabIndex        =   37
         Top             =   210
         Width           =   1095
         Begin VB.OptionButton op_out_6 
            Caption         =   "6"
            Height          =   255
            Left            =   240
            TabIndex        =   40
            Top             =   240
            Width           =   615
         End
         Begin VB.OptionButton op_out_8 
            Caption         =   "8"
            Height          =   255
            Left            =   240
            TabIndex        =   39
            Top             =   600
            Value           =   -1  'True
            Width           =   615
         End
         Begin VB.OptionButton op_out_10 
            Caption         =   "10"
            Height          =   255
            Left            =   240
            TabIndex        =   38
            Top             =   945
            Width           =   615
         End
      End
      Begin VB.CheckBox chk_ga256 
         Caption         =   "Gamma256"
         Height          =   375
         Left            =   180
         TabIndex        =   36
         Top             =   1785
         Width           =   1455
      End
      Begin VB.CheckBox chk_frc2 
         Caption         =   "Avoid FRC Noise"
         Enabled         =   0   'False
         Height          =   315
         Left            =   1605
         TabIndex        =   35
         Top             =   1830
         Width           =   1575
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "7. Gray"
      Height          =   500
      Left            =   6315
      TabIndex        =   24
      Top             =   960
      Width           =   1200
   End
   Begin VB.Frame Frame6 
      Caption         =   "Bit Depth"
      Height          =   2070
      Left            =   1725
      TabIndex        =   23
      Top             =   5625
      Width           =   3315
      Begin VB.Frame Frame8 
         Caption         =   "LUT Option"
         Height          =   1515
         Left            =   1905
         TabIndex        =   31
         Top             =   300
         Width           =   1260
         Begin VB.OptionButton option_10bit 
            Caption         =   "10 bit"
            Height          =   345
            Left            =   120
            TabIndex        =   33
            Top             =   285
            Value           =   -1  'True
            Width           =   990
         End
         Begin VB.OptionButton option_12bit 
            Caption         =   "12 bit"
            Height          =   360
            Left            =   120
            TabIndex        =   32
            Top             =   660
            Width           =   900
         End
      End
      Begin VB.Frame Frame7 
         Caption         =   "Panel Option"
         Height          =   1560
         Left            =   75
         TabIndex        =   26
         Top             =   285
         Width           =   1695
         Begin VB.OptionButton Option2 
            Caption         =   "6 + 2 FRC"
            Height          =   285
            Left            =   75
            TabIndex        =   30
            Top             =   1140
            Width           =   1095
         End
         Begin VB.OptionButton Option3 
            Caption         =   "6 + 3 FRC"
            Height          =   300
            Left            =   75
            TabIndex        =   29
            Top             =   825
            Width           =   1170
         End
         Begin VB.OptionButton Option1 
            Caption         =   "8 + 2 FRC"
            Height          =   360
            Left            =   75
            TabIndex        =   28
            Top             =   480
            Value           =   -1  'True
            Width           =   1185
         End
         Begin VB.OptionButton Option4 
            Caption         =   "10 + 2 FRC"
            Height          =   270
            Left            =   75
            TabIndex        =   27
            Top             =   195
            Width           =   1200
         End
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "7. RGB"
      Height          =   500
      Left            =   6270
      TabIndex        =   11
      Top             =   2160
      Width           =   1200
   End
   Begin VB.TextBox Text_path 
      Height          =   375
      Left            =   1890
      TabIndex        =   9
      Text            =   "D:\Gamma Table\"
      Top             =   4470
      Width           =   2550
   End
   Begin VB.TextBox Text_FN 
      Height          =   360
      Left            =   1890
      TabIndex        =   8
      Text            =   "Calib00_Table"
      Top             =   3975
      Width           =   2520
   End
   Begin VB.Frame Frame3 
      Caption         =   "2. Gray Level Step"
      Height          =   825
      Left            =   2400
      TabIndex        =   2
      Top             =   330
      Width           =   1500
      Begin VB.TextBox Text_LS 
         Alignment       =   2  'Center
         Height          =   300
         Left            =   495
         TabIndex        =   5
         Text            =   "0"
         Top             =   285
         Width           =   585
      End
      Begin VB.Label Label1 
         Caption         =   "2"
         Height          =   240
         Left            =   330
         TabIndex        =   4
         Top             =   510
         Width           =   240
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Gamma"
      Height          =   3510
      Left            =   4215
      TabIndex        =   1
      Top             =   315
      Width           =   3960
      Begin VB.CommandButton Command4 
         Caption         =   "Debug"
         Height          =   435
         Left            =   2460
         TabIndex        =   25
         Top             =   2955
         Visible         =   0   'False
         Width           =   1260
      End
      Begin VB.CommandButton Command3 
         Caption         =   "6. Load Gamma"
         Height          =   465
         Left            =   360
         TabIndex        =   22
         Top             =   2910
         Width           =   1590
      End
      Begin VB.Frame Frame5 
         Caption         =   "6. Gray"
         Height          =   810
         Left            =   300
         TabIndex        =   16
         Top             =   450
         Width           =   3315
         Begin VB.TextBox Text_ga 
            Alignment       =   2  'Center
            Height          =   315
            Left            =   660
            TabIndex        =   17
            Text            =   "2.4"
            Top             =   270
            Width           =   795
         End
         Begin VB.Label Label5 
            Caption         =   "W"
            Height          =   255
            Left            =   270
            TabIndex        =   18
            Top             =   315
            Width           =   285
         End
      End
      Begin VB.Frame Frame4 
         Caption         =   "6. RGB"
         Height          =   1485
         Left            =   285
         TabIndex        =   12
         Top             =   1365
         Width           =   3300
         Begin VB.TextBox Text_gga 
            Alignment       =   2  'Center
            Height          =   285
            Left            =   645
            TabIndex        =   21
            Text            =   "2.4"
            Top             =   570
            Width           =   825
         End
         Begin VB.TextBox Text_bga 
            Alignment       =   2  'Center
            Height          =   285
            Left            =   660
            TabIndex        =   20
            Text            =   "2.4"
            Top             =   960
            Width           =   825
         End
         Begin VB.TextBox Text_rga 
            Alignment       =   2  'Center
            Height          =   285
            Left            =   660
            TabIndex        =   19
            Text            =   "2.4"
            Top             =   210
            Width           =   825
         End
         Begin VB.Label Label8 
            Caption         =   "G"
            Height          =   255
            Left            =   300
            TabIndex        =   15
            Top             =   615
            Width           =   285
         End
         Begin VB.Label Label7 
            Caption         =   "B"
            Height          =   255
            Left            =   285
            TabIndex        =   14
            Top             =   1005
            Width           =   285
         End
         Begin VB.Label Label6 
            Caption         =   "R"
            Height          =   255
            Left            =   300
            TabIndex        =   13
            Top             =   255
            Width           =   285
         End
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "1. Channel"
      Height          =   825
      Left            =   330
      TabIndex        =   0
      Top             =   330
      Width           =   1500
      Begin VB.TextBox Text_ch 
         Alignment       =   2  'Center
         Height          =   285
         Left            =   405
         TabIndex        =   3
         Text            =   "0"
         Top             =   330
         Width           =   795
      End
   End
   Begin MSComDlg.CommonDialog cmdDiag 
      Left            =   5460
      Top             =   4170
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Label4 
      Caption         =   "Copyright (C) 2005. AU Optronics Corp., All Rights Reserved"
      Height          =   255
      Left            =   360
      TabIndex        =   10
      Top             =   5055
      Width           =   4410
   End
   Begin VB.Label Label3 
      Caption         =   "5. Save As Location"
      Height          =   300
      Left            =   240
      TabIndex        =   7
      Top             =   4515
      Width           =   1515
   End
   Begin VB.Label Label2 
      Caption         =   "4. Save As File Name"
      Height          =   315
      Left            =   240
      TabIndex        =   6
      Top             =   3990
      Width           =   1605
   End
End
Attribute VB_Name = "frmGamma"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Const GLT = 256
Dim DesiredGamma(GLT) As Single
Dim DesiredGammaR(GLT) As Single
Dim DesiredGammaG(GLT) As Single
Dim DesiredGammaB(GLT) As Single



Private Sub Command1_Click()
Go_ahead = True
MainForm.WindowState = 1
'''''''''' Parameter
If Text_LS > 0 Then
    StartG = 256
Else
    StartG = 255
End If



EndG = 0
STP = 2 ^ Val(Text_LS)
Background.BKIGL = 0
Background.BKA = 0

''''''''' Open Index File
        
    Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
        
        sheet.setSheetIndex 1
        sheet.cell(1, 1) = "Gray Level"
        sheet.cell(1, 2) = "Gamma R"
        sheet.cell(1, 3) = "Gamma G"
        sheet.cell(1, 4) = "Gamma B"
        sheet.setSheetIndex 2
        sheet.cell(1, 1) = "Gray Level"
        sheet.cell(1, 2) = "W_x"
        sheet.cell(1, 3) = "W_y"
        sheet.cell(1, 4) = "W_Y (nit)"
  



 '''''' Record Original Data    Measurement
 objCa.RemoteMode = 1
 objMemory.ChannelNO = Text_ch
 
''''''''''''''''Test Remove recipe by stockton 12/14
Const GLT = 256

Dim Lx(GLT) As Double
Dim Ly(GLT) As Double
Dim YYN(GLT) As Double
Dim Lgain(GLT) As Single
Dim MeasuredGamma(GLT) As Single
Dim DesiredGamma(GLT) As Single

Dim index(GLT) As Single

Dim RL(GLT) As Single
Dim GL(GLT) As Single
Dim BL(GLT) As Single
Dim GrayL(GLT) As Single
    Call PatternI(255)
    row1 = 1
    Background.setShow
    Tims (10)
    Call RGBcal.CA210(Cx, Cy, Y255)
    Call Background.BGShow1(255, Y255, 0)
    

        sheet.setSheetIndex 2
        For GLX = StartG To EndG Step -STP
                x = GLX
                If x > 255 Then x = 255
                GrayL(row1 - 1) = x
          
            Call PatternI(x)
            Call RGBcal.CA210(Cx, Cy, Yx)
            Call Background.BGShow2(x, Yx, 0)
                 row1 = row1 + 1
            Lx(row1 - 2) = Cx 'L(0)=L255
            Ly(row1 - 2) = Cy
            YYN(row1 - 2) = Yx
       
    
            sheet.cell(row1, 1) = x
            sheet.cell(row1, 2) = Cx
            sheet.cell(row1, 3) = Cy
            sheet.cell(row1, 4) = Yx
            
          
        Next GLX

'''''''''''''''Data Normalize Remove Recipe by Stockton 12/14
    Dim n As Integer
    n = row1 - 1
    Ymin = YYN(n - 1)
Unload Background


'''''''''''''' Predict RGB Remove Recipe by Stockton 12/14 TEST OK
If flag_LoadG = False Then
    For i = 0 To 255
        DesiredGamma(i) = ((255 - i) / 255) ^ Val(Text_ga.Text)
    Next i
End If
For i = 0 To n - 1
   MeasuredGamma(i) = (YYN(i) - Ymin) / (YYN(0) - Ymin)
Next i
For i = 0 To 255

DesiredG = DesiredGamma(i)
    For j = 0 To n - 1
    temp = MeasuredGamma(j)
    If ((DesiredG - temp) = 0) Then
             
             
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round(GrayL(j) * 4, 0)
            Else
                RL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round(GrayL(j) * 16, 0)
            Else
                RL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If
            
        End If
    '    If Option3.Value = True Then RL(i) = Round(GrayL(j) / 255 * 1008, 0)
        
        
        Exit For
    ElseIf ((DesiredG - temp) > 0) Then
         
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round((GrayL(j) + (DesiredG - temp) / (MeasuredGamma(j - 1) - temp) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
                RL(i) = Round((GrayL(j) + (DesiredG - temp) / (MeasuredGamma(j - 1) - temp) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round((GrayL(j) + (DesiredG - temp) / (MeasuredGamma(j - 1) - temp) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
                RL(i) = Round((GrayL(j) + (DesiredG - temp) / (MeasuredGamma(j - 1) - temp) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If
        
        End If
         
        Exit For
    End If
        
        
    Next j
    
Next i

    RL(255) = 0
    GL(255) = 0
    BL(255) = 0
    
    sheet.setSheetIndex 1
    For i = 0 To 255
        sheet.cell(i + 2, 1) = i
        sheet.cell(i + 2, 2) = RL(255 - i)
        sheet.cell(i + 2, 3) = RL(255 - i)
        sheet.cell(i + 2, 4) = RL(255 - i)
    Next i

 sheet.setSheetIndex 1
 sheet.setSheetName "Gamma Table"

 Utils.changeColorAnd sheet
 
 sheet.setSheetIndex 2
 sheet.setSheetName "Raw Data"
           
'''''''''''''' Save Data
sheet.setSheetFilename Text_path & Text_FN
sheet.store
sheet.closing

'ETime = Time  '''''''''' Timer
'MsgBox "Start Time - End Time : " & STime & " - " & ETime
'EndG:


frmGamma.Show



End Sub

Private Sub Command2_Click()


Go_ahead = True
MainForm.WindowState = 1
'''''''''' Parameter
If Text_LS > 0 Then
    StartG = 256
Else
    StartG = 255
End If


EndG = 0
STP = 2 ^ Val(Text_LS)

        Background.BKIGL = 0
        Background.BKA = 0
        
        ''''''''' Open Index File
        Dim sheet As SpreadSheet
        Set sheet = Utils.newSheet
                
                sheet.setSheetIndex 1
                sheet.cell(1, 1) = "Gray Level"
                sheet.cell(1, 2) = "Gamma R"
                sheet.cell(1, 3) = "Gamma G"
                sheet.cell(1, 4) = "Gamma B"
                sheet.setSheetIndex 2
                sheet.cell(1, 1) = "Gray Level"
                sheet.cell(1, 2) = "R_x"
                sheet.cell(1, 3) = "R_y"
                sheet.cell(1, 4) = "R_Y (nit)"
                sheet.cell(1, 5) = "G_x"
                sheet.cell(1, 6) = "G_y"
                sheet.cell(1, 7) = "G_Y (nit)"
                sheet.cell(1, 8) = "B_x"
                sheet.cell(1, 9) = "B_y"
                sheet.cell(1, 10) = "B_Y (nit)"
        
        
        
         '''''' Record Original Data    Measurement
         objCa.RemoteMode = 1
         objMemory.ChannelNO = Text_ch
     
    ''''''''''''''''Test Remove recipe by stockton 12/14
    
    
    Dim Rx(GLT) As Double
    Dim Ry(GLT) As Double
    Dim RYN(GLT) As Double
    Dim Gx(GLT) As Double
    Dim Gy(GLT) As Double
    Dim GYN(GLT) As Double
    Dim Bx(GLT) As Double
    Dim By(GLT) As Double
    Dim BYN(GLT) As Double
    
    Dim Lgain(GLT) As Single
    Dim MeasuredGammaR(GLT) As Single
    Dim MeasuredGammaG(GLT) As Single
    Dim MeasuredGammaB(GLT) As Single
    
    Dim index(GLT) As Single
    
    Dim RL(GLT) As Single
    Dim GL(GLT) As Single
    Dim BL(GLT) As Single
    Dim GrayL(GLT) As Single
        Call PatternRGB(255, 0, 0)
        row1 = 1
        Background.setShow
        Tims (10)
        Call RGBcal.CA210(Cx, Cy, Y255)
        Call Background.BGShow1(255, Y255, 0)
        
    
            sheet.setSheetIndex 2
            For GLX = StartG To EndG Step -STP
                    x = GLX
                    If x > 255 Then x = 255
                    GrayL(row1 - 1) = x
              
                Call PatternRGB(x, 0, 0)
                Call RGBcal.CA210(Cx, Cy, Yx)
                Call Background.BGShow2(x, Yx, 0)
                     row1 = row1 + 1
                Rx(row1 - 2) = Cx 'L(0)=L255
                Ry(row1 - 2) = Cy
                RYN(row1 - 2) = Yx
           
        
                sheet.cell(row1, 1) = x
                sheet.cell(row1, 2) = Cx
                sheet.cell(row1, 3) = Cy
                sheet.cell(row1, 4) = Yx
                
              
            Next GLX
            
        '''''''''''''''''''''''G
            
            
        Call PatternRGB(0, 255, 0)
        row1 = 1
        Background.setShow
        Tims (10)
        Call RGBcal.CA210(Cx, Cy, Y255)
        Call Background.BGShow1(255, Y255, 0)
        
    
            sheet.setSheetIndex 2
            For GLX = StartG To EndG Step -STP
                    x = GLX
                    If x > 255 Then x = 255
                    GrayL(row1 - 1) = x
              
                Call PatternRGB(0, x, 0)
                Call RGBcal.CA210(Cx, Cy, Yx)
                Call Background.BGShow2(x, Yx, 0)
                     row1 = row1 + 1
                Gx(row1 - 2) = Cx 'L(0)=L255
                Gy(row1 - 2) = Cy
                GYN(row1 - 2) = Yx
           
        
                sheet.cell(row1, 5) = Cx
                sheet.cell(row1, 6) = Cy
                sheet.cell(row1, 7) = Yx
                
              
            Next GLX
            
        ''''''''''''''''''B
        
        Call PatternRGB(0, 0, 255)
        row1 = 1
        Background.setShow
        Tims (10)
        Call RGBcal.CA210(Cx, Cy, Y255)
        Call Background.BGShow1(255, Y255, 0)
        
    
            sheet.setSheetIndex 2
            For GLX = StartG To EndG Step -STP
                    x = GLX
                    If x > 255 Then x = 255
                    GrayL(row1 - 1) = x
              
                Call PatternRGB(0, 0, x)
                Call RGBcal.CA210(Cx, Cy, Yx)
                Call Background.BGShow2(x, Yx, 0)
                     row1 = row1 + 1
                Bx(row1 - 2) = Cx 'L(0)=L255
                By(row1 - 2) = Cy
                BYN(row1 - 2) = Yx
           
        
                sheet.cell(row1, 8) = Cx
                sheet.cell(row1, 9) = Cy
                sheet.cell(row1, 10) = Yx
                
              
            Next GLX
            
            
            
            
    
    '''''''''''''''Data Normalize Remove Recipe by Stockton 12/14
        Dim n As Integer
        n = row1 - 1
        Rmin = RYN(n - 1)
        Gmin = GYN(n - 1)
        Bmin = BYN(n - 1)
    Unload Background


'''''''''''''' Predict RGB Remove Recipe by Stockton 12/14 TEST OK
If flag_LoadG = False Then
    For i = 0 To 255
        DesiredGamma(i) = ((255 - i) / 255) ^ Val(Text_ga.Text)
        DesiredGammaR(i) = ((255 - i) / 255) ^ Val(Text_rga.Text)
        DesiredGammaG(i) = ((255 - i) / 255) ^ Val(Text_gga.Text)
        DesiredGammaB(i) = ((255 - i) / 255) ^ Val(Text_bga.Text)
    Next i
End If
For i = 0 To n - 1
   MeasuredGammaR(i) = (RYN(i) - Rmin) / (RYN(0) - Rmin)
   MeasuredGammaG(i) = (GYN(i) - Gmin) / (GYN(0) - Gmin)
   MeasuredGammaB(i) = (BYN(i) - Bmin) / (BYN(0) - Bmin)
Next i

''''''''''''''R
For i = 0 To 255

DesiredG = DesiredGammaR(i)
    For j = 0 To n - 1
    tempR = MeasuredGammaR(j)
    If ((DesiredG - tempR) = 0) Then
    
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round(GrayL(j) * 4, 0)
            Else
                RL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round(GrayL(j) * 16, 0)
            Else
                RL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If
        
        
        End If
        

        Exit For
    ElseIf ((DesiredG - tempR) > 0) Then
         
         If (option_10bit.Value = True) Then
         
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
         Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If
        
         End If
        
        Exit For
    End If
     
        
    Next j
    
Next i

''''''''''''''G
For i = 0 To 255

DesiredG = DesiredGammaG(i)
    For j = 0 To n - 1
    tempG = MeasuredGammaG(j)
    If ((DesiredG - tempG) = 0) Then
        'If Option1.Value = True Then
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round(GrayL(j) * 4, 0)
            Else
                GL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round(GrayL(j) * 16, 0)
            Else
                GL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If
        End If
        
        
        Exit For
    ElseIf ((DesiredG - tempG) > 0) Then
    
        If (option_10bit.Value = True) Then
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
        Else
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If

        End If
        Exit For
    End If
     
        
    Next j
    
Next i

''''''''''''''B
For i = 0 To 255

DesiredG = DesiredGammaB(i)
    For j = 0 To n - 1
    tempB = MeasuredGammaB(j)
    If ((DesiredG - tempB) = 0) Then
        
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round(GrayL(j) * 4, 0)
            Else
            
                BL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round(GrayL(j) * 16, 0)
            Else
            
                BL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If

        End If
        'If Option3.Value = True Then BL(i) = Round(GrayL(j) / 255 * 1008, 0)
        
        'End If
        Exit For
    ElseIf ((DesiredG - tempB) > 0) Then
         
        
        If (option_10bit.Value = True) Then
        
        'If Option1.Value = True Then
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If

        End If
            
        ' If Option3.Value = True Then BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) / 255 * 1008, 0)
        'End If
        Exit For
    End If
     
        
    Next j
   
Next i




    RL(255) = 0
    GL(255) = 0
    BL(255) = 0
    sheet.setSheetIndex 1
    For i = 0 To 255
        sheet.cell(i + 2, 1) = i
        sheet.cell(i + 2, 2) = RL(255 - i)
        sheet.cell(i + 2, 3) = GL(255 - i)
        sheet.cell(i + 2, 4) = BL(255 - i)
    Next i

 sheet.setSheetIndex 1
 sheet.setSheetName "Gamma Table"
 Utils.changeColorAnd sheet
 

 sheet.setSheetIndex 2
 sheet.setSheetName "Raw Data"
           
'''''''''''''' Save Data
sheet.setSheetFilename Text_path & Text_FN
sheet.store
sheet.closing

'ETime = Time  '''''''''' Timer
'MsgBox "Start Time - End Time : " & STime & " - " & ETime
'EndG:


frmGamma.Show

End Sub

Private Sub Command3_Click()
 Dim fm As String, fnum As Integer, fname As String
    'Dim iCheck As Integer
    
    'iCheck = MsgBox("Are you sure to load file to CA-210", vbOKCancel)
    
    'If iCheck = 2 Then
    'Exit Sub
    'End If
    
    On Error Resume Next
    cmdDiag.CancelError = True
    cmdDiag.filename = "*.xls"
    cmdDiag.Filter = "Normalizaed Gamma data (*.xls)|*.xls"
    cmdDiag.FilterIndex = 2
    cmdDiag.Action = 1
    If Err.Number = cdlCancel Then
        Exit Sub
    Else
        fm = cmdDiag.filename
        'fm = Mid$(fm, 1, InStr(1, fm, ".")) + "xls"
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
   For i = 0 To 255
        DesiredGamma(i) = xlsheet.Cells(i + 2, 2)
        DesiredGammaR(i) = xlsheet.Cells(i + 2, 3)
        DesiredGammaG(i) = xlsheet.Cells(i + 2, 4)
        DesiredGammaB(i) = xlsheet.Cells(i + 2, 5)
    Next i
    flag_LoadG = True
End Sub

Private Sub Command4_Click()
Dim GrayL(GLT) As Single
Dim fm As String

    cmdDiag.CancelError = True
    cmdDiag.filename = "*.xls"
    cmdDiag.Filter = "Row Data (*.xls)|*.xls"
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

    Dim RYN(GLT) As Double
    Dim GYN(GLT) As Double
    Dim BYN(GLT) As Double
Dim RL(GLT) As Single
Dim GL(GLT) As Single
Dim BL(GLT) As Single
row1 = 1

'''''''''' Parameter
    If Text_LS > 0 Then
        StartG = 256
    Else
        StartG = 255
    End If


EndG = 0
STP = 2 ^ Val(Text_LS)

    Dim sheet As SpreadSheet
    Set sheet = Utils.openSheet(fm)
    sheet.setSheetIndex 1
    
        
    For GLX = StartG To EndG Step -STP
            x = GLX
            If x > 255 Then x = 255
            GrayL(row1 - 1) = x

        row1 = row1 + 1
        RYN(row1 - 2) = sheet.cell(row1, 4) 'L(0)=L255
        GYN(row1 - 2) = sheet.cell(row1, 7)
        BYN(row1 - 2) = sheet.cell(row1, 10)
       
    Next GLX
Go_ahead = True
MainForm.WindowState = 1

    
    

    
    Dim Lgain(GLT) As Single
    Dim MeasuredGammaR(GLT) As Single
    Dim MeasuredGammaG(GLT) As Single
    Dim MeasuredGammaB(GLT) As Single
    
    Dim index(GLT) As Single
    
   ' Dim GrayL(GLT) As Single
        
    
        
          
            
        '''''''''''''''''''''''G
            
            
     
            
            
            
            
    
    '''''''''''''''Data Normalize Remove Recipe by Stockton 12/14
        Dim n As Integer
        n = row1 - 1
        Rmin = RYN(n - 1)
        Gmin = GYN(n - 1)
        Bmin = BYN(n - 1)
    ''''''''Unload Background


'''''''''''''' Predict RGB Remove Recipe by Stockton 12/14 TEST OK
If flag_LoadG = False Then
    For i = 0 To 255
        DesiredGamma(i) = ((255 - i) / 255) ^ Val(Text_ga.Text)
        DesiredGammaR(i) = ((255 - i) / 255) ^ Val(Text_rga.Text)
        DesiredGammaG(i) = ((255 - i) / 255) ^ Val(Text_gga.Text)
        DesiredGammaB(i) = ((255 - i) / 255) ^ Val(Text_bga.Text)
    Next i
End If
For i = 0 To n - 1
   MeasuredGammaR(i) = (RYN(i) - Rmin) / (RYN(0) - Rmin)
   MeasuredGammaG(i) = (GYN(i) - Gmin) / (GYN(0) - Gmin)
   MeasuredGammaB(i) = (BYN(i) - Bmin) / (BYN(0) - Bmin)
Next i

''''''''''''''R
For i = 0 To 255

DesiredG = DesiredGammaR(i)
    For j = 0 To n - 1
    tempR = MeasuredGammaR(j)
    If ((DesiredG - tempR) = 0) Then
            
        If (option_10bit.Value = True) Then
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round(GrayL(j) * 4, 0)
            Else
                RL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                RL(i) = Round(GrayL(j) * 16, 0)
            Else
                RL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If

        End If

        Exit For
    ElseIf ((DesiredG - tempR) > 0) Then
    
         If (option_10bit.Value = True) Then
         
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
         
         Else
            
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
               RL(i) = Round((GrayL(j) + (DesiredG - tempR) / (MeasuredGammaR(j - 1) - tempR) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If
        
         End If
        
        Exit For
    End If
     
        
    Next j
    
Next i

''''''''''''''G
For i = 0 To 255

DesiredG = DesiredGammaG(i)
    For j = 0 To n - 1
    tempG = MeasuredGammaG(j)
    If ((DesiredG - tempG) = 0) Then
        'If Option1.Value = True Then
        
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round(GrayL(j) * 4, 0)
            Else
                GL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        Else
            
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round(GrayL(j) * 16, 0)
            Else
                GL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If
        
        End If

        Exit For
    ElseIf ((DesiredG - tempG) > 0) Then
    
        If (option_10bit.Value = True) Then
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
                GL(i) = Round((GrayL(j) + (DesiredG - tempG) / (MeasuredGammaG(j - 1) - tempG) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If

        End If
        
        Exit For
    End If
     
        
    Next j
    
Next i

''''''''''''''B
For i = 0 To 255

DesiredG = DesiredGammaB(i)
    For j = 0 To n - 1
    tempB = MeasuredGammaB(j)
    If ((DesiredG - tempB) = 0) Then
        
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round(GrayL(j) * 4, 0)
            Else
            
                BL(i) = Round(GrayL(j) * 2, 0) * 2
            End If
        
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round(GrayL(j) * 16, 0)
            Else
            
                BL(i) = Round(GrayL(j) * 2, 0) * 2 * 4
            End If

        End If
        'If Option3.Value = True Then BL(i) = Round(GrayL(j) / 255 * 1008, 0)
        
        'End If
        Exit For
    ElseIf ((DesiredG - tempB) > 0) Then
         
        'If Option1.Value = True Then
        If (option_10bit.Value = True) Then
        
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 4, 0)
            Else
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2
            End If
        Else
            If ((Option1.Value = True) Or (Option4.Value = True)) Then
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 16, 0)
            Else
                BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) * 2, 0) * 2 * 4
            End If
        End If
        
        
        ' If Option3.Value = True Then BL(i) = Round((GrayL(j) + (DesiredG - tempB) / (MeasuredGammaB(j - 1) - tempB) * (GrayL(j - 1) - GrayL(j))) / 255 * 1008, 0)
        'End If
        
        
        Exit For
    End If
     
        
    Next j
    
Next i




    RL(255) = 0
    GL(255) = 0
    BL(255) = 0
    sheet.setSheetIndex 2
    For i = 0 To 255
        sheet.cell(i + 2, 1) = i
        sheet.cell(i + 2, 2) = RL(255 - i)
        sheet.cell(i + 2, 3) = GL(255 - i)
        sheet.cell(i + 2, 4) = BL(255 - i)
    Next i

sheet.setSheetName "Gamma Table"
sheet.setZoom 75
           
'''''''''''''' Save Data
sheet.setSheetFilename Text_path & Text_FN
sheet.store
sheet.closing

'ETime = Time  '''''''''' Timer
'MsgBox "Start Time - End Time : " & STime & " - " & ETime
'EndG:


frmGamma.Show



End Sub

Private Sub Form_Load()
flag_LoadG = False
If Debug_enable = True Then Command4.visible = True

End Sub

Private Sub op_10bit2_Click()
option_10bit.Value = True
End Sub

Private Sub op_12bit2_Click()
option_12bit.Value = True
End Sub

Private Sub op_in_10_Click()
op_out_6.Enabled = False
op_out_10.Enabled = True
op_out_8.Enabled = True
op_10bit2.Enabled = False

op_12bit2.Value = True
'GSL = 1023
'GLS = 2
chk_ga256.Value = 1
'If op_out_8.Value = True Then
chk_frc2.Enabled = False
Option4.Value = True
End Sub

Private Sub op_in_6_Click()
Option3.Value = True
op_out_6.Enabled = True
op_10bit2.Enabled = True
op_10bit2.Value = True
op_12bit2.Enabled = False
op_out_10.Enabled = False
'op_out_8.Enabled = False
'If op_out_8.Value = True Then
  '  GSL = 255
  '  GLS = 0
chk_ga256.Value = 0
chk_frc2.Enabled = True
End Sub

Private Sub op_in_8_Click()
op_out_6.Enabled = True
op_10bit2.Enabled = True
op_12bit2.Enabled = True
op_10bit2.Value = True
op_out_10.Enabled = False
op_out_8.Value = True
'If op_out_8.Value = True Then
  '  GSL = 255
  '  GLS = 0
'End If
Option1.Value = True
chk_ga256.Value = 0
chk_frc2.Enabled = True
End Sub
