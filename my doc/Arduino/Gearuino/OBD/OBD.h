/*************************************************************************
* Arduino Library for OBD-II UART Adapter
* Distributed under GPL v2.0
* Copyright (c) 2012~2013 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
*************************************************************************/

#define OBD_TIMEOUT_SHORT 2000 /* ms */
#define OBD_TIMEOUT_LONG 7000 /* ms */
#define OBD_SERIAL_BAUDRATE 38400
#define OBD_RECV_BUF_SIZE 128

#ifndef OBDUART
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega644P__)
#define OBDUART Serial1
#else
#define OBDUART Serial
#endif
#endif

// mode 0 pids
#define PID_RPM 0x0C
#define PID_SPEED 0x0D
#define PID_THROTTLE 0x11
#define PID_ENGINE_LOAD 0x04
#define PID_COOLANT_TEMP 0x05
#define PID_INTAKE_TEMP 0x0F
#define PID_MAF_FLOW 0x10
#define PID_ABS_ENGINE_LOAD 0x43
#define PID_AMBIENT_TEMP 0x46
#define PID_FUEL_PRESSURE 0x0A
#define PID_INTAKE_MAP 0x0B
#define PID_BAROMETRIC 0x33
#define PID_TIMING_ADVANCE 0x0E
#define PID_FUEL_LEVEL 0x2F
#define PID_RUNTIME 0x1F
#define PID_DISTANCE 0x31

// states
#define OBD_DISCONNECTED 0
#define OBD_CONNECTING 1
#define OBD_CONNECTED 2

unsigned int hex2uint16(const char *p);
unsigned char hex2uint8(const char *p);

class COBD
{
public:
	COBD():dataMode(1),errors(0),m_state(OBD_DISCONNECTED) {}
	void begin();
	bool init(bool passive = false);
	bool readSensor(byte pid, int& result, bool passive = false);
	bool isValidPID(byte pid);
	void sleep(int seconds);
	// Query and GetResponse for advanced usage only
	void sendQuery(byte pid);
	char* getResponse(byte& pid, char* buffer);
	bool getResponseParsed(byte& pid, int& result);
	byte getState() { return m_state; }
	byte dataMode;
	byte errors;
	byte pidmap[4 * 4];
	byte vin[17];
	//char recvBuf[OBD_RECV_BUF_SIZE];
protected:
	byte receive(char* buffer);
	void debugOutput(const char* s);
	static int normalizeData(byte pid, char* data);
	static int getPercentageValue(char* data)
	{
		return (int)hex2uint8(data) * 100 / 255;
	}
	static unsigned int getLargeValue(char* data)
	{
		return hex2uint16(data);
	}
	static int getSmallValue(char* data)
	{
		return hex2uint8(data);
	}
	static int getTemperatureValue(char* data)
	{
		return (int)hex2uint8(data) - 40;
	}
	virtual bool available();
	virtual char read();
	virtual void write(const char* s);
	virtual void write(const char c);
	virtual void dataIdleLoop() {}
	byte m_state;
};
