#include "Serial.h"
#include <iostream>

static HANDLE hSerialReadEvent;
static OVERLAPPED ovWrite, ovRead;

Serial::Serial()
{
	//Do Nothing
}

Serial::Serial(CString portName, DWORD baudrate)
{
	if (hPort) {
		/* serial line is connected already */
		dcb.BaudRate = baudrate;							// new baud rate

		if (!SetCommState(hPort, &dcb)) {
		}

		return;
	}

	hPort = CreateFile(portName,						// file name
		GENERIC_READ | GENERIC_WRITE,	// access mode
		0,								// share mode
		NULL,							// security attributes
		OPEN_EXISTING,					// how to create
		0,								// file attributes
		NULL);							// handle to template file

	if (hPort != INVALID_HANDLE_VALUE) {

		dcb.DCBlength = sizeof(dcb);
		dcb.BaudRate = baudrate;
		dcb.fBinary = 1;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.ByteSize = 8;

		if (!SetCommState(hPort, &dcb)) {
		}

		hSerialReadEvent = CreateEvent(NULL,			// security attributes
			FALSE,			// reset type (automatic/manual)
			FALSE,			// initial state
			(LPCWSTR)"RxEvent");		// object name

		ovRead.hEvent = hSerialReadEvent;
	}
}

void Serial::Open(CString portName, DWORD baudrate)
{
	if (hPort) {
		/* serial line is connected already */
		dcb.BaudRate = baudrate;							// new baud rate

		if (!SetCommState(hPort, &dcb)) {
		}

		return;
	}

	hPort = CreateFile(portName,						// file name
		GENERIC_READ | GENERIC_WRITE,	// access mode
		0,								// share mode
		NULL,							// security attributes
		OPEN_EXISTING,					// how to create
		0,								// file attributes
		NULL);							// handle to template file

	if (hPort != INVALID_HANDLE_VALUE) {

		dcb.DCBlength = sizeof(dcb);
		dcb.BaudRate = baudrate;
		dcb.fBinary = 1;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.ByteSize = 8;

		if (!SetCommState(hPort, &dcb)) {
		}

		hSerialReadEvent = CreateEvent(NULL,			// security attributes
			FALSE,			// reset type (automatic/manual)
			FALSE,			// initial state
			(LPCWSTR)"RxEvent");		// object name

		ovRead.hEvent = hSerialReadEvent;
	}
}

char Serial::Read(uint8_t* buffer)
{
	unsigned long bytesRead = 0;
	char          c;

	ReadFile(hPort,			// handle to file
		&c,				// data buffer
		1,					// number of bytes to write
		&bytesRead,		// number of bytes written
		&ovRead);			// overlapped buffer

	if (bytesRead == 1) return((int)c);
	return(-1);
}

unsigned int Serial::Write(const uint8_t data)
{
	unsigned long bytesWritten = 0;

	if (HasOverlappedIoCompleted(&ovRead))
	{
		WriteFile(hPort,			// handle to file
			&data,				// data buffer
			1,				// number of bytes to write
			&bytesWritten,	// number of bytes written
			&ovWrite);		// overlapped buffer
	}

	return(1);
}

int Serial::Available()
{
	DWORD error;
	COMSTAT status;
	ClearCommError(hPort, &error, &status);

	return status.cbInQue;
}

void Serial::Get_SensorData(uint8_t* buffer, size_t bufferSize)
{
	uint8_t readChar = 0;
	size_t nbBytes = 0;

	DWORD bytesRead = 0;

	while (nbBytes < bufferSize)
	{
		char val = Read(&readChar);

		if (val == -1)
		{
			return;
		}

		buffer[nbBytes++] = val;
	}
}

void Serial::Stop()
{
	CloseHandle(hPort);
}