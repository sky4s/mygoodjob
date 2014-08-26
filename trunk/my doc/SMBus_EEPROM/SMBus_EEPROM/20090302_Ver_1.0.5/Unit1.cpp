//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <stdio.h>
#include "WinIo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "WinIo_bc.lib"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    bWinIoInitOK = InitializeWinIo();
    if(!bWinIoInitOK)
    {
        Application->MessageBox("Init WinIO NG","Message",MB_OK|MB_ICONSTOP);
        Application->Terminate();
    }
    InitPortFuncs();
}
//---------------------------------------------------------------------------

int TForm1::I2CReadRegByte(
    unsigned int SMBusBase,
    int I2CDeviceAddress,
    int I2CDeviceReg,
    int *I2CRegValue5)
{
    int rg, count;
    int I2Cstatus;

    count = 0;
    do
    {
        outportb(SMBusBase + 0x03, I2CDeviceReg);
        rg = inportb(SMBusBase + 0x03);
        count++;
    } while((rg != I2CDeviceReg) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x00, 0xff);
        rg = inportb(SMBusBase + 0x00);
        count++;
    } while(((rg & 0x02) != 0x00) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x04, I2CDeviceAddress + 0x1);
        rg = inportb(SMBusBase + 0x04);
        count++;
    } while((rg != I2CDeviceAddress + 0x1) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x00, 0xff);
        rg = inportb(SMBusBase + 0x00);
        count++;
    } while(((rg & 0x02) != 0x00) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x02, 0x48);
        rg = inportb(SMBusBase + 0x02);
        count++;
    } while((rg != 0x08) && (count < 10));

    count = 0;
    I2Cstatus = inportb(SMBusBase + 0x00);
    while(((I2Cstatus & 0x02) != 0x02) && (count <= 32000))
    {
        outportb(SMBusBase + 0x00, I2Cstatus);
        I2Cstatus = inportb(SMBusBase + 0x00);
        count++;
    }

    if(count > 32000)
    {
        printf("SMBus transfer failed!\n");
        rg = inportb(SMBusBase + 0x00);
        return 0;
    }

    *I2CRegValue5 = inportb(SMBusBase + 0x05);

    return 1;
}
//---------------------------------------------------------------------------

int TForm1::I2CWriteRegByte(
    unsigned int SMBusBase,
    int I2CDeviceAddress,
    int I2CDeviceReg,
    int WriteValue
    )
{
    int rg, count;
    int I2Cstatus;

    count = 0;
    do
    {
        outportb(SMBusBase + 0x04, I2CDeviceAddress + 0x0);
        rg = inportb(SMBusBase + 0x04);
        count++;
    } while(((rg !=(I2CDeviceAddress + 0x0)) && (count < 10)));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x03, I2CDeviceReg);
        rg = inportb(SMBusBase + 0x03);
        count++;
    } while((rg != I2CDeviceReg) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x05, WriteValue);
        rg = inportb(SMBusBase + 0x05);
        count++;
    } while((rg != WriteValue) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x06, 0x00);
        rg = inportb(SMBusBase + 0x06);
        count++;
    } while((rg != 0x00) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x00, 0xff);
        rg = inportb(SMBusBase + 0x00);
        count++;
    } while(((rg & 0x02) != 0x00) && (count < 10));

    count = 0;
    do
    {
        outportb(SMBusBase + 0x02, 0x48);
        rg = inportb(SMBusBase + 0x02);
        count++;
    } while((rg != 0x08) && (count < 10));

    count = 0;
    I2Cstatus = inportb(SMBusBase + 0x00);
    while(((I2Cstatus & 0x02) != 0x02) && (count <= 32000))
    {
        I2Cstatus = inportb(SMBusBase + 0x00);
        count++;
    }
    if(count > 32000)
    {
        printf("SMBus transfer failed!\n");
        rg = inportb(SMBusBase + 0x00);
        return 0;
    }

    return 1;
}
//---------------------------------------------------------------------------

int TForm1::IN_Port_Long(
    unsigned long PortBase,
    int PortOffset,
    unsigned long *PortRegValue
    )
{
    *PortRegValue = inportd(PortBase + PortOffset);

    return 1;
}
//---------------------------------------------------------------------------

int TForm1::Out_Port_Long(
    unsigned long PortBase,
    int PortOffset,
    int PortRegValue
    )
{
    int rg, count;

    count = 0;
    do
    {
        outportd(PortBase + PortOffset, PortRegValue);
        rg = inportd(PortBase + PortOffset);
        count++;
    } while((rg != PortRegValue) && (rg != 0xFF) && (count < 10));

    if (count < 10)
        return 1;
    else
        return 0;
}
//---------------------------------------------------------------------------

