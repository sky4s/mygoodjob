//---------------------------------------------------------------------------
#ifndef USBHIDIOCH
#define USBHIDIOCH
//---------------------------------------------------------------------------

// usbhidiocDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUsbhidiocDlg dialog

class CUsbhidioc		//: public CDialog
{
  public:
    bool ReadReportEx(char *);
    bool WriteReport(char *, unsigned int);
    void CloseReport();
    ~CUsbhidioc(void);



    bool FindTheHID();
  protected:
    void GetDeviceCapabilities();
    void PrepareForOverlappedTransfer();
};

#endif

