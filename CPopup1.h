#pragma once


// CPopup1 대화 상자

class CPopup1 : public CDialog
{
	DECLARE_DYNAMIC(CPopup1)

public:
	CPopup1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPopup1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
