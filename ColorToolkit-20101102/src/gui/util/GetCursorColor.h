//---------------------------------------------------------------------------

#ifndef GetCursorColorH
#define GetCursorColorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <java/lang.h>
//---------------------------------------------------------------------------

class RGBInfoCallbackIF
{
public:
  virtual void callback(int_array rgbValues) = 0;
};
class TPColorThread1:public TThread
{
  typedef struct tagTHREADNAME_INFO
  {
    DWORD dwType;               // must be 0x1000
    LPCSTR szName;              // pointer to name (in user addr space)
    DWORD dwThreadID;           // thread ID (-1=caller thread)
    DWORD dwFlags;              // reserved for future use, must be zero
  }
  THREADNAME_INFO;
private:
  void SetName();
  RGBInfoCallbackIF *callback;
protected:
  void __fastcall Execute();
public:
   __fastcall TPColorThread1(bool CreateSuspended,
                             RGBInfoCallbackIF * callback);
};

//---------------------------------------------------------------------------
#endif

