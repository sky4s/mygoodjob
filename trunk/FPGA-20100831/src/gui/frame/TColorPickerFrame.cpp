//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TColorPickerFrame.h"

//C系統文件

//C++系統文件

//vcl庫頭文件
#include <jpeg.hpp>
//其他庫頭文件

//本項目內頭文件
#include <c3d/core.h>

//本項目內gui頭文件

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TColorPickerFrame *ColorPickerFrame;
//---------------------------------------------------------------------------
__fastcall TColorPickerFrame::TColorPickerFrame(TComponent * Owner)
:TFrame(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TColorPickerFrame::Img_3DLUTMouseMove(TObject * Sender,
						      TShiftState Shift, int X, int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    color = Img_3DLUT->Canvas->Pixels[X][Y];
    if (color == -1)
	color = 0;

    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;
    rgb2hsv(r, g, b, &h, &s, &i, &v);

    i = (double (int (i * 10))) /10.0;
    h = (double (int (h * 10))) /10.0;
    s = (double (int (s * 1000))) /1000.0;

    lb_c3d_showX->Caption = "X: " + IntToStr((int) X);
    lb_c3d_showY->Caption = "Y: " + IntToStr((int) Y);
    lb_c3d_showR->Caption = "R: " + IntToStr((int) r);
    lb_c3d_showG->Caption = "G: " + IntToStr((int) g);
    lb_c3d_showB->Caption = "B: " + IntToStr((int) b);
    lb_c3d_showH->Caption = "H: " + IntToStr((int) h);
    lb_c3d_showS->Caption = "S: " + FloatToStr((float) s);
    lb_c3d_showV->Caption = "V: " + IntToStr((int) v);
    using namespace gui::event;
    foreach(bwptr < MouseMotionListener > listener, mouseMotionListenerVector) {
	bptr < MouseMotionListener > l = listener.lock();
	if (null != l) {
	    l->mouseMoved(Sender, Shift, X, Y);
	}
    }
}

//---------------------------------------------------------------------------
void TColorPickerFrame::addMouseMotionListener(bptr < gui::event::MouseMotionListener > listener)
{
    bwptr < gui::event::MouseMotionListener > wptr(listener);
    mouseMotionListenerVector.push_back(wptr);
};
void TColorPickerFrame::addMouseListener(bptr < gui::event::MouseListener > listener)
{
    bwptr < gui::event::MouseListener > wptr(listener);
    mouseListenerVector.push_back(wptr);
};

void __fastcall TColorPickerFrame::Img_3DLUTMouseDown(TObject * Sender,
						      TMouseButton Button, TShiftState Shift, int X,
						      int Y)
{
    using namespace gui::event;
    foreach(bwptr < MouseListener > listener, mouseListenerVector) {
	bptr < MouseListener > l = listener.lock();
	if (null != l) {
	    l->mousePressed(Sender, Button, Shift, X, Y);
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TColorPickerFrame::Img_3DLUTMouseUp(TObject * Sender,
						    TMouseButton Button, TShiftState Shift, int X,
						    int Y)
{
    using namespace gui::event;
    foreach(bwptr < MouseListener > listener, mouseListenerVector) {
	bptr < MouseListener > l = listener.lock();
	if (null != l) {
	    l->mouseReleased(Sender, Button, Shift, X, Y);
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TColorPickerFrame::btn_c3d_load_imgClick(TObject * Sender)
{
    AnsiString S1;
    Graphics::TBitmap * OrgBitmap = new Graphics::TBitmap();

    if (OpenDialog_img->Execute()) {
	S1 = OpenDialog_img->FileName;

	AnsiString curExt = LowerCase(ExtractFileExt(S1));
	TJPEGImage *JPEG = new TJPEGImage;
	Graphics::TBitmap * bitmap = new Graphics::TBitmap();

	if (curExt == ".jpg" || curExt == ".jpeg" || curExt == ".JPG") {
	    JPEG->Performance = jpBestQuality;
	    JPEG->LoadFromFile(S1);
	    JPEG->CompressionQuality = 100;

	    // bitmap->Width = JPEG->Width;     //放到bitmap裡, 自己寫resize
	    // bitmap->Height = JPEG->Height;
	    // bitmap->Assign(JPEG);

	    if (JPEG->Width > Img_3DLUT->Width * 4 + Img_3DLUT->Width * 2) {
		JPEG->Scale = jsEighth;
	    } else if (JPEG->Width > Img_3DLUT->Width * 2 + Img_3DLUT->Width) {
		JPEG->Scale = jsQuarter;
	    } else if (JPEG->Width > Img_3DLUT->Width + Img_3DLUT->Width) {
		JPEG->Scale = jsHalf;
	    } else {
		JPEG->Scale = jsFullSize;
	    }
	    Img_3DLUT->Width = JPEG->Width;
	    Img_3DLUT->Height = JPEG->Height;
	    Img_3DLUT->Picture->Bitmap->Assign(JPEG);

	} else if (curExt == ".bmp" || curExt == ".BMP" || curExt == ".Bitmap") {
	    Img_3DLUT->Picture->LoadFromFile(S1);
	    /* Graphics::TBitmap *pi = new Graphics::TBitmap();
	       try{
	       pi->LoadFromFile(S1);
	       Img_3DLUT->Width = pi->Width;
	       Img_3DLUT->Height = pi->Height;
	       Img_3DLUT->Canvas->Draw(0,0,pi);

	       }
	       __finally{
	       delete pi;
	       } */
	}
	delete bitmap;
	delete JPEG;
	OrgBitmap->Assign(Img_3DLUT->Picture->Bitmap);
	if (pc_img->TabIndex == 0 && null != inTargetForm) {
	    inTargetForm->img_in_target->Picture->Bitmap->Assign(Img_3DLUT->Picture->Bitmap);
	}
    }
    delete OrgBitmap;

    //edt_show_h->Visible = false; //看不到
}

//---------------------------------------------------------------------------
void TColorPickerFrame::setTInTargetForm(TInTargetForm * inTargetForm)
{
    this->inTargetForm = inTargetForm;
    if (null != inTargetForm) {
	cb_show_ref_img->Visible = true;
    }
};

void __fastcall TColorPickerFrame::cb_show_ref_imgClick(TObject * Sender)
{
    if (null != inTargetForm) {
	if (cb_show_ref_img->Checked == true) {
	    inTargetForm->WindowState = wsNormal;
	} else {
	    inTargetForm->WindowState = wsMinimized;
	}
    }
}

//---------------------------------------------------------------------------

