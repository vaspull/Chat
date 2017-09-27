#include <ws2tcpip.h>
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include <limits.h>
#include <ctype.h>

#define PORT 7770
#define SERVERADDR "127.0.0.1"

using namespace std;

SOCKET Connect;
char key[1024]="key";

void shifr (char *res, char *key)
{
    int reslen = 0, keylen = 0, keydigit = 0, trashlen = 0, itoglen = 0;
    char trash[100000]="", itog[100000]="";
    while(res[reslen]) reslen++;
    for(int i = 0; i <= (reslen*2); i++){
        trash[i] = rand() % 127;
        if(isalnum(trash[i]) == 0) {
            trash[i] = 63;
        }
        i++;
        trash[i] = rand() % 127;
        if(isalnum(trash[i]) == 0) {
            trash[i] = 63;
        }
    }
    trashlen = 0;
    while(trash[trashlen]) trashlen++;
    for(int i = 0, a = 0, j = 0; a < reslen; ){
        itog[i++] = trash[j++];
        itog[i++] = trash[j++];
        itog[i++] = res[a++];
    }
    while(itog[itoglen]) itoglen++;
    for(int i = 0; i < reslen; i++) res[i] = 0;
    for(int i = 0; i < itoglen; i++) res[i] = itog[i];
    while(key[keylen]) keylen++;
    reslen = 0;
    while(res[reslen]) reslen++;
    keydigit = reslen % 4;
    for (int i = 0; i < reslen;){
        for (int a = 0; a < keylen;a++){
            if(i<reslen){
                res[i] = res[i]+key[a]+keydigit;
                i++;
            }
            else{
                break;
            }
        }
    }
}

void deshifr (char *res, char *key)
{
    int reslen = 0, keylen = 0, keydigit = 0, itoglen = 0;
    char itog[100000]="";
    while(res[reslen]) reslen++;
    keydigit = reslen % 4;
    while(key[keylen]) keylen++;
    for (int i = 0; i < reslen;){
        for (int a = 0; a < keylen;a++){
            if(i<reslen){
                res[i] = res[i]-key[a]-keydigit;
                i++;
            }
            else{
                break;
            }
        }
    }
    for(int i = 0, a = 2; i < reslen; i++){
        itog[i] = res[a];
        a += 3;
    }
    while(itog[itoglen]) itoglen++;
    for(int i = 0; i < reslen; i++) res[i] = 0;
    for(int i = 0; i < itoglen; i++) res[i] = itog[i];
}

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
    for ( ; ; Sleep(75))
    {
        char buffer[50000] = "";
        for (int i = 0; buffer[i] != 0; i++) buffer[i] = '\0';
        if (recv(Connect, buffer, sizeof(buffer), 0)!= SOCKET_ERROR)
        {
            deshifr(buffer,key);
            printf("%s",buffer);
        }
        for (int i = 0; buffer[i] != 0; i++) buffer[i] = '\0';
    }
}

void WriteMessageToServer(char *name)
{
    int namelen = 0, reslen = 0, bufferlen = 0;
    while(name[namelen]) namelen++;
    int b = namelen;
    char res[50000] = "";
    for ( ; ; Sleep(75))
    {
        char buffer[50000] = "";
        for (int i = 0; buffer[i] != 0; i++) buffer[i] = '\0';
        fgets(buffer,sizeof(buffer), stdin);
        rus(buffer);
        if (!strcmp(&buffer[0],"quit\n"))
        {
            printf("Exit...");
            closesocket(Connect);
            WSACleanup();
            exit(0);
            break;
        }
        while(buffer[bufferlen]) bufferlen++;
        int count = 0;
        for(; count < namelen; count++)res[count] = name[count];
        for(int i = 0; i < bufferlen; i++) res[count++] = buffer[i];
        shifr(res,key);
        send(Connect,res,sizeof(res),0);
        while(res[reslen]) reslen++;
        for(int i = 0; i < reslen; i++) res[i] = '\0';
        for(int i = 0; i < bufferlen; i++) buffer[i] = '\0';
        namelen = b;
        reslen = b;
        bufferlen = b;
        for (int i = 0; buffer[i] != 0; i++) buffer[i] = '\0';
    }
}

int main()
{
    int i = 0, connlen = 0, res2len = 0, counter = 0, namelen = 0, pwdlen = 0, count = 0, count2 = 0;
    char buff[50000] = "", res2[1024] = "", name[1024] = "", pwd[1024] = "";
    char conn[1024] = "<----CONNECTED TO CHAT\n";
    printf("Chat client ver. 0.1\n");
    printf("\n\nlogin:");
    fgets(name,sizeof(name), stdin);
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
    send(Connect,res2, sizeof(res2), 0);
    deshifr(res2,key);
    res2len = 0;
    while(res2[res2len]) res2len++;
    res2len = res2len - 23;
    res2[res2len] = '\0';
    for(int i = (res2len+1); i < 23; i++) res2[i] = '\0';
    printf("Connection on chat server: %s is stable\n\n",SERVERADDR);
    for (int clear666 = 0; buff[clear666] != 0; clear666++) buff[clear666] = '\0';
    for (int clear666 = 0; conn[clear666] != 0; clear666++) conn[clear666] = '\0';
    for (int clear666 = 0; name[clear666] != 0; clear666++) name[clear666] = '\0';
    for (int clear666 = 0; pwd[clear666] != 0; clear666++) pwd[clear666] = '\0';
    for(;;Sleep(75))
    {
        if(recv(Connect,buff, sizeof(buff),0) !=SOCKET_ERROR){
            deshifr(buff,key);
            printf("%s",buff);
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
