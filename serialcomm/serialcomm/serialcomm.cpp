
/*
    We send to serial port a "smiley face" from gcode.txt file.
    The program written in Arduino IDE takes this instructions and it draws the image with 3 motors.
*/

#include "stdafx.h"

#include<fstream>
#include <iostream>
#include <windows.h>
#include <string>
#include<ctime>
#define bufSize 1024

int main()
{
	std::wstring comID = L"COM3";

	// Declare variables and structures
	HANDLE hSerial;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	// Open the comID serial port number
	fprintf(stderr, "Opening serial port...");
	hSerial = CreateFile(comID.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error\n");
		system("pause");
		return 1;
	}
	else fprintf(stderr, "OK\n");

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error getting device state\n");
		CloseHandle(hSerial);
		system("pause");
		return 1;
	}

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (SetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error setting device parameters\n");
		CloseHandle(hSerial);
		system("pause");
		return 1;
	}

	// Set COM port timeout settings
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (SetCommTimeouts(hSerial, &timeouts) == 0)
	{
		fprintf(stderr, "Error setting timeouts\n");
		CloseHandle(hSerial);
		system("pause");
		return 1;
	}

	//Reading the gcode.txt file

	FILE* fp;
	fopen_s(&fp, "smiley_noi.txt", "r");
	char buf[bufSize];
	char bufferReceived[bufSize];
	DWORD bytes_read;
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		buf[strlen(buf) - 1] = '\n'; // eat the newline fgets() stores

		printf("%s\n", buf);


		// Send specified text (remaining command line arguments)
		DWORD bytes_written, total_bytes_written = 0;

		ReadFile(hSerial, bufferReceived, sizeof(bufferReceived), &bytes_read, NULL);

		fprintf(stderr, "%d bytes read\n", bytes_read);
		bufferReceived[0] = '\0';
		for (int i = 0; i < strlen(bufferReceived); i++)
			bufferReceived[i] = '\0';

		fprintf(stderr, "Sending bytes...");

		if (!WriteFile(hSerial, buf, strlen(buf), &bytes_written, NULL))
		{
			fprintf(stderr, "Error\n");
			CloseHandle(hSerial);
			system("pause");
			return 1;
		}



		Sleep(1000);

		fprintf(stderr, "%d bytes written\n", bytes_written);

		system("pause");
	}
	fclose(fp);

	// Close serial port
	fprintf(stderr, "Closing serial port...");
	if (CloseHandle(hSerial) == 0)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	fprintf(stderr, "OK\n");

	// exit normally
	system("pause");
	return 0;
}
