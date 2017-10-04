#include <ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sha512.h>
#define maxlenghlogin 10
#define minlenghlogin 6
#define maxlenghpwd 12
#define minlenghpwd 6
#define keysize 1024

const char key[keysize] = "key";

struct my_struct
{
    SOCKET* Connections;
    int ClientCount = 0;
    int ID;
};

void settime(char *t)
{
    struct tm *u;
    const time_t timer = time(NULL);
    u = localtime(&timer);
    for(unsigned int i = 0; i < strlen(t); i++) t[i] = 0;
    strftime(t, 40, "%d.%m.%Y %H:%M:%S", u);
}

void reguser()
{
    printf("User registration program\n\n");
    std::ifstream read;
    std::ofstream write;
    for(;;Sleep(50))
    {
        int isTruePwdLengh = 1, isTrueLoginLengh = 1, isExist = 1;
        std::string login, pwd, hash, summ, findeExistUser, isAgain, copy;
        for(;isTrueLoginLengh;) //check for the length of the entered login
        {
            printf("\nLogin:");
            std::getline(std::cin,login);
            if (strlen(login.c_str()) > maxlenghlogin)
            {
                printf("You have exceeded the maximum value for login. The maximum value %d, try again...\n", maxlenghlogin);
            }
            else if (strlen(login.c_str()) < minlenghlogin)
            {
                printf("You entered too short a login. The minimum value %d, try again...\n", minlenghlogin);
            }
            else
            {
                isTrueLoginLengh = 0;
            }
        }
        for(;isTruePwdLengh;) //check for the length of the entered password
        {
            printf("Password:");
            std::getline(std::cin,pwd);
            if (strlen(pwd.c_str()) > maxlenghpwd)
            {
                printf("You have exceeded the maximum value for password. The maximum value %d, try again...\n", maxlenghpwd);
            }
            else if (strlen(pwd.c_str()) < minlenghpwd)
            {
                printf("You entered too short a password. The minimum value %d, try again...\n", minlenghpwd);
            }
            else
            {
                isTruePwdLengh = 0;
            }
        }
        summ = login + pwd;
        hash = sha512(summ);
        read.open("pwd.txt", std::ifstream::in);//search in pwd.txt, there may already exist such a record
        for(;getline(read,findeExistUser) && isExist != 0;)
        {
            if ( findeExistUser == hash )
            {
                read.close();
                isExist = 0;
                std::cout << "\nThe user " << "|" << login << "|" << " is already created, enter 'y' if you want to change his data:";
                std::getline(std::cin,isAgain);
            }
        }
        read.close();
        if(isExist) //if the entry does not exist, then pwd.txt is opened and a new hash is written
        {
            write.open("pwd.txt", std::ofstream::app);
            write << hash << "\n";
            write.close();
            std::cout << "\nUser data:\nLogin:" << "|" << login << "|" << "\nPassword:" << "|" << pwd << "|" << "\nHash:" << "|" << hash << "|" << std::endl;
        }

        isTruePwdLengh = 1, isTrueLoginLengh = 1, isExist = 1;

        if(isAgain == "y" || isAgain == "Y") // if the selection is selected to update the user data, then overwrite the pwd.txt file
        {
            read.open("pwd.txt", std::ifstream::in);//Open the pwd.txt file and the temp.txt file to copy from pwd to temp all the data except those that need to be changed
            write.open("temp.txt", std::ofstream::trunc);
            for(;getline(read,copy);)
            {
                if( hash != copy)
                {
                    write << copy << "\n";
                }
            }
            read.close();
            write.close();
            read.open("temp.txt", std::ifstream::in); //the pwd and temp files are reopened to re-write back from temp to pwd
            write.open("pwd.txt", std::ofstream::out);
            for(;getline(read,copy);)
            {
                write << copy << "\n";
            }
            read.close();
            write.close();
            for(;isTrueLoginLengh;)
            {
                printf("\nEnter new data\nLogin:");
                std::getline(std::cin,login);
                if (strlen(login.c_str()) > maxlenghlogin)
                {
                    printf("You have exceeded the maximum value for login. The maximum value %d, try again...\n", maxlenghlogin);
                }
                else
                {
                    isTrueLoginLengh = 0;
                }
            }
            for(;isTruePwdLengh;)
            {
                printf("Password:");
                std::getline(std::cin,pwd);
                if (strlen(pwd.c_str()) > maxlenghpwd)
                {
                    printf("You have exceeded the maximum value for password. The maximum value %d, try again...\n", maxlenghpwd);
                }
                else
                {
                    isTruePwdLengh = 0;
                }
            }
            summ = login + pwd;
            hash = sha512(summ);
            write.open("pwd.txt", std::ofstream::app); //write changed data to pwd.txt
            write << hash << "\n";
            write.close();
            isTruePwdLengh = 1, isTrueLoginLengh = 1, isExist = 1;
            write.open("temp.txt", std::ofstream::trunc); //cleaning temp.txt
            write.close();
            std::cout << "\nUpdated user data:\nLogin:" << "|" << login << "|" << "\nPassword:" << "|" << pwd << "|" << "\nHash:" << "|" << hash << "|" << std::endl;
        }
    }
}

void shifr (char *res, const char *key)
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

void deshifr (char *res, const char *key)
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

