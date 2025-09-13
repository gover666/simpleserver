#include <HPSocket/HPSocket4C.h>
#include<stdio.h>
En_HP_HandleResult OnConnect(HP_Client pSender, HP_CONNID dwConnID)
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

	return HR_IGNORE;
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
	//2.创建客户端
	HP_Client client = Create_HP_TcpClient(listener);

	//给监听器添加回调函数
	HP_Set_FN_Client_OnConnect(listener, OnConnect);
	HP_Set_FN_Client_OnReceive(listener, OnReceive);
	HP_Set_FN_Client_OnClose(listener, OnClose);

	//3.开启服务器
	if (!HP_Client_Start(client, "127.0.0.1", 65535, FALSE))
	{
		printf("connet to Server error:%s\n", HP_Client_GetLastErrorDesc(client));
		return -1;
	}


	//给服务器发送消息
	const char* msg = "i'm Client";
	HP_Client_Send(client,(const BYTE *)msg,strlen(msg));

	//不能让程序退出
	getchar();

	Destroy_HP_TcpClientListener(listener);
	Destroy_HP_TcpClient(client);
	return 0;
}