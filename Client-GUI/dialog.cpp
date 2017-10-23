#include "dialog.h"
#include "ui_dialog.h"

class my_lis                          //We describe a class list of the elements of the structure Elem
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
    my_lis()
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
    my_lis m;
};

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

void Dialog::create_privat_chat(my_struct &condata)
{
    Dialog *d = new Dialog;
    d->show_chat(condata);
}

void Dialog::show_chat(my_struct &condata)
{
    this->show();
    ui->privat_chat_nickname_label->setText(QString::fromStdString(condata.name));
}
