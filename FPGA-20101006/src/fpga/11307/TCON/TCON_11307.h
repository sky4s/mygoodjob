//---------------------------------------------------------------------------
//    20100623 version
//---------------------------------------------------------------------------
#include "TCON1.h"
#ifndef TCON_11307H
#define TCON_11307H
//---------------------------------------------------------------------------


class TCON_11307:public AbstTCON {
  public:
    //device
    virtual TBit * SetDevChkBx();
    virtual TBit *SetDevCboBx();
    virtual TBit2 *SetDevLblE2();

    //status
    virtual TBit *SetStaCboBx();
    virtual TBit2 *SetStaLblE2();

    //input/output
    virtual TBit *SetIOChkBx();
    virtual TBit *SetIOCboBx();
    //driving
    virtual TBit *SetDrvChkBx();
    virtual TBit *SetDrvCboBx();
    virtual TBit2 *SetDrvLblE();
    virtual TBit3 *SetDrvLblE3();	//Add by Michelle 20100625
    //Timing
    virtual TBit2 *SetTimLblE2();
    virtual TBit3 *SetTimLblE3();

     TCON_11307();
};

//--------------------------------------------------------------------------
bool GetAddr(TBit * Addr, String name)	//Get TBit type Address
{
    if (name == "_NULL")
	return 0;

    char *buffer = Load_File("auo_11307_address.txt");
    char tmp[40];		//string of error message
    char *pch, *tok, *ptr1;
    int idx;
    char slash = '/';
    char str1[50] = "";
    bool name_ok;
    char *str = name.c_str();

    pch = strtok(buffer, "\n\0");	//讀入一行文字
    if (pch == NULL) {		//沒有資料  return
	StrCopy(tmp, "Can't find String ");
	StrCat(tmp, name.c_str());
	MessageBox(NULL, tmp, "Error", MB_OK);
	return 0;
    }
    do {
	ptr1 = strchr(pch, slash);	//註解前的字串複製到ptr1
	if (ptr1 == NULL)
	    strcpy(str1, pch);	//註解不存在, 保留完整字串在str1
	else {
	    strncpy(str1, pch, ptr1 - pch);	//註解存在, 保留註解前字串在str1
	    str1[ptr1 - pch + 1] = ' ';
	}

	name_ok = 1;
	for (int i = 0; i < name.Length(); i++)	//逐一比較name與str1的字元
	    if (str[i] != str1[i])
		name_ok = 0;
	if (name_ok == 1) {
	    if (str1[name.Length()] != ' ' && str1[name.Length()] != ',')
		name_ok = 0;
	}
	pch = strtok(NULL, "\n");	//讀入下一行文字
    } while (name_ok == 0);

    int val[3];
    char *t[3];
    pch = strtok(str1, " ,\t");
    for (int i = 0; i < 3; i++) {
	t[i] = strtok(NULL, " ,\t");
	if (t[i] == NULL) {
	    MessageBox(NULL, str1, "Error numbers of parameter.", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], name);
    delete[]buffer;
    return 1;
}

//----------------------------------------------------------------------------

bool SetAddr(TBit * Addr, String str)	//Get TBit type Address
{
    if (str == "_NULL")
	return 0;
    int val[3];
    char *t[3];
    char *string = str.c_str();
    char *name = strtok(string, " ,\t");
    for (int i = 0; i < 3; i++) {
	t[i] = strtok(NULL, " ,\t");
	if (t[i] == NULL) {
	    MessageBox(NULL, str.c_str(), "Error numbers of parameter.", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], (String) name);
    return 1;
}

//--------------------------------------------------------------------------
bool GetAddr(TBit2 * Addr, String name)
{
    if (name == "_NULL")
	return 0;

    char *buffer = Load_File("auo_11307_address.txt");

    char tmp[40];		//string of error message
    char *pch, *tok, *ptr1;
    int idx;
    char slash = '/';
    char str1[50] = "";
    bool name_ok = 0;
    char *str = name.c_str();

    pch = strtok(buffer, "\n\0");	//讀入一行文字
    if (pch == NULL) {		//沒有資料  return
	StrCopy(tmp, "Can't find String ");
	StrCat(tmp, name.c_str());
	MessageBox(NULL, tmp, "Error", MB_OK);
	return 0;
    }

    do {
	ptr1 = strchr(pch, slash);	//註解前的字串複製到ptr1
	if (ptr1 == NULL)
	    strcpy(str1, pch);	//註解不存在, 保留完整字串在str1
	else
	    strncpy(str1, pch, ptr1 - pch + 1);	//註解存在, 保留註解前字串在str1
	name_ok = 1;
	for (int i = 0; i < name.Length(); i++)	//逐一比較name與str1的字元
	    if (str[i] != str1[i])
		name_ok = 0;
	if (name_ok == 1) {
	    if (str1[name.Length()] != ' ' && str1[name.Length()] != ',')
		name_ok = 0;
	}
	pch = strtok(NULL, "\n");	//讀入下一行文字
    } while (name_ok == 0);

    pch = strtok(str1, "\t ,");
    int val[6];
    char *t[6];
    for (int i = 0; i < 6; i++) {
	t[i] = strtok(NULL, "\t ,");
	if (t[i] == NULL && i >= 3)
	    val[i] = 0;
	else if (t[i] == NULL && i < 3) {
	    StrCopy(tmp, "Incorrect address format for ");
	    StrCat(tmp, name.c_str());
	    MessageBox(NULL, tmp, "Error", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], val[3], val[4], val[5], (String) name);
    delete[]buffer;
    return 1;
}

//---------------------------------------------------------------------------
bool SetAddr(TBit2 * Addr, String str)	//Get TBit type Address
{
    if (str == "_NULL")
	return 0;

    char tmp[40];		//string of error message
    int val[6];
    char *t[6];
    char *string = str.c_str();
    char *name = strtok(string, " ,\t");
    for (int i = 0; i < 6; i++) {
	t[i] = strtok(NULL, " ,\t");
	if (t[i] == NULL && i >= 3)
	    val[i] = 0;
	else if (t[i] == NULL && i < 3) {	//缺少data
	    StrCopy(tmp, "Incorrect address format for ");
	    StrCat(tmp, name);
	    MessageBox(NULL, tmp, "Error", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], val[3], val[4], val[5], name);
    return 1;
}

//---------------------------------------------------------------------------
bool GetAddr(TLUT * Addr, String name)
{
    if (name == "_NULL")
	return 0;

    char *buffer = Load_File("auo_11307_address.txt");

    char tmp[40];		//string of error message
    char *pch, *tok, *ptr1;
    int idx;
    char slash = '/';
    char str1[50] = "";
    bool name_ok;
    char *str = name.c_str();

    pch = strtok(buffer, "\n\0");	//讀入一行文字
    if (pch == NULL) {		//沒有資料  return
	StrCopy(tmp, "Can't find String ");
	StrCat(tmp, name.c_str());
	MessageBox(NULL, tmp, "Error", MB_OK);
	return 0;
    }

    do {
	ptr1 = strchr(pch, slash);	//註解前的字串複製到ptr1
	if (ptr1 == NULL)
	    strcpy(str1, pch);	//註解不存在, 保留完整字串在str1
	else
	    strncpy(str1, pch, ptr1 - pch + 1);	//註解存在, 保留註解前字串在str1
	name_ok = 1;
	for (int i = 0; i < name.Length(); i++)	//逐一比較name與str1的字元
	    if (str[i] != str1[i])
		name_ok = 0;
	if (name_ok == 1) {
	    if (str1[name.Length()] != ' ' && str1[name.Length()] != ',')
		name_ok = 0;
	}
	pch = strtok(NULL, "\n");	//讀入下一行文字
    } while (name_ok == 0);

    pch = strtok(str1, "\t ,");
    int val[4];
    char *t[4];
    for (int i = 0; i < 4; i++) {
	t[i] = strtok(NULL, "\t ,");
	if (t[i] == NULL && i >= 3)	//Type設定為NULL, 設為Type 1
	    val[i] = 1;
	else if (t[i] == NULL && i < 3) {	//缺少data
	    StrCopy(tmp, "Incorrect address format for ");
	    StrCat(tmp, name.c_str());
	    MessageBox(NULL, tmp, "Error", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], val[3], name);
    delete[]buffer;
    return 1;
}

//---------------------------------------------------------------------------
bool SetAddr(TLUT * Addr, String str)	//Get TBit type Address
{
    if (str == "_NULL")
	return 0;
    char tmp[40];		//string of error message
    int val[4];
    char *t[4];
    char *string = str.c_str();
    char *name = strtok(string, " ,\t");
    for (int i = 0; i < 4; i++) {
	t[i] = strtok(NULL, "\t ,");
	if (t[i] == NULL && i >= 3)	//Type設定為NULL, 設為Type 1
	    val[i] = 1;
	else if (t[i] == NULL && i < 3) {	//缺少data
	    StrCopy(tmp, "Incorrect address format for ");
	    StrCat(tmp, name);
	    MessageBox(NULL, tmp, "Error", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], val[3], name);
    return 1;
}

bool SetAddr(TBit3 * Addr, String str)	//Get TBit type Address
{
    if (str == "_NULL")
	return 0;
    char tmp[40];		//string of error message
    int val[9];
    char *t[9];
    char *string = str.c_str();
    char *name = strtok(string, " ,\t");
    for (int i = 0; i < 9; i++) {
	t[i] = strtok(NULL, " ,\t");
	if (t[i] == NULL && i >= 3)
	    val[i] = 0;
	else if (t[i] == NULL && i < 3) {	//缺少data
	    StrCopy(tmp, "Incorrect address format for ");
	    StrCat(tmp, name);
	    MessageBox(NULL, tmp, "Error", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8], name);
    return 1;
}

bool SetAddr(TBit4 * Addr, String str)	//Get TBit type Address
{
    if (str == "_NULL")
	return 0;
    char tmp[40];		//string of error message
    int val[12];
    char *t[12];
    char *string = str.c_str();
    char *name = strtok(string, " ,\t");
    for (int i = 0; i < 12; i++) {
	t[i] = strtok(NULL, " ,\t");
	if (t[i] == NULL && i >= 3)
	    val[i] = 0;
	else if (t[i] == NULL && i < 3) {	//缺少data
	    StrCopy(tmp, "Incorrect address format for ");
	    StrCat(tmp, name);
	    MessageBox(NULL, tmp, "Error", MB_OK);
	    return 0;
	} else if (isdigit(t[i][0]))
	    val[i] = StrToInt(t[i]);
    }
    Addr->set(val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7],
	      val[8], val[9], val[10], val[11], name);
    return 1;
}

//--------------------------------------------------------------------------
#endif

