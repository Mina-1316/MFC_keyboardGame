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
	: CDialog(IDD_SINGLEPLAY_DIALOG, pParent)
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
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// SinglePlayDialog 메시지 처리기


BOOL SinglePlayDialog::OnInitDialog() //비행기 비트맵을 LOAD하는걸 잘 몰라서 우선은 TEXT로 출력을 하려고 한다. SinglePlayDialog 에  비행기의 x,y 좌표 초기 값을 설정.
                                      //OnInitDialog()를 추가했다.
{
	CDialog::OnInitDialog();

	airPlaneLocation.x = 600;
	airPlaneLocation.y = 720;

	std::random_device randDev;
	randEng.seed(randDev());

	SetTimer(0, timerTick, NULL);  //실행 후, 바로 타이머가 켜짐


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void SinglePlayDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI){
	// 창의 크기를 고정 시킴 - 최대로 늘어나는 범위, 최소로 줄어드는 범위 설정
	lpMMI->ptMinTrackSize = CPoint(dialogXSize, dialogYSize);
	lpMMI->ptMaxTrackSize = CPoint(dialogXSize, dialogYSize);


	CDialog::OnGetMinMaxInfo(lpMMI);
}

//싱글 게임 실행시SinglePlayDialog에 비행기 TEXT문자를 그리기 위해서 추가했다.
void SinglePlayDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	
}

void SinglePlayDialog::OnTimer(UINT_PTR nIDEvent){
	switch (nIDEvent) {
	case 0:
		//비행기 움직임을 처리하는 메소드
		processAirplane();
		//탄의 움직임을 처리하는 메소드
		processBullet();
		//장애물의 움직임을 처리하는 메소드
		processEnemy();
		//처리 완료 후, 화면을 그리는 메소드
		drawScene();
		timertick++;
		break;
	}

	CDialog::OnTimer(nIDEvent);
}


void SinglePlayDialog::processAirplane() //비행기 그리는 메소드
{
	//각 키의 입력 상태에 따라, 비행기 좌표를 조종함.
	if (isSPressed) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y + planeSpeed);
	if (isWPressed) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y - planeSpeed);
	if (isAPressed) airPlaneLocation.SetPoint(airPlaneLocation.x - planeSpeed, airPlaneLocation.y);
	if (isDPressed) airPlaneLocation.SetPoint(airPlaneLocation.x + planeSpeed, airPlaneLocation.y);
}

void SinglePlayDialog::processBullet() {	//총알의 이동을 제어하는 메소드

	//총알의 이동을 제어하는 람다식
	//해당 클래스에 상수로 정의된 탄의 속도만큼 y축 위로 전진한다(-한다)
	int bulletSpeed = this->bulletSpeed;
	auto doBulletMove = [bulletSpeed](CPoint& tgt) {
		tgt.SetPoint(tgt.x, tgt.y - bulletSpeed);
	};

	std::for_each(bulletList.begin(), bulletList.end(), doBulletMove);
}

void SinglePlayDialog::processEnemy() {
	//적을 생성하는 부분
	std::uniform_int_distribution<int> enemyGen(0, maxEnemyGen);	//생성하는 적 숫자를 설정하는 난수
	std::uniform_int_distribution<int> vectorGen((-1)*maxEnemySpeed, maxEnemySpeed); // 적의 속도를 생성하는 난수
	std::uniform_int_distribution<int> locationGen(10, dialogXSize - 10);	//적의 위치를 생성하는 난수

	int enemyGenNumber = enemyGen(randEng);
	for (int i = 0; i < enemyGenNumber; i++) 
	{
		//무작위 위치에 적을 생성해서, enemyList에 넣음
		enemyList.push_back(
			Enemy{CPoint(locationGen(randEng),-10), CPoint(vectorGen(randEng),std::abs(vectorGen(randEng))) 
			});
	}

	//벡터만큼 움직이는 적을 구현하는 람다 표현식
	auto doEnemyMove = [](Enemy& tgt) 
	{
		tgt.point.SetPoint(tgt.point.x + tgt.vector.x, tgt.point.y + tgt.vector.y); 
	};
	std::for_each(enemyList.begin(), enemyList.end(), doEnemyMove);

	//탄에 맞은 적을 삭제하는 람다 표현식
	const int enemySize = this->enemySize;
	for (auto bullet : bulletList) {
		//(x좌표차^2)+(y좌표차^2)가 실제 원 반지름 안쪽에 있는 경우, true를 반환하는 람다식
		auto checkDist = [bullet, enemySize](Enemy tgt) {
			return (pow(bullet.x - tgt.point.x, 2) + pow(bullet.y - tgt.point.y, 2)) < pow(enemySize, 2) ?
				true : false;
		};
		//checkDist 람다식을 기반으로, 일정 범위 안에 들어올 경우, 데이터를 삭제시킨다.
		std::remove_if(enemyList.begin(), enemyList.end(), checkDist);
	}

	//밖으로 나간 적을 삭제하는 람다 표현식
	const int dialogXSize = this->dialogXSize;
	const int dialogYSize = this->dialogYSize;
	auto deleteOutsideEnemy = [enemySize, dialogXSize, dialogYSize](Enemy tgt) {
			//x축 밖에 나갔는지 검사
		return (tgt.point.x<0-enemySize||tgt.point.x>dialogXSize+enemySize||
			//y축 아래로 내려갔는지 검사
			tgt.point.y>dialogYSize+enemySize)?	true : false;
	};
	//x축 좌/우 또는 y축 아래로 나간 것이 감지될 경우, 적을 삭제시킨다.
	std::remove_if(enemyList.begin(), enemyList.end(), deleteOutsideEnemy);
}

void SinglePlayDialog::drawScene() //모든것을 그리는 메소드
{
	Invalidate(true);

	//비행기 그리기
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_PLANE);
	CBitmap* oldbitmap = MemDC.SelectObject(&bitmap);
	dc.BitBlt(airPlaneLocation.x, airPlaneLocation.y , 100, 90, &MemDC, 10, 10, SRCCOPY);
	dc.SelectObject(oldbitmap);
	bitmap.DeleteObject();


	//원 그리기 , brush 사용
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush* oldbrush = dc.SelectObject(&brush);
	for (auto &enemy : enemyList) {
		dc.Ellipse(enemy.point.x - enemySize, enemy.point.y - enemySize, enemy.point.x +enemySize, enemy.point.y+ enemySize ); // enemy.point.x , y가 중심점
	}
	dc.SelectObject(&oldbrush);
	brush.DeleteObject();

	//탄 그리기 필요
	

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
