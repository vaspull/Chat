#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    info *inf = new info;
    inf->show();
    QObject::connect(w,SIGNAL(show_option_window()),inf,SLOT(show_options_window()));
    QObject::connect(inf,SIGNAL(push_to_connect_button()),w,SLOT(on_connect_button_clicked()));
    return a.exec();
}
