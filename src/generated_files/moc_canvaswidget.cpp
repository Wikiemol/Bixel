/****************************************************************************
** Meta object code from reading C++ file 'canvaswidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../canvaswidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvaswidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CanvasWidget_t {
    QByteArrayData data[21];
    char stringdata[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CanvasWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CanvasWidget_t qt_meta_stringdata_CanvasWidget = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 10),
QT_MOC_LITERAL(4, 38, 12),
QT_MOC_LITERAL(5, 51, 10),
QT_MOC_LITERAL(6, 62, 4),
QT_MOC_LITERAL(7, 67, 15),
QT_MOC_LITERAL(8, 83, 15),
QT_MOC_LITERAL(9, 99, 5),
QT_MOC_LITERAL(10, 105, 11),
QT_MOC_LITERAL(11, 117, 9),
QT_MOC_LITERAL(12, 127, 6),
QT_MOC_LITERAL(13, 134, 7),
QT_MOC_LITERAL(14, 142, 10),
QT_MOC_LITERAL(15, 153, 4),
QT_MOC_LITERAL(16, 158, 4),
QT_MOC_LITERAL(17, 163, 4),
QT_MOC_LITERAL(18, 168, 11),
QT_MOC_LITERAL(19, 180, 8),
QT_MOC_LITERAL(20, 189, 6)
    },
    "CanvasWidget\0colorChanged\0\0styleSheet\0"
    "stateChanged\0changeTool\0tool\0"
    "openColorPicker\0setCurrentColor\0color\0"
    "deselectAll\0selectAll\0zoomIn\0zoomOut\0"
    "updateSize\0undo\0redo\0open\0std::string\0"
    "fileName\0saveAs\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanvasWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06,
       4,    0,   87,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    1,   88,    2, 0x0a,
       7,    0,   91,    2, 0x0a,
       8,    1,   92,    2, 0x0a,
      10,    0,   95,    2, 0x0a,
      11,    0,   96,    2, 0x0a,
      12,    0,   97,    2, 0x0a,
      13,    0,   98,    2, 0x0a,
      14,    0,   99,    2, 0x0a,
      15,    0,  100,    2, 0x0a,
      16,    0,  101,    2, 0x0a,
      17,    1,  102,    2, 0x0a,
      20,    1,  105,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void CanvasWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CanvasWidget *_t = static_cast<CanvasWidget *>(_o);
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->stateChanged(); break;
        case 2: _t->changeTool((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->openColorPicker(); break;
        case 4: _t->setCurrentColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 5: _t->deselectAll(); break;
        case 6: _t->selectAll(); break;
        case 7: _t->zoomIn(); break;
        case 8: _t->zoomOut(); break;
        case 9: _t->updateSize(); break;
        case 10: _t->undo(); break;
        case 11: _t->redo(); break;
        case 12: _t->open((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 13: _t->saveAs((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CanvasWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CanvasWidget::colorChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (CanvasWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CanvasWidget::stateChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CanvasWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CanvasWidget.data,
      qt_meta_data_CanvasWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CanvasWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanvasWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CanvasWidget.stringdata))
        return static_cast<void*>(const_cast< CanvasWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CanvasWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void CanvasWidget::colorChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CanvasWidget::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE