/****************************************************************************
** Meta object code from reading C++ file 'bixelwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bixelwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bixelwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BixelWindow_t {
    QByteArrayData data[25];
    char stringdata[341];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_BixelWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_BixelWindow_t qt_meta_stringdata_BixelWindow = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 15),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 11),
QT_MOC_LITERAL(4, 41, 14),
QT_MOC_LITERAL(5, 56, 11),
QT_MOC_LITERAL(6, 68, 8),
QT_MOC_LITERAL(7, 77, 11),
QT_MOC_LITERAL(8, 89, 19),
QT_MOC_LITERAL(9, 109, 18),
QT_MOC_LITERAL(10, 128, 11),
QT_MOC_LITERAL(11, 140, 11),
QT_MOC_LITERAL(12, 152, 11),
QT_MOC_LITERAL(13, 164, 10),
QT_MOC_LITERAL(14, 175, 12),
QT_MOC_LITERAL(15, 188, 17),
QT_MOC_LITERAL(16, 206, 19),
QT_MOC_LITERAL(17, 226, 17),
QT_MOC_LITERAL(18, 244, 14),
QT_MOC_LITERAL(19, 259, 15),
QT_MOC_LITERAL(20, 275, 18),
QT_MOC_LITERAL(21, 294, 9),
QT_MOC_LITERAL(22, 304, 12),
QT_MOC_LITERAL(23, 317, 9),
QT_MOC_LITERAL(24, 327, 12)
    },
    "BixelWindow\0new_file_signal\0\0save_signal\0"
    "save_as_signal\0std::string\0fileName\0"
    "open_signal\0export_image_signal\0"
    "preferences_signal\0undo_signal\0"
    "redo_signal\0copy_signal\0cut_signal\0"
    "paste_signal\0select_all_signal\0"
    "deselect_all_signal\0reset_view_signal\0"
    "zoom_in_signal\0zoom_out_signal\0"
    "custom_zoom_signal\0open_slot\0save_as_slot\0"
    "save_slot\0stateChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BixelWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06,
       3,    0,  120,    2, 0x06,
       4,    1,  121,    2, 0x06,
       7,    1,  124,    2, 0x06,
       8,    0,  127,    2, 0x06,
       9,    0,  128,    2, 0x06,
      10,    0,  129,    2, 0x06,
      11,    0,  130,    2, 0x06,
      12,    0,  131,    2, 0x06,
      13,    0,  132,    2, 0x06,
      14,    0,  133,    2, 0x06,
      15,    0,  134,    2, 0x06,
      16,    0,  135,    2, 0x06,
      17,    0,  136,    2, 0x06,
      18,    0,  137,    2, 0x06,
      19,    0,  138,    2, 0x06,
      20,    0,  139,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      21,    0,  140,    2, 0x08,
      22,    0,  141,    2, 0x08,
      23,    0,  142,    2, 0x08,
      24,    0,  143,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BixelWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BixelWindow *_t = static_cast<BixelWindow *>(_o);
        switch (_id) {
        case 0: _t->new_file_signal(); break;
        case 1: _t->save_signal(); break;
        case 2: _t->save_as_signal((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 3: _t->open_signal((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 4: _t->export_image_signal(); break;
        case 5: _t->preferences_signal(); break;
        case 6: _t->undo_signal(); break;
        case 7: _t->redo_signal(); break;
        case 8: _t->copy_signal(); break;
        case 9: _t->cut_signal(); break;
        case 10: _t->paste_signal(); break;
        case 11: _t->select_all_signal(); break;
        case 12: _t->deselect_all_signal(); break;
        case 13: _t->reset_view_signal(); break;
        case 14: _t->zoom_in_signal(); break;
        case 15: _t->zoom_out_signal(); break;
        case 16: _t->custom_zoom_signal(); break;
        case 17: _t->open_slot(); break;
        case 18: _t->save_as_slot(); break;
        case 19: _t->save_slot(); break;
        case 20: _t->stateChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::new_file_signal)) {
                *result = 0;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::save_signal)) {
                *result = 1;
            }
        }
        {
            typedef void (BixelWindow::*_t)(const std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::save_as_signal)) {
                *result = 2;
            }
        }
        {
            typedef void (BixelWindow::*_t)(const std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::open_signal)) {
                *result = 3;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::export_image_signal)) {
                *result = 4;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::preferences_signal)) {
                *result = 5;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::undo_signal)) {
                *result = 6;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::redo_signal)) {
                *result = 7;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::copy_signal)) {
                *result = 8;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::cut_signal)) {
                *result = 9;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::paste_signal)) {
                *result = 10;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::select_all_signal)) {
                *result = 11;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::deselect_all_signal)) {
                *result = 12;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::reset_view_signal)) {
                *result = 13;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::zoom_in_signal)) {
                *result = 14;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::zoom_out_signal)) {
                *result = 15;
            }
        }
        {
            typedef void (BixelWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BixelWindow::custom_zoom_signal)) {
                *result = 16;
            }
        }
    }
}

const QMetaObject BixelWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BixelWindow.data,
      qt_meta_data_BixelWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *BixelWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BixelWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BixelWindow.stringdata))
        return static_cast<void*>(const_cast< BixelWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BixelWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void BixelWindow::new_file_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BixelWindow::save_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void BixelWindow::save_as_signal(const std::string & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BixelWindow::open_signal(const std::string & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BixelWindow::export_image_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void BixelWindow::preferences_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void BixelWindow::undo_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void BixelWindow::redo_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void BixelWindow::copy_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void BixelWindow::cut_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void BixelWindow::paste_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void BixelWindow::select_all_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void BixelWindow::deselect_all_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void BixelWindow::reset_view_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void BixelWindow::zoom_in_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void BixelWindow::zoom_out_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}

// SIGNAL 16
void BixelWindow::custom_zoom_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}
QT_END_MOC_NAMESPACE
