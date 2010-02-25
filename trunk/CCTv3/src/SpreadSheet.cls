VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SpreadSheet"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' basic sheet setup
Private sheetFilename As String
Private sheetType As OpType
Private sheetMode As OpMode

' check for init
Private initialized As Boolean
' output debug message in debugMode
Private Const DebugMode As Boolean = True


' for open office only
Private workbook As Object
Private document As Object
Private serviceManager As Object

'for MS office only
Private msDesktop As Object

' for common use
Private desktop As Object
Private sheet As Object
Private Const SheetEnable As Boolean = True


Public Enum OpMode
    NewFile = 1
    OpenFile = 2
End Enum

Public Enum OpType
    Excel = 1
    Calc = 2
    CSV = 4
End Enum

Public Sub setSheetFilename(filename As String)
    If False = SheetEnable Then
        Exit Sub
    End If

    sheetFilename = getFilename(filename, sheetMode, sheetType)
End Sub

Public Sub setVisible(visible As Boolean)
    If False = SheetEnable Then
        Exit Sub
    End If

    Call checkInitialized
    Select Case sheetType
        Case Excel
            'desktop.visible = visible
        Case Calc
            'workbook.isVisible = visible
    End Select
End Sub

Public Sub setSheetName(sheetName As String)
    If False = SheetEnable Then
        Exit Sub
    End If

    Call checkInitialized
    Select Case sheetType
        Case Excel
            sheet.Name = sheetName
        Case Calc
            sheet.Name = sheetName
    End Select
End Sub

Public Property Get cell(column As Integer, row As Integer) As Variant
    If False = SheetEnable Then
        Exit Property
    End If
    
    cell = getCellValue(column, row)
End Property

Public Property Let cell(column As Integer, row As Integer, ByVal Value As Variant)
    If False = SheetEnable Then
        Exit Property
    End If
    
    Call setCellValue(column, row, Value)
End Property


Public Sub setCellValue(column As Integer, row As Integer, Value As Variant)
    If False = SheetEnable Then
        Exit Sub
    End If

    Call checkInitialized
    Select Case sheetType
        Case Excel
            'sheet.Cells(row, column) = Value
            sheet.Cells(column, row) = Value
        Case Calc
            Select Case VarType(Value)
                Case vbString
                    sheet.getCellByPosition(row - 1, column - 1).String = Value
                Case Else
                    sheet.getCellByPosition(row - 1, column - 1).Value = Value
            End Select
    End Select
End Sub

 

Public Function getCellValue(column As Integer, row As Integer)
    If False = SheetEnable Then
        Exit Function
    End If

    Call checkInitialized
    Select Case sheetType
        Case Excel
            getCellValue = sheet.Cells(column, row)
        Case Calc
            getCellValue = sheet.getCellByPosition(row - 1, column - 1).Value
    End Select
End Function

Public Sub setSheetIndex(sheetIndex As Integer)
    If False = SheetEnable Then
        Exit Sub
    End If

    Call checkInitialized
    Select Case sheetType
        Case Excel
            Set sheet = desktop.ActiveWorkbook.Sheets(sheetIndex)
        Case Calc
            Set sheet = workbook.Sheets.getByIndex(sheetIndex - 1)
    End Select
End Sub

Private Function getExtFilename() As String
    Select Case sheetType
        Case Excel
            getExtFilename = "xls"
        Case Calc
            getExtFilename = "ods"
        Case CSV
            getExtFilename = "csv"
    End Select
End Function

Public Sub store()
    If False = SheetEnable Then
        Exit Sub
    End If

    Call checkInitialized
    If sheetFilename = "" Then
        ' 若沒有 sheetFilename, 無法存檔
        debugMsg "sheetFilename is Nothing! Must call setSheetFilename() before store()."
        Err.Raise -1, "sheetFilename is Nothing! Must call setSheetFilename() before store()."
    End If
    
    Select Case sheetType
        Case Excel
            desktop.ActiveWorkbook.SaveAs sheetFilename
        Case Calc
            Static arg()
            Dim url  As String
            url = ConvertToUrl(sheetFilename)
            Call workbook.storeToURL(ConvertToUrl(sheetFilename), arg())
    End Select
End Sub

Public Sub closing()
    If False = SheetEnable Then
        Exit Sub
    End If

    Call checkInitialized
    Select Case sheetType
        Case Excel
            desktop.ActiveWorkbook.Close
            desktop.Quit
        Case Calc
            Static arg()
            workbook.Close (True)
            Set workbook = Nothing
    End Select
End Sub

