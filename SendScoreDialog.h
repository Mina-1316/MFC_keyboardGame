#pragma once

#include <string>


// SendScoreDialog 대화 상자

class SendScoreDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SendScoreDialog)

public:
	SendScoreDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SendScoreDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SendScore_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CString m_score;
	int m_score = 0; // SendScoreDialog.cpp에 있는   , m_score(0)를 지우고 0으로 초기화 했습니다.
	CString m_userID; //에러 발생, 다시 CString으로 변경, 출력만 std::string으로 하기
	afx_msg void OnBnClickedOk();
};
