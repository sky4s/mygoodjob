Attribute VB_Name = "Utils"
Option Explicit
Private msDesktop As Object
Private Const AlwaysNewExcel As Boolean = False
Private Const WaitAMoment As Integer = 1
Private Declare Function GetTickCount Lib "kernel32" () As Long
 
Private past As Single
Private doingEvents As Boolean
Private Const DoEventsRound As Integer = 50
Private Const TimsEnable As Boolean = True
Private Const TimsUseDoEvents As Boolean = True
Private Const DoEventsEnable As Boolean = True
Declare Function GetQueueStatus Lib "user32" (ByVal qsFlags As Long) As Long


Public Function newSheet()
    Dim sheet As SpreadSheet
    Set sheet = New SpreadSheet
    sheet.setMSDesktop msDesktop
    Call sheet.initNew(Module1.sheetType)
    'sheet.setVisible True
    'Call Tims(WaitAMoment)
    If AlwaysNewExcel = False Then
        Set msDesktop = sheet.getMSDesktop
    End If
    Set newSheet = sheet
End Function

Public Function openSheet(filename As String)
    Dim sheet As SpreadSheet
    Set sheet = New SpreadSheet
    sheet.setMSDesktop msDesktop
    Call sheet.init(filename, OpMode.OpenFile, Module1.sheetType)
    'sheet.setVisible True
    'Call Tims(WaitAMoment)
    If AlwaysNewExcel = False Then
        Set msDesktop = sheet.getMSDesktop
    End If
    Set openSheet = sheet
End Function

Public Sub changeColorAnd(sheet As SpreadSheet)
    '    Ex.ActiveWorkbook.Sheets(1).Columns("B:B").Select
    '    Ex.Selection.Font.ColorIndex = 3
    '    Ex.ActiveWorkbook.Sheets(1).Columns("C:C").Select
    '    Ex.Selection.Font.ColorIndex = 10
    '    Ex.ActiveWorkbook.Sheets(1).Columns("D:D").Select
    '    Ex.Selection.Font.ColorIndex = 5
    '    Ex.Selection.Columns.AutoFit
    sheet.setZoom 75
    
End Sub

Public Sub changeFormatAnd(sheet As SpreadSheet)
    '    Ex.Columns("A:A").Select
    '    Ex.Selection.NumberFormatLocal = "hh:mm:ss"
    '    Ex.Cells.Select
    '    With Ex.Selection.Font
    '        .Name = "Arial"
    '        .Size = 10
    '    End With
    '    Ex.Selection.Columns.AutoFit
    sheet.setZoom 75
End Sub


Public Sub changeFontAnd(sheet As SpreadSheet)
    '            Ex.Cells.Select
    '                With Ex.Selection.Font
    '                    .Name = "Arial"
    '                    .Size = 10
    '                End With
    '
    '            Ex.Selection.Columns.AutoFit
    sheet.setZoom 75
End Sub


Public Sub catch()
    '    Dim strErr As String
    '    Dim iReturn As Integer
    '    strErr = "Error from " + Err.Source + Chr$(10) + Chr$(13)
    '    strErr = strErr + Err.Description + Chr$(10) + Chr$(13)
    '    strErr = strErr + "HRESULT " + CStr(Err.Number - vbObjectError)
    '    iReturn = MsgBox(strErr, vbRetryCancel)
    '    Select Case iReturn
    '        Case vbRetry: Resume
    '        Case Else:
    '        objCa.RemoteMode = 0
    '        End
    '    End Select
    
    Dim strERR As String
    Dim iReturn As Integer

    strERR = "Error from " + Err.Source + Chr$(10) + Chr$(13)
    strERR = strERR + Err.Description + Chr$(10) + Chr$(13)
    strERR = strERR + "HRESULT " + CStr(Err.Number - vbObjectError)
    iReturn = MsgBox(strERR, vbRetryCancel)
    Select Case iReturn
        Case vbRetry
            Resume
        Case Else:
            If True = MeasureTool.UseCA210 Then objCa.RemoteMode = 0
        End
End Select
Resume Next
End Sub

Public Sub Tims(bb)
    If False = TimsEnable Then
        Exit Sub
    End If
    
    Call callDoEvents
    
    Dim t As Single
    t = Timer '§@¼È°±
    Dim count As Long
    Dim first As Boolean
    first = True
    
    Do Until (Timer - t) > bb
        If t > Timer Then t = t - 86400
        past = ((Timer - t) * 10) Mod 10
        
        If True = first Or past > 6 Then
            count = count + 1
            If (True = TimsUseDoEvents) And _
            (True = first Or ((count Mod DoEventsRound = 0) And (doingEvents = False))) Then
                Call callDoEvents
                first = False
            Else
                Sleep (1)
            End If
        End If

    Loop
End Sub

Public Sub callDoEvents()
     If True = DoEventsEnable And GetQueueStatus(255) <> 0 Then
        doingEvents = True
        DoEvents
        doingEvents = False
    End If
End Sub

