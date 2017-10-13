#include "mainwindow.h"


struct my_struct
{
    SOCKET Connect;
    std::string name;
    std::string pwd;
    int isConnected = 1;
    std::string str;
    std::string str2;
    int isShow = 1;
    char srv[20] = "";
    unsigned short prt;
}condata;

void crypt (std::string &res, const std::string key)
{
    int keydigit = 0, istruevalue = 1, isend = 1;
    std::string trash, itog;
    for(unsigned int i = 0; i <= strlen(res.c_str())*2; i++){
        trash += rand() % 127;
        for(;istruevalue;)
        {
            if(isalnum(trash[i]) == 0)
            {
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
            if(isalnum(trash[i]) == 0)
            {
                trash[i] = rand()%127;
            }
            else
            {
                istruevalue = 0;
            }
        }
        istruevalue = 1;
    }
    for(unsigned int a = 0, j = 0; a <= strlen(res.c_str()); )
    {
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
    for(unsigned int i = 2; i < strlen(res.c_str());)
    {
        itog += res[i];
        i += 3;
    }
    res.clear();
    res = itog;
    itog.clear();
}

MyWindow::MyWindow(QWidget *parent) : QDialog(parent)
{
    lbl = new QLabel("Список пользователей");
    lbl2 = new QLabel("Твой ник: ");
    lbl3 = new QLabel();
    lbl4 = new QLabel();
    line = new QLineEdit;
    conn = new QPushButton("Подключить");
    sendmessage =  new QPushButton("Отправить");
    options = new QPushButton("Настройки");
    edittext = new QTextEdit;
    edittext->setEnabled(false);
    edittext2 = new QTextEdit;
    edittext2->setEnabled(false);
    QHBoxLayout *upper = new QHBoxLayout;
    upper->addWidget(lbl2);
    upper->addWidget(lbl3);
    upper->addWidget(lbl4);
    QVBoxLayout *left = new QVBoxLayout;
    left->addLayout(upper);
    left->addWidget(edittext);
    left->addWidget(line);
    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(lbl);
    right->addWidget(edittext2);
    right->addWidget(options);
    right->addWidget(conn);
    right->addWidget(sendmessage);
    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);
    sendmessage->setDefault(true);
    sendmessage->setAutoDefault(true);
    sendmessage->setEnabled(false);
    setLayout(main);
    setWindowTitle("Чатик");
    edittext->setReadOnly(true);
    edittext2->setMaximumWidth(150);
    connect(conn,SIGNAL(clicked()),this,SLOT(con()));
    connect(sendmessage,SIGNAL(clicked()),this,SLOT(sen()));
    connect(options,SIGNAL(clicked(bool)),this,SLOT(opt()));
}

info::info(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Авторизация");
    lbl = new QLabel("Логин:");
    lbl2 = new QLabel("Пароль:");
    lbl3 = new QLabel("Сервер:");
    lbl4 = new QLabel("Порт:");
    line = new QLineEdit;
    line2 = new QLineEdit;
    line2->setEchoMode(QLineEdit::Password);
    line3 = new QLineEdit;
    line4 = new QLineEdit;
    ok =  new QPushButton("Ok");
    ok->setDefault(true);
    ok->setAutoDefault(true);
    closed = new QPushButton("Выход");
    save1 = new QPushButton("Записать учетные данные");
    save2 = new QPushButton("Записать данные сервера");
    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(lbl);
    left->addWidget(lbl2);
    left->addWidget(lbl3);
    left->addWidget(lbl4);
    left->addWidget(save1);
    left->addWidget(ok);
    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(line);
    right->addWidget(line2);
    right->addWidget(line3);
    right->addWidget(line4);
    right->addWidget(save2);
    right->addWidget(closed);
    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);
    setLayout(main);
    connect(closed,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ok,SIGNAL(clicked(bool)),this,SLOT(okey()));
    connect(save1,SIGNAL(clicked(bool)),this,SLOT(sav1()));
    connect(save2,SIGNAL(clicked(bool)),this,SLOT(sav2()));
    line->setText(QString::fromStdString(condata.name));
    line2->setText(QString::fromStdString(condata.pwd));
    std::ifstream readname("sec",std::ifstream::in);
    std::string finde,name,pwd,srv,port;
    for(;std::getline(readname,finde);)
    {
        if(name.empty())
        {
            name = finde;
        }
        else
        {
            pwd = finde;
        }
    }
    readname.close();
    decrypt(name,key2);
    decrypt(pwd,key2);
    if(!name.empty())
    {
        line->setText(QString::fromStdString(name));
    }
    if(!pwd.empty())
    {
        line2->setText(QString::fromStdString(pwd));
    }
    finde.clear(),name.clear(),pwd.clear();

    readname.open("conf.txt",std::ifstream::in);
    for(;std::getline(readname,finde);)
    {
        if(srv.empty())
        {
            srv = finde;
        }
        else
        {
            port = finde;
        }
    }
    if(!srv.empty())
    {
        line3->setText(QString::fromStdString(srv));
    }
    if(!port.empty())
    {
        line4->setText(QString::fromStdString(port));
    }
    readname.close();
    srv.clear(),port.clear(),finde.clear();

}

