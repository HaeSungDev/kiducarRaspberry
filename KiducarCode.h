#ifndef _KIDUCAR_CODE_
#define _KIDUCAR_CODE_

#include "CommonDefine.h"

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
	~KiducarCode();

	// 코드를 실행
	void run();
};

#endif
