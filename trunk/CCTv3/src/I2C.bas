Attribute VB_Name = "I2C"

Public TimeD As Long
Public SCL As Integer
Public EN As Integer
Public EN_Level As Integer
Public Scl_Level As Integer
Public SDO As Integer
Public Sdo_Level As Integer
Public SDI As Integer
Public Sdi_Level As Integer
Public LPTAddressBase As Integer
Public current_lpt_data As Integer
Public current_lpt_ctrl As Integer
Public current_scl As Integer
Public current_sda As Integer
'Public ICStr(10) As String
'StatusAddress=Base+1
'ControlAddress=Base+2
'LPT1 Base=&H378
Public LPTOutData As Integer
Public Declare Function Inp Lib "inpout32.dll" Alias "Inp32" (ByVal PortAddress As Integer) As Integer
Public Declare Sub Out Lib "inpout32.dll" Alias "Out32" (ByVal PortAddress As Integer, ByVal Value As Integer)

'Public Declare Function Inp Lib "inpout32.dll" Alias "Inp32" (ByVal LPTAddress As Integer) As Integer
'Public Declare Function Out Lib "inpout32.dll" Alias "Out32" (ByVal LPTAddressBase As Integer, ByVal OutData As Integer) As Integer
'Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Public Sub delay_us()
    Dim tt, ii, jj As Integer
    tt = 0
    For ii = 0 To 3
        For jj = 0 To 1
            tt = tt + ii * jj
        Next jj
    Next ii
    
End Sub

