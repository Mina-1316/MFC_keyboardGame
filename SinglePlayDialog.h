#pragma once


// SinglePlayDialog 대화 상자

class SinglePlayDialog : public CDialog
{
	DECLARE_DYNAMIC(SinglePlayDialog)

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
	int airplane_X;
//	int airplane_;
	int airplane_Y;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
