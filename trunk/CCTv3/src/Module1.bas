Attribute VB_Name = "Module1"
Declare Function GetKeyState Lib "user32" (ByVal nVirtKey As Long) As Integer
Declare Function SetKeyboardState Lib "user32" (lppbKeyState As Byte) As Long

Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Declare Function DestroyWindow Lib "user32" (ByVal hwnd As Long) As Long

Public Debug_enable As Boolean
Public Go_ahead As Boolean
Public Go_ahead6 As Boolean

Public keystate(0 To 255) As Byte
Public Rval As Long

'******** Form Check
Public MinoltaFormCK As Integer

'******** Chroma
Public BR232 As String
Public D232 As String
Public P232 As String
Public ChromaS As String

Public Source_CH As Integer
Public Calib_CH As Integer


Public row1 As Integer

Public flag_LoadG As Boolean

'******GrayTest
Public R_value(9000) As Double
Public G_value(9000) As Double
Public B_value(9000) As Double

' output file format
Public sheetType As OpType
Private Const DebugFile As String = "debug.txt"



Private Sub sheetTest()
    Dim s As SpreadSheet
    Set s = Utils.newSheet
    Dim i As Integer
    For i = 1 To 100
        Call s.setCellValue(1, i, i)
    Next
End Sub


Private Sub setKeyState()
    If GetKeyState(vbKeyEscape) And &H1 = &H1 Then
        keystate(vbKeyEscape) = 0
        Rval = SetKeyboardState(keystate(vbKeyEscape))
    End If
End Sub

Public Sub Main()
    On Error GoTo E
    sheetType = OpType.Excel
    UseCA210 = FileSystem.Dir(DebugFile) = ""
    Call setKeyState

    
    Dim i As Integer
    SCL = 6
    Scl_Level = 0
    SDO = 7
    Sdo_Level = 0
    SDI = 7
    Sdi_Level = 0
    LPTAddressBase = &H378
    LPTOutData = 255
    px = Screen.Width
    ppx = Screen.TwipsPerPixelX
    plx = px / ppx
    
    py = Screen.Height
    ppy = Screen.TwipsPerPixelY
    ply = py / ppy
    
    MainForm.Rx = plx
    MainForm.Ry = ply
    
    If True = UseCA210 Then '''''For Test
        'MeasureTool.initCA210
    End If
    
    MainForm.Show
    Exit Sub
    
    
E:
    Call Utils.catch
    '    Dim strErr As String
    '    Dim iReturn As Integer
    '
    '    strErr = "Error from " + Err.Source + Chr$(10) + Chr$(13)
    '    strErr = strErr + Err.Description + Chr$(10) + Chr$(13)
    '    strErr = strErr + "HRESULT " + CStr(Err.Number - vbObjectError)
    '    iReturn = MsgBox(strErr, vbRetryCancel)
    '    Select Case iReturn
    '        Case vbRetry
    '            Resume
    '        Case Else:
    '            objCa.RemoteMode = 0
    '        End
    '    End Select
    '    Resume Next
End Sub
