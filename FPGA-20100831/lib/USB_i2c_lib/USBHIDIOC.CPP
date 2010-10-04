//                            Software License Agreement
//
// Copyright (c) 2005-2006, Microchip Technology Inc. All rights reserved.
//
// You may use, copy, modify and distribute the Software for use with Microchip
// products only.  If you distribute the Software or its derivatives, the
// Software must have this entire copyright and disclaimer notice prominently
// posted in a location where end users will see it (e.g., installation program,
// program headers, About Box, etc.).  To the maximum extent permitted by law,
// this Software is distributed “AS IS?and WITHOUT ANY WARRANTY INCLUDING BUT
// NOT LIMITED TO ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR
// PARTICULAR PURPOSE, or NON-INFRINGEMENT. IN NO EVENT WILL MICROCHIP OR ITS
// LICENSORS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
// DAMAGES OF ANY KIND ARISING FROM OR RELATED TO THE USE, MODIFICATION OR
// DISTRIBUTION OF THIS SOFTWARE OR ITS DERIVATIVES.
//
//---------------------------------------------------------------------------
// usbhidioc.cpp : USB HID I/O implementation file
/*
Date: 23 Nov 2004
Dan Butler, Microchip Technology
Version 1.0, Based on Jan Axelson's (jan@lvr.com) USBHIDIOC V2.0
Implements PC to device communication via the HID driver.

Written for Borland C++ Builder V6

Access is through three functions:
   WriteFile
   ReadFile
   CloseFile
Both Read and Write functions check to see if the device is opened on each call.
If not, it goes out and looks for the device and opens the file.  On failure,
the channel is closed so it will attempt to reopen the device on the next call.

bool WriteFile (char *buffer)
Assumes the contents of the buffer is correct and appropriate for the end
device.  It adds on the 0 to the beginning of the buffer and sends it to
the HID driver, which formats it and sends it to the device.

bool ReadFile (char *buffer)
Returns the buffer read from the device.


Project: usbhidioc.cpp
Version: 2.0
Date: 12/20/00
by Jan Axelson (jan@lvr.com)

Purpose: demonstrates USB communications with a HID-class device using overlapped I/O.

Description:
	Finds an attached HID-class device that matches specific vendor & product IDs.
	Retrieves the device's capabilities.

This application was created with Borland's C++ Builder 6's.

About overlapped I/O

Reading HID input reports is done with the API function ReadFile.
Non-overlapped ReadFile is a blocking call. If the device doesn't return the
expected amount of data, the application hangs and will wait forever.

With overlapped I/O, the call to ReadFile returns immediately. The application then calls
WaitForSingleObject, which returns when either the data has arrived or the specified timeout has elapsed.

*/

#include <vcl.h>

#include "USBHIDIOC.h"

#include <wtypes.h>
#include <initguid.h>
#include <process.h>

extern "C" {
#include "hidsdi.h"
#include <setupapi.h>
}

//function prototypes

void __cdecl RcvThreadFunction(HANDLE hidHandle) ;

bool fg_RunThread=false;
bool fg_ThreadRunning=false;
bool fg_NewData=false;
char InBuffer[65];
int InBufferLen;

/////////////////////////////////////////////////////////////////////////////
// CUsbhidioc




//Application global variables
	HIDP_CAPS		Capabilities; //  08Mar2005 - Capabilities call fails on WinXP
	DWORD			cbBytesRead;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
	bool			DeviceDetected = false;
	HANDLE			DeviceHandle;
	DWORD			dwError;
	HANDLE			hEventObject;
	HANDLE			hDevInfo;
	GUID			HidGuid;
	OVERLAPPED		HIDOverlapped;
	char			InputReport[65];
	ULONG			Length;
	DWORD			NumberOfBytesRead;
	HANDLE			ReadHandle;
	ULONG			Required;
	int InBufferValidLen;

CUsbhidioc  USB;
/////////////////////////////////////////////////////////////////////////////
// CUsbhidiocDlg message handlers
	unsigned int VendorID=0x04b4;// = 0x0e8f;    // Uses Microchip's Vendor ID.
	unsigned int ProductID=0xf232;// = 0x0003;   // PICkit 2 Flash Starter Kit
    AnsiString ErrorName;

