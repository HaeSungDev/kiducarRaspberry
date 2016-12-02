#ifndef _BLUETOOTH_SERIAL_
#define _BLUETOOTH_SERIAL_

#include "CommonDefine.h"

// 블루투스 시리얼 통신을 위한 클래스(HC-06 모듈 사용)

class BluetoothSerial
{
private:
	
	// 시리얼 통신 파일 지정 번호
	int m_bluetoothFD;
	
public:

	// 생성자
	BluetoothSerial();
	// 소멸자
	~BluetoothSerial();


	// 블루투스 통신을 위한 초기화
	bool initBluetooth();
	// 블루투스 모듈에서 데이터를 읽어온다. 동기형 함수. 데이터를 다 받을때까지 봉쇄된다.
	int recvData(char* data, int size);
	// 블루투스 모듈로 데이터를 쓴다.
	int sendData(char* data, int size);
};

#endif
