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

void updatecondata(struct my_struct &condata)
{
    for(;;usleep(1000))
    {
        condata2 = condata;
    }
}

class Elemlist                          //We describe a class list of the elements of the structure Elem
{
private:
    struct Elem                         //Describe the structure of a linked list
    {
        std::string data;                    //The information includes a list item
        int ID;
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

    void add(std::string d,int ID)                   //A method of adding a new item to the list
    {
        Elem *newelem = new Elem;        //Memory allocation for the new element
        newelem -> data = d;             //We set the value of data to the new structure element
        newelem -> ID = ID;
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
    void finde(std::string name, int &ID)
    {
        Elem *info = first;
        while(info&&name!=info->data)
        {
            info = info -> next;
        }
        ID=info->ID;
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

    int check(std::string privat_name)
    {
        int i = 1;
        Elem *info = first;
        while(info)
        {
            if(info->data==privat_name)
            {
                i = 0;
                //info = info -> next;
                break;
            }
            else
            {
                info = info -> next;
            }
        }
        return i;
    }

    void del_privat_name(std::string privat_name)
    {
//        if(counter > 0)
//        {
            Elem *info = first;
            int i = 1;
            while(info)
            {
                if(info->data==privat_name)
                {
                    del(i);
                    break;
                }
                else
                {
                    i++;
                }
            }
 //       }
    }
}m;

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

void parcer(std::string str, std::string &privat_name)
{
    for(uint i = 0; i < strlen(str.c_str());i++)
    {
        if(str[i]==93)
        {
            i +=2;
            for(;str[i]!=58;i++)
            {
                privat_name += str[i];
            }
        }
    }
}

void Dialog::create_privat_chat(my_struct &condata)
{
    if(condata.isupdate)
    {
        CreateThread(0,0,(LPTHREAD_START_ROUTINE)updatecondata,(LPVOID)&condata,0,0);
        condata.isupdate = 0;
    }
    std::string privat_name;
    parcer(condata.str,privat_name);
    if(m.check(privat_name)==1)
    {
        Dialog *d = new Dialog;
        m.add(privat_name,0);
        d->show_chat(privat_name);
    }
}

void Dialog::create_privat_chat2(my_struct &condata)
{
    if(condata.isupdate)
    {
        CreateThread(0,0,(LPTHREAD_START_ROUTINE)updatecondata,(LPVOID)&condata,0,0);
        condata.isupdate = 0;
    }
    if(m.check(condata2.name_privat)==1)
    {
        Dialog *d = new Dialog;
        m.add(condata2.name_privat,0);
        d->show_chat2(condata);
    }
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

void Dialog::show_chat(std::string privat_name)
{   this->show();
    ui->privat_chat_nickname_label->setText(QString::fromStdString(privat_name));
    Dialog::read();
}

void Dialog::show_chat2(my_struct &condata)
{   this->show();
    ui->privat_chat_nickname_label->setText(QString::fromStdString(condata.name_privat));
    Dialog::read();
}

void Dialog::on_senmessage_privat_chat_button_clicked()
{
    std::string name_privat = QString(ui->privat_chat_nickname_label->text()).toStdString();
    std::string buff = QString(ui->sendmessage_privat_chat_line->text()).toStdString();
    ui->sendmessage_privat_chat_line->clear();
    std::string strsend = condata2.name+"\n"+condata2.pwd+"\n"+"!privat"+"\n"+name_privat+"\n"+buff+"\n";
    crypto(strsend,key3);
    char sendchar[strlen(strsend.c_str())+2];
    for(unsigned int i = 0; i < strlen(strsend.c_str())+2;i++) sendchar[i] = '\0';
    for(unsigned int i = 0; i < strlen(strsend.c_str()); i++) sendchar[i] = strsend[i];
    send(condata2.Connect, sendchar, sizeof(sendchar),0);
}

void Dialog::closeEvent(QCloseEvent *event)
{
    std::string privat_name = QString(ui->privat_chat_nickname_label->text()).toStdString();
    m.del_privat_name(privat_name);
    event->accept();
}
