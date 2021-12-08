#pragma once


// LeaderboardDialog 대화 상자

class LeaderboardDialog : public CDialog
{
	DECLARE_DYNAMIC(LeaderboardDialog)

	//-----변수-----
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
};
