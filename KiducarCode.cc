#include "KiducarCode.h"

KiducarCode::KiducarCode(MemoryBlock* memBlockCode)
{
	m_memBlockCode = memBlockCode;
}

bool KiducarCode::initKiducar()
{
	// wiringPi 설정
	if(wiringPiSetup() == -1)
	{
		std::cerr << "wiringPiSetup() failed";
		return false;
	}

	// 왼쪽 바퀴와 오른쪽 바퀴를 OUTPUT 모드로 설정
	pinMode(LEFT_TIRE_PWM, OUTPUT);
	pinMode(LEFT_TIRE_DIR, OUTPUT);

	pinMode(RIGHT_TIRE_PWM, OUTPUT);
	pinMode(RIGHT_TIRE_DIR, OUTPUT);
}

bool KiducarCode::interpretAndExecute(int* blockCode)
{
	int blockType = blockCode[1];

	switch(blockType)
	{
		case MOVEBLOCK:
			{
				int moveDirection = blockCode[2];
				if(moveDirection == 0)
					moveForwardCode();
				else
					moveBackwardCode();
			}
			break;
		
		case ROTATEBLOCK:
			{
				int rotateDirection = blockCode[2];
				
				if(rotateDirection == 0)
					rotateRightCode();
				else
					rotateLeftCode();
			}
			break;

		case REPEATBLOCK:
			{	
				int repeatNum = blockCode[2];
				int repeatCodeNum = blockCode[3];
				
				if(!repeatCode(repeatNum, repeatCodeNum))
					return false;
			}	
			break;

		case CONDITIONBLOCK:
			break;
		case DISTANCECHECKBLOCK:
			break;
	}

	return true;
}

void KiducarCode::moveForwardCode()
{
	digitalWrite(LEFT_TIRE_PWM, 1);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 1);
	digitalWrite(RIGHT_TIRE_DIR, 0);

	// 0.1초간 앞으로 이동
	delay(100);

	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);
}

void KiducarCode::moveBackwardCode()
{
	digitalWrite(LEFT_TIRE_PWM, 1);
	digitalWrite(LEFT_TIRE_DIR, 1);
	
	digitalWrite(RIGHT_TIRE_PWM, 1);
	digitalWrite(RIGHT_TIRE_DIR, 1);

	// 0.1초간 뒤로 이동
	delay(100);

	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);
}

void KiducarCode::rotateRightCode()
{
	digitalWrite(LEFT_TIRE_PWM, 1);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);

	// 0.1초간 오른쪽으로 회전
	delay(100);

	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);
}

void KiducarCode::rotateLeftCode()
{	
	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 1);
	digitalWrite(RIGHT_TIRE_DIR, 0);

	// 0.1초간 왼쪽으로 회전
	delay(100);

	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);
}

bool KiducarCode::repeatCode(int repeatNum, int repeatCodeNum)
{
	// 반복의 시작점을 정해줌.
	int startPoint = m_memBlockCode->getMemExecutePoint();
	
	for(int i = 0;i < repeatNum;i++)
	{
		// 반복 시작 부분 설정
		if(!m_memBlockCode->setMemExecutePoint(startPoint))
			return false;

		// 반복 코드 실행
		for(int j = 0;j < repeatCodeNum;j++)
		{
			// 다음 코드를 실행
			if(!m_memBlockCode->setMemExecutePoint(m_memBlockCode->getMemExecutePoint() + 1))
				return false;

			// 블록 해석 및 실행
			if(!interpretAndExecute(m_memBlockCode->curExecuteBlock()))
				return false;
		}
	}

	return true;
}

void KiducarCode::run()
{
	// 프로그램 시작
	std::cout << "Program Start!!!" << std::endl;

	// wiringPi 초기화
	initKiducar();

	// 메모리 블록 포인터를 처음으로 이동
	if(!m_memBlockCode->setMemExecutePoint(0))
	{
		std::cout << "There is no code" << std::endl;
		return;
	}

	// 코드를 순차적으로 실행
	while(1)
	{
		if(!interpretAndExecute(m_memBlockCode->curExecuteBlock()))
			break;
		
		if(!m_memBlockCode->setMemExecutePoint(m_memBlockCode->getMemExecutePoint()+1))
			break;
	}
	
	// 프로그램 끝
	std::cout << "Program End!!!" << std::endl;
}
