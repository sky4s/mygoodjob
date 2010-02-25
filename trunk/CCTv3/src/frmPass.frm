VERSION 5.00
Begin VB.Form frmPass 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "CCT Adjustment V3.10"
   ClientHeight    =   3804
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   5388
   Icon            =   "frmPass.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3804
   ScaleWidth      =   5388
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   375
      Left            =   2145
      TabIndex        =   2
      Top             =   2865
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   1830
      PasswordChar    =   "*"
      TabIndex        =   0
      Top             =   2400
      Width           =   1740
   End
   Begin VB.Image Image1 
      Height          =   504
      Left            =   252
      Picture         =   "frmPass.frx":030A
      Top             =   312
      Width           =   1200
   End
   Begin VB.Label Label3 
      Caption         =   "CCT Adjustment V3.10"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   14.4
         Charset         =   136
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2040
      TabIndex        =   5
      Top             =   480
      Width           =   2985
   End
   Begin VB.Label Label2 
      BackColor       =   &H80000004&
      Caption         =   $"frmPass.frx":0A18
      Height          =   975
      Left            =   240
      TabIndex        =   4
      Top             =   1200
      Width           =   4815
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
      Left            =   840
      TabIndex        =   3
      Top             =   3480
      Width           =   4395
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Password"
      Height          =   180
      Left            =   960
      TabIndex        =   1
      Top             =   2520
      Width           =   645
   End
End
Attribute VB_Name = "frmPass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Magic_word = "AUO0504618"
    Magic_word2 = "FIFI0504618"
    If ((UCase(Text1.Text) <> Magic_word) And ((UCase(Text1.Text) <> Magic_word2))) Then
        x = MsgBox("The Password is Wrong!", vbOKOnly + vbExclamation, "ERROR")
    End
Else
    If (UCase(Text1.Text)) = Magic_word2 Then
        Debug_enable = True
    Else
        Debug_enable = False
    End If
    MainForm.Show
    Unload frmPass
End If

End Sub
Private Sub Form_Load()
Debug_enable = True
MainForm.Show
Unload frmPass
End Sub
