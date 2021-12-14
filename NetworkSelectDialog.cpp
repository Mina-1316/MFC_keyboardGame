// NetworkSelectDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "NetworkSelectDialog.h"
#include "afxdialogex.h"
#include <string>


// NetworkSelectDialog 대화 상자

IMPLEMENT_DYNAMIC(NetworkSelectDialog, CDialog)

NetworkSelectDialog::NetworkSelectDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNETCONN, pParent)
	, ipInput(_T(""))
{

}

NetworkSelectDialog::~NetworkSelectDialog()
{
}

//TCP
//void NetworkSelectDialog::setNetworkSocket(MultiPlaySocket* sPtr, MultiPlaySocket* cPtr) {
//	cSocket = cPtr;
//	sSocket = sPtr;
//
//	cSocket->setParentWnd(this);
//	sSocket->setParentWnd(this);
//}

//UDP
void NetworkSelectDialog::setNetworkSocket(MultiPlaySocket* sockPtr) {
	uSocket = sockPtr;
}

void NetworkSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IPIN, ipInput);
}


BEGIN_MESSAGE_MAP(NetworkSelectDialog, CDialog)
	ON_BN_CLICKED(IDC_BSERVER, &NetworkSelectDialog::OnBnClickedBserver)
	ON_BN_CLICKED(IDC_BCLIENT, &NetworkSelectDialog::OnBnClickedBclient)
	ON_BN_CLICKED(IDCANCEL, &NetworkSelectDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// NetworkSelectDialog 메시지 처리기


void NetworkSelectDialog::OnBnClickedBserver()
{
	//TCP
	/*sSocket->Create(netPort);
	sSocket->Listen();*/

	//UDP
	uSocket->Create(netPort, SOCK_DGRAM);

	GetDlgItem(IDC_BSERVER)->EnableWindow(false);
	GetDlgItem(IDC_BCLIENT)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_IPIN)->EnableWindow(false);

	sSocket.Create(tcpPort);
	sSocket.Listen();
}


void NetworkSelectDialog::OnBnClickedBclient()
{
	//TCP
	/*cSocket->Create(netPort);
	cSocket->Connect(ipInput, netPort + 1);*/


	//UDP
	//TCP 연결을 실행 후, 클라이언트 정보 제공 및 동기화, UDP로 변환
	uSocket->Create(netPort, SOCK_DGRAM);
	UpdateData(true);
	cSocket.Create(tcpPort + 1);
	cSocket.Connect(ipInput, tcpPort);

	
}

void NetworkSelectDialog::OnReceive() {
	
	
	//TCP
	


	/*UDP
	CString ip;
	UINT port;
	char* rBuf = new char[rBufSize];
	int rcvdLength = cSocket->Receive(rBuf, rBufSize - 1);
	if (rcvdLength != -1) {
		rBuf[rcvdLength + 1] = NULL;
		if (strcmp(rBuf, "handshake") == 0) {			//1번 handshake
			const char* msg = "handshake2";
			int msgLen = strlen(msg);
			cSocket->SendTo(msg, msgLen, netPort, ipInput);
			OnOK();
		}
		else if (strcmp(rBuf, "handshake2") == 0) {		//2번 handshake
			OnOK();
		}
		else {											//Ip 정보를 받아오고 handshake 전송
			ipInput = rBuf;
			const char* msg = "handshake";
			int msgLen = strlen(msg);
			cSocket->SendTo(msg, msgLen, netPort, ipInput);
		}
	}*/

}

void NetworkSelectDialog::OnConnect()
{
	CString peerName;
	UINT port;

	cSocket.GetPeerName(peerName, port);
	peerName = ipInput;
	
	OnOK();
}

void NetworkSelectDialog::OnAccept()
{
	sSocket.Accept(cSocket);
	CString peerName;
	UINT port;

	cSocket.GetPeerName(peerName, port);
	peerName = ipInput;

	OnOK();
}

void NetworkSelectDialog::OnBnClickedCancel()
{
	OnCancel();
}