int valid(char *name, char *pwd)
{
    std::string needString =  std::string(name) + std::string(pwd);
    std::string summHash = sha512(needString);
    std::string string;
    bool isHave = 0;
    std::ifstream ifstream1("pwd.txt");
    while( std::getline( ifstream1, string ) )
        if( string == summHash ){
            isHave = 1;
            break;
        }
    ifstream1.close();
    return isHave;
}


char parce(char *buffer, char *name, char *pwd, char *text, char *res)
{
    int g = 0, c = 0, namelen = 0, textlen = 0, count = 0, parce = 0;
    if(buffer[0]!='\0'){
        parce = 1;
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
    return parce;
}

void SendMessageToClient(struct my_struct *condata)
{
    int ID = condata->ID;
    char accden[1024] = "access denied, push enter to continue\n";
    char time[40] = "";
    for ( ; ; Sleep(750))
    {
        std::ofstream logs("logs.txt", std::ios_base::app);
        logs.close();
        char buffer[50000] = "";
        for (int clear666 = 0; buffer[clear666] != 0; clear666++) buffer[clear666] = '\0';
        if (recv(condata->Connections[ID], buffer, sizeof(buffer), 0)){
            char res[50000] = "";
            char pwd[1024] = "";
            char name[1024] = "";
            char text[50000] = "";
            deshifr(buffer,key);
            parce(buffer, name, pwd, text, res);
            if((valid(name,pwd) == 0) && connect(condata->Connections[ID],0,0) != SOCKET_ERROR){
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << ID << " : authorization attempt with name: " << name <<" <-- NO VALID!!!\n";
                logs.close();
                shifr(accden,key);
                send(condata->Connections[ID],accden, sizeof(accden), 0);
                deshifr(accden,key);
                shutdown(condata->Connections[ID],2);
                closesocket(condata->Connections[ID]);
                memset(buffer, 0, sizeof(buffer));
                memset(res, 0, sizeof(res));
                memset(pwd, 0, sizeof(pwd));
                memset(name, 0, sizeof(name));
                memset(text, 0, sizeof(text));
                break;
            }
            else if(res[0] != '\0'){
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << ID << ":" << res;
                logs.close();
                shifr(res,key);
                for (int i = 0; i < condata->ClientCount; i++)
                {
                     if (i!=ID){
                          send(condata->Connections[i], res, sizeof(res), 0);
                    }
                }
            }
            else {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << ID << " <- DISCONNECT!\n";
                logs.close();
                shifr(accden,key);
                send(condata->Connections[ID],accden, sizeof(accden), 0);
                deshifr(accden,key);
                shutdown(condata->Connections[ID],2);
                closesocket(condata->Connections[ID]);
                memset(buffer, 0, sizeof(buffer));
                memset(res, 0, sizeof(res));
                memset(pwd, 0, sizeof(pwd));
                memset(name, 0, sizeof(name));
                memset(text, 0, sizeof(text));
                break;
            }
            memset(buffer, 0, sizeof(buffer));
            memset(res, 0, sizeof(res));
            memset(pwd, 0, sizeof(pwd));
            memset(name, 0, sizeof(name));
            memset(text, 0, sizeof(text));
        }
        else {
            shutdown(condata->Connections[ID],2);
            closesocket(condata->Connections[ID]);
            memset(buffer, 0, sizeof(buffer));
            break;
        }
    }
}

int main()
{
    struct my_struct condata;
    char accden[1024] = "access denied, push enter to continue\n";
    shifr(accden, key);
    SOCKET Connect;
    SOCKET Listen;
    char time[40] = "";
    std::ofstream logs("logs.txt", std::ios_base::app);
    logs.close();
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
    condata.Connections = (SOCKET*)calloc(64,sizeof(SOCKET));
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
    logs.open("logs.txt", std::ios_base::app);
    settime(time);
    logs << time;
    logs << ": Start server...\n";
    logs.close();
    char m_connect[] = "online\n\n";
    shifr(m_connect,key);
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)reguser,0,0,0);
    for(;;Sleep(75)) {
        if((Connect = accept(Listen,0,0)) != INVALID_SOCKET) {
            logs.open("logs.txt", std::ios_base::app);
            settime(time);
            logs << time;
            logs << ": Client id: " << condata.ClientCount << " connect...\n";
            logs.close();
            condata.Connections[condata.ClientCount] = Connect;
            char buffer[50000], res[50000], pwd[1024], name[1024], text[50000];
            recv(condata.Connections[condata.ClientCount], buffer, sizeof(buffer), 0);
            deshifr(buffer,key);
            parce(buffer, name, pwd, text, res);
            if(valid(name,pwd) == 0){
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << condata.ClientCount << " : authorization attempt with name: " << name <<" <-- NO VALID!!!\n";
                logs.close();
                send(condata.Connections[condata.ClientCount],accden, sizeof(accden), 0);
                shutdown(condata.Connections[condata.ClientCount],2);
                closesocket(condata.Connections[condata.ClientCount]);
            }
            else {
                shifr(res,key);
                for (int i = 0; i < condata.ClientCount; i++) send(condata.Connections[i], res, sizeof(res), 0);
                send(condata.Connections[condata.ClientCount],m_connect,strlen(m_connect),0);
                condata.ID = condata.ClientCount;
                (condata.ClientCount)++;
                CreateThread(0,0,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)&condata,0,0);
            }
            memset(buffer, 0, sizeof(buffer));
            memset(res, 0, sizeof(res));
            memset(pwd, 0, sizeof(pwd));
            memset(name, 0, sizeof(name));
            memset(text, 0, sizeof(text));
        }
    }
    return 1;
}
