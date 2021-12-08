// LeaderboardDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "LeaderboardDialog.h"
#include "afxdialogex.h"


// LeaderboardDialog 대화 상자

IMPLEMENT_DYNAMIC(LeaderboardDialog, CDialog)

LeaderboardDialog::LeaderboardDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_LEADERBOARD, pParent)
{

}

BOOL LeaderboardDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


LeaderboardDialog::~LeaderboardDialog()
{
}

void LeaderboardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LeaderboardDialog, CDialog)
	ON_BN_CLICKED(IDOK, &LeaderboardDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// LeaderboardDialog 메시지 처리기

void LeaderboardDialog::OnBnClickedOk()
{
	CDialog::OnOK();
}


