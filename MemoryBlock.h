#ifndef _MEMORY_BLOCK_
#define _MEMORY_BLOCK_

#include <iostream>

// 메모리 블럭을 생성하는 클래스
// 블럭은 각각 인트형 배열로 구성되며 MemoryBlock 클래스는 이러한 블록들의 논리 메모리를 구성해준다.

class MemoryBlock
{
private:
	// 메모리를 할당하여 블록을 저장할 포인터
	int** m_memBlock;
	// 메모리 블럭 크기	
	int m_memBlockSize;	

	// 메모리 블럭 기본 크기
	const int DEFAULT_MEMBLOCK_SIZE = 30;
	// 메모리 블럭 기본 증가 크기
	const int DEFAULT_MEMBLOCK_INCREASE_SIZE = 20;

public:

	// memSize 크기만큼 메모리 블럭 생성
	bool MemoryBlock(int memSize = DEFAULT_MEMBLOCK_SIZE);
	
	// 메모리 블럭의 크기를 increaseSize만큼 증가
	bool MemoryBlock(int increaseSize = DEFAULT_MEMBLOCK_SIZE);
}

#endif