void info::sav1()
{
    std::string name = QString(line->text()).toStdString(), pwd = QString(line2->text()).toStdString();
    crypt(name,key2);
    crypt(pwd,key2);
    std::ofstream write("sec",std::ofstream::trunc);
    write << name << "\n" << pwd;
    write.close();
}

void info::sav2()
{
    std::ofstream write("conf.txt",std::ofstream::trunc);
    write << QString(line3->text()).toStdString() << '\n' << QString(line4->text()).toStdString();
    write.close();
}


void info::okey()
{
    condata.name = QString(line->text()).toStdString();
    condata.pwd = QString(line2->text()).toStdString();
    std::string srv = QString(line3->text()).toStdString();
    condata.prt = QString(line4->text()).toUShort();
    for(unsigned int i = 0; i < strlen(srv.c_str());i++)
    {
        condata.srv[i] = srv[i];
    }


    if(!condata.name.empty()&&!condata.pwd.empty())
    {
        info::close();
        emit getok();
    }    
}

void info::getinfo()
{
    this->show();
}

void MyWindow::opt()
{
    emit getinfosignal();
}

void startconnection(int &isConnect)
{
    isConnect = 0;
    WSAData data;
    WORD version = MAKEWORD(2,2);
    WSAStartup(version,&data);
    condata.Connect = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in hos_addr;
    hos_addr.sin_family=AF_INET;
    hos_addr.sin_port = htons(condata.prt);
    hos_addr.sin_addr.S_un.S_addr = inet_addr(condata.srv);
    if (connect(condata.Connect,(sockaddr *)&hos_addr,sizeof(hos_addr)) == SOCKET_ERROR)
    {
        printf("Connect error %d\n",WSAGetLastError());
        isConnect = 0;
    }
    else
    {
        printf("Connection on chat server: %s is stable\n\n",condata.srv);
        isConnect = 1;
    }
}

void ReadMessageFromServer()
{
    for ( ;!condata.isConnected; )
    {
        char buffer[buffersize] = "";
        if (recv(condata.Connect, buffer, sizeof(buffer), 0) != SOCKET_ERROR)
        {
            std::string buff = std::string(buffer);
            memset(buffer,0,sizeof(buffer));
            decrypt(buff,key);
            condata.str = buff;
        }
        else
        {
            condata.str = "server offline\n";
            send(condata.Connect,"gubabo", 10, 0);
            shutdown(condata.Connect,2);
            closesocket(condata.Connect);
            WSACleanup();
        }
    }
    send(condata.Connect,"gubabo", 10, 0);
    shutdown(condata.Connect,2);
    closesocket(condata.Connect);
    WSACleanup();
}

void MyWindow::sen()
{
    QString str1 = line->text();
    edittext->moveCursor(QTextCursor::End);
    edittext->textCursor().insertText("Ты:");
    edittext->textCursor().insertText(str1);
    edittext->textCursor().insertText("\n");
    line->setText("");
    std::string buff = QString(str1).toStdString();
    std::string strsend = condata.name+"\n"+condata.pwd+"\n"+buff+"\n";
    crypt(strsend,key);
    char sendchar[strlen(strsend.c_str())];
    for(unsigned int i = 0; i < strlen(strsend.c_str()); i++) sendchar[i] = strsend[i];
    send(condata.Connect, sendchar, sizeof(sendchar),0);
    memset(sendchar,0,sizeof(sendchar));
}


