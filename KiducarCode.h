#ifndef _KIDUCAR_CODE_
#define _KIDUCAR_CODE_

#include "CommonDefine.h"
#include "MemoryBlock.h"

// 블럭에 대한 자동차의 실행 코드를 다루는 클래스

class KiducarCode
{
private:

	// 코드를 읽어올 메모리 블록
	MemoryBlock* m_memBlockCode;

public:

	// 생성자, 코드를 읽을 메모리 블럭을 외부로부터 받아옴
	KiducarCode(MemoryBlock* memBlockCode);
	// 소멸자
	~KiducarCode(){}

	// 차 제어에 필요한 초기화 코드
	bool initKiducar();

	// 블록을 분석하여 해당 블록에 맞는 코드를 실행시켜주는 함수.
	bool interpretAndExecute(int* blockCode);

	// 차를 앞으로 약간 이동하는 코드
	void moveForwardCode();
	// 차를 뒤로 약간 이동하는 코드
	void moveBackwardCode();

	// 차를 오른쪽으로 조금 회전시키는 코드
	void rotateRightCode();
	// 차를 왼쪽으로 조금 회전시키는 코드
	void rotateLeftCode();

	// 반복해서 블럭을 실행하는 코드, 반복 횟수와 반복할 코드 개수를 매개변수로 받음
	bool repeatCode(int repeatNum, int repeatCodeNum);

	// 코드를 실행
	void run();
};

#endif