CUsbhidioc::~CUsbhidioc(void)
{
	if(DeviceDetected)
    {
    	CloseHandle(DeviceHandle);
        // CloseHandle(ReadHandle);
    }
	fg_RunThread = false;
	while (fg_ThreadRunning);
}
bool CUsbhidioc::FindTheHID()
{
	//Use a series of API calls to find a HID with a matching Vendor and Product ID.

	HIDD_ATTRIBUTES			   Attributes;
	SP_DEVICE_INTERFACE_DATA	   devInfoData;
	bool				   LastDevice = FALSE;
	int				   MemberIndex = 0;
	LONG				   Result;

	//These are the vendor and product IDs to look for.

	//const unsigned int VendorID = 0x04b4;    // Uses Microchip's Vendor ID.
	//const unsigned int ProductID = 0xf232;   // PICkit 2 Flash Starter Kit

	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;

	/*
	API function: HidD_GetHidGuid
	Get the GUID for all system HIDs.
	Returns: the GUID in HidGuid.
	*/

	HidD_GetHidGuid(&HidGuid);
	
	/*
	API function: SetupDiGetClassDevs
	Returns: a handle to a device information set for all installed devices.
	Requires: the GUID returned by GetHidGuid.
	*/
	
	hDevInfo=SetupDiGetClassDevs
		(&HidGuid,
		NULL, 
		NULL,
		//DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		DIGCF_PRESENT|DIGCF_DEVICEINTERFACE);

	devInfoData.cbSize = sizeof(devInfoData);

	//Step through the available devices looking for the one we want. 
	//Quit on detecting the desired device or checking all available devices without success.
	MemberIndex = 0;
	LastDevice = FALSE;

	do
	{
		DeviceDetected=false;

		/*
		API function: SetupDiEnumDeviceInterfaces
		On return, MyDeviceInterfaceData contains the handle to a
		SP_DEVICE_INTERFACE_DATA structure for a detected device.
		Requires:
		The DeviceInfoSet returned in SetupDiGetClassDevs.
		The HidGuid returned in GetHidGuid.
		An index to specify a device.
		*/

		Result=SetupDiEnumDeviceInterfaces
			(hDevInfo,
			0,
			&HidGuid,
			MemberIndex,
			&devInfoData);

		if (Result != 0)
		{
			//A device has been detected, so get more information about it.

			/*
			API function: SetupDiGetDeviceInterfaceDetail
			Returns: an SP_DEVICE_INTERFACE_DETAIL_DATA structure
			containing information about a device.
			To retrieve the information, call this function twice.
			The first time returns the size of the structure in Length.
			The second time returns a pointer to the data in DeviceInfoSet.
			Requires:
			A DeviceInfoSet returned by SetupDiGetClassDevs
			The SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces.

			The final parameter is an optional pointer to an SP_DEV_INFO_DATA structure.
			This application doesn't retrieve or use the structure.
			If retrieving the structure, set
			MyDeviceInfoData.cbSize = length of MyDeviceInfoData.
			and pass the structure's address.
			*/

			//Get the Length value.
			//The call will return with a "buffer too small" error which can be ignored.
			Result = SetupDiGetDeviceInterfaceDetail
				(hDevInfo,
				&devInfoData,
				NULL,
				0,
				&Length,
				NULL);

			//Allocate memory for the hDevInfo structure, using the returned Length.
			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);

			//Set cbSize in the detailData structure.
			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        // **** IMPORTANT ****
        // sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) should equal 5.
        // In C++ Builder, go to Project/Options/Advanced Compiler/Data Alignment
        // and select "byte" align.

			//Call the function again, this time passing it the returned buffer size.
			Result = SetupDiGetDeviceInterfaceDetail
				(hDevInfo,
				&devInfoData,
				detailData,
				Length,
				&Required,
				NULL);

            Result = GetLastError ();
			//Open a handle to the device.

			/*
			API function: CreateFile
			Returns: a handle that enables reading and writing to the device.
			Requires:
			The DevicePath in the detailData structure
			returned by SetupDiGetDeviceInterfaceDetail.
			*/

			DeviceHandle=CreateFile
				(detailData->DevicePath,
				GENERIC_READ|GENERIC_WRITE,
				FILE_SHARE_READ|FILE_SHARE_WRITE,
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING,
                0,
				//FILE_FLAG_OVERLAPPED,
				NULL);


			/*
			API function: HidD_GetAttributes
			Requests information from the device.
			Requires: the handle returned by CreateFile.
			Returns: a HIDD_ATTRIBUTES structure containing
			the Vendor ID, Product ID, and Product Version Number.
			Use this information to decide if the detected device is
			the one we're looking for.
			*/

			//Set the Size to the number of bytes in the structure.
			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes
				(DeviceHandle,
				&Attributes);

			//Is it the desired device?
			DeviceDetected = false;

			if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{
					//Both the Product and Vendor IDs match.
					DeviceDetected = true;
					GetDeviceCapabilities();//  08Mar2005 - Capabilities call fails on WinXP
                    // fg_RunThread = true;
                    //_beginthread(RcvThreadFunction, 0, DeviceHandle);
					PrepareForOverlappedTransfer();
				} //if (Attributes.ProductID == ProductID)

				else
					//The Product ID doesn't match.
					CloseHandle(DeviceHandle);
			} //if (Attributes.VendorID == VendorID)

			else
				//The Vendor ID doesn't match.
				CloseHandle(DeviceHandle);

		//Free the memory used by the detailData structure (no longer needed).
		free(detailData);
		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.
			LastDevice=TRUE;

		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.
		MemberIndex = MemberIndex + 1;

	} //do
	while ((LastDevice == FALSE) && (DeviceDetected == false));

	//Free the memory reserved for hDevInfo by SetupDiClassDevs.
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return DeviceDetected;
}