void MyWindow::read()
{
    if(condata.str!=condata.str2)
    {
        edittext->textCursor().insertText(QString::fromStdString(condata.str));
    }

    if(condata.str == "access denied, push enter to continue\n")
    {
        lbl4->setText("Доступ запрещен");
        lbl4->setStyleSheet("color: rgb(227,38,54)");
        send(condata.Connect,"gubabo", 10, 0);
        shutdown(condata.Connect,2);
        closesocket(condata.Connect);
        WSACleanup();
        conn->setText("Подключение");
        condata.isConnected = 1;
        sendmessage->setEnabled(false);
        edittext->setEnabled(false);
        edittext->clear();
        options->setEnabled(true);
        condata.Connect = 0;
        condata.isConnected = 1;
        condata.str = "";
        condata.str2 = "";
    }
    else if(condata.str == "server offline\n")
    {
        lbl4->setText("Сервер офлайн");
        lbl4->setStyleSheet("color: rgb(227,38,54)");
        send(condata.Connect,"gubabo", 10, 0);
        shutdown(condata.Connect,2);
        closesocket(condata.Connect);
        WSACleanup();
        conn->setText("Подключение");
        condata.isConnected = 1;
        sendmessage->setEnabled(false);
        edittext->setEnabled(false);
        edittext->clear();
        options->setEnabled(true);
        condata.Connect = 0;
        condata.isConnected = 1;
        condata.str = "";
        condata.str2 = "";
    }
    //else
    //{
    condata.str2 = condata.str;
    usleep(1000);
    if(!condata.isConnected)
    {
        QMetaObject::invokeMethod(this, "read", Qt::QueuedConnection);
    }
    //}
}

void MyWindow::con()
{
    int isConnect;
    if(condata.isShow)
    {
        this->show();
        condata.isShow = 0;
    }

    //    if(condata.name.empty() || condata.pwd.empty())
    //    {
    //        emit getinfosignal();
    //    }

    //    if (!condata.name.empty()&&!condata.pwd.empty())
    //    {
    if(condata.isConnected)
    {
        std::string conne = deffconn;
        std::string strsend = condata.name+"\n"+condata.pwd+"\n"+conne+"\n";
        startconnection(isConnect);
        if(isConnect)
        {
            condata.isConnected = 0;
            crypt(strsend,key);
            char strsendchar[strlen(strsend.c_str())];
            for(unsigned int i = 0; i < strlen(strsend.c_str()) ; i++) strsendchar[i] = strsend[i];
            send(condata.Connect,strsendchar, sizeof(strsendchar), 0);
            char buffer[buffersize] = "";
            recv(condata.Connect, buffer, sizeof(buffer), 0);
            std::string buff = std::string(buffer);
            memset(buffer,0,sizeof(buffer));
            decrypt(buff,key);
            condata.str = buff;
            if(buff=="access denied, push enter to continue\n")
            {
                buff.clear();
                edittext->setText("access denied");
                lbl3->setText("");
                lbl4->setText("Доступ запрещен");
                lbl4->setStyleSheet("color: rgb(227,38,54)");
                send(condata.Connect,"gubabo", 10, 0);
                shutdown(condata.Connect,2);
                closesocket(condata.Connect);
                WSACleanup();
                conn->setText("Подключение");
                sendmessage->setEnabled(false);
                edittext->setEnabled(false);
                edittext->clear();
                options->setEnabled(true);
                condata.Connect = 0;
                condata.isConnected = 1;
                condata.str = "";
                condata.str2 = "";
            }
            else
            {
                edittext->textCursor().insertText(QString::fromStdString(condata.str));
                condata.str2 = condata.str;
                CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReadMessageFromServer,0,0,0);
                memset(strsendchar, 0, sizeof(strsendchar));
                conn->setText("Отключение");
                edittext->setEnabled(true);
                sendmessage->setEnabled(true);
                options->setEnabled(false);
                lbl3->setText(QString::fromStdString(condata.name));
                lbl4->setText("Подключено");
                lbl4->setStyleSheet("color: rgb(141,182,0)");
                read();
            }
        }
        else
        {
            lbl4->setText("Ошибка подключения");
            lbl4->setStyleSheet("color: rgb(227,38,54)");
            send(condata.Connect,"gubabo", 10, 0);
            shutdown(condata.Connect,2);
            closesocket(condata.Connect);
            WSACleanup();
            conn->setText("Подключение");
            condata.isConnected = 1;
            sendmessage->setEnabled(false);
            edittext->setEnabled(false);
            edittext->clear();
            options->setEnabled(true);
        }
    }
    else
    {
        condata.isConnected = 1;
        send(condata.Connect,"gubabo", 10, 0);
        shutdown(condata.Connect,2);
        closesocket(condata.Connect);
        WSACleanup();
        condata.str="";
        condata.str2="";
        lbl4->setText("Отключено");
        lbl4->setStyleSheet("color: rgb(227,38,54)");
        conn->setText("Подключение");
        sendmessage->setEnabled(false);
        edittext->setEnabled(false);
        edittext->clear();
        options->setEnabled(true);
    }
}
//}





