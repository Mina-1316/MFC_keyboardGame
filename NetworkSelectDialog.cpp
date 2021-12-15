// NetworkSelectDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "NetworkSelectDialog.h"
#include "afxdialogex.h"
#include "resource.h"
#include <string>


// NetworkSelectDialog 대화 상자

IMPLEMENT_DYNAMIC(NetworkSelectDialog, CDialog)

NetworkSelectDialog::NetworkSelectDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DNETCONN, pParent)
{

}

NetworkSelectDialog::~NetworkSelectDialog()
{
}

//TCP
void NetworkSelectDialog::setNetworkSocket(MultiPlaySocket* sPtr, MultiPlaySocket* cPtr) {
	cSocket = cPtr;
	sSocket = sPtr;

	cSocket->setParentWnd((NetworkHandler*)this);
	sSocket->setParentWnd((NetworkHandler*)this);
}

//UDP
//void NetworkSelectDialog::setNetworkSocket(MultiPlaySocket* sockPtr) {
//	uSocket = sockPtr;
//}

void NetworkSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IPIN, ipInput);
}


BEGIN_MESSAGE_MAP(NetworkSelectDialog, CDialog)
	ON_BN_CLICKED(IDC_BCONNECT, &NetworkSelectDialog::OnBnClickedBconnect)
	ON_BN_CLICKED(IDCANCEL, &NetworkSelectDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BHOST, &NetworkSelectDialog::OnBnClickedBhost)
END_MESSAGE_MAP()


// NetworkSelectDialog 메시지 처리기


void NetworkSelectDialog::OnBnClickedBconnect()
{
	GetDlgItem(IDC_EDIT_IPIN)->EnableWindow(false);
	GetDlgItem(IDC_BHOST)->EnableWindow(false);
	GetDlgItem(IDC_BCONNECT)->EnableWindow(false);
	isServer = false;
	
	UpdateData(true);
	cSocket->Create(clientPort);
	cSocket->Connect(ipInput, servPort);
	UpdateData(false);
}

void NetworkSelectDialog::OnBnClickedBhost()
{
	GetDlgItem(IDC_EDIT_IPIN)->EnableWindow(false);
	GetDlgItem(IDC_BHOST)->EnableWindow(false);
	GetDlgItem(IDC_BCONNECT)->EnableWindow(false);
	isServer = true;

	sSocket->Create(servPort);
	sSocket->Listen();
}

void NetworkSelectDialog::OnReceive() 
{
	
}

void NetworkSelectDialog::OnConnect()
{
	OnOK();
}

void NetworkSelectDialog::OnAccept()
{
	sSocket->Accept(*cSocket);
	OnOK();
}

void NetworkSelectDialog::OnBnClickedCancel()
{
	OnCancel();
}


