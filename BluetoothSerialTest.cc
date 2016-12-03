#include "BluetoothSerial.h"

int main()
{
	BluetoothSerial bs;

	bs.initBluetooth();

	char buf[256];
	while(1)
	{
		int len = bs.recvData(buf, 256);
		printf("%d\n", len);
		for(int i = 0;i < len;i+=4)
			printf("%d\n", *(int*)(buf+i));
	}

	return 0;
}
