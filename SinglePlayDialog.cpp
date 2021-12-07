// SinglePlayDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "SinglePlayDialog.h" //싱글 플레이 버튼을 눌렀을때 뜨는 창을 SinglePlayDialog으로 변경했음.
#include "afxdialogex.h"
#include "Resource.h"



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
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// SinglePlayDialog 메시지 처리기


BOOL SinglePlayDialog::OnInitDialog() //비행기 비트맵을 LOAD하는걸 잘 몰라서 우선은 TEXT로 출력을 하려고 한다. SinglePlayDialog 에  비행기의 x,y 좌표 초기 값을 설정.
                                      //OnInitDialog()를 추가했다.
{
	CDialog::OnInitDialog();

	airPlaneLocation.x = 100;
	airPlaneLocation.y = 100;

	std::random_device randDev;
	randEng.seed(randDev());

	SetTimer(0, timerTick, NULL);  //실행 후, 바로 타이머가 켜짐


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//싱글 게임 실행시SinglePlayDialog에 비행기 TEXT문자를 그리기 위해서 추가했다.
void SinglePlayDialog::OnPaint()  
{
	
}

//
void SinglePlayDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// 창의 크기를 고정 시킴 - 최대로 늘어나는 범위, 최소로 줄어드는 범위 설정
	lpMMI->ptMinTrackSize = CPoint(dialogXSize, dialogYSize);
	lpMMI->ptMaxTrackSize = CPoint(dialogXSize, dialogYSize);


	CDialog::OnGetMinMaxInfo(lpMMI);
}

void SinglePlayDialog::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent){
	case 0:

		Invalidate(TRUE);
		//비행기가 움직이는 메소드
		drawAirplane();
		//장애물을 그리는 메소드
		//drawEnemy();
		//탄이 발사 되는 메소드
		break;
	}

}

void SinglePlayDialog::drawAirplane() //비행기 그리는 메소드
{
	
	if (isSPressed) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y + 10);
	if (isWPressed) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y - 10);
	if (isAPressed) airPlaneLocation.SetPoint(airPlaneLocation.x-10, airPlaneLocation.y);
	if (isDPressed) airPlaneLocation.SetPoint(airPlaneLocation.x+10, airPlaneLocation.y);

	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_PLANE);
	CBitmap* oldbitmap = MemDC.SelectObject(&bitmap);
	
    dc.BitBlt(airPlaneLocation.x,airPlaneLocation.y, 100, 90, &MemDC, 0, 0, SRCCOPY);
		
	dc.SelectObject(oldbitmap);
	bitmap.DeleteObject();

}

void SinglePlayDialog::drawEnemy() {
	//적을 생성하는 부분
	std::uniform_int_distribution<int> enemyGen(0, maxEnemyGen);	//생성하는 적 숫자를 설정하는 난수
	std::uniform_int_distribution<int> vectorGen((-1)*maxEnemySpeed, maxEnemySpeed); // 적의 속도를 생성하는 난수

	for (int i = 0; i < enemyGen(randEng); i++) {
	}

	CClientDC dc(this);


}

void SinglePlayDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //키보드 방향키 WASD를 각각 아래로 눌렀을때 is*Pressed true 변경 , 각각 10정도 이동
{
	switch (nChar) {
	case 'S':
	case 's':
		isSPressed = true;
		break;

	case 'A':
	case 'a':
		isAPressed = true;
		break;

	case 'W':
	case 'w':
		isWPressed = true;
		break;

	case 'D':
	case 'd':
		isDPressed = true;
		break;

	case 'J':
	case 'j':
		isJPressed = false;
		break;

	}

	Invalidate(TRUE);
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void SinglePlayDialog::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) //키보드 방향키 WASD를 release할때 is*Pressed =  false 변경 
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case 'S':
	case 's':
		isSPressed = false;
		break;

	case 'A':
	case 'a':
		isAPressed = false;
		break;

	case 'W':
	case 'w':
		isWPressed = false;
		break;

	case 'D':
	case 'd':
		isDPressed = false;
		break;

	case 'J':
	case 'j':
		isJPressed = false;
		break;

		CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
	}
}



	
