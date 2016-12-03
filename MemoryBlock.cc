#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(int memSize)
{
	m_memBlockSize = memSize;
	m_memEndPoint = 0;
	m_memExecutePoint = 0;

	try
	{
		m_memBlock = new int*[memSize];
	}
	catch(std::bad_alloc& ba)
	{
		std::cerr << "memory allocation failed" << ba.what() << std::endl;

		m_memBlockSize = 0;
	}
}

MemoryBlock::~MemoryBlock()
{
	for(int i = 0;i < m_memBlockSize;i++)
	{
		if(m_memBlock[i])
			delete[] m_memBlock[i];
	}

	if(m_memBlock)
		delete[] m_memBlock;
}

bool MemoryBlock::increaseSize(int increaseSize)
{
	int** temp;

	try
	{
		temp = new int*[m_memBlockSize+increaseSize];
	}
	catch(std::bad_alloc& ba)
	{	
		std::cerr << "memory allocation failed" << ba.what() << std::endl;

		return false;
	}

	for(int i = 0;i < m_memBlockSize;i++)
	{
		temp[i] = m_memBlock[i];
	}

	delete[] m_memBlock;

	m_memBlockSize += increaseSize;
	m_memBlock = temp;
	

	return true;
}

bool MemoryBlock::insertBlock(int* block, int size)
{
	int index = m_memEndPoint;

	if(index >= m_memBlockSize)
	{
		if(!increaseSize())
			return false;
	}

	try
	{
		m_memBlock[index] = new int[size+1];
	}
	catch(std::bad_alloc& ba)
	{
		std::cerr << "memory allocation failed" << ba.what() << std::endl;

		return false;
	}

	// 맨 앞에 블록의 크기를 저장해준다
	m_memBlock[index][0] = size+1;

	for(int i = 0;i < size;i++)
	{
		m_memBlock[index][i+1] = block[i];
	}

	++m_memEndPoint;

	return true;
}

void MemoryBlock::deleteAllBlock()
{
	for(int i = 0;i < m_memEndPoint;i++)
	{
		if(m_memBlock)
			delete[] m_memBlock[i];
	}

	m_memEndPoint = 0;
	m_memExecutePoint = 0;
}

int* MemoryBlock::curExecuteBlock()
{
	if(m_memEndPoint == 0)
		return nullptr;

	return m_memBlock[m_memExecutePoint];
}

bool MemoryBlock::setMemExecutePoint(int memExecutePoint)
{
	if(memExecutePoint < 0 || memExecutePoint >= m_memEndPoint)
		return false;

	m_memExecutePoint = memExecutePoint;	

	return true;
}

int MemoryBlock::getMemExecutePoint()
{
	return m_memExecutePoint;
}
