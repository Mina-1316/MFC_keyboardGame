#pragma once

#include <json/json.h>

// LeaderboardDialog 대화 상자

class LeaderboardDialog : public CDialog
{
	DECLARE_DYNAMIC(LeaderboardDialog)


	//-----상수-----
private:
	//http 통신에 필요함
	const char* serverDomain = "http://:8091/getscore";
	const char* requestBody = "";

	//그리기를 시작할 지점, 각 지점간의 갭 등을 설정
	const int drawXPoint = 40;
	const int drawYPoint = 20;
	const int drawHorizonGap = 120;
	const int drawVertGap = 15;

	const int maxLeaderboardAmount = 10;

	//-----변수-----
private:
	Json::Value response;

	//-----멤버 함수-----
private:
	

public:
	LeaderboardDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LeaderboardDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LEADERBOARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
};
