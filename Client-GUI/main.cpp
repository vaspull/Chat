#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    info *inf = new info;
    inf->show();
    Dialog *d = new Dialog;
    QObject::connect(w,SIGNAL(show_option_window()),inf,SLOT(show_options_window()));
    QObject::connect(inf,SIGNAL(push_to_connect_button()),w,SLOT(on_connect_button_clicked()));
    QObject::connect(w,SIGNAL(create_privat_chat(struct my_struct&)),d,SLOT(create_privat_chat(struct my_struct&)));
    return a.exec();
}
