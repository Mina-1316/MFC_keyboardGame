// SendScoreDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "SendScoreDialog.h"
#include "afxdialogex.h"
#include "HttpConnClass.h"

// SendScoreDialog 대화 상자

IMPLEMENT_DYNAMIC(SendScoreDialog, CDialogEx)

SendScoreDialog::SendScoreDialog(int scoreIn, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SENDSCORE_DIALOG, pParent) , m_score(scoreIn)
{

}

SendScoreDialog::~SendScoreDialog()
{
}

void SendScoreDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_SCORE, m_score);
	DDX_Text(pDX, IDC_SCORE, m_score);
	DDX_Text(pDX, IDC_USERID, m_userID);
}


BEGIN_MESSAGE_MAP(SendScoreDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &SendScoreDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// SendScoreDialog 메시지 처리기


void SendScoreDialog::OnBnClickedOk()
{
	requestBody = "name"

	HttpConnClass::stringPostRequest(serverDomain, )


	CDialogEx::OnOK();
}
