#include<HPSocket/HPSocket.h>
#include<iostream>
class Server:ITcpServerListener
{
public:
	Server()
		:m_server(this)
	{
		m_server->Start("127.0.0.1", 65535);
	}
private:
	CTcpServerPtr m_server;

	// ͨ�� ITcpServerListener �̳�
	virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		//��ȡ����
		for (size_t i = 0; i < iLength; i++)
		{
			putchar(pData[i]);
		}
		//������ԭ�����͸��ͻ���
		pSender->Send(dwConnID, pData, iLength);
		return HR_IGNORE;
	}
	EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnShutdown(ITcpServer* pSender) override
	{
		printf("%s\n", __FUNCTION__);
		return HR_IGNORE;
	}
	EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen) override
	{
		printf("%s\n", __FUNCTION__);
		return HR_IGNORE;
	}
	EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
};

int main()
{
	Server server;
	getchar();
	return 0;
}