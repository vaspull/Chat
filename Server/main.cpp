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
#define sleeptime 200
#define DEFPORT "7770"

const std::string key = "key";

class Elemlist                          //We describe a class list of the elements of the structure Elem
{
private:
    struct Elem                         //Describe the structure of a linked list
    {
        std::string data;                    //The information includes a list item
        Elem* next;                     //Pointer to the next element
        Elem* prev;                     //A pointer to the previous element
    };
    int counter;                        //Counter items
    Elem* first;                        //Pointer to the first element of the list
    Elem* last;                         //Pointer to the last item in the list
public:
    Elemlist()
    {
        counter = 0;
        first = NULL;
        last = NULL;
    }

    void add(std::string d)                   //A method of adding a new item to the list
    {
        Elem *newelem = new Elem;        //Memory allocation for the new element
        newelem -> data = d;             //We set the value of data to the new structure element
        newelem -> next = NULL;          //Assigning a pointer to the next element to NULL
        counter++;                       //Increase the value of the counter elements
        if ( first == NULL )             //Checking if the list is empty - a new element of the structure will be the first and last at the same time, the previous will be NULL
        {
            first = newelem;
            newelem -> prev = NULL;
            last=first;
        }
        else
        {
            newelem -> prev = last;      //A pointer to the previous element, for the new element will be the previous recently added
            last -> next = newelem;      //A pointer to the next element appearing after the last existing element that is the one that is now adding
            last = newelem;              //A new element becomes the last in the list
        }
    }

    void del(int v)                     //Removal of any element
    {
        if ( counter == 0 )             //If the list is empty, then display a message indicating an empty list
        {
        }
        else if ( ( v > counter ) || ( v < 1 ) ) //If the number is more than the element to remove all items in the list or negative, then an error message
        {
        }
        else if ( ( v == 1 ) and ( first -> next ) ) //If the first element is removed, but the list of more than 1 item
        {
            Elem *delelem = first;
            first = first -> next;
            first -> prev = NULL;
            delete delelem;
            counter--;
        }
        else if ( ( v == 1 ) and ( first == last ) ) //If you delete the first and only item
        {
            first -> next = NULL;
            first -> prev=NULL;
            first = NULL;
            last = NULL;
            delete first;
            counter--;
        }
        else if ( (v == counter) )                 //If you delete the last item
        {
            Elem *delelem = last;
            last = last -> prev;
            last -> next = NULL;
            delete delelem;
            counter--;
        }
        else                                       //Remove item from the middle of the list
        {
            Elem *delelem = first;
            Elem *delelem2;
            for ( int i = 1 ; i < v ; i++ ) delelem = delelem -> next;
            delelem2 = delelem;
            delelem2 -> prev -> next = delelem -> next; //Indicates that the next item to the fact that it is facing a removable element which is removed after
            delelem2 -> next -> prev = delelem -> prev; //Point out that the previous element for what is to be removed after an element that stands in front of removable
            delete delelem;
            counter--;
        }
    }

    void vivod()
    {
        Elem *info = first;
        while(info)
        {
            std::cout << info->data << std::endl;
            info = info -> next;
        }
    }

    void sss(std::string name,int &i)
    {
        Elem *info = first;
        for(i=1;info&&info->data!=name;i++)
        {
            info = info -> next;
        }
    }

    void result(std::string &result)
    {
        result.clear();
        Elem *info = first;
        while(info)
        {
            result += info->data + '\n';
            info = info -> next;
        }

    }
};

struct my_struct
{
    SOCKET* Connections;
    int ClientCount = 0;
    int ID = 0;
    Elemlist m;
    std::string name;
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
            res = name + ": " + text + '\n';
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
    std::string name2 = condata->name;
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
        if (recv((condata->Connections)[ID], buffer, sizeof(buffer), 0))
        {
            std::string name,pwd,res, buff = std::string(buffer);
            memset(buffer,0,sizeof(buffer));
            decrypt(buff,key);
            parcer(buff, name, pwd, res);
            buff.clear();
            if(!res.empty() && valid(name,pwd))
            {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << "[" << time << "] client id " << ID << ":" << res;
                logs.close();
                std::string itog = "["+std::string(time)+"] "+ res;
                crypt(itog,key);
                char reschar[strlen(itog.c_str())];
                for(unsigned int i = 0; i < strlen(itog.c_str());i++) reschar[i] = itog[i];
                itog.clear();
                res.clear();
                name.clear();
                pwd.clear();
                for (int i = 0; i < condata->ClientCount; i++)
                {
                    //if (i!=ID)
                    //{
                    send((condata->Connections)[i], reschar, sizeof(reschar), 0);
                    //}
                }
                memset(reschar,0,sizeof(reschar));
            }
            else if(connect(condata->Connections[ID],0,0))
            {

                logs.open("logs.txt", std::ios_base::app);
                settime(time);

                std::string skobka = "[";
                std::string diss = skobka + time + "] "  + name2 + " <- DISCONNECT!\n";
                crypt(diss,key);
                char disschar[strlen(diss.c_str())];
                for(unsigned int i = 0; i < strlen(diss.c_str());i++) disschar[i] = diss[i];
                for (int i = 0; i < condata->ClientCount; i++)
                    if (i!=ID)
                    {
                        send(condata->Connections[i],disschar,sizeof(disschar),0);
                    }
                memset(disschar,0,sizeof(disschar));
                diss.clear();
                logs << "[" << time << "] client id " << ID << " name " << name2 <<" <- DISCONNECT!\n";
                logs.close();
                Sleep(200);
                int cou;
                condata->m.sss(name2,cou);
                condata->m.del(cou);
                std::string result;
                condata->m.result(result);
                crypt(result,key);
                char resultchar[strlen(result.c_str())];
                for(unsigned int i = 0; i < strlen(result.c_str());i++) resultchar[i] = result[i];
                for (int i = 0; i < condata->ClientCount; i++) send(condata->Connections[i],resultchar,sizeof(resultchar),0);
                memset(resultchar,0,sizeof(resultchar));
                //setsockopt(condata->Connections[ID],SOL_SOCKET,SO_LINGER,0,0);
                shutdown((condata->Connections)[ID],2);
                closesocket((condata->Connections)[ID]);
                condata->Connections[ID] = '\0';
                break;
            }

            else if(!valid(name,pwd))
            {
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << "[" << time <<"] client id " << ID << " : authorization attempt with name: "<< "|" << name << "|" << " and pwd:"<< "|" << pwd << "|" <<" <-- NO VALID!!!\n";
                logs.close();
                send((condata->Connections)[ID],accdenchar, sizeof(accdenchar), 0);
                shutdown((condata->Connections)[ID],2);
                closesocket((condata->Connections)[ID]);
                condata->Connections[ID] = '\0';
                break;
            }

        }
        else
        {
            shutdown(condata->Connections[ID],2);
            closesocket(condata->Connections[ID]);
            condata->Connections[ID] = '\0';
            break;
        }
    }
}

