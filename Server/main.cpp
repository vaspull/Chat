#include <ws2tcpip.h>
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string.h>
#include <crypto.cpp>

using namespace std;

SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;
char key[1024] = "key";
char accden[1024] = "access denied, push enter to continue\n";
int ClientCount = 0;

int valid(char *name, char *pwd)
{
    string strName = string(name);
    string strPwd = string(pwd);
    std::string needString =  strName + strPwd;
    std::string string;
    bool isHave = 0;
    std::ifstream ifstream1("pwd.txt");
    while( std::getline( ifstream1, string ) )
        if( string == needString ){
            isHave = 1;
            break;
        }
    ifstream1.close();
    return isHave;
}

void parce(char (&buffer)[1024], char (&name)[1024], char (&pwd)[1024], char (&text)[1024], char (&res)[1024])
{
    int g = 0, c = 0, namelen = 0, textlen = 0, count = 0;
    if(buffer[0]!='\0'){
        while(buffer[g] != '\n') name[c++] = buffer[g++];
        name[c]='\0';
        g++;
        c=0;
        while(buffer[g] != '\n')pwd[c++] = buffer[g++];
        pwd[c]='\0';
        g++;
        c=0;
        while(buffer[g])text[c++] = buffer[g++];
        text[c]='\0';
        while(name[namelen]) namelen++;
        while(text[textlen]) textlen++;
        for(int i = 0; i < namelen; i++, count++) res[count] = name[count];
        res[count++] = ':';
        for(int i = 0; i < textlen; i++, count++) res[count] = text[i];
    }
}


void SendMessageToClient(int ID)
{
    for ( ; ; Sleep(750))
    {
        char buffer[1024] = "";
        for (int clear666 = 0; buffer[clear666] != 0; clear666++) buffer[clear666] = '\0';
        if (recv(Connections[ID], buffer, 1024, 0)){
            char buff[1024] = "";
            char res[1024] = "";
            char pwd[1024] = "";
            char name[1024] = "";
            char text[1024] = "";
            deshifr(buffer,key);
            parce(buffer, name, pwd, text, res);
            if(valid(name,pwd) == 0){
                printf("client id %d: <- NO VALID!!!\n", ID);
                shifr(accden,key);
                send(Connections[ID],accden, 1024, 0);
                deshifr(accden,key);
                shutdown(Connections[ID],2);
                while(recv(Connections[ID], buff, 1024, 0)!=-1);
                closesocket(Connections[ID]);
                //ClientCount--;
                break;
            }
            else if(res[0] != '\0'){
                printf("client id %d: ", ID);
                printf("client id %d: \n", ClientCount);
                printf("%s",res);
                for (int i = 0; i < ClientCount; i++) //Отправка каждому подключенному клиенту
                {
                    if ((i!=ID) && (Connections[i]!=SOCKET_ERROR)){
                        shifr(res,key);
                        send(Connections[i], res, 1024, 0);
                        deshifr(res,key);
                    }
                    else {
                    }
                }
                for (int clear666 = 0; res[clear666] != 0; clear666++) res[clear666] = '\0';
            }
            else {
                printf("client id %d: <- DISCONNECT!\n", ID);
                shifr(accden,key);
                send(Connections[ID],accden, 1024, 0);
                deshifr(accden,key);
                shutdown(Connections[ID],2);
                while(recv(Connections[ID], buff, 1024, 0)!=-1);
                closesocket(Connections[ID]);
                //ClientCount--;
                break;
            }
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
            for (int clear666 = 0; name[clear666] != 0; clear666++) name[clear666] = '\0';
            for (int clear666 = 0; text[clear666] != 0; clear666++) text[clear666] = '\0';
            for (int clear666 = 0; res[clear666] != 0; clear666++) res[clear666] = '\0';
            for (int clear666 = 0; pwd[clear666] != 0; clear666++) pwd[clear666] = '\0';
        }
        else {
            char buff[1024] = "";
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
            shutdown(Connections[ID],2);
            while(recv(Connections[ID], buff, 1024, 0)!=-1);
            closesocket(Connections[ID]);
            break;
        }
        for (int clear666 = 0; buffer[clear666] != 0; clear666++) buffer[clear666] = '\0';
    }
}

int main()
{
    FILE* pwd = fopen("pwd.txt", "r");
    if (!pwd) {
        printf("File pwd.txt does not exist. Check paths.\n");
    }
    else {
        printf("Pwd file ok... ");
    }
    fclose(pwd);
    setlocale(LC_ALL, "russian");
    WSAData data;
    WORD version = MAKEWORD(2,2);
    int res = WSAStartup(version,&data);
    if(res!=0)  {
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
    for(;;Sleep(75)) {
        if((Connect = accept(Listen,0,0)) != SOCKET_ERROR) {
            printf("Client id:%d connect...\n", ClientCount);
            Connections[ClientCount] = Connect;
            send(Connections[ClientCount],m_connect,strlen(m_connect),0);
            ClientCount++;
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)(ClientCount-1),0,0);
        }
    }
    return 1;
}
