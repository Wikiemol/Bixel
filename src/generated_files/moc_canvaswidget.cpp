/****************************************************************************
** Meta object code from reading C++ file 'canvaswidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../canvaswidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvaswidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CanvasWidget_t {
    QByteArrayData data[22];
    char stringdata[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CanvasWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CanvasWidget_t qt_meta_stringdata_CanvasWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CanvasWidget"
QT_MOC_LITERAL(1, 13, 12), // "colorChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "styleSheet"
QT_MOC_LITERAL(4, 38, 12), // "stateChanged"
QT_MOC_LITERAL(5, 51, 10), // "changeTool"
QT_MOC_LITERAL(6, 62, 4), // "tool"
QT_MOC_LITERAL(7, 67, 15), // "openColorPicker"
QT_MOC_LITERAL(8, 83, 15), // "setCurrentColor"
QT_MOC_LITERAL(9, 99, 5), // "color"
QT_MOC_LITERAL(10, 105, 11), // "deselectAll"
QT_MOC_LITERAL(11, 117, 9), // "selectAll"
QT_MOC_LITERAL(12, 127, 6), // "zoomIn"
QT_MOC_LITERAL(13, 134, 7), // "zoomOut"
QT_MOC_LITERAL(14, 142, 10), // "updateSize"
QT_MOC_LITERAL(15, 153, 4), // "undo"
QT_MOC_LITERAL(16, 158, 4), // "redo"
QT_MOC_LITERAL(17, 163, 4), // "open"
QT_MOC_LITERAL(18, 168, 11), // "std::string"
QT_MOC_LITERAL(19, 180, 8), // "fileName"
QT_MOC_LITERAL(20, 189, 6), // "saveAs"
QT_MOC_LITERAL(21, 196, 9) // "exportPNG"

    },
    "CanvasWidget\0colorChanged\0\0styleSheet\0"
    "stateChanged\0changeTool\0tool\0"
    "openColorPicker\0setCurrentColor\0color\0"
    "deselectAll\0selectAll\0zoomIn\0zoomOut\0"
    "updateSize\0undo\0redo\0open\0std::string\0"
    "fileName\0saveAs\0exportPNG"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanvasWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   93,    2, 0x0a /* Public */,
       7,    0,   96,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
      10,    0,  100,    2, 0x0a /* Public */,
      11,    0,  101,    2, 0x0a /* Public */,
      12,    0,  102,    2, 0x0a /* Public */,
      13,    0,  103,    2, 0x0a /* Public */,
      14,    0,  104,    2, 0x0a /* Public */,
      15,    0,  105,    2, 0x0a /* Public */,
      16,    0,  106,    2, 0x0a /* Public */,
      17,    1,  107,    2, 0x0a /* Public */,
      20,    1,  110,    2, 0x0a /* Public */,
      21,    1,  113,    2, 0x0a /* Public */,

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
    QMetaType::Bool, 0x80000000 | 18,   19,
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
        case 12: { bool _r = _t->open((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->saveAs((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 14: _t->exportPNG((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
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
      qt_meta_data_CanvasWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CanvasWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanvasWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CanvasWidget::colorChanged(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CanvasWidget::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
