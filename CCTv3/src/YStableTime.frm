VERSION 5.00
Begin VB.Form YStableTime 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Stability Measurement"
   ClientHeight    =   3348
   ClientLeft      =   7536
   ClientTop       =   6828
   ClientWidth     =   5052
   Icon            =   "YStableTime.frx":0000
   LinkTopic       =   "Form6"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3348
   ScaleWidth      =   5052
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame4 
      Caption         =   "Source Channel"
      Height          =   852
      Left            =   2160
      TabIndex        =   13
      Top             =   1800
      Width           =   1455
      Begin VB.TextBox TCH 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   480
         TabIndex        =   14
         Text            =   "0"
         Top             =   360
         Width           =   612
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Stop"
      Height          =   1212
      Left            =   2760
      TabIndex        =   11
      Top             =   240
      Width           =   1572
      Begin VB.Label Label1 
         Caption         =   "Pressure "" F4 "" will stop this measurement"
         Height          =   612
         Left            =   240
         TabIndex        =   12
         Top             =   360
         Width           =   1092
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Gray Level"
      Height          =   1452
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   2412
      Begin VB.TextBox B6 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   1440
         TabIndex        =   8
         Text            =   "255"
         Top             =   1080
         Width           =   612
      End
      Begin VB.TextBox G6 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   1440
         TabIndex        =   7
         Text            =   "255"
         Top             =   720
         Width           =   612
      End
      Begin VB.TextBox R6 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   1440
         TabIndex        =   6
         Text            =   "255"
         Top             =   360
         Width           =   612
      End
      Begin VB.Label Label5 
         Caption         =   "B Gray Level"
         Height          =   252
         Left            =   240
         TabIndex        =   5
         Top             =   1080
         Width           =   1092
      End
      Begin VB.Label Label4 
         Caption         =   "G Gray Level"
         Height          =   252
         Left            =   240
         TabIndex        =   4
         Top             =   720
         Width           =   972
      End
      Begin VB.Label Label3 
         Caption         =   "R Gray Level"
         Height          =   252
         Left            =   240
         TabIndex        =   3
         Top             =   360
         Width           =   1092
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Run"
      Height          =   372
      Left            =   3840
      TabIndex        =   1
      Top             =   2280
      Width           =   852
   End
   Begin VB.TextBox IT6 
      Alignment       =   2  'Center
      Height          =   264
      Left            =   600
      TabIndex        =   0
      Text            =   "3"
      Top             =   2160
      Width           =   492
   End
   Begin VB.Frame Frame2 
      Caption         =   "Interval Time"
      Height          =   852
      Left            =   120
      TabIndex        =   9
      Top             =   1800
      Width           =   1812
      Begin VB.Label Label6 
         Caption         =   "sec."
         Height          =   252
         Left            =   1080
         TabIndex        =   10
         Top             =   360
         Width           =   492
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
      Left            =   480
      TabIndex        =   15
      Top             =   3000
      Width           =   4395
   End
End
Attribute VB_Name = "YStableTime"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Go_ahead6 = True
    Go_ahead = True
    MainForm.WindowState = 1
    BR6 = Val(YStableTime.R6)
    BG6 = Val(YStableTime.G6)
    BB6 = Val(YStableTime.B6)
    
    
    ''''''''' Open Recorder
    Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
    
    sheet.cell(1, 1) = "Time"
    sheet.cell(1, 2) = "x"
    sheet.cell(1, 3) = "y"
    sheet.cell(1, 4) = "Y"
    
    
    '''''' Start Test
    row1 = 1
    Background.setShow
    
    Call PatternRGB(BR6, BG6, BB6)
    SaTime = Time
    
    objCa.RemoteMode = 1
    objMemory.ChannelNO = TCH
    
    Do Until Go_ahead6 = False
        
        Call Tims(Val(YStableTime.IT6))
        Call RGBcal.CA210(Cx, Cy, Yx)
        Call Background.BGShow2(Empty, Yx, 0)
        Call PatternRGB(BR6, BG6, BB6)
        
        RTime = Time - SaTime
        If RTime < 0 Then RTime = RTime + 1 ''修正超過晚上12點時間為負值 by Stockton 03/26/2007
        row1 = row1 + 1
        sheet.cell(row1, 1) = RTime
        sheet.cell(row1, 2) = Cx
        sheet.cell(row1, 3) = Cy
        sheet.cell(row1, 4) = Yx
        Call Utils.callDoEvents
    Loop
    
    Utils.changeFormatAnd sheet
    
    Unload Me
    MainForm.Show
    
    
End Sub


Private Sub Command2_Click()
    Go_ahead6 = False
    YStableTime.Hide
End Sub


Private Sub Form_Load()
    If GetKeyState(vbKeyF4) And &H1 = &H1 Then
        keystate(vbKeyF4) = 0
        Rval = SetKeyboardState(keystate(vbKeyF4))
    End If
End Sub
