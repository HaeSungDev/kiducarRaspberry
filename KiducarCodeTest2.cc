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
	int repeat[3] = {REPEATBLOCK, 100, 2};
	int repeatRight[3] = {REPEATBLOCK, 2, 1};
	int repeatBackward[3] = {REPEATBLOCK, 3, 1};
	int condition[3] = {CONDITIONBLOCK, 1, 0};
	int distanceCheck[2] = {DISTANCECHECKBLOCK, 30};
	int c[3] = {CONDITIONBLOCK, 1, 0};
	int dc[2] = {DISTANCECHECKBLOCK, 10};

	MemoryBlock mb;

	mb.insertBlock(repeat, 3);
	
	mb.insertBlock(condition, 3);
	mb.insertBlock(distanceCheck, 2);
	mb.insertBlock(repeatRight, 3);
	mb.insertBlock(rightRotate, 2);
	mb.insertBlock(forward, 2);
	
	mb.insertBlock(c, 3);
	mb.insertBlock(dc, 2);
	mb.insertBlock(repeatBackward, 3);
	mb.insertBlock(backward, 2); 

	KiducarCode kc(&mb);

	kc.run();

	return 0;
}
