#pragma once
#include "MultiPlaySocket.h"
#include "NetworkHandlerClass.h"

// NetworkSelectDialog 대화 상자

class NetworkSelectDialog : public CDialog, NetworkHandler
{
	DECLARE_DYNAMIC(NetworkSelectDialog)

public:
	NetworkSelectDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NetworkSelectDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNETCONN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//-----const------
	const int netPort = 11210;
	const int rBufSize = 1024;

	const int tcpPort = 11211;		//TCP소켓이 사용하는 포트, client는 +1

	//-----Variables-----
	CString ipInput;		//IP 주소

	//TCP
	//MultiPlaySocket* cSocket = nullptr;
	//MultiPlaySocket* sSocket = nullptr;		//소켓 포인터

	//UDP
	MultiPlaySocket* uSocket = nullptr;
	MultiPlaySocket sSocket = MultiPlaySocket(this);
	MultiPlaySocket cSocket = MultiPlaySocket(this);

	//-----Methods-----
	//TCP
	//void setNetworkSocket(MultiPlaySocket* uPtr, MultiPlaySocket* cPtr);
	//UDP
	void setNetworkSocket(MultiPlaySocket* sockPtr);

	virtual void OnReceive();
	virtual void OnConnect();
	virtual void OnAccept();

	afx_msg void OnBnClickedBserver();
	afx_msg void OnBnClickedBclient();
	afx_msg void OnBnClickedCancel();
};
