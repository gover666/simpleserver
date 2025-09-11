#include <HPSocket/HPSocket4C.h>
#include<stdio.h>
En_HP_HandleResult onAccept(HP_Server pSender, HP_CONNID dwConnID, UINT_PTR pClient)
{
	printf("%s %llu\n", __FUNCTION__, dwConnID);
	return HR_IGNORE;
}
En_HP_HandleResult OnReceive(HP_Server pSender, HP_CONNID dwConnID, const BYTE* pData, int iLength)
{
	printf("%s %llu\n", __FUNCTION__, dwConnID);
	//��ȡ����
	for (size_t i = 0; i < iLength;i++)
	{
		putchar(pData[i]);
	}
	//������ԭ�����͸��ͻ���
	HP_Server_Send(pSender, dwConnID, pData, iLength);
	return HR_OK;
}
En_HP_HandleResult OnClose(HP_Server pSender, HP_CONNID dwConnID, En_HP_SocketOperation enOperation, int iErrorCode)
{
	printf("%s %llu\n", __FUNCTION__, dwConnID);
	return HR_IGNORE;
}
int main()
{
	//1.����һ����������
	HP_TcpServerListener listener = Create_HP_TcpServerListener();
	//2.����������
	HP_TcpServer tcpServer = Create_HP_TcpServer(listener);

	//����������ӻص�����
	HP_Set_FN_Server_OnAccept(listener, onAccept);
	HP_Set_FN_Server_OnReceive(listener,OnReceive);
	HP_Set_FN_Server_OnClose(listener,OnClose);

	//3.����������
	HP_Server_Start(tcpServer,"0.0.0.0",65535);

	//�����ó����˳�
	getchar();

	Destroy_HP_TcpServerListener(listener);
	Destroy_HP_TcpServer(tcpServer);
	return 0;
}