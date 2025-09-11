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
	//读取数据
	for (size_t i = 0; i < iLength;i++)
	{
		putchar(pData[i]);
	}
	//把数据原样发送给客户端
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
	//1.创建一个监听对象
	HP_TcpServerListener listener = Create_HP_TcpServerListener();
	//2.创建服务器
	HP_TcpServer tcpServer = Create_HP_TcpServer(listener);

	//给监听器添加回调函数
	HP_Set_FN_Server_OnAccept(listener, onAccept);
	HP_Set_FN_Server_OnReceive(listener,OnReceive);
	HP_Set_FN_Server_OnClose(listener,OnClose);

	//3.开启服务器
	HP_Server_Start(tcpServer,"0.0.0.0",65535);

	//不能让程序退出
	getchar();

	Destroy_HP_TcpServerListener(listener);
	Destroy_HP_TcpServer(tcpServer);
	return 0;
}