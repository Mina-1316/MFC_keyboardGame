// SendScoreDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "SendScoreDialog.h"
#include "afxdialogex.h"
#include "HttpConnClass.h"

#include <json/json.h>

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
	//서버에 점수 기록 업로드 후 OnOK 반환
	UpdateData(true);
	requestBody = "{\"name\" : \"" + std::string((CT2CA)m_userID) +
		"\", \"score\" : \"" + std::to_string(m_score) + "\"}";

	//연결 신청
	Json::Value response = HttpConnClass::jsonPostRequest(
		serverDomain, requestBody.c_str());

	//받은 메시지를 기반으로, 메시지박스 생성
	//정상적으로 전송됬을 경우
	if (response["message"].asString()== "Succesfully uploaded") {
		MessageBox(_T("정상적으로 전송되었습니다."), _T("성공"), MB_ICONINFORMATION);
	}
	//전송이 되지 않았을 경우
	else {
		MessageBox(_T("에러가 발생했습니다."), _T("에러 발생"), MB_ICONWARNING);
	}

	UpdateData(false);
	CDialogEx::OnOK();
}
