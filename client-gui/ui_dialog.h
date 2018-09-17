/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *senmessage_privat_chat_button;
    QTextEdit *read_text_privat_chat_field;
    QLineEdit *sendmessage_privat_chat_line;
    QHBoxLayout *horizontalLayout;
    QLabel *privat_chat_label;
    QLabel *privat_chat_nickname_label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(717, 338);
        gridLayout_2 = new QGridLayout(Dialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        senmessage_privat_chat_button = new QPushButton(Dialog);
        senmessage_privat_chat_button->setObjectName(QStringLiteral("senmessage_privat_chat_button"));

        gridLayout->addWidget(senmessage_privat_chat_button, 2, 0, 1, 1);

        read_text_privat_chat_field = new QTextEdit(Dialog);
        read_text_privat_chat_field->setObjectName(QStringLiteral("read_text_privat_chat_field"));
        read_text_privat_chat_field->setReadOnly(true);

        gridLayout->addWidget(read_text_privat_chat_field, 0, 0, 1, 1);

        sendmessage_privat_chat_line = new QLineEdit(Dialog);
        sendmessage_privat_chat_line->setObjectName(QStringLiteral("sendmessage_privat_chat_line"));

        gridLayout->addWidget(sendmessage_privat_chat_line, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        privat_chat_label = new QLabel(Dialog);
        privat_chat_label->setObjectName(QStringLiteral("privat_chat_label"));

        horizontalLayout->addWidget(privat_chat_label);

        privat_chat_nickname_label = new QLabel(Dialog);
        privat_chat_nickname_label->setObjectName(QStringLiteral("privat_chat_nickname_label"));

        horizontalLayout->addWidget(privat_chat_nickname_label);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Dialog);

        senmessage_privat_chat_button->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        senmessage_privat_chat_button->setText(QApplication::translate("Dialog", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        privat_chat_label->setText(QApplication::translate("Dialog", "\320\237\321\200\320\270\320\262\320\260\321\202\320\275\321\213\320\271 \321\207\320\260\321\202 \321\201:", Q_NULLPTR));
        privat_chat_nickname_label->setText(QApplication::translate("Dialog", "nickname", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
