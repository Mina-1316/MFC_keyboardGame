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

	airplane_X = 0;
	airplane_Y = 0;
}

SinglePlayDialog::~SinglePlayDialog()
{
}

void SinglePlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SinglePlayDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// SinglePlayDialog 메시지 처리기


BOOL SinglePlayDialog::OnInitDialog() //비행기 비트맵을 LOAD하는걸 잘 몰라서 우선은 TEXT로 출력을 하려고 한다. SinglePlayDialog 에  비행기의 x,y 좌표 초기 값을 설정.
                                      //OnInitDialog()를 추가했다.
{
	CDialog::OnInitDialog();

	airplane_X = 300;
	airplane_Y = 300;


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SinglePlayDialog::OnPaint()  //싱글 게임 실행시SinglePlayDialog에 비행기 TEXT문자를 그리기 위해서 추가했다.
{
	CPaintDC dc(this);
	dc.TextOutW(airplane_X, airplane_Y, _T("비행기 그림")); //X,Y좌표에 원래는 비트맵을 나타내야 하지만 현재 비트맵을 LOAD하는 방법을 모르겠다.
}


void SinglePlayDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //키보드 방향키 WASD를 각각 아래로 눌렀을때 비행기가 움직이기 위해서 추가했다.
{
	switch (nChar) {
	case 'S':
	case 's':
		airplane_Y += 10;
		break;

	case 'A':
	case 'a':
		airplane_X -= 10;
		break;

	case 'W':
	case 'w':
		airplane_Y -= 10;
		break;

	case 'D':
	case 'd':
		airplane_X += 10;
		break;
	}

	Invalidate(TRUE);
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
