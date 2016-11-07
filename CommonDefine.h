#ifndef _COMMON_DEFINE_
#define _COMMON_DEFINE_

// 표준 입출력
#include <iostream>
// 라즈베리파이 gpio를 사용하기 위한 함수
#include <wiringPi.h>
// 라즈베리파이 gpio serial port를 사용하기 위한 함수
#include <wiringSerial.h>
// new 연산자 예외처리
#include <new>

// wiringPI pin 번호 정의
const int LEFT_TIRE_PWM = 0;
const int LEFT_TIRE_DIR = 1;

const int RIGHT_TIRE_PWM = 2;
const int RIGHT_TIRE_DIR = 3;

// 블록 타입 정의
const int MOVEBLOCK = 0;
const int ROTATEBLOCK = 1;
const int REPEATBLOCK = 2;
const int CONDITIONBLOCK = 3;
const int DISTANCECHECKBLOCK = 4;

#endif
