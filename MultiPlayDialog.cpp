﻿#include "pch.h"
#include "MFC_keyboardGame.h"
#include "MultiPlayDialog.h"
#include "MultiPlaySocket.h"
#include "NetworkSelectDialog.h"

#include "Resource.h"

#include <json/json.h>

// MultiPlayDialog 대화 상자

IMPLEMENT_DYNAMIC(MultiPlayDialog, CDialog)

void MultiPlayDialog::processAirplane()
{
	//각 키의 입력 상태에 따라, 비행기 좌표를 조종함.
	if (isSPressed) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y + planeSpeed);
	if (isWPressed) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y - planeSpeed);
	if (isAPressed) airPlaneLocation.SetPoint(airPlaneLocation.x - planeSpeed, airPlaneLocation.y);
	if (isDPressed) airPlaneLocation.SetPoint(airPlaneLocation.x + planeSpeed, airPlaneLocation.y);

	//비행기가 맵 안에서만 움직이도록 구현 - 추가(수정) 필요
	if (airPlaneLocation.x > dialogXSize - airplaneXSize) airPlaneLocation.SetPoint(airPlaneLocation.x - planeSpeed, airPlaneLocation.y);
	if (airPlaneLocation.y > dialogYSize - airplaneYSize * 3 / 2) airPlaneLocation.SetPoint(airPlaneLocation.x, airPlaneLocation.y - planeSpeed); //dialogYSize - 62, 62대신 airplaneYSize 했는데 원하는 모양이 안나와서 임의로 설정했음
	// airplaneYSize*3/2 --> 이 숫자는 화면 밖으로 안 나가게 하는 숫자 입니다

	//비행기가 적과 충돌시 종료 된다. - 추가 필요

}

void MultiPlayDialog::processBullet()
{
	//총알의 이동을 제어하는 람다식
	//해당 클래스에 상수로 정의된 탄의 속도만큼 y축 위로 전진한다(-한다)
	int bulletSpeed = this->bulletSpeed;
	auto doBulletMove = [bulletSpeed](CPoint& tgt) {
		tgt.SetPoint(tgt.x, tgt.y - bulletSpeed);
	};
	std::for_each(bulletList.begin(), bulletList.end(), doBulletMove);


	//J버튼을 누르면 총알이 날아가는 코드
	if (isJPressed && bulletTimer <= 0)
	{
		//J를 누르는 순간의 비행기 좌표를 탄의 초기 좌표로 입력
		//좌표값을 doBulletMove의 인자로 넘겨준다
		bulletList.push_back(
			(CPoint(airPlaneLocation.x, airPlaneLocation.y)));

		bulletTimer = bulletFireRate;
	}
	else {
		bulletTimer--;
	}


	//총알이 맵 밖에 나갈 경우 제거하는 람다식
	const int dialogYSize = this->dialogYSize;
	auto deleteOutsideBullet = [dialogYSize](CPoint tgt) {
		//Y축 밖에 나갔는지 검사 , 현재 X축은 지정된 범위이상 넘어가지 않으므로 신경 안써도 괜찮다. , Y축에서 -10보다 작아질때 탄의 메모리를 삭제한다.
		return (tgt.y < -10) ? true : false;
	};
	//x축 좌/우 또는 y축 아래로 나간 것이 감지될 경우, 탄을 삭제시킨다.
	std::remove_if(bulletList.begin(), bulletList.end(), deleteOutsideBullet);
}

MultiPlayDialog::MultiPlayDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MultiPlayDialog, pParent)
{
	
}

MultiPlayDialog::~MultiPlayDialog()
{
}

void MultiPlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MultiPlayDialog, CDialog)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// MultiPlayDialog 메시지 처리기


void MultiPlayDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) { //각 키을 눌렀을때 true
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
		isJPressed = true;
		break;

	}

	Invalidate(TRUE);


	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}



void MultiPlayDialog::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
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



void MultiPlayDialog::OnTimer(UINT_PTR nIDEvent) { //Timer에서 외부에서 다시 선언할 수 없습니다. 라는 오류가 뜨고 있습니다.

	switch (nIDEvent) {
	case 0:
		//비행기 움직임을 처리하는 메소드
		processAirplane();

		//탄의 움직임을 처리하는 메소드
		processBullet();

		//처리 완료 후, 화면을 그리는 메소드

		Invalidate(TRUE);
		timerCount++;

		//100초가 지나가면 종료하는 메소드 추가

		break;
	}

	CDialog::OnTimer(nIDEvent);
}


void MultiPlayDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

   //비행기 그리기
	CClientDC cdc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&cdc);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_PLANE);
	CBitmap* oldbitmap = MemDC.SelectObject(&bitmap);
	cdc.BitBlt(airPlaneLocation.x - (airplaneXSize / 2), airPlaneLocation.y - (airplaneYSize / 2),
		airplaneXSize, airplaneYSize, &MemDC, 0, 0, SRCCOPY);
	cdc.SelectObject(oldbitmap);
	bitmap.DeleteObject();


	//탄 그리기 필요
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0)); //빨간색 원의 반지름 4 => 탄
	CBrush* oldbrush = cdc.SelectObject(&brush); //oldbrush 변수 중첩 수정
	for (auto bullet : bulletList) {
		cdc.Ellipse(bullet.x - bulletSize, bullet.y - bulletSize, bullet.x + bulletSize, bullet.y + bulletSize); // bullet.point.x , y가 중심점

	}
	cdc.SelectObject(&oldbrush);
	brush.DeleteObject();


}


BOOL MultiPlayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	//다이얼로그의 크기를 고정시킴
	MoveWindow(0, 0, dialogXSize, dialogYSize);

	airPlaneLocation.x = 600;
	airPlaneLocation.y = 720;

	SetTimer(0, timerTick, NULL);  //실행 후, 바로 타이머가 켜짐

	NetworkSelectDialog dialog;
	//dialog.setNetworkSocket(&serverSocket, &clientSocket);
	dialog.setNetworkSocket(&udpSocket);
	UpdateData(true);
	if (dialog.DoModal() != IDOK) {
		MessageBox(_T("통신이 취소되었습니다."), _T(""), MB_OK | MB_ICONWARNING);
		OnCancel();
	}
	serverSocket.setParentWnd(this);
	serverSocket.setParentWnd(this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



//소켓 이벤트 핸들러
void MultiPlayDialog::OnAccept()
{

}

void MultiPlayDialog::OnClose()
{

}

void MultiPlayDialog::OnConnect()
{

}

void MultiPlayDialog::OnReceive()
{
	
}

void MultiPlayDialog::OnSend() 
{
	
}