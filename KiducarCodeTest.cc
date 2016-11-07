#include "KiducarCode.h"
#include "MemoryBlock.h"
#include <iostream>
using namespace std;

int main()
{
	int forward[2] = {MOVEBLOCK, 0};
	int right[2] = {ROTATEBLOCK, 1};
	int repeat[3] = {REPEATBLOCK, 4, 2};
	int repeatForward[3] = {REPEATBLOCK, 20, 1};
	int repeatBackward[3] = {REPEATBLOCK, 10, 1};

	MemoryBlock mb;

	mb.insertBlock(repeat, 3);
	mb.insertBlock(repeatForward, 3);
	mb.insertBlock(forward, 2);
	mb.insertBlock(repeatBackward, 3);
	mb.insertBlock(right, 2);

	KiducarCode kc(&mb);

	kc.run();
	return 0;
}
