#include "dialog.h"
#include "ui_dialog.h"

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
}condata2,condata3;

void crypto (std::string &res, const std::string key)
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

void decrypto (std::string &res, const std::string key)
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


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

Dialog::~Dialog()
{
    delete ui;
}

void updatecondata(struct my_struct &condata)
{
    for(;;)
    {
        condata2 = condata;
    }
}

void Dialog::create_privat_chat(my_struct &condata)
{
    if(condata.isupdate)
    {
        CreateThread(0,0,(LPTHREAD_START_ROUTINE)updatecondata,(LPVOID)&condata,0,0);
        condata.isupdate = 0;
    }
    Dialog *d = new Dialog;
    d->show_chat(condata);
}

void Dialog::read()
{
    std::string temp2,temp = condata2.str;
    if(temp[0] == 33)
    {
        if(temp != condata3.str2)
        {
            condata3.str2 = temp;
            int isname = 1;
            std::string name;
            uint i = 2;
            for(;isname;i++)
            {
                if(temp[i]=='\n')
                {
                    for(uint a = 2; a < i; a++)
                    {
                        name += temp[a];
                    }
                    isname = 0;
                }
            }
            if(QString::fromStdString(name) == ui->privat_chat_nickname_label->text() || QString::fromStdString(name) == QString::fromStdString(condata2.name))
            {
                for(;i<strlen(temp.c_str());i++)
                {
                    temp2 += temp[i];
                }
                ui->read_text_privat_chat_field->moveCursor(QTextCursor::End);
                ui->read_text_privat_chat_field->textCursor().insertText(QString::fromStdString(temp2));
                ui->read_text_privat_chat_field->moveCursor(QTextCursor::End);
                isname = 1;
                temp.clear();
                temp2.clear();
            }
        }
    }
    usleep(1000);
    QMetaObject::invokeMethod(this, "read",Qt::QueuedConnection);
}

void Dialog::show_chat(my_struct &condata)
{   condata2 = condata;
    this->show();
    ui->privat_chat_nickname_label->setText(QString::fromStdString(condata2.name_privat));
    Dialog::read();
}

void Dialog::on_senmessage_privat_chat_button_clicked()
{
    std::string name_privat = QString(ui->privat_chat_nickname_label->text()).toStdString();
    std::string buff = QString(ui->sendmessage_privat_chat_line->text()).toStdString();
    ui->sendmessage_privat_chat_line->clear();
    std::string strsend = condata2.name+"\n"+condata2.pwd+"\n"+"!privat"+"\n"+name_privat+"\n"+buff+"\n";
    crypto(strsend,key);
    char sendchar[strlen(strsend.c_str())+2];
    for(unsigned int i = 0; i < strlen(strsend.c_str())+2;i++) sendchar[i] = '\0';
    for(unsigned int i = 0; i < strlen(strsend.c_str()); i++) sendchar[i] = strsend[i];
    send(condata2.Connect, sendchar, sizeof(sendchar),0);
}
