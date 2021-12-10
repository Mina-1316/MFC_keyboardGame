// LeaderboardDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "LeaderboardDialog.h"
#include "afxdialogex.h"
#include "HttpConnClass.h"


// LeaderboardDialog 대화 상자

IMPLEMENT_DYNAMIC(LeaderboardDialog, CDialog)


LeaderboardDialog::LeaderboardDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_LEADERBOARD, pParent)
{

}

BOOL LeaderboardDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//서버와의 통신 - Json

	try {
		//get response from server as JSON
		response = HttpConnClass::jsonPostRequest(serverDomain, requestBody);
	}
	//Exception handle - When error occured
	catch(HttpConnException e){
		MessageBox(CString::CStringT(CA2CT(e.causeLoc.c_str())), _T("Server Error!"), MB_ICONWARNING);
		OnCancel();
	}

	Invalidate(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void LeaderboardDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	CClientDC cdc(this);
	//배경색을 투명하게 함
	cdc.SetBkMode(TRANSPARENT);

	//응답받은 데이터의 배열 길이 또는, 지정한 최대 길이에 도달할 경우 중지
	for (int i = 0; i < maxLeaderboardAmount || i < response.size(); i++) {
		//for 문의 진행에 따라 그려지는 Y축이 증가한다.
		cdc.TextOut(drawXPoint, drawYPoint + (drawVertGap * i), 
			CString::CStringT(CA2CT(response[i]["name"].asCString())));
		cdc.TextOut(drawXPoint + drawHorizonGap, drawYPoint + (drawVertGap * i),
			CString::CStringT(CA2CT(response[i]["score"].asCString())));
	}
	
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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// LeaderboardDialog 메시지 처리기

void LeaderboardDialog::OnBnClickedOk()
{
	CDialog::OnOK();
}