int TForm1::AtoiHex(char s[])
{
    int i ,ans;

    ans = 0;
    for(i = 0; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F') || (s[i] >= 'a' && s[i] <= 'f'); ++i)
    {
        if (s[i] >= 'A' && s[i] <= 'F')
            ans = 16 * ans + 9 + (s[i] - '@');
        else if (s[i] >= 'a' && s[i] <= 'f')
            ans = 16 * ans + 9 + (s[i] - '`');
        else ans = 16 * ans + (s[i] - '0');
    }
    return ans;
}
//---------------------------------------------------------------------------

unsigned long TForm1::LongAtoiDcb(char s[])
{
    int i;
    long ans;

    ans = 0;
    for(i = 0; (s[i] >= '0' && s[i] <= '9'); ++i)
        ans = 10 * ans + (s[i] - '0');
    return ans;
}
//---------------------------------------------------------------------------

bool TForm1::AtoiIntCHK(char s[])
{
    int i;
    bool CHK;

    CHK = true;
    for(i = 0; i < strlen(s); i++)
    {
        if (s[i] < '0' || s[i] > '9')
            CHK &= false;
    }
    return CHK;
}
//---------------------------------------------------------------------------

void TForm1::ReadSourceFile(void)
{
    BitBtn3->Enabled = false; // Burn In Button
    BitBtn7->Enabled = false; // Compare Button
    BitBtn8->Enabled = false; // W/C Button
    Edit6->Text = "";
    Edit7->Text = "";
    Edit8->Text = "";
    Edit9->Text = "";

    Application->ProcessMessages();
    SouFile_Info->Clear();
    SouFile_Info->Update();

    FILE *in_Sou_File;
    char Sou_File[512];
    int i, File_Len, File_Pos_MSB, File_Pos_LSB;
    AnsiString All_File_String, File_Type;

    Application->ProcessMessages();
    AftBurnin_Info->Lines->Append("The EEPROM been opening from the source file now......");
    AftBurnin_Info->Update();

    File_Type = Edit3->Text.SubString(Edit3->Text.Length() - 3, 4);
    Edit5->Text = "*" + File_Type;

    in_Sou_File = fopen(TestConfigIniFile.Sou_File_Path_Name.c_str(), "rb");
    if (in_Sou_File == NULL)
    {
        fclose(in_Sou_File);
        MessageDlg("Open the source file failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        return; // if error was happened, Prog. EXIT
    }

    // Check The Size of The Source File
    fseek(in_Sou_File, 0, SEEK_END);
    File_Len = ftell(in_Sou_File);
    fseek(in_Sou_File, 0, SEEK_SET);
    if ((File_Len > 256  && File_Type.LowerCase() == ".bin") || (File_Len > 512  && File_Type.LowerCase() == ".dat"))
    {
        fclose(in_Sou_File);
        MessageDlg("The size of the source file failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        return; // if error was happened, Prog. EXIT
    }

    fread(&Sou_File, sizeof(char), File_Len, in_Sou_File);

    fclose(in_Sou_File);

    // Get int Sou_Data form char Sou_File
    if (File_Type.LowerCase() == ".bin")
    {
        for (i = 0; i <= File_Len; i++)
            Sou_Data[i] = int(Sou_File[i]) & 0xff;
    }
    else if (File_Type.LowerCase() == ".dat" || File_Type.LowerCase() == ".txt")
    {
        for (i = 0; i <= File_Len; i++)
            Sou_Data[i] = AtoiHex(AnsiString(Sou_File).SubString(i * 2 + 1, 2).c_str());
    }
    else
    {
        MessageDlg("The type of the source file failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    SouFile_Info->Lines->Append("   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    for (File_Pos_MSB = 0x00; File_Pos_MSB <= 0x0f; File_Pos_MSB++)
    {
        All_File_String = "";

        for (File_Pos_LSB = 0x00; File_Pos_LSB <= 0x0f; File_Pos_LSB++)
            All_File_String = All_File_String + IntToHex(Sou_Data[(File_Pos_MSB << 4) + File_Pos_LSB], 2) + " " ;

        Application->ProcessMessages();
        SouFile_Info->Lines->Append(IntToHex(File_Pos_MSB, 2) + " " + All_File_String);
        SouFile_Info->Update();
    }

    // Setting Edit6-9 Diplay
    Edit6->Text = (Sou_Data[0x0f] << 24) + (Sou_Data[0x0e] << 16) + (Sou_Data[0x0d] << 8) + Sou_Data[0x0c];
    while (Edit6->Text.Length() < 10)
        Edit6->Text = "0" + Edit6->Text;
    Edit7->Text = Sou_Data[0x10];
    Edit8->Text = 1990 + Sou_Data[0x11];
    Edit9->Text = IntToHex(Sou_Data[0x7f], 2);

    // if error wasn't happened, Burn In and Compare Button Enable
    if (TestConfigIniFile.Burn_in_Set_Option == 0 || TestConfigIniFile.Burn_in_Set_Option == 3)
        BitBtn3->Enabled = true; // Burn In Button

    if (TestConfigIniFile.Burn_in_Set_Option == 2 || TestConfigIniFile.Burn_in_Set_Option == 3)
        BitBtn7->Enabled = true; // Compare Button

    if (TestConfigIniFile.Burn_in_Set_Option == 3)
        BitBtn8->Enabled = true; // W/C Button

    Set_Object_Property();
}
//---------------------------------------------------------------------------

void TForm1::Set_Object_Property(void)
{
    Object_Property[0] = BitBtn1->Enabled;
    Object_Property[1] = BitBtn2->Enabled;
    Object_Property[2] = BitBtn3->Enabled;
    Object_Property[3] = BitBtn4->Enabled;
    Object_Property[4] = BitBtn5->Enabled;
    Object_Property[5] = BitBtn6->Enabled;
    Object_Property[6] = BitBtn7->Enabled;
    Object_Property[7] = BitBtn8->Enabled;
    Object_Property[8] = Edit4->Enabled;
    Object_Property[9] = Edit6->Enabled;
    Object_Property[10] = Edit7->Enabled;
    Object_Property[11] = Edit8->Enabled;
}
//---------------------------------------------------------------------------

void TForm1::Object_Property_Recovery(void)
{
    BitBtn1->Enabled = Object_Property[0];
    BitBtn2->Enabled = Object_Property[1];
    BitBtn3->Enabled = Object_Property[2];
    BitBtn4->Enabled = Object_Property[3];
    BitBtn5->Enabled = Object_Property[4];
    BitBtn6->Enabled = Object_Property[5];
    BitBtn7->Enabled = Object_Property[6];
    BitBtn8->Enabled = Object_Property[7];
    Edit4->Enabled = Object_Property[8];
    Edit6->Enabled = Object_Property[9];
    Edit7->Enabled = Object_Property[10];
    Edit8->Enabled = Object_Property[11];
}
//---------------------------------------------------------------------------

void TForm1::Object_Property_Disabled(void)
{
    BitBtn1->Enabled = false;
    BitBtn2->Enabled = false;
    BitBtn3->Enabled = false;
    BitBtn4->Enabled = false;
    BitBtn5->Enabled = false;
    BitBtn6->Enabled = false;
    BitBtn7->Enabled = false;
    BitBtn8->Enabled = false;
    Edit4->Enabled = false;
    Edit6->Enabled = false;
    Edit7->Enabled = false;
    Edit8->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn4Click(TObject *Sender) // Exit Button
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    TIniFile   *SetInfo;
    AnsiString   SetFile;

    SetFile = GetCurrentDir() + "\\TestConfigIni.ini";
    SetInfo = new TIniFile(SetFile);

    // [Burn_in_Option]
    TestConfigIniFile.Sou_File_Name = SetInfo->ReadString("Burn_in_Option", "Sou_File_Name", "XXXXX"); // in TestConfigIni.ini Set for Name Display
    TestConfigIniFile.I2C_Device_Address = SetInfo->ReadString("Burn_in_Option", "I2C_Device_Address", "XX");
    TestConfigIniFile.Burn_in_Set_Option = SetInfo->ReadInteger("Burn_in_Option", "Burn_in_Set_Option", 0);
    TestConfigIniFile.IO_Delay_Time = SetInfo->ReadInteger("Burn_in_Option", "IO_Delay_Time", 1);
    TestConfigIniFile.Save_To_BackUp = SetInfo->ReadInteger("Burn_in_Option", "Save_To_BackUp", 0);

    delete  SetInfo;

    AnsiString Sou_File_Path_Name_Temp;
    int i;
    char SMBusIOBaseBuffer[10];

    Sou_File_Path_Name_Temp = GetCurrentDir() + "\\" + TestConfigIniFile.Sou_File_Name; // for TestConfigIniFile.Sou_File_Path_Name, and TestConfigIniFile.Sou_File_Path_Name for fread
    TestConfigIniFile.Sou_File_Path_Name = "";

    // Change File Path From '\' to '//'
    for (i = 0; i < Sou_File_Path_Name_Temp.Length(); i++)
    {
        Application->ProcessMessages();
        if (int(Sou_File_Path_Name_Temp.c_str()[i]) == 92) // Find '\'
            TestConfigIniFile.Sou_File_Path_Name = TestConfigIniFile.Sou_File_Path_Name + "//";
        else
            TestConfigIniFile.Sou_File_Path_Name = TestConfigIniFile.Sou_File_Path_Name + AnsiString(Sou_File_Path_Name_Temp.c_str()[i]);
    }

    PassFlag = 1;
    SaveFlag = false;

    // Check SMBus OK
    PassFlag &= Out_Port_Long(0xcf8, 0, 0x8000fb20);
    PassFlag &= IN_Port_Long(0xcfc, 0, &SMBusIOBase);
    if (!PassFlag)
    {
        MessageDlg("Access SMBus failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        exit(0); // if error was happened, Prog. EXIT
    }
    SMBusIOBase = SMBusIOBase - 0x01;
    sprintf(SMBusIOBaseBuffer, "%04lx\n", SMBusIOBase);

    TestConfigIniFile.Sou_File_Path = TestConfigIniFile.Sou_File_Path_Name.SubString(0, TestConfigIniFile.Sou_File_Path_Name.Pos(TestConfigIniFile.Sou_File_Name) - 1);// for Path Display

    /* Setting Form Diplay Option */
    // Setting Edit1-4 Diplay
    Edit1->Text = IntToHex(AtoiHex(TestConfigIniFile.I2C_Device_Address.c_str()), 2);
    Edit2->Text = SMBusIOBaseBuffer;
    Edit3->Text = TestConfigIniFile.Sou_File_Name;
    Edit4->Text = TestConfigIniFile.Sou_File_Path;

    // Setting Burn in Set Option Diplay
    if (TestConfigIniFile.Burn_in_Set_Option == 0 ||
        TestConfigIniFile.Burn_in_Set_Option == 2 ||
        TestConfigIniFile.Burn_in_Set_Option == 3) // EEPROM Burn In, Compare and All Button
    {
        BitBtn1->Enabled = true; // Open Button
        if (TestConfigIniFile.Sou_File_Name != "")
            ReadSourceFile();
    }
    if(TestConfigIniFile.Burn_in_Set_Option == 1 || TestConfigIniFile.Burn_in_Set_Option == 3) // EEPROM Modify
    {
        BitBtn5->Enabled = true; // Modify Button
        Edit6->Enabled = true;
        Edit7->Enabled = true;
        Edit8->Enabled = true;
    }
    if(TestConfigIniFile.Burn_in_Set_Option == 3) // EEPROM Save
    {
        BitBtn6->Enabled = true; // Save Button
        Edit4->Enabled = true;
    }

    // Setting Form Caption Diplay
    if (TestConfigIniFile.Burn_in_Set_Option == 0)
        Form1->Caption = Form1->Caption + " -  Burn In";
    else if (TestConfigIniFile.Burn_in_Set_Option == 1)
        Form1->Caption = Form1->Caption + " -  Modify";
    else if (TestConfigIniFile.Burn_in_Set_Option == 2)
        Form1->Caption = Form1->Caption + " -  Compare";
    else if (TestConfigIniFile.Burn_in_Set_Option == 3)
        Form1->Caption = Form1->Caption + " -  All Function";
    else
    {
        MessageDlg("The burn in set option failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        exit(0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender) // Open Button
{
    OpenDialog1->InitialDir = GetCurrentDir();

    AnsiString Sou_File_Path_Name_Temp;
    int i;

    Application->ProcessMessages();
    if (OpenDialog1->Execute())
    {
        Sou_File_Path_Name_Temp = OpenDialog1->FileName; // for TestConfigIniFile.Sou_File_Path_Name, and TestConfigIniFile.Sou_File_Path_Name for fread
        TestConfigIniFile.Sou_File_Path_Name = "";

        // Change File Path From '\' to '//'
        for (i = 0; i < Sou_File_Path_Name_Temp.Length(); i++)
        {
            if (int(Sou_File_Path_Name_Temp.c_str()[i]) == 92) // Find '\'
                TestConfigIniFile.Sou_File_Path_Name = TestConfigIniFile.Sou_File_Path_Name + "//";
            else
                TestConfigIniFile.Sou_File_Path_Name = TestConfigIniFile.Sou_File_Path_Name + AnsiString(Sou_File_Path_Name_Temp.c_str()[i]);
        }

        TestConfigIniFile.Sou_File_Name = ExtractFileName(OpenDialog1->FileName);
        TestConfigIniFile.Sou_File_Path = TestConfigIniFile.Sou_File_Path_Name.SubString(0, TestConfigIniFile.Sou_File_Path_Name.Pos(TestConfigIniFile.Sou_File_Name) - 1);

        // Setting Edit3, 4 Diplay
        Edit3->Text = TestConfigIniFile.Sou_File_Name;
        Edit4->Text = TestConfigIniFile.Sou_File_Path;
    }

    ReadSourceFile();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn2Click(TObject *Sender) // Read Button
{
    PassFlag = 1;
    Object_Property_Disabled();
    Edit6->Text = "";
    Edit7->Text = "";
    Edit8->Text = "";
    Edit9->Text = "";

    Application->ProcessMessages();
    AftBurnin_Info->Lines->Append("The EEPROM been reading now......");
    AftBurnin_Info->Update();
    BefBurnin_Info->Clear();
    BefBurnin_Info->Update();

    int Read_Pos_MSB, Read_Pos_LSB, Read_CheckSum;
    AnsiString All_Read_String;

    Read_CheckSum = 0;

    BefBurnin_Info->Lines->Append("   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    for (Read_Pos_MSB = 0x00; Read_Pos_MSB <= 0x0f; Read_Pos_MSB++)
    {
        All_Read_String = "";

        for (Read_Pos_LSB = 0x00; Read_Pos_LSB <= 0x0f; Read_Pos_LSB++)
        {
            Application->ProcessMessages();
            Sleep(TestConfigIniFile.IO_Delay_Time);
            PassFlag &= I2CReadRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), (Read_Pos_MSB << 4) + Read_Pos_LSB, &Read_String[(Read_Pos_MSB << 4) + Read_Pos_LSB]);
            if (PassFlag)
            {
                // Calculate Check Sum from 0x00 to 0x7e
                if (((Read_Pos_MSB << 4) + Read_Pos_LSB) < 0x7f)
                    Read_CheckSum = Read_CheckSum - Read_String[(Read_Pos_MSB << 4) + Read_Pos_LSB];

                All_Read_String = All_Read_String + IntToHex(Read_String[(Read_Pos_MSB << 4) + Read_Pos_LSB], 2) + " " ;
            }
            else
            {
                MessageDlg("Read the EEPROM failed!\n\nThe failed offset is: 0x" + IntToHex((Read_Pos_MSB << 4) + Read_Pos_LSB, 2), mtError, TMsgDlgButtons() << mbOK, 0);
                Object_Property_Recovery();
                return;
            }
        }
        
        Application->ProcessMessages();
        BefBurnin_Info->Lines->Append(IntToHex(Read_Pos_MSB, 2) + " " + All_Read_String);
        BefBurnin_Info->Update();
    }

    Read_CheckSum &= 0xff;

    // Setting Edit6-9 Diplay
    Edit6->Text = (Read_String[0x0f] << 24) + (Read_String[0x0e] << 16) + (Read_String[0x0d] << 8) + Read_String[0x0c];
    while (Edit6->Text.Length() < 10)
        Edit6->Text = "0" + Edit6->Text;
    Edit7->Text = Read_String[0x10];
    Edit8->Text = 1990 + Read_String[0x11];
    Edit9->Text = IntToHex(Read_CheckSum, 2);

    Application->ProcessMessages();
    Object_Property_Recovery();

    // if error was happened, Burn In, Modify, Compare and Save Button Disable
    if (!PassFlag)
    {
        BitBtn3->Enabled = false;
        BitBtn5->Enabled = false;
        BitBtn6->Enabled = false;
        BitBtn7->Enabled = false;
        BitBtn8->Enabled = false;
    }

    Application->ProcessMessages();
    Set_Object_Property();

    // Whether Read_CheckSum = Read_String[0x7f] or not
    if (Read_CheckSum != Read_String[0x7f])
    {
        MessageDlg("Read the EEPROM check sum failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        PassFlag &= 0; // Check Sum Error

        /* if Check Sum Failed, Compare Disable. */
        CompareFlag = false;
        BitBtn7->Enabled = false;
    }
    else
        CompareFlag = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
    if (AtoiHex(Edit1->Text.c_str()) & 0x01 == 0x01)
        Edit1->Text = IntToHex(AtoiHex(Edit1->Text.c_str())- 0x01, 2);
}
//---------------------------------------------------------------------------
    
void __fastcall TForm1::BitBtn3Click(TObject *Sender) // Burn In Button
{
    PassFlag = 1;
    
    if (TestConfigIniFile.Save_To_BackUp == 1)
    {
        SaveFlag = true;
        Application->ProcessMessages();
        Sleep(TestConfigIniFile.IO_Delay_Time);
        BitBtn6->Click();
    }
    Object_Property_Disabled();
    Application->ProcessMessages();
    Panel1->Color = clBtnFace;       Panel1->Caption = "";
    Panel1->Update();
    Panel2->Color = clBtnFace;       Panel2->Caption = "";
    Panel2->Update();

    Application->ProcessMessages();
    AftBurnin_Info->Lines->Append("The EEPROM been programming now......");
    AftBurnin_Info->Update();

    int Write_String[16], Write_Pos_MSB, Write_Pos_LSB;

    for (Write_Pos_MSB = 0x00; Write_Pos_MSB <= 0x0f; Write_Pos_MSB++)
        for (Write_Pos_LSB = 0x00; Write_Pos_LSB <= 0x0f; Write_Pos_LSB++)
        {
            Application->ProcessMessages();
            Sleep(TestConfigIniFile.IO_Delay_Time);
            PassFlag &= I2CWriteRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), (Write_Pos_MSB << 4) + Write_Pos_LSB, Sou_Data[(Write_Pos_MSB << 4) + Write_Pos_LSB]);
            if (!PassFlag)
            {
                MessageDlg("Write the EEPROM failed!\n\nThe failed offset is: 0x" + IntToHex((Write_Pos_MSB << 4) + Write_Pos_LSB, 2), mtError, TMsgDlgButtons() << mbOK, 0);
                Object_Property_Recovery();
                return; // if error was happened, Prog. EXIT
            }
        }

    // Read EEPROM Data and Check Sum
    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    BitBtn2->Click();

    if (PassFlag)
    {
        Panel1->Color = clGreen;
        Panel1->Caption = "PASS";
    }
    else
    {
        Panel1->Color = clRed;
        Panel1->Caption = "FAIL";
        PassFlag = 1;
    }

    Object_Property_Recovery();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn5Click(TObject *Sender) // Modify Button
{
    PassFlag = 1;
    Object_Property_Disabled();
    if (TestConfigIniFile.Save_To_BackUp == 1)
    {
        SaveFlag = true;
        Application->ProcessMessages();
        Sleep(TestConfigIniFile.IO_Delay_Time);
        BitBtn6->Click();
    }

    Application->ProcessMessages();
    Panel2->Color = clBtnFace;       Panel2->Caption = "";
    Panel2->Update();
    
    Application->ProcessMessages();
    AftBurnin_Info->Lines->Append("The EEPROM been modifing now......");
    AftBurnin_Info->Update();

    unsigned long SN_Data;
    int i, ChkSum_Write_Data, ChkSum_Read_Data, ChkSum_CHK_Data,
        SN_Write_Data[4], SN_Read_Data[4],
        Weak_Write_Data, Year_Write_Data,
        Weak_Read_Data, Year_Read_Data;

    if (Edit6->Text == "") Edit6->Text = "0";
    if (Edit7->Text == "") Edit7->Text = 0;
    if (Edit8->Text == "") Edit8->Text = 1990;

    // Read Initial Data
    for (i = 0; i < 4; i++)
    {
        Application->ProcessMessages();
        Sleep(TestConfigIniFile.IO_Delay_Time);
        PassFlag &= I2CReadRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x0C + i, &SN_Read_Data[i]);
        AftBurnin_Info->Lines->Append("Read serial number offset " + AnsiString(i) + " before modifing: " + IntToHex(SN_Read_Data[i], 2));
    }

    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    PassFlag &= I2CReadRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x10, &Weak_Read_Data);
    AftBurnin_Info->Lines->Append("Read week of manufacture before modifing: " + IntToHex(Weak_Read_Data, 2));

    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    PassFlag &= I2CReadRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x11, &Year_Read_Data);
    AftBurnin_Info->Lines->Append("Read year of manufacture before modifing: " + IntToHex(Year_Read_Data, 2));

    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    PassFlag &= I2CReadRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x7F, &ChkSum_Read_Data);
    AftBurnin_Info->Lines->Append("Read check sum before modifing: " + IntToHex(ChkSum_Read_Data, 2));

    // Check to Read Initial Data
    if (!PassFlag)
    {
        MessageDlg("Read the initial data failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        return; // if error was happened, Prog. EXIT
    }
    
    ChkSum_Write_Data = 0;

    // Wirte Setting Data
    SN_Data = LongAtoiDcb(AnsiString(Edit6->Text).c_str());
    if (!(AtoiIntCHK(Edit6->Text.c_str()) && SN_Data <= 0x7fffffff))
    {
        MessageDlg("The serial number input failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        AftBurnin_Info->Lines->Append("Serial number input failed!");
        PassFlag &= 0;
        return; // if error was happened, Prog. EXIT
    }
    else if (!(AtoiIntCHK(Edit7->Text.c_str()) && Edit7->Text.ToInt() <= 53))
    {
        MessageDlg("The week of manufactur input failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        AftBurnin_Info->Lines->Append("Week of manufactur input failed!");
        PassFlag &= 0;
        return; // if error was happened, Prog. EXIT
    }
    else if (!(AtoiIntCHK(Edit8->Text.c_str()) && Edit8->Text.ToInt() - 1990 <= 0xff && Edit8->Text.ToInt() - 1990 >= 0x00))
    {
        MessageDlg("The year of manufactur input failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        AftBurnin_Info->Lines->Append("Year of manufactur input failed!");
        PassFlag &= 0;
        return; // if error was happened, Prog. EXIT
    }
    else if (PassFlag)
        Object_Property_Recovery();

    for (i = 0; i < 4; i++)
    {
        // Modify Serial Number
        SN_Write_Data[i] = (SN_Data >> (8 * i)) & 0xff;
        AftBurnin_Info->Lines->Append("Writing serial number offset " + AnsiString(i) + ": " + IntToHex(SN_Write_Data[i], 2));
        Application->ProcessMessages();
        Sleep(TestConfigIniFile.IO_Delay_Time);
        PassFlag &= I2CWriteRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x0C + i, SN_Write_Data[i]);
        ChkSum_Write_Data = ChkSum_Write_Data + (SN_Write_Data[i] - SN_Read_Data[i]); // Calculate Check Sum Variation After Modifing Data
    }

    // Modify Week of Manufacture
    Weak_Write_Data = Edit7->Text.ToInt();
    AftBurnin_Info->Lines->Append("Writing weak of manufacture: " + IntToHex(Weak_Write_Data, 2));
    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    PassFlag &= I2CWriteRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x10, Weak_Write_Data);
    ChkSum_Write_Data = ChkSum_Write_Data + (Weak_Write_Data - Weak_Read_Data); // Calculate Check Sum Variation After Modifing Data

    // Modify Year of Manufacture
    Year_Write_Data = Edit8->Text.ToInt() - 1990;
    AftBurnin_Info->Lines->Append("Writing year of manufacture: " + IntToHex(Year_Write_Data, 2));
    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    PassFlag &= I2CWriteRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x11, Year_Write_Data);
    ChkSum_Write_Data = ChkSum_Write_Data + (Year_Write_Data - Year_Read_Data); // Calculate Check Sum Variation After Modifing Data

    // Calculate Check Sum Be Writed After Calculating Check Sum Variation
    ChkSum_Write_Data = ChkSum_Read_Data - ChkSum_Write_Data;
    ChkSum_Write_Data &= 0xff;

    // Modify Check Sum
    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    PassFlag &= I2CWriteRegByte(AtoiHex(Edit2->Text.c_str()), AtoiHex(Edit1->Text.c_str()), 0x7F, ChkSum_Write_Data);
    AftBurnin_Info->Lines->Append("Writing check sum: " + IntToHex(ChkSum_Write_Data, 2));

    if (!PassFlag)
    {
        MessageDlg("Write the data be modified failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        return; // if error was happened, Prog. EXIT
    }

    // Read EEPROM Data and Check Sum
    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    BitBtn2->Click();

    // Whether ChkSum_Write_Data = Read_String[0x7f] or not
    if (ChkSum_Write_Data != Read_String[0x7f])
        PassFlag &= 0;

    if (PassFlag)
    {
        Panel2->Color = clGreen;
        Panel2->Caption = "PASS";
    }
    else
    {
        Panel2->Color = clRed;
        Panel2->Caption = "FAIL";
        PassFlag = 1;
    }

    Object_Property_Recovery();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit6KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_RETURN)
        Edit7->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit7KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_RETURN)
        Edit8->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit8KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_RETURN)
        BitBtn5->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn6Click(TObject *Sender) // Save Button
{
    Object_Property_Disabled();
    SaveDialog1->InitialDir = GetCurrentDir();

    AnsiString Sav_File_Path_Name_Temp;
    int i;
    FILE *out_Sav_File;

    Application->ProcessMessages();
    if (!SaveFlag)
    {
        if (SaveDialog1->Execute())
        {
            Sav_File_Path_Name_Temp = SaveDialog1->FileName;
            TestConfigIniFile.Sav_File_Path_Name = "";

            // Change File Path From '\' to '//'
            for (i = 0; i < Sav_File_Path_Name_Temp.Length(); i++)
            {
                if (int(Sav_File_Path_Name_Temp.c_str()[i]) == 92) // Find '\'
                    TestConfigIniFile.Sav_File_Path_Name = TestConfigIniFile.Sav_File_Path_Name + "//";
                else
                    TestConfigIniFile.Sav_File_Path_Name = TestConfigIniFile.Sav_File_Path_Name + AnsiString(Sav_File_Path_Name_Temp.c_str()[i]);
            }
        }
    }
    else
    {
        TestConfigIniFile.Sav_File_Path_Name = "BackUp.bin";
        SaveFlag = false;
    }

    Application->ProcessMessages();
    AftBurnin_Info->Lines->Append("The EEPROM been saving to the backup file now......");
    AftBurnin_Info->Update();

    out_Sav_File = fopen(TestConfigIniFile.Sav_File_Path_Name.c_str(), "wb");
    if (out_Sav_File == NULL)
    {
        fclose(out_Sav_File);
        MessageDlg("Save the file failed!", mtError, TMsgDlgButtons() << mbOK, 0);
        PassFlag &= 0;
        return; // if error was happened, Prog. EXIT
    }
    
    for (i = 0; i < 256; i++)
        fwrite(&Read_String[i], 1, 1, out_Sav_File);
    
    fclose(out_Sav_File);

    Object_Property_Recovery();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn7Click(TObject *Sender) // Compare Button
{
    if (CompareFlag)
    {
        Object_Property_Disabled();

        Application->ProcessMessages();
        Panel3->Color = clBtnFace;       Panel3->Caption = "";
        Panel3->Update();

        Application->ProcessMessages();
        AftBurnin_Info->Lines->Append("The EEPROM been comparing wtih the file now......");
        AftBurnin_Info->Update();

        Application->ProcessMessages();
        Sleep(TestConfigIniFile.IO_Delay_Time);
        BitBtn2->Click();

        int i;
        AnsiString Temp_Buffer;

        for (i = 0; i <= 0xff; i++)
            if (Sou_Data[i] == Read_String[i])
                CompareFlag &= true;
            else
            {
                CompareFlag &= false;
                MessageDlg("Compare the EEPROM failed!\n\nThe failed offset is: 0x" + IntToHex(i, 2), mtError, TMsgDlgButtons() << mbOK, 0);
                break;
            }
    }

    if (CompareFlag)
    {
        Panel3->Color = clGreen;
        Panel3->Caption = "PASS";
    }
    else
    {
        Panel3->Color = clRed;
        Panel3->Caption = "FAIL";
    }

    Object_Property_Recovery();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
    Set_Object_Property();

    if(TestConfigIniFile.Burn_in_Set_Option == 1 || TestConfigIniFile.Burn_in_Set_Option == 3) // EEPROM Modify
        Edit6->SetFocus();

    // Read EEPROM Data and Check Sum
    Application->ProcessMessages();
    AftBurnin_Info->Clear();
    AftBurnin_Info->Update();
    Application->ProcessMessages();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    BitBtn2->Click();

    // Check The Header of The Data Structure
    if (Read_String[0x00] != 0x00 ||
        Read_String[0x01] != 0xff ||
        Read_String[0x02] != 0xff ||
        Read_String[0x03] != 0xff ||
        Read_String[0x04] != 0xff ||
        Read_String[0x05] != 0xff ||
        Read_String[0x06] != 0xff)
        if (MessageDlg("This one is maybe not a EDID EEPROM!\nThe data of the EEPROM will probably lost!\n\nDo you want to continue?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
            BitBtn4->Click();
        else
            PassFlag = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn8Click(TObject *Sender)
{
    Application->ProcessMessages();
    Panel1->Color = clBtnFace;       Panel1->Caption = "";
    Panel1->Update();
    Panel3->Color = clBtnFace;       Panel3->Caption = "";
    Panel3->Update();
    BitBtn3->Click();
    Sleep(TestConfigIniFile.IO_Delay_Time);
    BitBtn7->Click();
}
//---------------------------------------------------------------------------