void forkeepalive(struct my_struct *condata)
{
    for(;;Sleep(300000))
    {
            std::string result;
            condata->m.result(result);
            crypt(result,key);
            Sleep(200);
            char resultchar[strlen(result.c_str())];
            for(unsigned int i = 0; i < strlen(result.c_str());i++) resultchar[i] = result[i];
            for (int i = 0; i <= condata->ClientCount; i++) send(condata->Connections[i],resultchar,sizeof(resultchar),0);
            memset(resultchar,0,sizeof(resultchar));
    }
}


int main()
{
    std::string q;
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
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)reguser,0,0,0);
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)forkeepalive,(LPVOID)&condata,0,0);
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
            setsockopt(condata.Connections[condata.ClientCount],SOL_SOCKET,SO_KEEPALIVE,0,0);
            recv(condata.Connections[condata.ClientCount], buffer, sizeof(buffer), 0);
            std::string buff = std::string(buffer);
            memset(buffer,0,buffersize);
            decrypt(buff,key);
            parcer(buff, name, pwd, res);
            if(valid(name,pwd) == 0){
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << "[" << time << "] client id " << condata.ClientCount << " : authorization attempt with name: "<< "|" << name << "|" << " and pwd:"<< "|" << pwd << "|" <<" <-- NO VALID!!!\n";
                logs.close();
                char accdenchar[strlen(accden.c_str())];
                for(unsigned int i = 0; i < strlen(accden.c_str());i++) accdenchar[i] = accden[i];
                send(condata.Connections[condata.ClientCount],accdenchar, sizeof(accdenchar), 0);
                shutdown(condata.Connections[condata.ClientCount],2);
                closesocket(condata.Connections[condata.ClientCount]);
                condata.Connections[condata.ClientCount] = '\0';
            }
            else {
                condata.name = name;
                condata.m.add(name);
                logs.open("logs.txt", std::ios_base::app);
                settime(time);
                logs << "[" << time << "] client id " << condata.ClientCount << " : authorization attempt with name: "<< "|" << name << "|" << " and pwd:"<< "|" << pwd << "|" <<" <---SUCCESS!!!\n";
                logs.close();
                Sleep(200);
                std::string itog = "["+std::string(time)+"] "+ res;
                crypt(itog,key);
                char itogchar[strlen(itog.c_str())];
                for(unsigned int i = 0; i < strlen(itog.c_str());i++) itogchar[i] = itog[i];
                itog.clear();
                for (int i = 0; i < condata.ClientCount; i++) send(condata.Connections[i], itogchar, sizeof(itogchar), 0);
                memset(itogchar,0,sizeof(itogchar));
                Sleep(200);
                char m_connectchar[strlen(m_connect.c_str())];
                for(unsigned int i = 0; i < strlen(m_connect.c_str());i++) m_connectchar[i] = m_connect[i];
                send(condata.Connections[condata.ClientCount],m_connectchar,sizeof(m_connectchar),0);
                memset(m_connectchar,0,sizeof(m_connectchar));
                std::string result;
                condata.m.result(result);
                crypt(result,key);
                Sleep(200);
                char resultchar[strlen(result.c_str())];
                for(unsigned int i = 0; i < strlen(result.c_str());i++) resultchar[i] = result[i];
                for (int i = 0; i <= condata.ClientCount; i++) send(condata.Connections[i],resultchar,sizeof(resultchar),0);
                memset(resultchar,0,sizeof(resultchar));
                Sleep(20);
                condata.ID = condata.ClientCount;
                condata.ClientCount++;
                CreateThread(0,0,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)&condata,0,0);
            }
            buff.clear();
            name.clear();
            pwd.clear();
            res.clear();
        }
    }
    return 1;
}
