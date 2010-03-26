class _CHKB
{
        public:
                __fastcall ~_CHKB();
                TCheckBox* Chkb;
                TBit Addr;
};
__fastcall _CHKB::~_CHKB()
{
        delete [] Chkb;
}

class _CBOB
{
        public:
                __fastcall ~_CBOB();
                TComboBox* Cbob;
                TLabel* CbobL;
                TBit Addr;
};
__fastcall _CBOB::~_CBOB()
{
        delete [] Cbob;
        delete [] CbobL;
}

class _CBOB2     //Address 為 2Byte
{
        public:
                __fastcall ~_CBOB2();
                TComboBox* Cbob;
                TLabel* CbobL;
                TBit2 Addr;
};
__fastcall _CBOB2::~_CBOB2()
{
        delete [] Cbob;
        delete [] CbobL;
        //delete Addr.choice;
}


class _LBLE3     //Address 為 3Byte
{
        public:
                __fastcall ~_LBLE3();
                TLabeledEdit* Lble;
                TBit3 Addr;
};
__fastcall _LBLE3::~_LBLE3()
{
        delete [] Lble;
        //delete Addr.choice;
}

class _LBLE2     //Address 為 2Byte
{
        public:
                __fastcall ~_LBLE2();
                TLabeledEdit* Lble;
                TBit2 Addr;
};
__fastcall _LBLE2::~_LBLE2()
{
        delete [] Lble;
        //delete Addr.choice;
}

class _LBLE     //Address 為 1 byte
{
        public:
                __fastcall ~_LBLE();
                TLabeledEdit* Lble;
                TBit Addr;
};
__fastcall _LBLE::~_LBLE()
{
        delete [] Lble;
        //delete Addr.choice;
}

class _ScrollBar2     //Address 為 2Byte
{
        public:
                __fastcall ~_ScrollBar2();
                TLabel* Lbl;
                TScrollBar* ScrlB;
                TStaticText* StTxt;
                TBit2 Addr;
};
__fastcall _ScrollBar2::~_ScrollBar2()
{
        delete [] Lbl;
        delete [] StTxt;
        delete [] ScrlB;
        //delete Addr.choice;
}

class _ScrollBar     //Address 為 1 byte
{
        public:
                __fastcall ~_ScrollBar();
                TLabel* Lbl;
                TScrollBar* ScrlB;
                TStaticText* StTxt;
                TBit Addr;
};
__fastcall _ScrollBar::~_ScrollBar()
{
        delete [] Lbl;
        delete [] StTxt;
        delete [] ScrlB;
        //delete Addr.choice;
}
class _StaticText     //Address 為 1 byte    //no more use
{
        public:
                __fastcall ~_StaticText();
                TStaticText* StTxt;
                TBit Addr;
};
__fastcall _StaticText::~_StaticText()
{
        delete [] StTxt;
        //delete Addr.choice;
}
