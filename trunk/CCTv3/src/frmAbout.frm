VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "About CCT Adjustment V3.10"
   ClientHeight    =   2256
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   6720
   Icon            =   "frmAbout.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   2256
   ScaleWidth      =   6720
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   6045
      Top             =   1290
   End
   Begin VB.Image Image1 
      Height          =   504
      Left            =   120
      Picture         =   "frmAbout.frx":030A
      Top             =   1560
      Width           =   1200
   End
   Begin VB.Label Label2 
      BackColor       =   &H80000009&
      BorderStyle     =   1  'Fixed Single
      Caption         =   $"frmAbout.frx":0A18
      Height          =   975
      Left            =   885
      TabIndex        =   2
      Top             =   375
      Width           =   4935
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   15
      Left            =   3720
      TabIndex        =   1
      Top             =   960
      Width           =   135
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      Caption         =   "Copyright (C) 2005. AU Optronics Corp., All Rights Reserved"
      BeginProperty Font 
         Name            =   "·s²Ó©úÅé"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Left            =   2160
      TabIndex        =   0
      Top             =   1920
      Width           =   4395
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub btnAboutOK_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Dim caption As String
    
    'name and version info
    ' caption = App.ProductName & " v" & App.Major & "." & App.Minor & "." & App.Revision
    
    ' Me.caption = "About " & caption
    ' lblDescription.caption = caption
    ' lblCopyright.caption = App.LegalCopyright
    ' lblCredits.caption = "PortTalk driver - Craig Peacock (Craig.Peacock@beyondlogic.org), http://www.beyondlogic.org" + vbCr + vbCr + "CIE xy and u'v' chart - ppmcie (part of the Netpbm package), http://netpbm.sourceforge.net"
    
    'lblDisclaimer.caption = "This program is provided 'as is', with no guarantee of fitness or suitability for any purpose."
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Unload Me
End Sub

Private Sub Timer1_Timer()
    If GetKeyState(16) Then ''''''''''''''''''''''Shift
        If GetKeyState(vbKeyA) Then ''''''''''''''''''''AAAAAAAAAAA
            If GetKeyState(vbKeyU) Then
                If GetKeyState(vbKeyO) Then
                    keystate(vbKeyO) = 0
                    Rval = SetKeyboardState(keystate(vbKeyO))
                    Debug_enable = True
                End If
                
                keystate(vbKeyU) = 0
                Rval = SetKeyboardState(keystate(vbKeyU))
            End If
            keystate(vbKeyA) = 0
            Rval = SetKeyboardState(keystate(vbKeyA))
            
        End If
        keystate(16) = 0
        Rval = SetKeyboardState(keystate(16))
    End If
End Sub
