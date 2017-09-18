#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>


using namespace std;

SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;

int ClientCount = 0;

void SendMessageToClient(int ID)
{
    char * buffer;

    for ( ; ; Sleep(750))
    {
        buffer = new char[1024];
        memset(buffer, 0, sizeof(buffer)); //заполняет буфер символами "0"

        if (recv(Connections[ID], buffer, 1024, NULL))
        {
            printf("client id %d: ", ID);
            printf("%s",buffer);
            for (int i = 0; i <= ClientCount; i++) //Отправка каждому подключенному клиенту
            {
                if (i!=ID){
                send(Connections[i], buffer, strlen(buffer), NULL);
                }
                else {
                }
            }
        }
    }
    free(buffer);
}

int main()
{
    setlocale(LC_ALL, "russian");
    WSAData data;
    WORD version = MAKEWORD(2,2);
    int res = WSAStartup(version,&data);
    if(res!=0)
    {
        return 0;
    }

    struct addrinfo hints;
    struct addrinfo * result;


    Connections = (SOCKET*)calloc(64,sizeof(SOCKET));
    ZeroMemory(&hints,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo(NULL,"7770", &hints,&result);

    Listen = socket(result->ai_family, result->ai_socktype,result->ai_protocol);
    bind(Listen,result->ai_addr,result->ai_addrlen);
    listen(Listen,SOMAXCONN);

    freeaddrinfo(result);

    printf("Start server...\n");
    char m_connect[] = "asd";
    for(;;Sleep(75))
    {

        if(Connect = accept(Listen,NULL,NULL))
        {
            printf("Client id:%d connect...\n", ClientCount);
            Connections[ClientCount] = Connect;
            send(Connections[ClientCount],m_connect,strlen(m_connect),NULL);
            ClientCount++;
            CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)(ClientCount-1),NULL,NULL);
        }
    }

    return 1;
}
