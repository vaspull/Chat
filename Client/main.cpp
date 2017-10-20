#include <ws2tcpip.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#define maxlenghlogin 10
#define minlenghlogin 6
#define maxlenghpwd 12
#define minlenghpwd 6
#define sleeptime 300
#define buffersize 50000
#define PORT 7770
#define SERVERADDR "127.0.0.1"
#define pwdsize 1024
#define deffconn "<----CONNECTED TO CHAT"
const std::string key = "key";

void settime(char *t)
{
    struct tm *u;
    const time_t timer = time(NULL);
    u = localtime(&timer);
    for(unsigned int i = 0; i < strlen(t); i++) t[i] = 0;
    strftime(t, 40, "%d.%m.%Y %H:%M:%S", u);
}

struct my_struct
{
    SOCKET Connect;
    std::string name;
    std::string pwd;
};

void crypt (std::string &res, const std::string key)
{
    int keydigit = 0, istruevalue = 1, isend = 1;
    std::string trash, itog;
    for(unsigned int i = 0; i <= strlen(res.c_str())*2; i++){
        trash += rand() % 127;
        for(;istruevalue;)
        {
            if(isalnum(trash[i]) == 0) {
                trash[i] = rand()%127;
            }
            else
            {
                istruevalue = 0;
            }
        }
        istruevalue = 1;
        i++;
        trash += rand() % 127;
        for(;istruevalue;)
        {
            if(isalnum(trash[i]) == 0) {
                trash[i] = rand()%127;
            }
            else
            {
                istruevalue = 0;
            }
        }
        istruevalue = 1;
    }
    for(unsigned int a = 0, j = 0; a <= strlen(res.c_str()); ){
        itog += trash[j++];
        itog += trash[j++];
        itog += res[a++];
    }
    res.clear();
    res = itog;
    keydigit = strlen(res.c_str()) % 4;
    for (unsigned int i = 0; i < strlen(res.c_str());)
    {
        for (unsigned int a = 0; (a < strlen(key.c_str())) && isend;a++)
        {
            if(i<strlen(res.c_str()))
            {
                res[i] = res[i]+key[a]+keydigit-100;
                i++;
            }
            else
            {
                isend = 0;
            }
        }
        isend = 1;
    }
    itog.clear();
    trash.clear();
}

void decrypt (std::string &res, const std::string key)
{
    int keydigit = strlen(res.c_str()) % 4, isend = 1;;
    std::string itog;
    for (unsigned int i = 0; i < strlen(res.c_str());)
    {
        for (unsigned int a = 0; (a < strlen(key.c_str())) && isend;a++)
        {
            if( i < strlen(res.c_str()) )
            {
                res[i] = res[i]-key[a]-keydigit+100;
                i++;
            }
            else
            {
                isend = 0;
            }
        }
        isend = 1;
    }
    for(unsigned int i = 2; i < strlen(res.c_str());){
        itog += res[i];
        i += 3;
    }
    res.clear();
    res = itog;
    itog.clear();
}


std::string rus(std::string &st)
{
    for(unsigned int i = 0; i < st.length(); i++)
    {
        int a = st[i];
        if(a >= 192)
        {
            if(a<=239)
            {
                a -= 64;
            }
            else
            {
                a -=16;
            }
        }
    }
    return st;
}

void ReadMessageFromServer(struct my_struct *condata)
{
    for ( ; ; Sleep(sleeptime))
    {
        char buffer[buffersize] = "";
        if (recv(condata->Connect, buffer, sizeof(buffer), 0)!= SOCKET_ERROR)
        {
            std::string buff = std::string(buffer);
            memset(buffer,0,sizeof(buffer));
            decrypt(buff,key);
            std::cout << buff;
        }
    }
}

void WriteMessageToServer(struct my_struct *condata)
{
    for ( ; ; Sleep(sleeptime))
    {
        std::string buff, strsend;
        std::getline(std::cin,buff);
        rus(buff);
        if (!strcmp(&buff[0],"quit"))
        {
            printf("Exit...");
            closesocket(condata->Connect);
            WSACleanup();
            exit(0);
            break;
        }
        strsend = condata->name+"\n"+condata->pwd+"\n"+buff+"\n";
        crypt(strsend,key);
        char sendchar[strlen(strsend.c_str())];
        for(unsigned int i = 0; i < strlen(strsend.c_str()); i++) sendchar[i] = strsend[i];
        send(condata->Connect, sendchar, sizeof(sendchar),0);
        memset(sendchar,0,sizeof(sendchar));
    }
}

void getpwd(std::string &pwd)
{
    char pwdchar[pwdsize] = "";
    for(int i=0 ; (pwdchar[i] = getch()) != '\r'; )
    {
        if( pwdchar[i]=='\b' && i!=0 )
        {
            printf("%s", "\b \b");
            i--;
        }
        else if(pwdchar[i]!='\b')
        {
            printf("%c", '*');
            i++;
        }
    }
    pwdchar[strlen(pwdchar)-1] = '\0';
    pwd = std::string(pwdchar);
}

int main()
{
    struct my_struct condata;
    std::string conn = deffconn;
    std::string name, strpwd, strsend;
    printf("Chat client ver. 0.1\n");
    printf("\n\nlogin:");
    std::getline(std::cin, name);
    printf("password:");
    getpwd(strpwd);
    printf("\n");
    rus(name);
    WSAData data;
    WORD version = MAKEWORD(2,2);
    int res = WSAStartup(version,&data);
    if(res!=0)
    {
        return 0;
    }
    condata.Connect = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in hos_addr;
    hos_addr.sin_family=AF_INET;
    hos_addr.sin_port=htons(PORT);
    HOSTENT *hostt;
    //if (inet_addr(SERVERADDR)!=INADDR_NONE)
    //hos_addr.sin_addr.s_addr=inet_addr(SERVERADDR);
    //else
    hostt = gethostbyname(SERVERADDR);
    if (hostt){
        ((unsigned long *)&hos_addr.sin_addr)[0]=((unsigned long **)hostt->h_addr_list)[0][0];
    }
    else
    {
        printf("Wrong adress %s\n",SERVERADDR);
        closesocket(condata.Connect);
        WSACleanup();
        return -1;
    }
    if (connect(condata.Connect,(sockaddr *)&hos_addr,sizeof(hos_addr)))
    {
        printf("Connect error %d\n",WSAGetLastError());
        return -1;
    }
    strsend = name+"\n"+strpwd+"\n"+conn+"\n";
    crypt(strsend,key);
    char strsendchar[strlen(strsend.c_str())];
    for(unsigned int i = 0; i < strlen(strsend.c_str()) ; i++) strsendchar[i] = strsend[i];
    send(condata.Connect,strsendchar, sizeof(strsendchar), 0);
    memset(strsendchar, 0, sizeof(strsendchar));
    printf("Connection on chat server: %s is stable\n\n",SERVERADDR);
    condata.name = name;
    condata.pwd = strpwd;
    for(;;Sleep(sleeptime))
    {
        char buff[buffersize] = "";
        if(recv(condata.Connect,buff, sizeof(buff),0) !=SOCKET_ERROR){
            std::string buffer = std::string(buff);
            decrypt(buffer,key);
            std::cout << buffer;
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReadMessageFromServer,(LPVOID)&condata,0,0);
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)WriteMessageToServer,(LPVOID)&condata,0,0);
        }
        else
        {
            break;
        }
        memset(buff, 0, sizeof(buff));
    }
    shutdown(condata.Connect,2);
    closesocket(condata.Connect);
    WSACleanup();
    printf("Exit...\n");
    return 1;
}
