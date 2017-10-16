#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QCheckBox>
#include <QCloseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QAction>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMainWindow>
#include <ws2tcpip.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include "unistd.h"

#define maxlenghlogin 10
#define minlenghlogin 6
#define maxlenghpwd 12
#define minlenghpwd 6
#define sleeptime 5
#define buffersize 50000
#define pwdsize 1024
#define deffconn "<----CONNECTED TO CHAT"

const std::string key = "key";
const std::string key2 = "key2";

class MyWindow : public QDialog
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent=0);
protected:
    void closeEvent(QCloseEvent * event);
private:
    QLabel *lbl;
    QLabel *lbl2;
    QLabel *lbl3;
    QLabel *lbl4;
    QLineEdit *line;
    QPushButton *conn;
    QPushButton *sendmessage;
    QPushButton *options;
    QTextEdit *edittext;
    QTextEdit *edittext2;
    QSystemTrayIcon * trayIcon;
private slots:
    void con();
    void sen();
    void read();
    void opt();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
signals:
    void getinfosignal();
};

class info : public QDialog
{
    Q_OBJECT
public:
    info(QWidget *parent=0);
private:
    QLabel *lbl;
    QLabel *lbl2;
    QLabel *lbl3;
    QLabel *lbl4;
    QLineEdit *line;
    QLineEdit *line2;
    QLineEdit *line3;
    QLineEdit *line4;
    QPushButton *ok;
    QPushButton *closed;
    QPushButton *save1;
    QPushButton *save2;
    QCheckBox *cb1;
    QCheckBox *cb2;
public slots:
    void getinfo();
    void okey();
    void sav1();
    void sav2();
signals:
    void getok();
};

#endif // MYWINDOW_H
