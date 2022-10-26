/****************************************************************************
** Meta object code from reading C++ file 'chattingform.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Osstem_Project/chattingform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chattingform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChattingForm_t {
    uint offsetsAndSizes[22];
    char stringdata0[13];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[11];
    char stringdata5[13];
    char stringdata6[12];
    char stringdata7[6];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ChattingForm_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ChattingForm_t qt_meta_stringdata_ChattingForm = {
    {
        QT_MOC_LITERAL(0, 12),  // "ChattingForm"
        QT_MOC_LITERAL(13, 11),  // "receiveData"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 8),  // "sendData"
        QT_MOC_LITERAL(35, 10),  // "disconnect"
        QT_MOC_LITERAL(46, 12),  // "sendProtocol"
        QT_MOC_LITERAL(59, 11),  // "Chat_Status"
        QT_MOC_LITERAL(71, 5),  // "char*"
        QT_MOC_LITERAL(77, 8),  // "sendFile"
        QT_MOC_LITERAL(86, 8),  // "goOnSend"
        QT_MOC_LITERAL(95, 23)   // "on_logoutButton_clicked"
    },
    "ChattingForm",
    "receiveData",
    "",
    "sendData",
    "disconnect",
    "sendProtocol",
    "Chat_Status",
    "char*",
    "sendFile",
    "goOnSend",
    "on_logoutButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChattingForm[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    3,   65,    2, 0x08,    4 /* Private */,
       5,    2,   72,    2, 0x28,    8 /* Private | MethodCloned */,
       8,    0,   77,    2, 0x08,   11 /* Private */,
       9,    1,   78,    2, 0x08,   12 /* Private */,
      10,    0,   81,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 7, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 7,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,

       0        // eod
};

void ChattingForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChattingForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receiveData(); break;
        case 1: _t->sendData(); break;
        case 2: _t->disconnect(); break;
        case 3: _t->sendProtocol((*reinterpret_cast< std::add_pointer_t<Chat_Status>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->sendProtocol((*reinterpret_cast< std::add_pointer_t<Chat_Status>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<char*>>(_a[2]))); break;
        case 5: _t->sendFile(); break;
        case 6: _t->goOnSend((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 7: _t->on_logoutButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ChattingForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ChattingForm.offsetsAndSizes,
    qt_meta_data_ChattingForm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ChattingForm_t
, QtPrivate::TypeAndForceComplete<ChattingForm, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Chat_Status, std::false_type>, QtPrivate::TypeAndForceComplete<char *, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Chat_Status, std::false_type>, QtPrivate::TypeAndForceComplete<char *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ChattingForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChattingForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChattingForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChattingForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
