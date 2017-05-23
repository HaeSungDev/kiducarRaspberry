# Kiducar

키듀카는 소프트웨어 교육용 블록코딩 프로그램입니다. <br>
안드로이드 어플리케이션에서 블록들을 블록판에 드래그 앤 드롭으로 끼운다음 실행하면 자동차가 명령대로 작동합니다. <br>
<br>
프로그램은 안드로이드 어플리케이션과 라즈베리파이로 제작한 자동차로 구성됩니다. <br>
이 저장소는 라즈베리파이 소스코드를 저장하고 있습니다. <br>
<br>
## 설치 방법

* 자동차를 제작합니다.<br>
  - 라즈베리파이3 model B <br>
  - HC-SR04 초음파 센서 모듈 (echo_pin : 38번 trig_pin :40번) <br>
  - HC-06 블루투스 모듈 (rx : 8번 tx : 10번) <br>
  - 2x DC motor <br>
  - l298n 모터 제어 보드 (PWMA : 11번 DIRA : 12번 PWMB : 13번 DIRB : 15번) <br>
  - 4xAA 배터리 <br>
  - 라즈베리파이 전원 배터리 <br>

* 라즈베리파이에 Raspbian Jessie with Pixel OS를 설치합니다. <br>
[이미지 파일 다운로드](https://www.raspberrypi.org/downloads/raspbian/) <br>
[이미지 인스톨 방법](https://www.raspberrypi.org/documentation/installation/installing-images/README.md) <br>

* git clone 명령어를 이용해 저장소를 복사합니다. <br>
```bash
$ git clone https://github.com/xods1024/KiducarRaspberry
```
* 복사 한 KiducarRaspberry 디렉토리로 이동한 후 make 명령어를 이용해 실행파일을 생성합니다. <br>
```bash
$ cd KiducarRaspberry
$ make
```
* 프로그램을 실행합니다. <br>
```bash
$ sudo ./KiducarMain
```

## 사용 방법

* Kiducar의 전원을 작동시킨 후 Kiducar 프로그램을 실행합니다. <br>

* 어플리케이션을 실행한 후 자동차와 블루투스 연결을 합니다. <br>
[Kiducar 어플리케이션 설치](https://github.com/xods1024/Kiducar)
* 블록판에 블록들을 드래그 앤 드롭으로 끼워서 코딩을 합니다. <br>
* 실행 버튼을 누르면 자동차로 코드가 전송되고 실행 됩니다. <br>

![IMAGE ALT TEXT](http://img.youtube.com/vi/bGhjeFlXbWE/0.jpg) <br>
[어플리케이션 사용 동영상 보기](https://youtu.be/bGhjeFlXbWE) <br>

![IMAGE ALT TEXT](http://img.youtube.com/vi/RXiHn9HktLw/0.jpg) <br>
[자동차 시연 동영상 ](https://youtu.be/RXiHn9HktLw) <br>

## Contribute

* 프로젝트에 관해 궁금한 점 또는 건의사항이 있으시면 issue에 남겨주시거나 xods1025@gmail.com로 메일 주시기 바랍니다.
