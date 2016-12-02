#include "BluetoothSerial.h"

int main()
{
	BluetoothSerial bs;

	bs.initBluetooth();

	char buf[256];
	while(1)
	{
		int len = bs.recvData(buf, 256);
		buf[len] = '\0';

		printf("%s\n",buf);
	}

	return 0;
}
