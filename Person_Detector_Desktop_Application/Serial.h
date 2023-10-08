#ifndef SERIAL_H
#define SERIAL_H

#include <Windows.h>
#include <atlstr.h>

#define BEGIN_CHAR  '$'
#define END_CHAR    '%'
#define ESC_CHAR    ':'

class Serial
{
private:
	DCB dcb;
	HANDLE hPort;
	DWORD commModemStatus;
public:
	Serial();
	Serial(CString portName, DWORD baudrate);
	void Open(CString portName, DWORD baudrate);
	char Read(uint8_t* buffer);
	unsigned int Write(const uint8_t data);
	int Available();
	void Get_SensorData(uint8_t* buffer, size_t bufferSize);
	void Stop();
};

#endif /* SERIAL_H */
