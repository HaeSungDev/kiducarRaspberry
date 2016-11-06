#ifndef _MEMORY_BLOCK_
#define _MEMORY_BLOCK_

#include "CommonDefine.h"

// 메모리 블럭을 생성하는 클래스
// 블럭은 각각 인트형 배열로 구성되며 MemoryBlock 클래스는 이러한 블록들의 논리 메모리를 구성해준다.

class MemoryBlock
{
private:
	// 메모리를 할당하여 블록을 저장할 포인터
	int** m_memBlock;
	// 메모리 블럭 크기	
	int m_memBlockSize;
	// 메모리 블럭에 저장된 마지막 블럭 다음 위치
	int m_memEndPoint;
	// 현재 실행 중인 메모리블럭을 가리키는 위치, 현재 실행되는 메모리 명령 블록
	int m_memExecutePoint;

	// 메모리 블럭 기본 크기
	static const int DEFAULT_MEMBLOCK_SIZE = 30;
	// 메모리 블럭 기본 증가 크기
	static const int DEFAULT_MEMBLOCK_INCREASE_SIZE = 30;

public:

	// 생성자, memSize 크기만큼 메모리 블럭 생성
	MemoryBlock(int memSize = DEFAULT_MEMBLOCK_SIZE);
	// 소멸자, 메모리 블록 해제
	~MemoryBlock();
	
	// 메모리 블럭의 크기를 increaseSize만큼 증가
	bool increaseSize(int increaseSize = DEFAULT_MEMBLOCK_INCREASE_SIZE);

	// 블럭을 삽입함, 삽입시 블럭의 크기를 명시해 주기 위해 배열의 맨 앞에 배열 크기를 넣어줌.
	bool insertBlock(int* block, int size);

	// 현재 실행중인 배열을 가져옴
	int* curExecuteBlock();

	// 실행할 메모리 블럭의 위치를 설정
	bool setMemExecutePoint(int memExecutePoint);
	// 실행할 메모리 블럭의 위치를 가져옴
	int getMemExecutePoint();
};

#endif
