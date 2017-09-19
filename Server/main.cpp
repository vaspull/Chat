#include <ws2tcpip.h>
#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string.h>

using namespace std;

SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;

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

    int g = 0;
    int c = 0;
    if(buffer[0]!='\0'){
        while(buffer[g] != '\n'){
            name[c] = buffer[g];
            g++;
            c++;
        }
        name[c]='\0';
        g++;
        c=0;
        while(buffer[g] != '\n'){
            pwd[c] = buffer[g];
            g++;
            c++;
        }
        pwd[c]='\0';
        g++;
        c=0;
        while(buffer[g]){
            text[c] = buffer[g];
            g++;
            c++;
        }
        text[c]='\0';
    }
    int namelen = 0;
    while(name[namelen]) namelen++;
    int textlen = 0;
    while(text[textlen]) textlen++;
    int count = 0;
    int count2 = 0;
    while(namelen!=0){
        res[count] = name[count];
        count++;
        namelen--;
    }
    res[count] = ':';
    count++;
    while(textlen!=0){
        res[count] = text[count2];
        count++;
        count2++;
        textlen--;
    }
}


void SendMessageToClient(int ID)
{
    for ( ; ; Sleep(750))
    {
        char buffer[1024] = "";
        for (int clear666 = 0; buffer[clear666] != 0; clear666++) buffer[clear666] = '\0';
        if (recv(Connections[ID], buffer, 1024, 0))
        {
            char buff[1024] = "";
            char res[1024] = "";
            char pwd[1024] = "";
            char name[1024] = "";
            char text[1024] = "";
            parce(buffer, name, pwd, text, res);
            if(res[0] != ':') {
                printf("client id %d: ", ID);
                printf("%s",res);
            }
            else {
            }
            if((valid(name,pwd) == 1) && (res[0] != ':')){
                for (int i = 0; i <= ClientCount; i++) //Отправка каждому подключенному клиенту
                {
                    if (i!=ID){
                        send(Connections[i], res, 1024, 0);
                    }
                    else {
                    }
                }
            }
            else {
                send(Connections[ID], "access denied, push enter to continue\n", 1024, 0);
                shutdown(Connections[ID],2);
                while(recv(Connections[ID], buff, 1024, 0)!=-1);
                closesocket(Connections[ID]);
            }
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
            int clear = 0;
            while(buffer[clear]) buffer[clear++] = '\0';
            clear = 0;
            while(name[clear]) name[clear++] = '\0';
            clear = 0;
            while(name[clear]) name[clear++] = '\0';
            clear = 0;
            while(name[clear]) name[clear++] = '\0';
            clear = 0;
            while(name[clear]) name[clear++] = '\0';
            clear = 0;
        }
        else {
            char buff[1024] = "";
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
            shutdown(Connections[ID],2);
            while(recv(Connections[ID], buff, 1024, 0)!=-1);
            closesocket(Connections[ID]);
        }
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

