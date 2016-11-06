#include "MemoryBlock.h"

int main()
{
	int data1[4] = {1, 2, 3, 4};
	int data2[3] = {5, 6, 7};

	MemoryBlock mb;

	for(int i = 0;i < 20;i++)
	{
		if(!mb.insertBlock(data1, 4))
			std::cout << "insert failed" << std::endl;
	}

	for(int i = 0;i < 20;i++)
	{
		if(!mb.insertBlock(data2, 3))
		{
			std::cout << "insert failed" << std::endl;
		}
	}

	int executePoint = mb.getMemExecutePoint();

	while(1)
	{
		int *data;
		if(!(data = mb.curExecuteBlock()))
		{
			std::cout << "invalid block" << std::endl;
			break;
		}

		int size = data[0];

		for(int i = 0;i < size;i++)
		{
			std::cout << data[i] << ":";
		}
		std::cout << std::endl;

		executePoint++;
		if(!mb.setMemExecutePoint(executePoint))
		{
			break;
		}
	}
}
