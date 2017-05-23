KiducarMain : KiducarMain.cc KiducarCode.o BluetoothSerial.o MemoryBlock.o
	g++ -std=c++11 -o KiducarMain KiducarMain.cc KiducarCode.o BluetoothSerial.o MemoryBlock.o -l wiringPi -l pthread
	rm *.o

BluetoothSerial.o : BluetoothSerial.cc
	g++ -std=c++11 -c -o BluetoothSerial.o BluetoothSerial.cc -l wiringPi -l pthread

KiducarCode.o : KiducarCode.cc MemoryBlock.o
	g++ -std=c++11 -c -o KiducarCode.o KiducarCode.cc MemoryBlock.o -l wiringPi -l pthread

MemoryBlock.o : MemoryBlock.cc 
	g++ -std=c++11 -c -o MemoryBlock.o MemoryBlock.cc -l wiringPi -l pthread
