/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Json/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 21),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 17),
QT_MOC_LITERAL(4, 52, 4),
QT_MOC_LITERAL(5, 57, 22),
QT_MOC_LITERAL(6, 80, 20),
QT_MOC_LITERAL(7, 101, 20),
QT_MOC_LITERAL(8, 122, 32),
QT_MOC_LITERAL(9, 155, 18),
QT_MOC_LITERAL(10, 174, 8),
QT_MOC_LITERAL(11, 183, 14),
QT_MOC_LITERAL(12, 198, 4),
QT_MOC_LITERAL(13, 203, 5),
QT_MOC_LITERAL(14, 209, 4),
QT_MOC_LITERAL(15, 214, 15),
QT_MOC_LITERAL(16, 230, 12),
QT_MOC_LITERAL(17, 243, 4),
QT_MOC_LITERAL(18, 248, 12),
QT_MOC_LITERAL(19, 261, 12)
    },
    "MainWindow\0on_twYear_itemClicked\0\0"
    "QTableWidgetItem*\0item\0on_twMonth_itemClicked\0"
    "on_twDay_itemClicked\0on_btCurDate_clicked\0"
    "on_twTaskField_itemDoubleClicked\0"
    "isSelDatePresented\0sendFile\0readJsonObject\0"
    "json\0Note&\0note\0writeJsonObject\0"
    "QJsonObject&\0Note\0loadFileJson\0"
    "saveFileJson\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08,
       5,    1,   72,    2, 0x08,
       6,    1,   75,    2, 0x08,
       7,    0,   78,    2, 0x08,
       8,    1,   79,    2, 0x08,
       9,    0,   82,    2, 0x08,
      10,    0,   83,    2, 0x08,
      11,    2,   84,    2, 0x08,
      15,    2,   89,    2, 0x08,
      18,    0,   94,    2, 0x08,
      19,    0,   95,    2, 0x08,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject, 0x80000000 | 13,   12,   14,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 17,   12,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_twYear_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->on_twMonth_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_twDay_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_btCurDate_clicked(); break;
        case 4: _t->on_twTaskField_itemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 5: { bool _r = _t->isSelDatePresented();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->sendFile(); break;
        case 7: _t->readJsonObject((*reinterpret_cast< const QJsonObject(*)>(_a[1])),(*reinterpret_cast< Note(*)>(_a[2]))); break;
        case 8: _t->writeJsonObject((*reinterpret_cast< QJsonObject(*)>(_a[1])),(*reinterpret_cast< Note(*)>(_a[2]))); break;
        case 9: _t->loadFileJson(); break;
        case 10: _t->saveFileJson(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
