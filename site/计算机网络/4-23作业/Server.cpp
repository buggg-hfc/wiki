#include <stdio.h>
#include <winsock.h>

// Function prototype
void StreamServer(short nPort);

// Helper macro for displaying errors
#define PRINTERROR(s)	\
		fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	WORD wVersionRequested = MAKEWORD(1,1);//�����޷���16λ������Ϊ�汾�ţ�ָ���±����ĸߵ��ֽڶ�Ϊ1 
	WSADATA wsaData;//����ṹ�����wsaData
	int nRet;
	short nPort;

	//
	// Check for port argument
	//
	if (argc != 2)//���˿ڲ��� 
	{
		fprintf(stderr,"\nSyntax: server PortNumber\n");
		return 0;
	}

	nPort = atoi(argv[1]);

	//
	// Initialize WinSock and check version
	//
	nRet = WSAStartup(wVersionRequested, &wsaData);//��ʼ��Winsock������һ��Winsocket��汾
	if (wsaData.wVersion != wVersionRequested)//���а汾��飬�汾����ͬ���֪�汾�д� 
	{	
		fprintf(stderr,"\n Wrong version\n");//����汾���� 
		return 0;
	}
	// Do the stuff a stream server does
	StreamServer(nPort);// 
	// Release WinSock
	//
	WSACleanup();//���ã�ΪӦ�ó��� ���·������Դ 
}


void StreamServer(short nPort)
{
	//
	// Create a TCP/IP stream socket to "listen" with
	//
	SOCKET	listenSocket;//����SOCKET����listenSocket 

	listenSocket = socket(AF_INET,			// Address family����ʾIPV4 
						  SOCK_STREAM,		// Socket type����ʾ����TCP 
						  IPPROTO_TCP);		// Protocol��ָ��TCP 
	if (listenSocket == INVALID_SOCKET)//�������Ч��socket���֪���� 
	{
		PRINTERROR("socket()");
		return;
	}

	//
	// Fill in the address structure
	//
	SOCKADDR_IN saServer;	//�����ű��ص�ַ��Ϣ�Ľṹ�����saServer	

	saServer.sin_family = AF_INET;//sin_familyָ��Э���壬��ֵһ����AF_INET��ʾ����IPv4Э��
	saServer.sin_addr.s_addr = INADDR_ANY;	// Let WinSock supply address����Ӧ���е�ַ 
	saServer.sin_port = htons(nPort);// Use port from command line�����˿ںŸ���sin_port 

	//
	// bind the name to the socket
	//
	int nRet;
//��sockSrv�󶨵��˿ڣ�nport�� 
	nRet = bind(listenSocket,				// Socket 
				(LPSOCKADDR)&saServer,		// Our address
				sizeof(struct sockaddr));	// Size of address structure
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("bind()");
		closesocket(listenSocket);
		return;
	}

	//
	// This isn't normally done or required, but in this 
	// example we're printing out where the server is waiting
	// so that you can connect the example client.
	//
	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuf[256];

	nRet = gethostname(szBuf, sizeof(szBuf));//��ȡ������ 
	if (nRet == SOCKET_ERROR)//��������ƥ�� 
	{
		PRINTERROR("gethostname()");
		closesocket(listenSocket);
		return;
	}

	//
	// Show the server name and port number
	//
	printf("\nServer named %s waiting on port %d\n",
			szBuf, nPort);//����Ļ�������������˿ں� 

	//
	// Set the socket to listen
	//

	printf("\nlisten()");
	nRet = listen(listenSocket,					// Bound socket
		  SOMAXCONN);					// Number of connection request queue
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("listen()");
		closesocket(listenSocket);
		return;
	}

	//
	// Wait for an incoming request
	//
	SOCKET	remoteSocket;

	printf("\nBlocking at accept()");
	remoteSocket = accept(listenSocket,			// Listening socket
						  NULL,					// Optional client address������һ���µ��׽�������ͨ�� 
						  NULL);
	if (remoteSocket == INVALID_SOCKET)
	{
		PRINTERROR("accept()");
		closesocket(listenSocket);
		return;
	}

	//
	// We're connected to a client
	// New socket descriptor returned already
	// has clients address

	//
	// Receive data from the client
	//
	memset(szBuf, 0, sizeof(szBuf));//szBuf��0 
	nRet = recv(remoteSocket,					// Connected client���ӿͻ��˽������� 
				szBuf,							// Receive buffer
				sizeof(szBuf),					// Lenght of buffer
				0);								// Flags
	if (nRet == INVALID_SOCKET)//��ʾ���մ������� 
	{
		PRINTERROR("recv()");
		closesocket(listenSocket);//�ر����� 
		closesocket(remoteSocket);//�رս��� 
		return;
	}

	//
	// Display received data
	//
	printf("\nData received: %s", szBuf);//���szBuf���� 
    //�ṩ����
	//
	// Send data back to the client
	//
	strcpy(szBuf, "From the Server");//������Ϣ����buf 
	nRet = send(remoteSocket,				// Connected socket����ͻ��˷������� 
				szBuf,						// Data buffer
				strlen(szBuf),				// Lenght of data
				0);							// Flags

	//
	// Close BOTH sockets before exiting
	//
	closesocket(remoteSocket);//�ر����� 
	closesocket(listenSocket);//�رս��� 
	return;
}



