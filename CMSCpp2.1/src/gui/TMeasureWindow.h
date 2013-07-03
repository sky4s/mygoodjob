//---------------------------------------------------------------------------

#ifndef TMeasureWindowH
#define TMeasureWindowH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//�����ؤ��Y���
#include <i2c/tconcontrol.h>
//---------------------------------------------------------------------------
/*
 �n���n��TCON Control�Ԩ�measure window��?
 1.��
 �o��TCON�}���N�n�]�bmeasure window
 setRGB���ɭԴN��measure windows�ھ�tcon�}���ӨM�w�e�ƻ�rgb
 �M���d�Ikey press���ɭԤ]�i�H�M�w�n����������٬Ogamma test function off��

 2.����
 �n���~������ӨM�w�O�n����measure windows�٬O��������tcon control
 �o�ӥ~������q�`�N�Ometer measurement(mm), �p�Gmm�S���S��tcon control���ݨD.
 ���ܴN��tcon control�浹measure window

 final: �̫�Mĳ��
 */

enum Pattern {
    Normal, HStripe, HStripe2, Indepedent, HSD, FlickrPixel, FlickrSubPixel, Ninth
};
/*
Aging 0 : AG+DG Off
Aging 1 : AG+���㪺DG LUT
Aging 2 : AG+��@��RGB��JDG LUT(Ĵ�p0,0,0), �BAG���X(0,0,0)
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

