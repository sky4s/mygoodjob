Attribute VB_Name = "Pattern"
Private Const ShowPattern As Boolean = True
 

' ¥´pattern P (?)
Public Sub PatternI(P)
    If False = ShowPattern Then
        Exit Sub
    End If
    
    Call Utils.callDoEvents
    If Go_ahead = False Then GoTo PEnd
    If MainForm.op_pc.Value = True Then
        Background.setShow
        Background.BKGL = P
        Background.BackColor = RGB(P, P, P)
        
    Else
        Call Utils.callDoEvents
        TCON_RGB P, P, P
    End If

    Sleep Val(MainForm.IT)
    
PEnd:
    Background.setShow
End Sub


Public Sub MinoltaP()
    
    SyncM1 = ConfigForm.SyncM.ListIndex
    MR1 = ConfigForm.MR.ListIndex
    DM1 = ConfigForm.DM.ListIndex
    
    Unload ConfigForm
    
End Sub


Public Sub PatternRGB(PR, PG, PB)
    If False = ShowPattern Then
        Exit Sub
    End If

    If MainForm.op_pc.Value = True Then
        If Go_ahead = False Then GoTo PEnd
        Background.setShow
        Call Utils.callDoEvents
        Background.BackColor = RGB(PR, PG, PB)
        
PEnd:
        Background.setShow
    Else
        Call Utils.callDoEvents
        TCON_RGB PR, PG, PB
    End If
    Sleep Val(MainForm.IT)
    
    
End Sub


Public Sub TCON_RGB(ByVal Rin As Integer, ByVal Gin As Integer, ByVal Bin As Integer)
    If MainForm.op_single.Value = True Then
        Addr_master = Val("&H" & MainForm.Dev_single.Text)
    Else
        Addr_master = Val("&H" & MainForm.Dev_master.Text)
    End If
    Add_slave = Val("&H" & MainForm.Dev_slave.Text)
    Dim RH, RL, GH, GL, BH, BL As Integer
    
    
    
    
    
    '''AUO-12401
    RH = (Rin \ 256)
    RL = Rin Mod 256
    GH = (Gin \ 256)
    GL = Gin Mod 256
    BH = (Bin \ 256)
    BL = Bin Mod 256
    
    
    
    
    If MainForm.Com_Tcon_sel.Text = "AUO-12401" Then
        
        ''''''''''AUO-12401  Gamma Test Address 4A1[1] Rh4:4A7 Rl8 4A8
        Write_Byte Addr_master, &H4A1, 2 'Gamma_Test ON
        Write_Byte Addr_master, &H4A7, RH 'RH
        Write_Byte Addr_master, &H4A8, RL 'RL
        Write_Byte Addr_master, &H4A9, GH 'GH
        Write_Byte Addr_master, &H4AA, GL 'GL
        Write_Byte Addr_master, &H4AB, BH 'BH
        Write_Byte Addr_master, &H4AC, BL 'BL
        
        
        If MainForm.op_single.Value = False Then ''''''''''Dual TCON
            Write_Byte Add_slave, &H4A1, 2
            Write_Byte Add_slave, &H4A7, RH
            Write_Byte Add_slave, &H4A8, RL
            Write_Byte Add_slave, &H4A9, GH
            Write_Byte Add_slave, &H4AA, GL
            Write_Byte Add_slave, &H4AB, BH
            Write_Byte Add_slave, &H4AC, BL
        End If
    ElseIf MainForm.Com_Tcon_sel.Text = "AUO-12403" Then
        '''''''''AUO-12403  Gamma Test Address FF9[4] Rh4:4A7 Rl8 4A8
        Write_Byte Addr_master, &HFF9, 16 'Gamma_Test ON
        Write_Byte Addr_master, &HFFA, RL 'RH
        Write_Byte Addr_master, &HFFB, GH * 16 + RH
        Write_Byte Addr_master, &HFFC, GL 'GH
        Write_Byte Addr_master, &HFFD, BL 'GL
        Write_Byte Addr_master, &HFFE, BH 'BH
        
        
        
        If MainForm.op_single.Value = False Then ''''''''''Dual TCON
            Write_Byte Add_slave, &HFF9, 16
            Write_Byte Add_slave, &HFFA, RL
            Write_Byte Add_slave, &HFFB, GH * 16 + RH
            Write_Byte Add_slave, &HFFC, GL
            Write_Byte Add_slave, &HFFD, BL
            Write_Byte Add_slave, &HFFE, BH
        End If
    Else
        ' others
        Add_En = Val("&H" & MainForm.txt_en_addr.Text)
        bit_En = 2 ^ Val(MainForm.txt_en_bit.Text)
        Add_lut = Val("&H" & MainForm.txt_LUT_ST.Text)
        
        If MainForm.Com_type.Text = "AUO-12401" Then
            Write_Byte Addr_master, Add_En, bit_En 'Gamma_Test ON
            Write_Byte Addr_master, Add_lut, RH 'RH
            Write_Byte Addr_master, Add_lut + 1, RL 'RL
            Write_Byte Addr_master, Add_lut + 2, GH 'GH
            Write_Byte Addr_master, Add_lut + 3, GL 'GL
            Write_Byte Addr_master, Add_lut + 4, BH 'BH
            Write_Byte Addr_master, Add_lut + 5, BL 'BL
            
            
            If MainForm.op_single.Value = False Then ''''''''''Dual TCON
                Write_Byte Add_slave, Add_En, bit_En
                Write_Byte Add_slave, Add_lut, RH
                Write_Byte Add_slave, Add_lut + 1, RL
                Write_Byte Add_slave, Add_lut + 2, GH
                Write_Byte Add_slave, Add_lut + 3, GL
                Write_Byte Add_slave, Add_lut + 4, BH
                Write_Byte Add_slave, Add_lut + 5, BL
            End If
        Else
            
            '''''''''AUO-12403  Gamma Test Address FF9[4] Rh4:4A7 Rl8 4A8
            Write_Byte Addr_master, Add_En, bit_En 'Gamma_Test ON
            Write_Byte Addr_master, Add_lut, RL 'RH
            Write_Byte Addr_master, Add_lut + 1, GH * 16 + RH
            Write_Byte Addr_master, Add_lut + 2, GL 'GH
            Write_Byte Addr_master, Add_lut + 3, BL 'GL
            Write_Byte Addr_master, Add_lut + 4, BH 'BH
            
            
            
            If MainForm.op_single.Value = False Then ''''''''''Dual TCON
                Write_Byte Add_slave, Add_En, bit_En
                Write_Byte Add_slave, Add_lut, RL
                Write_Byte Add_slave, Add_lut + 1, GH * 16 + RH
                Write_Byte Add_slave, Add_lut + 2, GL
                Write_Byte Add_slave, Add_lut + 3, BL
                Write_Byte Add_slave, Add_lut + 4, BH
            End If
            
        End If
        
        
    End If
End Sub