void CUsbhidioc::PrepareForOverlappedTransfer()
{
	//Get another handle to the device for the overlapped ReadFiles.
	ReadHandle=CreateFile
		(detailData->DevicePath,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL);

	//Get an event object for the overlapped structure.

	/*API function: CreateEvent
	Requires:
	  Security attributes or Null
	  Manual reset (true). Use ResetEvent to set the event object's state to non-signaled.
	  Initial state (true = signaled)
	  Event object name (optional)
	Returns: a handle to the event object
	*/

	if (hEventObject == 0)
	{
            hEventObject = CreateEvent
                    (NULL,
                    TRUE,
                    //TRUE,   // Andy 0531 mask
                    false,	  // Andy 0531 add
                    "");

            //Set the members of the overlapped structure.
            HIDOverlapped.hEvent = hEventObject;
            HIDOverlapped.Offset = 0;
            HIDOverlapped.OffsetHigh = 0;
	}
}

bool CUsbhidioc::ReadReportEx(char InBuffer[])
{
	DWORD	Result;
    unsigned int i;

    ErrorName="NONE";
    if (DeviceDetected == false)
    {
    	FindTheHID ();
    }
    if (DeviceDetected)
    {
        InBufferValidLen=0;
        Result = ReadFile
            (ReadHandle,
            InputReport,
            Capabilities.InputReportByteLength,
            &NumberOfBytesRead,
            (LPOVERLAPPED) &HIDOverlapped);
        if(Result)
        {
        	//SetEvent(hEventObject);
            ErrorName="IMM_RETURN";
            InBufferValidLen = NumberOfBytesRead;
            for (i=0; i < NumberOfBytesRead; ++i)
                InBuffer[i] = InputReport [i+1];
        }
        else
        {
        	// Andy 0531 add Below lines
            Result = GetLastError();
            if(Result==ERROR_IO_PENDING)
            {
            // Andy 0531 add above lines
                Result = WaitForSingleObject(hEventObject,1000);
                if(Result== WAIT_OBJECT_0)
                {
                    Result=GetOverlappedResult(ReadHandle,
                        &HIDOverlapped,
                        &NumberOfBytesRead,
                        FALSE);
                    if(Result)
                    {
                        ErrorName="OBJECT_0_GOT";
                        InBufferValidLen = NumberOfBytesRead;
                        for (i=0; i < NumberOfBytesRead; ++i)
                            InBuffer[i] = InputReport [i+1];
                    }
                    else
                    {
                    	ErrorName="UNKNOWN 1";
                    }
                }
                else
                {
                    Result = CancelIo(ReadHandle);

                    //A timeout may mean that the device has been removed.
                    //Close the device handles and set DeviceDetected = False
                    //so the next access attempt will search for the device.
                    CloseHandle(ReadHandle);
                    CloseHandle(DeviceHandle);
                    DeviceDetected = FALSE;
                    Result = false;
                    ErrorName = "TIME_OUT";
                }
            }
            else
            {
                ErrorName = "ERROR NOT PENDING";
            }
        }
    }
    return Result;
}

int wid=0;
bool CUsbhidioc::WriteReport(char OutputBuffer[], unsigned int nBytes)
{
    DWORD   BytesWritten = 0;
    ULONG   Result;
    char    OutputReport [65];
    unsigned int     i;

	//The first byte is the report number.
    OutputReport[0]=0;
    for (i=0; i < nBytes; i++)
        OutputReport [i+1] = OutputBuffer[i];
    for (i = nBytes+1; i < 65; ++i)
        OutputReport [i] = 'Z';  // Pad buffer with Null Commands

/*
	API Function: WriteFile
	Sends a report to the device.
	Returns: success or failure.
	Requires:
	The device handle returned by CreateFile.
	The Output Report length returned by HidP_GetCaps,
	A report to send.
	*/

    if (DeviceDetected == false)
        FindTheHID ();

    if (DeviceDetected)
    {
        Result = WriteFile
		(DeviceHandle,
		OutputReport,
		//65, //
		Capabilities.OutputReportByteLength,//  08Mar2005 - Capabilities call fails on WinXP
		&BytesWritten,
		NULL);

        if (Result == 0)
        {
            Result = GetLastError ();
		//The WriteFile failed, so close the handle, display a message,
		//and set DeviceDetected to FALSE so the next attempt will look for the device.
		CloseHandle(DeviceHandle);
		CloseHandle(ReadHandle);
		DeviceDetected = false;
        }
    }
    else
        Result = false;
    return Result;
}


