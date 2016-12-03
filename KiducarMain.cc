#include "KiducarCode.h"
#include "BluetoothSerial.h"
// 쓰레드 사용
#include <pthread.h>
// usleep 사용, execl 사용
#include <unistd.h>
// 프로그램 종료코드 사용
#include <stdlib.h>

// 블루투스 모듈
BluetoothSerial btSerial;
// 실행 블록
KiducarCode kiducarCode;
// 메모리 블록
MemoryBlock memBlock;

// 통신 및 실행제어 쓰레드 선언
void* executeControlThread(void* arg);
// 실행 쓰레드 선언
void* runThread(void* arg);

// 쓰레드 실행 제어
bool isControlRun;
bool isRun;

// 키듀카 실행 제어
bool isKiducarRun;

int main()
{
	// wiringPi setup
	if(!initWiringPi())
	{
		exit(1);
	}

	// 쓰레드 실행상태
	isControlRun = true;
	isRun = true;

	// 쓰레드 관련 변수
	pthread_t thread[2];
	int thread_id;
	int status;

	// 실행제어 쓰레드 생성
	thread_id = pthread_create(&thread[0], nullptr, executeControlThread, nullptr);
	if(thread_id < 0)
	{
		perror("pthread create");
		exit(1);
	}
	// 실행 쓰레드 생성
	thread_id = pthread_create(&thread[1], nullptr, runThread, nullptr);
	if(thread_id < 0)
	{
		perror("pthread create");
		exit(1);
	}

	// 쓰레드 종료 대기
	pthread_join(thread[0], (void**)&status);
	pthread_join(thread[1], (void**)&status);

	return 0;
}

// 통신 및 실행제어 쓰레드 정의
void* executeControlThread(void* arg)
{	
	// 블루투스 시리얼에서 읽어올 데이터 버퍼
	char buf[128];
	// 메모리 블록에 저장할 블록
	int block[10];
	// 읽은 데이터 길이
	int len;
	// 데이터 타입
	int dataType;

	// 블루투스 초기화
	btSerial.initBluetooth();
	// 키듀카 실행 안하는 상태
	isKiducarRun = false;

	// 메모리 블럭 설정
	kiducarCode.setMemBlockCode(&memBlock);

	while(isControlRun)
	{
		// 데이터를 읽음
		len = btSerial.recvData(buf, sizeof(buf));
		dataType = *((int*)buf);
		switch(dataType)
		{
			// 시작 코드가오면 키듀카 실행을 중지하고 새롭게 실행
			case STARTCODE:
				{
					// 실행을 중지 시킴
					isKiducarRun = false;
					kiducarCode.setIsStop(true);
					// 실행이 중지될때까지 0.1초 기다림
					usleep(1000*200);
					// 메모리 블록 초기화
					memBlock.deleteAllBlock();
				}
				break;

			case MOVEBLOCK:
			case ROTATEBLOCK:
			case STOPBLOCK:
			case REPEATBLOCK:
			case CONDITIONBLOCK:
			case DISTANCECHECKBLOCK:
				{
					// 받은 데이터를 블록 데이터로 변환하여 메모리블록에 삽입
					for(int i = 0;i < len/4;i++)
					{
						block[i] = *((int*)(buf+(i*4)));
					}
					memBlock.insertBlock(block, len/4);
				}
				break;

			case ENDCODE:
				{
					// 키듀카 실행
					kiducarCode.setIsStop(false);
					isKiducarRun = true;
				}
				break;

			case STOPCODE:
				{
					// 실행을 중지 시킴
					isKiducarRun = false;
					kiducarCode.setIsStop(true);
					usleep(1000*200);
				}
				break;

			case EXITCODE:
				{
					// 실행을 중지 시키고 운영체제 종료시킴
					isKiducarRun = false;
					isRun = false;
					isKiducarRun = false;
					kiducarCode.setIsStop(true);

					usleep(1000*200);

					execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "now", (char*)NULL);
				}
				break;
		}
	}
}

// 실행 쓰레드 정의
void* runThread(void* arg)
{
	while(isRun)
	{
		if(isKiducarRun)
		{
			kiducarCode.run();
			isKiducarRun = false;
		}
	}
}
