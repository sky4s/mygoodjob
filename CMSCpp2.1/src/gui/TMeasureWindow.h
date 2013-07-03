//---------------------------------------------------------------------------

#ifndef TMeasureWindowH
#define TMeasureWindowH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//本項目內頭文件
#include <i2c/tconcontrol.h>
//---------------------------------------------------------------------------
/*
 要不要把TCON Control拉到measure window來?
 1.拉
 這樣TCON開關就要設在measure window
 setRGB的時候就由measure windows根據tcon開關來決定送甚麼rgb
 然後攔截key press的時候也可以決定要把視窗關掉還是gamma test function off掉

 2.不拉
 要有外部元件來決定是要控制measure windows還是直接控制tcon control
 這個外部元件通常就是meter measurement(mm), 如果mm沒有沒有tcon control的需求.
 乾脆就把tcon control交給measure window

 final: 最後決議拉
 */

enum Pattern {
    Normal, HStripe, HStripe2, Indepedent, HSD, FlickrPixel, FlickrSubPixel, Ninth
};
/*
Aging 0 : AG+DG Off
Aging 1 : AG+完整的DG LUT
Aging 2 : AG+單一的RGB塞入DG LUT(譬如0,0,0), 且AG打出(0,0,0)
*/
enum PatternSource {
    PC, DIRECT_GAMMA, DGLUT, AGING
};
class TMeasureWindow:public TForm {
    __published:		// IDE-managed Components
    TButton * Button1;
    TImage *Image1;
    TButton *Button2;
        TButton *Button3;
        TButton *Button4;
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall Button2Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
  private:			// User declarations
     PatternSource source;
    bool lineAdjoin;
     bptr < i2c::TCONControl > tconcontrol;
     std::vector < bptr < gui::event::WindowListener > >listenerVector;
     std::vector < bwptr < gui::event::WindowListener > >listenerVector2;
    Pattern pattern, testPattern;
     bptr < cms::util::DoubleBufferedCanvas > doubleBuffered;
     bptr < cms::util::DoubleBufferedCanvas > getDoubleBufferedCanvas();
     bptr < cms::lcd::BitDepthProcessor > bitDepth;
  public:			// User declarations
     __fastcall TMeasureWindow(TComponent * Owner);
    void setRGB(int r, int g, int b);
    void setRGB(RGB_ptr rgb);
    void setDirectGamma(bptr < i2c::TCONControl > tconcontrl,
			bptr < cms::lcd::BitDepthProcessor > bitDepth);
    void setAgingMode(bptr < i2c::TCONControl > tconcontrol,
		      bptr < cms::lcd::BitDepthProcessor > bitDepth);
    void setDGLUTInput(bptr < i2c::TCONControl > tconcontrl,
		       bptr < cms::lcd::BitDepthProcessor > bitDepth);
    void setTCONControlOff();
    void setVisible(bool visible);
    void addWindowListener(bptr < gui::event::WindowListener > listener);
    void setImageFilename(const std::string & filename);
    void setImageOff();
    void setPattern(Pattern pattern);
    void setTestPattern(Pattern pattern);
    void setLineAdjoin(bool lineAdjoin);
    void setAgingEnable(RGB_vector_ptr rgbMeasureCodeVector);
    bool isAgingSource();
};

//---------------------------------------------------------------------------
extern PACKAGE TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
#endif