// Close the channel
void CUsbhidioc::CloseReport ()
{
    if (DeviceDetected == true)
    {
        CancelIo(ReadHandle);

    //A timeout may mean that the device has been removed.
    //Close the device handles and set DeviceDetected = False
    //so the next access attempt will search for the device.
        CloseHandle(ReadHandle);
        CloseHandle(DeviceHandle);
        DeviceDetected = false;
    }
}

//08Mar2005 - Capabilities call fails on WinXP
void CUsbhidioc::GetDeviceCapabilities()
{
    ULONG  Result;
	//Get the Capabilities structure for the device.
	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	API function: HidD_GetPreparsedData
	Returns: a pointer to a buffer containing the information about the device's capabilities.
	Requires: A handle returned by CreateFile.
	There's no need to access the buffer directly,
	but HidP_GetCaps and other API functions require a pointer to the buffer.
	*/

	Result = HidD_GetPreparsedData
		(DeviceHandle,
		&PreparsedData);

	/*
	API function: HidP_GetCaps
	Learn the device's capabilities.
	For standard devices such as joysticks, you can find out the specific
	capabilities of the device.
	For a custom device, the software will probably know what the device is capable of,
	and the call only verifies the information.
	Requires: the pointer to the buffer returned by HidD_GetPreparsedData.
	Returns: a Capabilities structure containing the information.
	*/

	Result = HidP_GetCaps
		(PreparsedData,
		&Capabilities);

	//No need for PreparsedData any more, so free the memory it's using.
	HidD_FreePreparsedData(PreparsedData);
}

void __cdecl RcvThreadFunction(HANDLE hidHandle)
{
    char rcvDataBuf[65];
    //CString msg;

    // create Overlapped read structure and event
    HANDLE hIOWaiter = CreateEvent(NULL, TRUE, FALSE, NULL);

    if(hIOWaiter == NULL)
        goto exit2;

    OVERLAPPED ol;
    ol.Offset = 0;
    ol.OffsetHigh = 0;
    ol.hEvent = hIOWaiter;

    fg_ThreadRunning=true;
    // loop waiting for events, till fg_RunThread goes false
    for(;;)
    {
        // initiate overlapped read
        DWORD rcvdBytes;
        ResetEvent(hIOWaiter);
        if(!ReadFile(hidHandle, rcvDataBuf, 65, &rcvdBytes, &ol))
        {
            // Check for read errors
            DWORD err = GetLastError();
            if(err != ERROR_IO_PENDING && err != ERROR_DEVICE_NOT_CONNECTED && fg_RunThread)
            {
                //msg.Format("Read error: %d", err);
                //AfxMessageBox(msg);
                goto exit1;
            }


            // wait for read to complete (check for fg_RunThread going false every 100ms)
            while(WaitForSingleObject(hIOWaiter, 100) == WAIT_TIMEOUT)
            {
                if(!fg_RunThread)
                {
                    if(hidHandle != INVALID_HANDLE_VALUE) // if handle hasn't already been closed
                    {
                        // cancel the pending read
                        CancelIo(hidHandle);
                    }
                    goto exit1;
                }
            }

            // get read result, i.e. bytes transferred
            if(!GetOverlappedResult(hidHandle, &ol, &rcvdBytes, false))
            {
                err = GetLastError();
                if(err != ERROR_DEVICE_NOT_CONNECTED && fg_RunThread)
                {
                    //msg.Format("GetOverlappedResult error: %d", err);
                    //AfxMessageBox(msg);
                }

                continue;
            }
        }

        // make sure there's something there
        if(rcvdBytes < 65)
        {
            if(fg_RunThread)
            {
                //msg.Format("Only read %d bytes", rcvdBytes);
                //AfxMessageBox(msg);
            }

            continue;      // Loop while not finish receiving all bytes.
        }
        else
        {
        	//InBufferLen = rcvdBytes;
        	//memcpy(InBuffer,rcvDataBuf,rcvdBytes);
        	fg_NewData=true;

        }

        // notify app of new data
        // (note rcvDataBuf[0] just contains the report ID)
        //AfxGetMainWnd()->SendMessage(IDM_RCV_DATA, 0, (LPARAM)(rcvDataBuf + 1));
    }

exit1:
    CloseHandle(hIOWaiter);

exit2:
    fg_ThreadRunning=false;
    _endthread();

}