' 初始化的動作
Public Sub init(filename As String, M As OpMode, t As OpType)
    If False = SheetEnable Then
        Exit Sub
    End If

    If initialized = True Then
        ' prevent duplicated call init()
        debugMsg "Already call init() before"
        Exit Sub
    End If

    sheetMode = M
    sheetType = t
    setSheetFilename (filename)
    debugMsg sheetFilename & " " & M & " " & t

    Call init0
End Sub

Public Sub initNew(t As OpType)
    If False = SheetEnable Then
        Exit Sub
    End If
    
    If initialized = True Then
        ' prevent duplicated call init()
        debugMsg "Already call init() before"
        Exit Sub
    End If

    sheetMode = OpMode.NewFile
    sheetType = t

    Call init0
End Sub

' 產生filename, 如果是開啟舊檔, 就不用再加副檔名, 因為已經給了
Private Function getFilename(filename As String, M As OpMode, t As OpType)
    Select Case M
        Case NewFile
            getFilename = filename & "." & getExtFilename()
        Case OpenFile
            getFilename = filename
    End Select
End Function

Private Sub init0()
    Select Case sheetType
        Case Excel
            Call initMSOffice
        Case Calc
            Call initOpenOffice
    End Select
    initialized = True
    setSheetIndex (1)
End Sub

Private Sub initOpenOffice()
    Set desktop = CreateUnoService("com.sun.star.frame.Desktop")
    Dim url As String
    ' 由filename決定開新檔還是舊檔
    url = Switch(sheetMode = NewFile, "private:factory/scalc", sheetMode = OpenFile, ConvertToUrl(sheetFilename))
    Static arg()
    Set workbook = desktop.loadComponentFromURL(url, "_blank", 0, arg())
    'Set document = desktop.CurrentComponent.CurrentController.Frame
End Sub

Private Sub initMSOffice()
On Error GoTo catch
    If desktop Is Nothing And msDesktop Is Nothing Then
        Set desktop = CreateObject("Excel.Application")
        Set msDesktop = desktop
    Else
        Set desktop = msDesktop
    End If
    'Set desktop = CreateObject("Excel.Application")
    'Pause (1)
    desktop.visible = True
    'Pause (1)
    
    Select Case sheetMode
        Case NewFile
            desktop.Workbooks.Add
        Case OpenFile
            desktop.Workbooks.Open (sheetFilename)
    End Select
    Exit Sub
catch:
    Call Utils.catch
End Sub

Private Sub debugMsg(msg As String)
    If DebugMode = True Then
        Debug.Print msg
    End If
End Sub


'
'A simple shortcut to create a service
'
Private Function CreateUnoService(strServiceName) As Object
    If serviceManager Is Nothing Then
        ' 若manager不存在就創建
        Set serviceManager = CreateObject("com.sun.star.ServiceManager")
    End If
    Set CreateUnoService = serviceManager.createInstance(strServiceName)
End Function

'
'Converts a Ms Windows local pathname in URL (RFC 1738)
'
Private Function ConvertToUrl(ByVal strFile As String) As String
    strFile = Replace(strFile, "\", "/")
    strFile = Replace(strFile, ":", "|")
    strFile = Replace(strFile, " ", "%20")
    strFile = "file:///" + strFile
    ConvertToUrl = strFile
End Function


Private Sub checkInitialized()
    If False = initialized Then
        debugMsg "SpreadSheer had not call init() to initial!"
        Err.Raise -1, "SpreadSheet.checkInitialized()", "SpreadSheer had not call init() to initial! Must calling init() before any operation."
    End If
End Sub

Private Sub Class_Initialize()
    initialized = False
End Sub
Private Function MakePropertyValue(cName, uValue) As Object
    
  Dim oPropertyValue As Object
  Dim oSM As Object
    
  Set oPropertyValue = serviceManager.Bridge_GetStruct("com.sun.star.beans.PropertyValue")
  oPropertyValue.Name = cName
  oPropertyValue.Value = uValue
      
  Set MakePropertyValue = oPropertyValue

End Function

Public Sub setZoom(zoom As Integer)
    If False = SheetEnable Then
        Exit Sub
    End If
    
    Select Case sheetType
        Case Excel
            desktop.ActiveWindow.zoom = zoom
        Case Calc
            
    End Select
End Sub

Public Sub setMSDesktop(desktop As Object)
    If False = SheetEnable Then
        Exit Sub
    End If
    
    Set msDesktop = desktop
End Sub

Public Function getMSDesktop()
    Set getMSDesktop = msDesktop
End Function

Private Sub Class_Terminate()
    Set msDesktop = Nothing
    Set desktop = Nothing
    Set sheet = Nothing
End Sub
