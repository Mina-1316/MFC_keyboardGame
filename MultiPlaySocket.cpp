// MultiPlaySocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_keyboardGame.h"
#include "MultiPlaySocket.h"
#include "MultiPlayDialog.h"
#include "NetworkSelectDialog.h"


// MultiPlaySocket

MultiPlaySocket::MultiPlaySocket()
{

}

MultiPlaySocket::~MultiPlaySocket()
{
}


// MultiPlaySocket 멤버 함수


void MultiPlaySocket::setParentWnd(NetworkHandler* parent)
{
	this->parent = parent;
}

void MultiPlaySocket::OnAccept(int nErrorCode)
{
	if(nErrorCode==0)
		((NetworkHandler*)parent)->OnAccept();
}


void MultiPlaySocket::OnClose(int nErrorCode)
{
	if (nErrorCode == 0)
		((NetworkHandler*)parent)->OnClose();
}


void MultiPlaySocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
		((NetworkHandler*)parent)->OnConnect();
}


void MultiPlaySocket::OnReceive(int nErrorCode)
{
    	if (nErrorCode == 0)
		((NetworkHandler*)parent)->OnReceive();
}


void MultiPlaySocket::OnSend(int nErrorCode)
{
	if (nErrorCode == 0)
		((NetworkHandler*)parent)->OnSend();
}
