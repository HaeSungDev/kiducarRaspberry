#include "KiducarCode.h"

KiducarCode::KiducarCode()
{
	m_memBlockCode = nullptr;
	m_isStop = false;
}

bool KiducarCode::initKiducar()
{
	// 왼쪽 바퀴와 오른쪽 바퀴를 OUTPUT 모드로 설정
	pinMode(LEFT_TIRE_PWM, OUTPUT);
	pinMode(LEFT_TIRE_DIR, OUTPUT);

	pinMode(RIGHT_TIRE_PWM, OUTPUT);
	pinMode(RIGHT_TIRE_DIR, OUTPUT);

	// ECHO_PIN을 INPUT모드, TRIG_PIN을 OUTPUT모드로 설정
	pinMode(ECHO_PIN, INPUT);
	pinMode(TRIG_PIN, OUTPUT);

	// 거리 초기화를 위해 사용
	getDistance();
}

bool KiducarCode::interpretAndExecute(int* blockCode)
{
	// 프로그램이 중지상태가 되었다면 false 반환으로 실행을 중지시킴
	if(m_isStop)
		return false;

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

		case STOPBLOCK:
			{
				stopCode();
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
			{
				int okCodeNum = blockCode[2];
				int noCodeNum = blockCode[3];

				if(!conditionCode(okCodeNum, noCodeNum))
					return false;
			}
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
	
	digitalWrite(RIGHT_TIRE_PWM, 1);
	digitalWrite(RIGHT_TIRE_DIR, 1);

	// 0.1초간 오른쪽으로 회전
	delay(100);

	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);
}

void KiducarCode::rotateLeftCode()
{	
	digitalWrite(LEFT_TIRE_PWM, 1);
	digitalWrite(LEFT_TIRE_DIR, 1);
	
	digitalWrite(RIGHT_TIRE_PWM, 1);
	digitalWrite(RIGHT_TIRE_DIR, 0);

	// 0.1초간 왼쪽으로 회전
	delay(100);

	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);
}

void KiducarCode::stopCode()
{
	digitalWrite(LEFT_TIRE_PWM, 0);
	digitalWrite(LEFT_TIRE_DIR, 0);
	
	digitalWrite(RIGHT_TIRE_PWM, 0);
	digitalWrite(RIGHT_TIRE_DIR, 0);

	// 0.1초간 정지
	delay(100);
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

int KiducarCode::getDistance()
{
	// TRIG_PIN LOW로 초기화
	digitalWrite(TRIG_PIN, 0);
	delay(10);

	// 초음파를 내보냄
	digitalWrite(TRIG_PIN, 1);
	delayMicroseconds(20);
	digitalWrite(TRIG_PIN, 0);

	// 갔다가 돌아오는 신호 측정
	while(digitalRead(ECHO_PIN) == 0);

	long startTime = micros();
	while(digitalRead(ECHO_PIN) == 1);
	long travelTime = micros()-startTime;

	// 시간에 58을 나눠서 거리 계산
	int distance = travelTime / 58;

	return distance;
}

bool KiducarCode::conditionCheck(int* blockCode)
{
	int blockType = blockCode[1];

	switch(blockType)
	{
		case DISTANCECHECKBLOCK:
			{
				int distance = blockCode[2];
				if(distance > getDistance())
					return true;
				else
					return false;
			}
			break;
	}

	return false;
}

bool KiducarCode::interpretAndIgnore(int* blockCode)
{
	// 프로그램이 중지상태가 되었다면 false 반환으로 실행을 중지시킴
	if(m_isStop)
		return false;
	int blockType = blockCode[1];

	// 블록을 실행 안하고 무시한다.
	switch(blockType)
	{
		case MOVEBLOCK:
		case ROTATEBLOCK:
			{
				return true;
			}
			break;

		case REPEATBLOCK:
			{	
				int repeatCodeNum = blockCode[3];
			
				// 반복블록 내부는 외부에서 하나의 블록으로 인식하므로 건너뛰어줌
				if(!skipCode(repeatCodeNum))
					return false;
			}	
			break;

		case CONDITIONBLOCK:
			{
				int okCodeNum = blockCode[2];
				int noCodeNum = blockCode[3];

				// 조건문 내부는 외부에서 하나의 블록으로 인식하므로 건너뛰어줌
				if(!skipCode(okCodeNum+noCodeNum))
					return false;
			}
			break;
	}

	return true;
}

bool KiducarCode::skipCode(int codeNum)
{
	for(int i = 0;i < codeNum;i++)
	{
		if(!m_memBlockCode->setMemExecutePoint(m_memBlockCode->getMemExecutePoint()+1))
			return false;

		if(!interpretAndIgnore(m_memBlockCode->curExecuteBlock()))
			return false;
	}

	return true;
}

bool KiducarCode::conditionCode(int okCodeNum, int noCodeNum)
{
	// 조건 블록 다음에는 체크할 조건 블록이 있으므로 실행 포인트를 1증가한다.
	if(!m_memBlockCode->setMemExecutePoint(m_memBlockCode->getMemExecutePoint()+1))
		return false;

	if(conditionCheck(m_memBlockCode->curExecuteBlock()))
	{
		// okCode 실행
		for(int i = 0;i < okCodeNum;i++)
		{
			if(!m_memBlockCode->setMemExecutePoint(m_memBlockCode->getMemExecutePoint()+1))
				return false;

			if(!interpretAndExecute(m_memBlockCode->curExecuteBlock()))
				return false;
		}

		// okCode를 실행하였으므로 noCode는 건너뜀
		if(!skipCode(noCodeNum))
			return false;
	}
	else
	{
		// okCode를 실행하지 않았으므로 okCode를 건너뜀
		if(!skipCode(okCodeNum))
			return false;

		// noCode 실행
		for(int i = 0;i < noCodeNum;i++)
		{
			if(!m_memBlockCode->setMemExecutePoint(m_memBlockCode->getMemExecutePoint()+1))
				return false;

			if(!interpretAndExecute(m_memBlockCode->curExecuteBlock()))
				return false;
		}
	}

	return true;
}

void KiducarCode::setMemBlockCode(MemoryBlock* memBlockCode)
{
	m_memBlockCode = memBlockCode;
}
MemoryBlock* KiducarCode::getMemBlockCode()
{
	return m_memBlockCode;
}

void KiducarCode::setIsStop(bool isStop)
{
	m_isStop = isStop;
}
bool KiducarCode::getIsStop()
{
	return m_isStop;
}

void KiducarCode::run()
{
	if(m_memBlockCode == nullptr)
		return;

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
