#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
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
#include <QDialog>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_send_button_clicked();

    void on_connect_button_clicked();

    void on_option_button_clicked();

    void read();

signals:
    void show_option_window();
private slots:
    void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

private:
    Ui::MainWindow *ui;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
};


class info : public QDialog
{
    Q_OBJECT
public:
    info(QWidget *parent=0);
private:
    QLabel *name_label;
    QLabel *pwd_label;
    QLabel *srvaddr_label;
    QLabel *srvport_label;
    QLineEdit *name_line;
    QLineEdit *pwd_line;
    QLineEdit *srvaddr_line;
    QLineEdit *srvport_line;
    QPushButton *ok_button;
    QPushButton *close_button;
    QPushButton *save_name_pwd_button;
    QPushButton *save_programm_options;
    QCheckBox *check_box_tray;
    QCheckBox *check_box_notice;
public slots:
    void show_options_window();
    void on_ok_button_clicked();
    void on_save_name_pwd_button_clicked();
    void on_save_programm_options_button_clicked();
signals:
    void push_to_connect_button();
};


#endif // MAINWINDOW_H
