# MFC_keyboardGame

2학년 팀프로젝트 - university MFC teamproject
--------------------------

### 기능
1. 제한 시간 내에, 최대한 많은 점수를 얻는 싱글 플레이 모드
2. UTP 통신을 이용한, 멀티 플레이 모드
3. 서버와 연결해서, 서버에 저장된 최고 점수 리스트를 출력하는 리더보드 기능

### 사용한 라이브러리
1. libcurl

`windows - c++`
```ps
vcpkg integrate install
vcpkg install curl
```
2. jsoncpp

`windows - c++`
```ps
vcpkg integrate install
vcpkg install jsoncpp
```
해당 라이브러리가 없을 경우 빌드할 수 없음
