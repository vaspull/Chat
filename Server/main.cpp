#include <ws2tcpip.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sha512.h>
#include <time.h>
#include <ctype.h>
#define maxlenghlogin 10
#define minlenghlogin 6
#define maxlenghpwd 12
#define minlenghpwd 6
#define buffersize 50000
#define sleeptime 750
#define DEFPORT "7770"

const std::string key = "key";

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
    for(;;Sleep(sleeptime))
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
                res[i] = res[i]+key[a]+keydigit;
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
                res[i] = res[i]-key[a]-keydigit;
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

void parcer(std:: string buffer, std::string &name, std::string &pwd, std::string &res)
{
    if(!buffer.empty())
    {
        int isname = 1, ispwd = 1, istext = 1;
        unsigned int cur = 0;
        std::string text;
        for(unsigned int i = 0; i < strlen(buffer.c_str());)
        {
            if(buffer[i]=='\n' && isname)
            {
                for(unsigned int a = 0; a < i; a++)
                {
                    name += buffer[cur++];
                }
                isname = 0, cur++, i++;
            }
            else if(buffer[i]=='\n' && ispwd)
            {
                for(unsigned int a = 0; a < (i-strlen(name.c_str())-1); a++)
                {
                    pwd += buffer[cur++];
                }
                ispwd = 0, cur++,i++;
            }
            else if(buffer[i]=='\n' && istext)
            {
                for(unsigned int a = 0; a < (i-(strlen(name.c_str())+strlen(pwd.c_str()))-2); a++)
                {
                    text += buffer[cur++];
                }
                istext = 0, i++;
            }
            else
            {
                i++;
            }
        }
        if(!isname && !ispwd && !istext)
        {
            res = name + ':' + text + '\n';
        }
        else
        {
            res.clear();
            name.clear();
            pwd.clear();
        }
    }
}

int valid(std::string name, std::string pwd)
{
    std::string summHash = sha512(name+pwd);
    std::string string;
    bool isHave = 0;
    std::ifstream read("pwd.txt", std::ifstream::in);
    while(std::getline(read, string))
    {
        if(string == summHash && isHave == 0)
        {
            isHave = 1;
        }
    }
    read.close();
    return isHave;
}

void SendMessageToClient(struct my_struct *condata)
{
    int ID = condata->ID;
    std::string accden = "access denied, push enter to continue\n";
    crypt(accden,key);
    char accdenchar[strlen(accden.c_str())];
    for(unsigned int i = 0; i < strlen(accden.c_str());i++) accdenchar[i] = accden[i];
    char time[40] = "";
    for ( ; ; Sleep(sleeptime))
    {
        std::ofstream logs("logs.txt", std::ios_base::app);
        logs.close();
        char buffer[buffersize] ="";
        if (recv(condata->Connections[ID], buffer, sizeof(buffer), 0))
        {
            std::string name,pwd,res, buff = std::string(buffer);
            memset(buffer,0,sizeof(buffer));
            decrypt(buff,key);
            parcer(buff, name, pwd, res);
            if(!res.empty()&& valid(name,pwd))
            {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << ID << ":" << res;
                logs.close();
                crypt(res,key);
                char reschar[strlen(res.c_str())];
                for(unsigned int i = 0; i < strlen(res.c_str());i++) reschar[i] = res[i];
                for (int i = 0; i < condata->ClientCount; i++)
                {
                    if (i!=ID)
                    {
                        send(condata->Connections[i], reschar, sizeof(reschar), 0);
                    }
                }
                memset(reschar,0,sizeof(reschar));
            }

            else if(!valid(name,pwd))
            {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << ID << " : authorization attempt with name: "<< "|" << name << "|" << " and pwd:"<< "|" << pwd << "|" <<" <-- NO VALID!!!\n";
                logs.close();
                send(condata->Connections[ID],accdenchar, sizeof(accdenchar), 0);
                shutdown(condata->Connections[ID],2);
                closesocket(condata->Connections[ID]);
                break;
            }

            else if(connect(condata->Connections[ID],0,0) != SOCKET_ERROR)
            {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << ID << " <- DISCONNECT!\n";
                logs.close();
                shutdown(condata->Connections[ID],2);
                closesocket(condata->Connections[ID]);
                break;
            }
        }
        else
        {
            shutdown(condata->Connections[ID],2);
            closesocket(condata->Connections[ID]);
            break;
        }
    }
}

int main()
{
    struct my_struct condata;
    std::string accden = "access denied, push enter to continue\n";
    crypt(accden,key);
    SOCKET Connect;
    SOCKET Listen;
    char time[40] = "";
    std::ofstream logs("logs.txt", std::ios_base::app);
    logs.close();
    FILE* pwd = fopen("pwd.txt", "r");
    if (!pwd)
    {
        printf("File pwd.txt does not exist. Check paths.\n");
    }
    else
    {
        printf("Pwd file ok... ");
    }
    fclose(pwd);
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
    condata.Connections = (SOCKET*)calloc(64,sizeof(SOCKET));
    ZeroMemory(&hints,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    getaddrinfo(NULL,DEFPORT, &hints,&result);
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
    std::string m_connect = "online\n\n";
    crypt(m_connect,key);
    char m_connectchar[strlen(m_connect.c_str())];
    for(unsigned int i = 0; i < strlen(m_connect.c_str());i++) m_connectchar[i] = m_connect[i];
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)reguser,0,0,0);
    for(;;Sleep(75)) {
        if((Connect = accept(Listen,0,0)) != INVALID_SOCKET) {
            logs.open("logs.txt", std::ios_base::app);
            settime(time);
            logs << time;
            logs << ": Client id: " << condata.ClientCount << " connect...\n";
            logs.close();
            condata.Connections[condata.ClientCount] = Connect;
            char buffer[buffersize];
            std::string name,pwd,res;
            recv(condata.Connections[condata.ClientCount], buffer, sizeof(buffer), 0);
            std::string buff = std::string(buffer);
            decrypt(buff,key);
            parcer(buff, name, pwd, res);
            if(valid(name,pwd) == 0){
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << condata.ClientCount << " : authorization attempt with name: "<< "|" << name << "|" << " and pwd:"<< "|" << pwd << "|" <<" <-- NO VALID!!!\n";
                logs.close();
                char accdenchar[strlen(accden.c_str())];
                for(unsigned int i = 0; i < strlen(accden.c_str());i++) accdenchar[i] = accden[i];
                send(condata.Connections[condata.ClientCount],accdenchar, sizeof(accdenchar), 0);
                shutdown(condata.Connections[condata.ClientCount],2);
                closesocket(condata.Connections[condata.ClientCount]);
            }
            else {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << time;
                logs << ": client id: " << condata.ClientCount << " : authorization attempt with name: "<< "|" << name << "|" << " and pwd:"<< "|" << pwd << "|" <<" <---SUCCESS!!!\n";
                logs.close();
                crypt(res,key);
                char reschar[strlen(res.c_str())];
                for(unsigned int i = 0; i < strlen(res.c_str());i++) reschar[i] = res[i];
                for (int i = 0; i < condata.ClientCount; i++) send(condata.Connections[i], reschar, sizeof(reschar), 0);
                send(condata.Connections[condata.ClientCount],m_connectchar,sizeof(m_connectchar),0);
                condata.ID = condata.ClientCount;
                (condata.ClientCount)++;
                CreateThread(0,0,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)&condata,0,0);
            }
            memset(buffer,0,sizeof(buffer));
        }
    }
    return 1;
}
