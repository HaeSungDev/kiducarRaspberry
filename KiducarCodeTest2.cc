#include "KiducarCode.h"
#include "MemoryBlock.h"
#include <iostream>
using namespace std;

int main()
{
	int forward[2] = {MOVEBLOCK, 0};
	int backward[2] = {MOVEBLOCK, 1};
	int rightRotate[2] = {ROTATEBLOCK, 0};
	int leftRotate[2] = {ROTATEBLOCK, 1};
	int repeat[3] = {REPEATBLOCK, 100, 1};
	int repeatForward[3] = {REPEATBLOCK, 100, 1};
	int repeatBackward[3] = {REPEATBLOCK, 10, 1};
	int condition[3] = {CONDITIONBLOCK, 1, 1};
	int distanceCheck[2] = {DISTANCECHECKBLOCK, 10};

	MemoryBlock mb;

	mb.insertBlock(repeat, 3);
	mb.insertBlock(condition, 3);
	mb.insertBlock(distanceCheck, 2);
	mb.insertBlock(repeatBackward, 3);
	mb.insertBlock(backward, 2);
	mb.insertBlock(forward, 2);

	KiducarCode kc(&mb);

	kc.run();
	

	return 0;
}
