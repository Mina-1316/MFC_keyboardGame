#pragma once
#include "LinkedList.h"

// SinglePlayDialog 대화 상자

class SinglePlayDialog : public CDialog
{
	DECLARE_DYNAMIC(SinglePlayDialog)

private:
	const int timerTick = 70; //Timer 틱 간격

	CPointList bullet;  //발사된 총알의 위치를 저장하는 LinkedList
	CPointList enemy;	//생성된 적들의 위치를 저장하는 LinkedList

public:
	SinglePlayDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SinglePlayDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
     //각각의 버튼 눌렀을때의 true,false 눌렀을때 true , 때면 false
	bool isWPressed;
	bool isAPressed;
	bool isSPressed;
	bool isDPressed;
	CPoint airPlaneLocation; //비행기의 위치 CPoint로 생성
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//비행기 움직이기 위한 메소드
	void drawAirplane();
	//장애물이 떨어지기 위한 메소드

	// 탄이 발사되기 위한 메소드
};
