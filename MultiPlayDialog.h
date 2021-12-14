#pragma once
#include <list>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "MultiPlaySocket.h"
#include "NetworkHandlerClass.h"

// MultiPlayDialog 대화 상자

class MultiPlayDialog : public CDialog, NetworkHandler
{
	DECLARE_DYNAMIC(MultiPlayDialog)

private:

	//----const-----
	//시스템 사용
	const int timerTick = 70; //Timer 틱 간격
	const int dialogXSize = 1200; //창의 X축 크기1200
	const int dialogYSize = 800; //창의 Y축 크기800

	//매직넘버
	const int planeSpeed = 6; //비행기의 속도
	const int airplaneXSize = 40; //비행기의 가로 크기
	const int airplaneYSize = 38; //비행기의 세로 크기
	const int bulletSpeed = 10; //총알의 속도 
	const int bulletSize = 4; //총알의 반지름(원 )
	const int bulletFireRate = 6; //총알의 발사 term 

	//네트워크
	const int networkBufferSize = 2048; //네트워크로부터 받는 통신의 버퍼 사이즈

	//-----var-----
	//기존의 직접 만든 Single LinkedList에서 STL에서 지원하는 list로 교체
	std::list<CPoint> bulletList;	//총알의 위치가 저장되는 배열

	//각각의 버튼 눌렀을때의 true,false 눌렀을때 true , 때면 false
	bool isWPressed = false;
	bool isAPressed = false;
	bool isSPressed = false;
	bool isDPressed = false;
	bool isJPressed = false;


	int timerCount = 0;		//시간이 얼마나 지났는지를 체크하는 변수
	int bulletTimer = 0;	//탄의 연사 속도를 조절하는 타이머 

	MultiPlaySocket clientSocket = MultiPlaySocket(this);
	MultiPlaySocket serverSocket = MultiPlaySocket(this);


	CString tgtAddress;

	//-----Methods-----
	//비행기 움직임을 처리하는 메소드
	void processAirplane();
	//탄의 움직임을 처리하는 메소드  
	void processBullet();

public:
	//네트워크 연결을 제어하는 메소드
	virtual void OnAccept();
	virtual void OnClose();
	virtual void OnConnect();
	virtual void OnReceive();
	virtual void OnSend();


public:
	MultiPlayDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MultiPlayDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MultlPlayDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);


	CPoint airPlaneLocation; //비행기의 위치 CPoint로 생성
	CPoint enemyPlaneLocation;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};