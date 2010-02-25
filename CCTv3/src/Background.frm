VERSION 5.00
Begin VB.Form Background 
   BackColor       =   &H00000000&
   BorderStyle     =   0  'None
   Caption         =   "Background"
   ClientHeight    =   9000
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   12000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   750
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   1000
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   WindowState     =   2  'Maximized
   Begin VB.TextBox Text8 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   7.8
         Charset         =   136
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   156
      Left            =   4920
      TabIndex        =   16
      Text            =   "1"
      Top             =   480
      Visible         =   0   'False
      Width           =   372
   End
   Begin VB.TextBox Text7 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   7.8
         Charset         =   136
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   156
      Left            =   4920
      TabIndex        =   15
      Text            =   "2"
      Top             =   840
      Visible         =   0   'False
      Width           =   372
   End
   Begin VB.TextBox Text6 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   8160
      TabIndex        =   14
      Text            =   "Difference"
      Top             =   120
      Visible         =   0   'False
      Width           =   972
   End
   Begin VB.TextBox Text5 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   6960
      TabIndex        =   13
      Text            =   "Brightness"
      Top             =   120
      Visible         =   0   'False
      Width           =   972
   End
   Begin VB.TextBox Text4 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   5280
      TabIndex        =   12
      Text            =   "Actual Gray Level"
      Top             =   105
      Visible         =   0   'False
      Width           =   1452
   End
   Begin VB.TextBox Text3 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   3360
      TabIndex        =   11
      Text            =   "Algorithm"
      Top             =   120
      Visible         =   0   'False
      Width           =   972
   End
   Begin VB.TextBox Text2 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   1920
      TabIndex        =   10
      Text            =   "Input Gray Level"
      Top             =   120
      Visible         =   0   'False
      Width           =   1212
   End
   Begin VB.TextBox Text1 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   240
      TabIndex        =   9
      Text            =   "Gray Level"
      Top             =   120
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKD2 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   8160
      TabIndex        =   8
      Text            =   "0"
      Top             =   840
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKB2 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   7080
      TabIndex        =   7
      Text            =   "0"
      Top             =   840
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKAGL2 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   5640
      TabIndex        =   6
      Text            =   "0"
      Top             =   840
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKD1 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   8160
      TabIndex        =   5
      Text            =   "0"
      Top             =   480
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKB1 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   7080
      TabIndex        =   4
      Text            =   "0"
      Top             =   480
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKAGL1 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   5640
      TabIndex        =   3
      Text            =   "0"
      Top             =   480
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKA 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   3375
      TabIndex        =   2
      Text            =   "0"
      Top             =   480
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKIGL 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   2040
      TabIndex        =   1
      Text            =   "0"
      Top             =   480
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.TextBox BKGL 
      Alignment       =   2  'Center
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H00FFFFFF&
      Height          =   252
      Left            =   240
      TabIndex        =   0
      Text            =   "0"
      Top             =   480
      Visible         =   0   'False
      Width           =   852
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   1080
      Top             =   960
   End
End
Attribute VB_Name = "Background"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Const ShowMe As Boolean = True
Private showingMe As Boolean
Private Const BGShow As Boolean = True

Private Sub Timer1_Timer()
    
    If GetKeyState(vbKeyEscape) And &H1 = &H1 Then
        Go_ahead = False
        keystate(vbKeyEscape) = 0
        Rval = SetKeyboardState(keystate(vbKeyEscape))
        '******** End program
    End
End If


If GetKeyState(vbKeyS) And &H1 = &H1 Then
    Call setShow
    'Tims (1)
    MainForm.Show
    keystate(vbKeyS) = 0
    Rval = SetKeyboardState(keystate(vbKeyS))
End If

If GetKeyState(vbKeyF4) And &H1 = &H1 Then
    Go_ahead6 = False
    keystate(vbKeyF4) = 0
    Rval = SetKeyboardState(keystate(vbKeyF4))
End If

End Sub

Public Sub setShow()
    If True = ShowMe And False = Me.visible And False = showingMe Then
        showingMe = True
        Me.Show
        showingMe = False
        'Tims (1)
    End If
End Sub
Public Sub BGShow1(AGL1, B1, D1)
    If False = BGShow Then
        Exit Sub
    End If
    
    Background.BKAGL1 = AGL1
    Background.BKB1 = B1
    Background.BKD1 = D1
End Sub
Public Sub BGShow2(AGL2, B2, D2)
    If False = BGShow Then
        Exit Sub
    End If

If MainForm.op_pc.Value = True Then
    Background.BKAGL2 = AGL2
    Background.BKB2 = B2
    Background.BKD2 = D2
End If
End Sub
