#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <ws2tcpip.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>

const std::string key = "key";

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    Ui::Dialog *ui;
private slots:
    void create_privat_chat(struct my_struct &condata);
    void show_chat(struct my_struct &condata);
    void on_senmessage_privat_chat_button_clicked();
    void read();
};

#endif // DIALOG_H
