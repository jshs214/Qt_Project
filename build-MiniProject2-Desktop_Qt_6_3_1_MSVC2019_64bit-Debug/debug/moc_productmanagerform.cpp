/****************************************************************************
** Meta object code from reading C++ file 'productmanagerform.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MiniProject2/productmanagerform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'productmanagerform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProductManagerForm_t {
    const uint offsetsAndSize[44];
    char stringdata0[388];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ProductManagerForm_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ProductManagerForm_t qt_meta_stringdata_ProductManagerForm = {
    {
QT_MOC_LITERAL(0, 18), // "ProductManagerForm"
QT_MOC_LITERAL(19, 15), // "productdataSent"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 12), // "ProductItem*"
QT_MOC_LITERAL(49, 16), // "clickProductSent"
QT_MOC_LITERAL(66, 25), // "on_treeWidget_itemClicked"
QT_MOC_LITERAL(92, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(109, 4), // "item"
QT_MOC_LITERAL(114, 6), // "column"
QT_MOC_LITERAL(121, 15), // "showContextMenu"
QT_MOC_LITERAL(137, 10), // "removeItem"
QT_MOC_LITERAL(148, 24), // "on_addPushButton_clicked"
QT_MOC_LITERAL(173, 27), // "on_modifyPushButton_clicked"
QT_MOC_LITERAL(201, 27), // "on_searchPushButton_clicked"
QT_MOC_LITERAL(229, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(251, 18), // "receiveProductName"
QT_MOC_LITERAL(270, 15), // "receiveAddStock"
QT_MOC_LITERAL(286, 15), // "receiveModStock"
QT_MOC_LITERAL(302, 15), // "receiveDelStock"
QT_MOC_LITERAL(318, 17), // "receiveProductKey"
QT_MOC_LITERAL(336, 22), // "on_clearbutton_clicked"
QT_MOC_LITERAL(359, 28) // "on_ProductManagement_clicked"

    },
    "ProductManagerForm\0productdataSent\0\0"
    "ProductItem*\0clickProductSent\0"
    "on_treeWidget_itemClicked\0QTreeWidgetItem*\0"
    "item\0column\0showContextMenu\0removeItem\0"
    "on_addPushButton_clicked\0"
    "on_modifyPushButton_clicked\0"
    "on_searchPushButton_clicked\0"
    "on_pushButton_clicked\0receiveProductName\0"
    "receiveAddStock\0receiveModStock\0"
    "receiveDelStock\0receiveProductKey\0"
    "on_clearbutton_clicked\0"
    "on_ProductManagement_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProductManagerForm[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  110,    2, 0x06,    1 /* Public */,
       4,    1,  113,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    2,  116,    2, 0x08,    5 /* Private */,
       9,    1,  121,    2, 0x08,    8 /* Private */,
      10,    0,  124,    2, 0x08,   10 /* Private */,
      11,    0,  125,    2, 0x08,   11 /* Private */,
      12,    0,  126,    2, 0x08,   12 /* Private */,
      13,    0,  127,    2, 0x08,   13 /* Private */,
      14,    0,  128,    2, 0x08,   14 /* Private */,
      15,    1,  129,    2, 0x08,   15 /* Private */,
      16,    2,  132,    2, 0x08,   17 /* Private */,
      17,    3,  137,    2, 0x08,   20 /* Private */,
      18,    2,  144,    2, 0x08,   24 /* Private */,
      19,    1,  149,    2, 0x08,   27 /* Private */,
      20,    0,  152,    2, 0x08,   29 /* Private */,
      21,    0,  153,    2, 0x08,   30 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ProductManagerForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProductManagerForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->productdataSent((*reinterpret_cast< std::add_pointer_t<ProductItem*>>(_a[1]))); break;
        case 1: _t->clickProductSent((*reinterpret_cast< std::add_pointer_t<ProductItem*>>(_a[1]))); break;
        case 2: _t->on_treeWidget_itemClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->showContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 4: _t->removeItem(); break;
        case 5: _t->on_addPushButton_clicked(); break;
        case 6: _t->on_modifyPushButton_clicked(); break;
        case 7: _t->on_searchPushButton_clicked(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->receiveProductName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->receiveAddStock((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->receiveModStock((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 12: _t->receiveDelStock((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->receiveProductKey((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->on_clearbutton_clicked(); break;
        case 15: _t->on_ProductManagement_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProductManagerForm::*)(ProductItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductManagerForm::productdataSent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProductManagerForm::*)(ProductItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProductManagerForm::clickProductSent)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ProductManagerForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ProductManagerForm.offsetsAndSize,
    qt_meta_data_ProductManagerForm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ProductManagerForm_t
, QtPrivate::TypeAndForceComplete<ProductManagerForm, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ProductItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ProductItem *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ProductManagerForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProductManagerForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProductManagerForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ProductManagerForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ProductManagerForm::productdataSent(ProductItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProductManagerForm::clickProductSent(ProductItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
