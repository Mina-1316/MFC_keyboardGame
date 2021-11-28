// CPopup1.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "CPopup1.h"
#include "afxdialogex.h"


// CPopup1 대화 상자

IMPLEMENT_DYNAMIC(CPopup1, CDialog)

CPopup1::CPopup1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CPopup1::~CPopup1()
{
}

void CPopup1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopup1, CDialog)
END_MESSAGE_MAP()


// CPopup1 메시지 처리기
