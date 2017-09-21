#include <ws2tcpip.h>
#include <iostream>
#include <winsock2.h>
#define PORT 7770
#define SERVERADDR "127.0.0.1"
#include <colordlg.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <clocale>
#include <limits.h>
#include <crypto.cpp>


using namespace std;

SOCKET Connect;
char key[1024]="key";

char* rus(char* st)
{
    char* p = st;
    while( *p ){
        if(*p >= 192)
            if(*p <= 239)
                *p -= 64;
            else
                *p -= 16;
        p++;
    }
    return st;
}

void ReadMessageFromServer()
{
    char * buffer;
    for ( ; ; Sleep(75))
    {
        buffer = new char[1024];
        memset(buffer, 0, 1024);

        if (recv(Connect, buffer, 1024, 0))
        {
            deshifr(buffer,key);
            printf("%s",buffer);
        }
        for (int i = 0; buffer[i] != 0; i++) buffer[i] = '\0';
    }
}

void WriteMessageToServer(char *name)
{
    char * buffer;
    int namelen = 0;
    while(name[namelen]) namelen++;
    int b = namelen;
    char res[1024] = "";
    for ( ; ; Sleep(75))
    {
        buffer = new char[1024];
        memset(buffer, 0, 1024);
        fgets(buffer,1024, stdin);
        rus(buffer);
        if (!strcmp(&buffer[0],"quit\n"))
        {
            printf("Exit...");
            closesocket(Connect);
            WSACleanup();
            exit(0);
            break;
        }
        int bufferlen = 0;
        while(buffer[bufferlen]) bufferlen++;
        int count = 0;
        int count2 = 0;
        while(namelen!=0){
            res[count] = name[count];
            count++;
            namelen--;
        }
        while(bufferlen!=0){
            res[count] = buffer[count2];
            count++;
            count2++;
            bufferlen--;
        }
        shifr(res,key);
        send(Connect,res,1024,0);
        int clear = 0;
        while(res[clear]){
            res[clear] = 0;
            clear++;
        }
        int clear2 = 0;
        while(buffer[clear2]){
            res[clear2] = 0;
            clear2++;
        }
        namelen = b;
    }
}

int main()
{
    int i = 0, connlen = 0, res2len = 0, counter = 0, namelen = 0, pwdlen = 0, count = 0, count2 = 0;
    char buff[1024] = "", res2[1024] = "", name[1024] = "", pwd[1024] = "";
    char conn[1024] = "<----CONNECTED TO CHAT\n";
    printf("Chat client ver. 0.1\n");
    printf("\n\nlogin:");
    fgets(name,2000, stdin);
    printf("password:");
    for(i=0;(pwd[i] = getch()) != '\r';)   {
        if(pwd[i]=='\b' && i!=0) {
            printf("%s", "\b \b");
            i--;
        }
        else if(pwd[i]!='\b') {
            printf("%c", '*');
            i++;
        }
    }
    pwd[i] = '\n';
    i++;
    pwd[i] = '\0';
    printf("\n");
    rus(name);
    while(name[namelen])namelen++;
    while(pwd[pwdlen]) pwdlen++;
    while(namelen!=0){
        res2[count] = name[count];
        count++;
        namelen--;
    }
    while(pwdlen!=0){
        res2[count] = pwd[count2];
        count++;
        count2++;
        pwdlen--;
    }
    res2[count] = '\0';

    WSAData data;
    WORD version = MAKEWORD(2,2);
    int res = WSAStartup(version,&data);
    if(res!=0) {
        return 0;
    }
    Connect = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in hos_addr;
    hos_addr.sin_family=AF_INET;
    hos_addr.sin_port=htons(PORT);
    HOSTENT *hostt;
    //if (inet_addr(SERVERADDR)!=INADDR_NONE)
    //hos_addr.sin_addr.s_addr=inet_addr(SERVERADDR);
    //else
    if (hostt=gethostbyname(SERVERADDR)){
        ((unsigned long *)&hos_addr.sin_addr)[0]=((unsigned long **)hostt->h_addr_list)[0][0];
    }
    else
    {
        printf("Wrong adress %s\n",SERVERADDR);
        closesocket(Connect);
        WSACleanup();
        return -1;
    }
    if (connect(Connect,(sockaddr *)&hos_addr,sizeof(hos_addr)))
    {
        printf("Connect error %d\n",WSAGetLastError());
        return -1;
    }

    while(conn[connlen]) connlen++;
    while(res2[res2len]) res2len++;
    while(connlen > 0){
        res2[res2len++] = conn[counter++];
        connlen--;
    }
    res2[res2len] = '\0';
    shifr(res2,key);
    send(Connect,res2, 1024, 0);
    deshifr(res2,key);
    res2len = 0;
    while(res2[res2len]) res2len++;
    res2len = res2len - 23;
    res2[res2len] = '\0';
    for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
    printf("Connection on chat server: %s is stable\n\n",SERVERADDR);
    for(;;Sleep(75))
    {
        if(recv(Connect,buff, 1024,0) !=SOCKET_ERROR){
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReadMessageFromServer,0,0,0);
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)WriteMessageToServer,(LPVOID)res2,0,0);
            for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
        }
        else {
            break;
        }
    }
    for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
    for (int clear666 = 0; res2[clear666] != 0; clear666++) res2[clear666] = '\0';
    for (int clear666 = 0; conn[clear666] != 0; clear666++) conn[clear666] = '\0';
    for (int clear666 = 0; name[clear666] != 0; clear666++) name[clear666] = '\0';
    for (int clear666 = 0; pwd[clear666] != 0; clear666++) pwd[clear666] = '\0';
    i = 0, connlen = 0, res2len = 0, counter = 0, namelen = 0, pwdlen = 0, count = 0, count2 = 0;
    shutdown(Connect,2);
    closesocket(Connect);
    WSACleanup();
    printf("Exit...\n");
    return 1;
}
