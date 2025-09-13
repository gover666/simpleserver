#include<HPSocket/HPSocket.h>
#include<iostream>
#include<string>
class Client :ITcpClientListener
{
public:
	Client()
		:m_client(this)
	{
		if (!m_client->Start("127.0.0.1", 65535, FALSE))
		{
			printf("connect to Server error:%s\n",m_client->GetLastErrorDesc());
		}
		std::string msg = "i'm client";
		m_client->Send((const BYTE *)msg.data(),msg.size());
	}
private:
	CTcpClientPtr m_client;

	EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		//��ȡ����
		for (size_t i = 0; i < iLength; i++)
		{
			putchar(pData[i]);
		}
		//������ԭ�����͸��ͻ���
		//pSender->Send(pData, iLength);
		return HR_IGNORE;
	}
	EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}
	EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override
	{
		printf("%s %llu\n", __FUNCTION__, dwConnID);
		return HR_IGNORE;
	}

	// ͨ�� ITcpClientListener �̳�
	EnHandleResult OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket) override
	{
		return EnHandleResult();
	}
	EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID) override
	{
		return EnHandleResult();
	}
};


int main()
{
	Client client;
	getchar();
	return 0;
}