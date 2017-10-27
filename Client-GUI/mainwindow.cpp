#include "mainwindow.h"
#include "ui_mainwindow.h"

struct my_struct
{
    SOCKET Connect;
    std::string name;
    std::string pwd;
    int isConnected = 1;
    std::string str;
    std::string str2;
    int isShow = 1;
    int isCheck = 0;
    int isCheck2 = 0;
    char srv[20] = "";
    unsigned short prt;
    std::string name_privat;
    int isupdate = 1;
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
    for(unsigned int i = 2; i < strlen(res.c_str());)
    {
        itog += res[i];
        i += 3;
    }
    res.clear();
    res = itog;
    itog.clear();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Чатик");
    this -> setTrayIconActions();
    this -> showTrayIcon();
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    trayIcon->setToolTip("Chat Client GUI" "\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

info::info(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowTitle("Авторизация");
    name_label = new QLabel("Логин:");
    pwd_label = new QLabel("Пароль:");
    srvaddr_label = new QLabel("Сервер:");
    srvport_label = new QLabel("Порт:");
    name_line = new QLineEdit;
    pwd_line = new QLineEdit;
    pwd_line->setEchoMode(QLineEdit::Password);
    srvaddr_line = new QLineEdit;
    srvport_line = new QLineEdit;
    check_box_tray = new QCheckBox("Сворачивать в трей");
    check_box_notice = new QCheckBox("Отключить уведомления");
    ok_button =  new QPushButton("Ok");
    ok_button->setDefault(true);
    ok_button->setAutoDefault(true);
    close_button = new QPushButton("Выход");
    save_name_pwd_button = new QPushButton("Записать учетные данные");
    save_programm_options = new QPushButton("Сохранить настройки");
    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(name_label);
    left->addWidget(pwd_label);
    left->addWidget(srvaddr_label);
    left->addWidget(srvport_label);
    left->addWidget(save_name_pwd_button);
    left->addWidget(ok_button);
    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(name_line);
    right->addWidget(pwd_line);
    right->addWidget(srvaddr_line);
    right->addWidget(srvport_line);
    right->addWidget(save_programm_options);
    right->addWidget(close_button);
    QHBoxLayout *main1 = new QHBoxLayout;
    main1->addLayout(left);
    main1->addLayout(right);
    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(main1);
    main->addWidget(check_box_tray);
    main->addWidget(check_box_notice);
    setLayout(main);
    connect(close_button,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(on_ok_button_clicked()));
    connect(save_name_pwd_button,SIGNAL(clicked(bool)),this,SLOT(on_save_name_pwd_button_clicked()));
    connect(save_programm_options,SIGNAL(clicked(bool)),this,SLOT(on_save_programm_options_button_clicked()));
    name_line->setText(QString::fromStdString(condata.name));
    pwd_line->setText(QString::fromStdString(condata.pwd));
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
        name_line->setText(QString::fromStdString(name));
    }
    if(!pwd.empty())
    {
        pwd_line->setText(QString::fromStdString(pwd));
    }
    finde.clear(),name.clear(),pwd.clear();
    readname.open("conf.txt",std::ifstream::in);
    for(int i = 0;std::getline(readname,finde);i++)
    {
        if(i==0)
        {
            srv = finde;
        }
        else if(i==1)
        {
            port = finde;
        }
        else if(i==2)
        {
            if(finde=="1")
            {
                check_box_tray->setChecked(true);
            }
        }
        else if(i==3)
        {
            if(finde=="1")
            {
                check_box_notice->setChecked(true);
            }
        }
    }

    if(!srv.empty())
    {
        srvaddr_line->setText(QString::fromStdString(srv));
    }
    if(!port.empty())
    {
        srvport_line->setText(QString::fromStdString(port));
    }
    srv.clear(),port.clear(),finde.clear();
    readname.close();
    finde.clear();
}

void info::on_save_name_pwd_button_clicked()
{
    std::string name = QString(name_line->text()).toStdString(), pwd = QString(pwd_line->text()).toStdString();
    crypt(name,key2);
    crypt(pwd,key2);
    std::ofstream write("sec",std::ofstream::trunc);
    write << name << "\n" << pwd;
    write.close();
}

void info::on_save_programm_options_button_clicked()
{
    std::ofstream write("conf.txt",std::ofstream::trunc);
    write << QString(srvaddr_line->text()).toStdString() << '\n' << QString(srvport_line->text()).toStdString() << '\n';
    if(check_box_tray->isChecked())
    {
        write << 1 << '\n';
    }
    else
    {
        write << 0 << '\n';
    }
    if(check_box_notice->isChecked())
    {
        write << 1 << '\n';
    }
    else
    {
        write << 0 << '\n';
    }
    write.close();
}

void info::on_ok_button_clicked()
{
    condata.name = QString(name_line->text()).toStdString();
    condata.pwd = QString(pwd_line->text()).toStdString();
    std::string srv = QString(srvaddr_line->text()).toStdString();
    condata.prt = QString(srvport_line->text()).toUShort();
    for(unsigned int i = 0; i < strlen(srv.c_str());i++)
    {
        condata.srv[i] = srv[i];
    }
    if(!condata.name.empty( )&& !condata.pwd.empty() && !srvaddr_line->text().isEmpty() && !srvport_line->text().isEmpty())
    {
        if(check_box_tray->isChecked())
        {
            condata.isCheck = 1;
        }
        else
        {
            condata.isCheck = 0;
        }
        if(check_box_notice->isChecked())
        {
            condata.isCheck2 = 1;
        }
        else
        {
            condata.isCheck2 = 0;
        }
        info::close();
        emit push_to_connect_button();
    }
}

void info::show_options_window()
{
    this->show();
}

void startconnection(int &isConnect)
{
    isConnect = 0;
    WSAData data;
    WORD version = MAKEWORD(2,2);
    WSAStartup(version,&data);
    condata.Connect = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
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
        setsockopt(condata.Connect,SOL_SOCKET,SO_KEEPALIVE,0,0);
        printf("Connection on chat server: %s is stable\n\n",condata.srv);
        isConnect = 1;
    }
}

