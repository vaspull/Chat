/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *connect_button;
    QLineEdit *send_message_line;
    QTextEdit *read_text_field;
    QPushButton *option_button;
    QLabel *userlist_label;
    QPushButton *send_button;
    QListWidget *userlist_field;
    QHBoxLayout *horizontalLayout;
    QLabel *your_nick_static_label;
    QLabel *your_nick_label;
    QLabel *connect_status_label;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(682, 350);
        QIcon icon;
        icon.addFile(QStringLiteral("Iconka-Meow-Cat-tied.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        connect_button = new QPushButton(centralWidget);
        connect_button->setObjectName(QStringLiteral("connect_button"));

        gridLayout->addWidget(connect_button, 5, 2, 1, 1);

        send_message_line = new QLineEdit(centralWidget);
        send_message_line->setObjectName(QStringLiteral("send_message_line"));
        send_message_line->setEnabled(false);
        send_message_line->setFocusPolicy(Qt::WheelFocus);

        gridLayout->addWidget(send_message_line, 6, 0, 1, 1);

        read_text_field = new QTextEdit(centralWidget);
        read_text_field->setObjectName(QStringLiteral("read_text_field"));
        read_text_field->setEnabled(false);
        read_text_field->setReadOnly(true);

        gridLayout->addWidget(read_text_field, 3, 0, 3, 1);

        option_button = new QPushButton(centralWidget);
        option_button->setObjectName(QStringLiteral("option_button"));

        gridLayout->addWidget(option_button, 4, 2, 1, 1);

        userlist_label = new QLabel(centralWidget);
        userlist_label->setObjectName(QStringLiteral("userlist_label"));

        gridLayout->addWidget(userlist_label, 0, 2, 1, 1);

        send_button = new QPushButton(centralWidget);
        send_button->setObjectName(QStringLiteral("send_button"));
        send_button->setEnabled(false);
        send_button->setAutoDefault(true);

        gridLayout->addWidget(send_button, 6, 2, 1, 1);

        userlist_field = new QListWidget(centralWidget);
        userlist_field->setObjectName(QStringLiteral("userlist_field"));
        userlist_field->setEnabled(false);
        userlist_field->setMinimumSize(QSize(150, 0));
        userlist_field->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(userlist_field, 3, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        your_nick_static_label = new QLabel(centralWidget);
        your_nick_static_label->setObjectName(QStringLiteral("your_nick_static_label"));

        horizontalLayout->addWidget(your_nick_static_label);

        your_nick_label = new QLabel(centralWidget);
        your_nick_label->setObjectName(QStringLiteral("your_nick_label"));

        horizontalLayout->addWidget(your_nick_label);

        connect_status_label = new QLabel(centralWidget);
        connect_status_label->setObjectName(QStringLiteral("connect_status_label"));

        horizontalLayout->addWidget(connect_status_label);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 682, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(MainWindow);

        send_button->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", Q_NULLPTR));
        connect_button->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", Q_NULLPTR));
        option_button->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", Q_NULLPTR));
        userlist_label->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265\320\271", Q_NULLPTR));
        send_button->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        send_button->setShortcut(QApplication::translate("MainWindow", "Return", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        your_nick_static_label->setText(QApplication::translate("MainWindow", "\320\242\320\262\320\276\320\271 \320\275\320\270\320\272:", Q_NULLPTR));
        your_nick_label->setText(QString());
        connect_status_label->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\276", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
