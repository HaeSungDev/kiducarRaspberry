#include "KiducarCode.h"
#include "MemoryBlock.h"
#include <iostream>
using namespace std;

int main()
{
	int forward[2] = {MOVEBLOCK, 0};
	int rightRotate[2] = {ROTATEBLOCK, 0};
	int repeat[3] = {REPEATBLOCK, 8, 2};
	int repeatForward[3] = {REPEATBLOCK, 10, 1};
	int repeatRightRotate[3] = {REPEATBLOCK, 7, 1};

	MemoryBlock mb;

	mb.insertBlock(repeat, 3);
	mb.insertBlock(repeatForward, 3);
	mb.insertBlock(forward, 2);
	mb.insertBlock(repeatRightRotate, 3);
	mb.insertBlock(rightRotate, 2);

	KiducarCode kc(&mb);

	kc.run();

	return 0;
}