void ReadMessageFromServer()
{
    for ( ;!condata.isConnected;usleep(1000))
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

void parcer2(std::string str, std::string &privat_name)
{
    for(uint i = 0; str[i] !=91;i++)
    {
        if(str[i]=='\n')
        {
            i +=1;
            for(;str[i]!='\n';i++)
            {
                privat_name += str[i];
            }
        }
    }
}

void MainWindow::read()
{
    if(condata.str != condata.str2 && condata.str[0] != 33)
    {
        condata.str2 = condata.str;
        if(condata.str == "access denied, push enter to continue\n")
        {
            ui->send_button->setEnabled(false);
            ui->userlist_field->setEnabled(false);
            ui->userlist_field->clear();
            ui->read_text_field->setText("access denied");
            ui->read_text_field->setEnabled(false);
            ui->read_text_field->clear();
            ui->option_button->setEnabled(true);
            ui->your_nick_label->setText("");
            ui->connect_status_label->setText("Доступ запрещен");
            ui->connect_status_label->setStyleSheet("color: rgb(227,38,54)");
            ui->connect_button->setText("Подключение");
            ui->send_message_line->setEnabled(false);
            send(condata.Connect,"gubabo", 10, 0);
            shutdown(condata.Connect,2);
            closesocket(condata.Connect);
            WSACleanup();
            condata.Connect = 0;
            condata.isConnected = 1;
            condata.str = "";
            condata.str2 = "";
        }
        else if(condata.str == "server offline\n")
        {
            ui->send_button->setEnabled(false);
            ui->userlist_field->setEnabled(false);
            ui->userlist_field->clear();
            ui->read_text_field->setEnabled(false);
            ui->read_text_field->clear();
            ui->option_button->setEnabled(true);
            ui->your_nick_label->setText("");
            ui->connect_status_label->setText("Сервер офлайн");
            ui->connect_status_label->setStyleSheet("color: rgb(227,38,54)");
            ui->connect_button->setText("Подключение");
            ui->send_message_line->setEnabled(false);
            send(condata.Connect,"gubabo", 10, 0);
            shutdown(condata.Connect,2);
            closesocket(condata.Connect);
            WSACleanup();
            condata.Connect = 0;
            condata.isConnected = 1;
            condata.str = "";
            condata.str2 = "";
        }
        else if(condata.str == "")
        {
            ui->send_button->setEnabled(false);
            ui->read_text_field->setEnabled(false);
            ui->read_text_field->clear();
            ui->option_button->setEnabled(true);
            ui->your_nick_label->setText("");
            ui->connect_status_label->setText("Разрыв соединения");
            ui->connect_status_label->setStyleSheet("color: rgb(227,38,54)");
            ui->connect_button->setText("Подключение");
            ui->send_message_line->setEnabled(false);
            ui->userlist_field->setEnabled(false);
            ui->userlist_field->clear();
            send(condata.Connect,"gubabo", 10, 0);
            shutdown(condata.Connect,2);
            closesocket(condata.Connect);
            WSACleanup();
            condata.Connect = 0;
            condata.isConnected = 1;
            condata.str = "";
            condata.str2 = "";
        }
        else if(condata.str[0] == 91)
        {
            if(!this->isVisible())
            {
                trayIcon->setToolTip("Есть не прочитанные сообщения!");
                trayIcon -> setIcon(QIcon(":/images/3.png"));
                if(!condata.isCheck2)
                {
                    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
                    trayIcon->showMessage("Chat Client GUI",
                                          "Получено новое сообщение!",
                                          icon,
                                          2000);
                }
            }
            ui->read_text_field->moveCursor(QTextCursor::End);
            ui->read_text_field->textCursor().insertText(QString::fromStdString(condata.str));
            ui->read_text_field->moveCursor(QTextCursor::End);
        }
        else
        {
            std::string res, buf = condata.str;

            uint count = 0, count2 = 0;
            ui->userlist_field->clear();
            for(uint i = 0; i < strlen(buf.c_str()) ;i++)
            {
                if(buf[i] == '\n')
                {
                    for(; count < i ; count++)
                    {
                        res += buf[count];
                    }
                    count++;
                    ui->userlist_field->insertItem(count2,QString::fromStdString(res));
                    res.clear();
                }
            }
        }
    }
    else if(condata.str != condata.str2 && condata.str[0] == 33)
    {
        std::string prvt_name;
        parcer2(condata.str,prvt_name);
        condata.str2 = condata.str;
        if (prvt_name == condata.name)
        {
            condata.str2 = condata.str;
            emit create_privat_chat(condata);
        }
    }

    usleep(1000);
    if(!condata.isConnected)
    {
        QMetaObject::invokeMethod(this, "read", Qt::QueuedConnection);
    }
}

void MainWindow::on_connect_button_clicked()
{
    int isConnect;
    if(condata.isShow)
    {
        this->show();
        condata.isShow = 0;
    }
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
                ui->userlist_field->clear();
                ui->userlist_field->setEnabled(false);
                ui->read_text_field->setText("access denied");
                ui->read_text_field->setEnabled(false);
                ui->read_text_field->clear();
                ui->option_button->setEnabled(true);
                ui->your_nick_label->setText("");
                ui->connect_status_label->setText("Доступ запрещен");
                ui->connect_status_label->setStyleSheet("color: rgb(227,38,54)");
                ui->connect_button->setText("Подключение");
                ui->send_message_line->setEnabled(false);
                ui->send_button->setEnabled(false);
                send(condata.Connect,"gubabo", 10, 0);
                shutdown(condata.Connect,2);
                closesocket(condata.Connect);
                WSACleanup();
                condata.Connect = 0;
                condata.isConnected = 1;
                condata.str = "";
                condata.str2 = "";
            }
            else
            {
                trayIcon -> setIcon(QIcon(":/images/2.png"));
                ui->read_text_field->textCursor().insertText(QString::fromStdString(condata.str));
                ui->read_text_field->setEnabled(true);
                ui->send_message_line->setEnabled(true);
                condata.str2 = condata.str;
                CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReadMessageFromServer,0,0,0);
                memset(strsendchar, 0, sizeof(strsendchar));
                ui->connect_button->setText("Отключение");
                ui->send_button->setEnabled(true);
                ui->option_button->setEnabled(false);
                ui->your_nick_label->setText(QString::fromStdString(condata.name));
                ui->connect_status_label->setText("Подключено");
                ui->userlist_field->setEnabled(true);
                ui->connect_status_label->setStyleSheet("color: rgb(141,182,0)");
                MainWindow::read();
            }
        }
        else
        {
            ui->send_button->setEnabled(false);
            ui->userlist_field->clear();
            ui->connect_status_label->setText("Ошибка подключения");
            ui->connect_status_label->setStyleSheet("color: rgb(227,38,54)");
            ui->connect_button->setText("Подключение");
            ui->send_message_line->setEnabled(false);
            ui->read_text_field->setEnabled(false);
            ui->read_text_field->clear();
            ui->userlist_field->setEnabled(false);
            ui->option_button->setEnabled(true);
            send(condata.Connect,"gubabo", 10, 0);
            shutdown(condata.Connect,2);
            closesocket(condata.Connect);
            WSACleanup();
            condata.isConnected = 1;
        }
    }
    else
    {
        ui->send_button->setEnabled(false);
        trayIcon -> setIcon(QIcon(":/images/1.png"));
        ui->userlist_field->clear();
        ui->connect_status_label->setText("Отключено");
        ui->connect_status_label->setStyleSheet("color: rgb(227,38,54)");
        ui->connect_button->setText("Подключение");
        ui->send_message_line->setEnabled(false);
        ui->read_text_field->clear();
        ui->read_text_field->setEnabled(false);
        ui->option_button->setEnabled(true);
        ui->userlist_field->setEnabled(false);
        send(condata.Connect,"gubabo", 10, 0);
        shutdown(condata.Connect,2);
        closesocket(condata.Connect);
        WSACleanup();
        condata.isConnected = 1;
        condata.str="";
        condata.str2="";
    }
}

