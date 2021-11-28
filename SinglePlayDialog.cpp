// SinglePlayDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "SinglePlayDialog.h" //싱글 플레이 버튼을 눌렀을때 뜨는 창을 SinglePlayDialog으로 변경했음.
#include "afxdialogex.h"


// SinglePlayDialog 대화 상자

IMPLEMENT_DYNAMIC(SinglePlayDialog, CDialog)

SinglePlayDialog::SinglePlayDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

SinglePlayDialog::~SinglePlayDialog()
{
}

void SinglePlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SinglePlayDialog, CDialog)
END_MESSAGE_MAP()


// SinglePlayDialog 메시지 처리기
