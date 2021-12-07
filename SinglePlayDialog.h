#pragma once
#include <list>
#include <random>

// 현 위치, 속도벡터를 담기 위한 구조체
// 매 타이머 틱마다 벡터 방향으로 움직이도록 구현, vector 범위 내에서 랜덤으로 생성
struct Enemy {
	CPoint point;
	CPoint vector;
};

// SinglePlayDialog 대화 상자

class SinglePlayDialog : public CDialog
{
	DECLARE_DYNAMIC(SinglePlayDialog)

private:
	const int timerTick = 70; //Timer 틱 간격


	const int dialogXSize = 1200; //창의 X축 크기
	const int dialogYSize = 800; //창의 Y축 크기

	const int enemySize = 30; //적의 반지름
	const int maxEnemyGen = 2; //한번에 생성될 수 있는 적의 숫자
	const int maxEnemySpeed = 5; //적의 최대 속도, y벡터는 음수값 불가능
	const int bulletSpeed = 6; //총알의 속도


	//기존의 직접 만든 Single LinkedList에서 STL에서 지원하는 list로 교체
	std::list<CPoint> bulletList;
	std::list<Enemy> enemyList;

	//난수 생성을 위한 생성자
	std::mt19937 randEng;


	//Methods
	//비행기 움직이기 위한 메소드
	void drawAirplane();
	//장애물이 떨어지기 위한 메소드
	void drawEnemy();
	//탄이 발사되기 위한 메소드
	
	

public:
	SinglePlayDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SinglePlayDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SINGLEPLAY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	
     //각각의 버튼 눌렀을때의 true,false 눌렀을때 true , 때면 false
	bool isWPressed=false;
	bool isAPressed=false;
	bool isSPressed=false;
	bool isDPressed=false;
	bool isJPressed=false;

	CPoint airPlaneLocation; //비행기의 위치 CPoint로 생성
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
