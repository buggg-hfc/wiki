#include <stdio.h>
#include <winsock.h>

// Function prototype
void StreamClient(char *szServer, short nPort);

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
	// Check for the host and port arguments
	//
	if (argc != 3)//���˿����������� 
	{
		fprintf(stderr,"\nSyntax: client ServerName PortNumber\n");
		return 0;
	}

	nPort = atoi(argv[2]);


	//
	// Initialize WinSock and check the version
	//
	nRet = WSAStartup(wVersionRequested, &wsaData);//��ʼ��Winsock������һ��Winsocket��汾
	if (wsaData.wVersion != wVersionRequested)//���а汾��飬�汾����ͬ���֪�汾�д� 
	{	
		fprintf(stderr,"\n Wrong version\n");
		return 0;
	}


	//
	// Go do the stuff a stream client does
	//
	StreamClient(argv[1], nPort);
	
	//
	// Release WinSock
	//
	WSACleanup();//���ã�ΪӦ�ó��� ���·������Դ 
}

////////////////////////////////////////////////////////////

void StreamClient(char *szServer, short nPort)
{
	printf("\nStream Client connecting to server: %s on port: %d",
				szServer, nPort);

	//
	// Find the server
	//
    LPHOSTENT lpHostEntry;//��������IpHostEntry 

	lpHostEntry = gethostbyname(szServer);//��ȡserver 
    if (lpHostEntry == NULL)//û��ȡ��server�������Ӧ�Ĵ������� 
    {
        PRINTERROR("gethostbyname()");
        return;
    }

	//
	// Create a TCP/IP stream socket
	//
	SOCKET	theSocket;

	theSocket = socket(AF_INET,				// Address family����ʾIPV4 
					   SOCK_STREAM,			// Socket type������ʾ����TCP  
					   IPPROTO_TCP);		// Protocol��ָ��TCP 
	if (theSocket == INVALID_SOCKET)//�������Ч��socket���֪���� 
	{
		PRINTERROR("socket()");
		return;
	}

	//
	// Fill in the address structure
	//
	SOCKADDR_IN saServer;//�����ű��ص�ַ��Ϣ�Ľṹ�����

	saServer.sin_family = AF_INET;//sin_familyָ��Э���壬��ֵһ����AF_INET��ʾ����IPv4Э��
	saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);//��ӦIpHostEntry�ĵ�ַ 
										// ^ Server's address
	saServer.sin_port = htons(nPort);	// Port number from command line�����˿ںŸ���sin_port 

	//
	// connect to the server
	//
	int nRet;
//��sockSrv���ӵ��˿ڣ�nport��
	nRet = connect(theSocket,				// Socket
				   (LPSOCKADDR)&saServer,	// Server address
				   sizeof(struct sockaddr));// Length of server address structure
	if (nRet == SOCKET_ERROR)//��ʾ�������� 
	{
		PRINTERROR("socket()");
		closesocket(theSocket);
		return;
	}

	//
	// Send data to the server
	//
	char szBuf[256];

	strcpy(szBuf, "From the Client");//������Ϣ����buf 
	nRet = send(theSocket,				// Connected socket����������������� 
				szBuf,					// Data buffer
				strlen(szBuf),			// Length of data
				0);						// Flags
	if (nRet == SOCKET_ERROR)//��ʾ���ʹ������� 
	{
		PRINTERROR("send()");
		closesocket(theSocket);
		return;
	}

	//
	// Wait for a reply
	//
	nRet = recv(theSocket,				// Connected socket���ӷ������������� 
				szBuf,					// Receive buffer
				sizeof(szBuf),			// Size of receive buffer
				0);						// Flags
	if (nRet == SOCKET_ERROR)//��ʾ���մ������� 
	{
		PRINTERROR("recv()");
		closesocket(theSocket);
		return;
	}

	//
	// Display the received data
	//
	printf("\nData received: %s", szBuf);//����ӷ��������յ�������������� 


	closesocket(theSocket);//�����׽ӿ� 
	return;
}