void MainWindow::on_send_button_clicked()
{
    ui->send_button->setEnabled(false);
    QString str = ui->send_message_line->text();
    ui->send_message_line->clear();
    usleep(2500);
    std::string buff = QString(str).toStdString();
    std::string strsend = condata.name+"\n"+condata.pwd+"\n"+"!public"+"\n"+buff+"\n";
    crypt(strsend,key);
    char sendchar[strlen(strsend.c_str())+2];
    for(unsigned int i = 0; i < strlen(strsend.c_str())+2;i++) sendchar[i] = '\0';
    for(unsigned int i = 0; i < strlen(strsend.c_str()); i++) sendchar[i] = strsend[i];
    send(condata.Connect, sendchar, sizeof(sendchar),0);
    ui->send_button->setEnabled(true);
}

void MainWindow::on_option_button_clicked()
{
    emit show_option_window();
}

void MainWindow::showTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/1.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);
    trayIcon -> show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::trayActionExecute()
{
    if(condata.isConnected)
    {
        QIcon trayImage(":/images/1.png");
        trayIcon -> setIcon(trayImage);
    }
    else
    {
        QIcon trayImage(":/images/2.png");
        trayIcon -> setIcon(trayImage);
    }

    this->showNormal();
    trayIcon->setToolTip("Chat Client GUI" "\n");
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:

            this -> trayActionExecute();
            break;
          default:
            break;
    }
}

void MainWindow::setTrayIconActions()
{
    minimizeAction = new QAction("Свернуть", this);
    restoreAction = new QAction("Восстановить", this);
    quitAction = new QAction("Выход", this);
    connect (minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect (restoreAction, SIGNAL(triggered()), this, SLOT(trayActionExecute()));
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayIconMenu = new QMenu(this);
    trayIconMenu -> addAction (minimizeAction);
    trayIconMenu -> addAction (restoreAction);
    trayIconMenu -> addAction (quitAction);
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            if(condata.isCheck&&!condata.isCheck2)
            {
                QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
                trayIcon->showMessage("Chat Client GUI","Приложение свернуто в трей.",icon,2000);
                this -> hide();
            }
            else if(condata.isCheck&&condata.isCheck2)
            {
                this -> hide();
            }
        }
    }
}

void MainWindow::on_userlist_field_doubleClicked(const QModelIndex &index)
{
    QString str = ui->userlist_field->item(index.row())->text();
    condata.name_privat = QString(str).toStdString();
    emit create_privat_chat2(condata);
}







