#pragma once

// MultiPlaySocket 명령 대상

//for UDP
class MultiPlaySocket : public CAsyncSocket
{
private:
	CWnd* parent;		//saves parent window.

public:
	MultiPlaySocket(CWnd* parent);
	virtual ~MultiPlaySocket();

	//Event Handler
	void setParentWnd(CWnd* parent);

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};


