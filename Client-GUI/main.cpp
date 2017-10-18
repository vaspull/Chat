#include <QApplication>
#include <mainwindow.h>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MyWindow *window = new MyWindow();
    info *inf = new info;
    inf->show();

//    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    QObject::connect(window,SIGNAL(getinfosignal()),inf,SLOT(getinfo()));
    QObject::connect(inf,SIGNAL(getok()),window,SLOT(con()));

    return a.exec();
}