Public Function udelay(ByVal i As Integer)
    Dim K As Integer
    For K = 0 To i * 1 '''''original:2  240hz
        delay_us
    Next K
End Function


Public Function lpt_read_byte_st() As Integer
    Dim ret_data As Integer
    lpt_read_byte_st = Inp(&H379)
    
End Function


Public Sub lpt_send_byte_data(ByVal Data As Integer)
    Dim i, K, tt As Double
    i = 0
    K = 0
    tt = 0
    current_lpt_data = Data
    Out &H378, Data
    For j = 0 To 5 'original:100  240hz   50  389hz
        For K = 0 To 5
            tt = tt + j * K
        Next K
    Next j
    
End Sub


Public Sub lpt_send_byte_ctrl(ByVal Data As Integer)
    Dim i, K, tt As Double
    i = 0
    K = 0
    tt = 0
    current_lpt_ctrl = Data
    Out &H378, Data
    For j = 0 To 5 'original:100  240hz  50:  389hz
        For K = 0 To 5
            tt = tt + j * K
        Next K
    Next j
    
End Sub

Public Sub i2c_initial()
    current_scl = 1
    current_sda = 1
    lpt_send_byte_data (&H3F)
    lpt_send_byte_ctrl (&H3F)
    Dim i As Integer
    For i = 0 To 15
        
        i2c_start
        i2c_end
        
    Next i
    
End Sub

Public Sub i2c_set_scl()
    Dim lpt_data, tmp_lpt_data As Integer
    current_scl = 1
    udelay 1
    If (current_sda = 1) Then
        tmp_lpt_data = &H3F
    Else
        tmp_lpt_data = &HBF
    End If
    lpt_data = (current_lpt_ctrl And &H3F) Or tmp_lpt_data
    lpt_send_byte_ctrl (lpt_data)
    
End Sub


Public Sub i2c_reset_scl()
    Dim lpt_data, tmp_lpt_data As Integer
    current_scl = 0
    udelay 1
    If (current_sda = 1) Then
        tmp_lpt_data = &H7F
    Else
        tmp_lpt_data = &HFF
    End If
    lpt_data = (current_lpt_ctrl And &H3F) Or tmp_lpt_data
    lpt_send_byte_ctrl (lpt_data)
    
End Sub


Public Sub i2c_set_scl_ack()
    Dim lpt_data, tmp_lpt_data As Integer
    current_scl = 1
    udelay 1
    
    tmp_lpt_data = &H3F
    
    lpt_data = (current_lpt_ctrl And &H3F) Or tmp_lpt_data
    lpt_send_byte_ctrl (lpt_data)
    
End Sub

Public Sub i2c_reset_scl_ack()
    Dim lpt_data, tmp_lpt_data As Integer
    current_scl = 0
    udelay 1
    
    tmp_lpt_data = &H7F
    
    lpt_data = (current_lpt_ctrl And &H3F) Or tmp_lpt_data
    lpt_send_byte_ctrl (lpt_data)
    
End Sub


Public Sub i2c_set_sda()
    Dim lpt_data, tmp_lpt_data As Integer
    current_sda = 1
    udelay 1
    If (current_scl = 1) Then
        tmp_lpt_data = &H3F
    Else
        tmp_lpt_data = &H7F
    End If
    lpt_data = (current_lpt_data And &H3F) Or tmp_lpt_data
    lpt_send_byte_data (lpt_data)
    
End Sub


Public Sub i2c_reset_sda()
    Dim lpt_data, tmp_lpt_data As Integer
    current_sda = 0
    udelay 1
    If (current_scl = 1) Then
        tmp_lpt_data = &HBF
    Else
        tmp_lpt_data = &HFF
    End If
    lpt_data = (current_lpt_data And &H3F) Or tmp_lpt_data
    lpt_send_byte_data (lpt_data)
    
End Sub


Public Sub i2c_start()
    i2c_reset_sda
End Sub


Public Sub i2c_end()
    i2c_reset_sda
    udelay 1
    i2c_set_scl
    udelay 1
    i2c_set_sda
End Sub


Public Function i2c_send_byte(ByVal Data As Integer) As Boolean
    Dim i, j, K As Integer
    Dim ack_fail_cnt As Integer
    ack_fail_cnt = 0
    
    
    t = Data Mod &H100
    
    For i = 7 To 0 Step -1
        i2c_reset_scl
        '    k = (Right(Data, i))
        'If (t \ &H80) = 1 Then
        '    SetSDA
        'Else
        '    ClrSDA
        'End If
        ' t = (t * 2) Mod &H100
        'If ((Right(Data, i) And (&H1)) >< 1) Then
        
        ' If (("&H" & Right(Data, i)) And (&H1) <> 0) Then
        If ((t \ (2 ^ i)) And (&H1) > 0) Then
            'If ((t \ &H80) = 1) Then
            
            i2c_set_sda
            
        Else
            i2c_reset_sda
            
        End If
        t = t Mod (2 ^ i)
        udelay 1
        i2c_set_scl
        udelay 1
    Next i
    i2c_reset_scl
    udelay 1
    i2c_reset_sda
    Dim data_tmp As Integer
    data_tmp = current_lpt_data And &H7F
    current_sda = 0
    lpt_send_byte_data (data_tmp)
    
    Dim st_data As Integer
    ack_fail_cnt = 0
    udelay 1
    i2c_set_scl_ack
    udelay 1
    i2c_reset_scl_ack
    'udelay 1    '''''test HL delay by stockton
    
End Function


Public Sub Write_Byte(ByVal addr As Integer, ByVal AddrI As Integer, ByVal d As Integer)
    
    i2c_start
    SubAddrH = (Int(Val(AddrI) / 256))
    'SubAddrL = (Val("&H" & Right(AddrI, 2)))
    SubAddrL = Val(AddrI) Mod 256
    i2c_send_byte addr
    i2c_send_byte SubAddrH
    i2c_send_byte SubAddrL
    i2c_send_byte d
    i2c_end
End Sub

Public Sub Write_Byte2(ByVal addr As Integer, ByVal SubAddrH As Integer, ByVal SubAddrL As Integer, ByVal d As Integer)
    
    i2c_start
    
    i2c_send_byte addr
    i2c_send_byte SubAddrH
    i2c_send_byte SubAddrL
    i2c_send_byte d
    i2c_end
End Sub
