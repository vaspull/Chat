/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[335];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "show_option_window"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18), // "create_privat_chat"
QT_MOC_LITERAL(4, 50, 10), // "my_struct&"
QT_MOC_LITERAL(5, 61, 7), // "condata"
QT_MOC_LITERAL(6, 69, 19), // "create_privat_chat2"
QT_MOC_LITERAL(7, 89, 22), // "on_send_button_clicked"
QT_MOC_LITERAL(8, 112, 25), // "on_connect_button_clicked"
QT_MOC_LITERAL(9, 138, 24), // "on_option_button_clicked"
QT_MOC_LITERAL(10, 163, 4), // "read"
QT_MOC_LITERAL(11, 168, 11), // "changeEvent"
QT_MOC_LITERAL(12, 180, 7), // "QEvent*"
QT_MOC_LITERAL(13, 188, 17), // "trayIconActivated"
QT_MOC_LITERAL(14, 206, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(15, 240, 6), // "reason"
QT_MOC_LITERAL(16, 247, 17), // "trayActionExecute"
QT_MOC_LITERAL(17, 265, 18), // "setTrayIconActions"
QT_MOC_LITERAL(18, 284, 12), // "showTrayIcon"
QT_MOC_LITERAL(19, 297, 31), // "on_userlist_field_doubleClicked"
QT_MOC_LITERAL(20, 329, 5) // "index"

    },
    "MainWindow\0show_option_window\0\0"
    "create_privat_chat\0my_struct&\0condata\0"
    "create_privat_chat2\0on_send_button_clicked\0"
    "on_connect_button_clicked\0"
    "on_option_button_clicked\0read\0changeEvent\0"
    "QEvent*\0trayIconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0trayActionExecute\0setTrayIconActions\0"
    "showTrayIcon\0on_userlist_field_doubleClicked\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    1,   80,    2, 0x06 /* Public */,
       6,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    1,   90,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      16,    0,   96,    2, 0x08 /* Private */,
      17,    0,   97,    2, 0x08 /* Private */,
      18,    0,   98,    2, 0x08 /* Private */,
      19,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show_option_window(); break;
        case 1: _t->create_privat_chat((*reinterpret_cast< my_struct(*)>(_a[1]))); break;
        case 2: _t->create_privat_chat2((*reinterpret_cast< my_struct(*)>(_a[1]))); break;
        case 3: _t->on_send_button_clicked(); break;
        case 4: _t->on_connect_button_clicked(); break;
        case 5: _t->on_option_button_clicked(); break;
        case 6: _t->read(); break;
        case 7: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 8: _t->trayIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 9: _t->trayActionExecute(); break;
        case 10: _t->setTrayIconActions(); break;
        case 11: _t->showTrayIcon(); break;
        case 12: _t->on_userlist_field_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::show_option_window)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(my_struct & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::create_privat_chat)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(my_struct & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::create_privat_chat2)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::show_option_window()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::create_privat_chat(my_struct & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::create_privat_chat2(my_struct & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_info_t {
    QByteArrayData data[7];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_info_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_info_t qt_meta_stringdata_info = {
    {
QT_MOC_LITERAL(0, 0, 4), // "info"
QT_MOC_LITERAL(1, 5, 22), // "push_to_connect_button"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "show_options_window"
QT_MOC_LITERAL(4, 49, 20), // "on_ok_button_clicked"
QT_MOC_LITERAL(5, 70, 31), // "on_save_name_pwd_button_clicked"
QT_MOC_LITERAL(6, 102, 39) // "on_save_programm_options_butt..."

    },
    "info\0push_to_connect_button\0\0"
    "show_options_window\0on_ok_button_clicked\0"
    "on_save_name_pwd_button_clicked\0"
    "on_save_programm_options_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_info[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void info::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        info *_t = static_cast<info *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->push_to_connect_button(); break;
        case 1: _t->show_options_window(); break;
        case 2: _t->on_ok_button_clicked(); break;
        case 3: _t->on_save_name_pwd_button_clicked(); break;
        case 4: _t->on_save_programm_options_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (info::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&info::push_to_connect_button)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject info::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_info.data,
      qt_meta_data_info,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *info::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *info::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_info.stringdata0))
        return static_cast<void*>(const_cast< info*>(this));
    return QDialog::qt_metacast(_clname);
}

int info::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void info::push_to_connect_button()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
