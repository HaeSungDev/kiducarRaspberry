#include "BluetoothSerial.h"

BluetoothSerial::BluetoothSerial()
{
	m_bluetoothFD = -1;
}

BluetoothSerial::~BluetoothSerial()
{
	if(m_bluetoothFD != -1)
		serialClose(m_bluetoothFD);
}

bool BluetoothSerial::initBluetooth()
{
	if(!initWiringPi())
		return false;
	// 시리얼 통신을 연다.
	m_bluetoothFD = serialOpen("/dev/ttyAMA0", 9600);
	if(m_bluetoothFD == -1)
	{
		std::cerr << "serialOpen() failed";
		return false;
	}

	return true;
}

int BluetoothSerial::recvData(char* data, int size)
{
	if(m_bluetoothFD == -1)
	{
		std::cout << "bluetooth is not connected" << std::endl;
		return -1;
	}

	char lenBuf[4];
	
	// 상대가 전송한 데이터 길이를 가져온다.
	for(int i = 0;i < 4;i++)
	{
		// 데이터가 있을때까지 기다림
		while(1)
		{
			if(serialDataAvail(m_bluetoothFD))
			{
				lenBuf[i] = serialGetchar(m_bluetoothFD);
				break;
			}
		}
	}

	// 읽은 데이터를 길이로 변환
	int len = *(int*)lenBuf;

	// 상대가 전송한 데이터를 읽음
	int readLen;
	for(readLen = 0;readLen < len && readLen < size;readLen++)
	{
		// 데이터가 있을때까지 기다림
		while(1)
		{
			if(serialDataAvail(m_bluetoothFD))
			{
				data[readLen] = serialGetchar(m_bluetoothFD);
				break;
			}
		}
	}

	return readLen;
}

int BluetoothSerial::sendData(char* data, int size)
{
	if(m_bluetoothFD == -1)
	{
		std::cout << "bluetooth is not connected" << std::endl;
		return -1;
	}

	// 데이터 길이를 먼저 전송
	char lenBuf[4];
	*(int*)lenBuf = size;

	for(int i = 0;i < 4;i++)
	{
		serialPutchar(m_bluetoothFD, lenBuf[i]);
	}

	// 길이만큼 데이터 전송
	int sendLen;
	for(sendLen = 0;sendLen < size;sendLen++)
	{
		serialPutchar(m_bluetoothFD, sendLen[i]);
	}

	return sendLen;
}
