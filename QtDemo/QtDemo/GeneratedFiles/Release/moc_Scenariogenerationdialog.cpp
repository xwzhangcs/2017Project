/****************************************************************************
** Meta object code from reading C++ file 'Scenariogenerationdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Scenariogenerationdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Scenariogenerationdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScenarioGenerationDialog_t {
    QByteArrayData data[5];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScenarioGenerationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScenarioGenerationDialog_t qt_meta_stringdata_ScenarioGenerationDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ScenarioGenerationDialog"
QT_MOC_LITERAL(1, 25, 17), // "onOutputDirectory"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 4), // "onOK"
QT_MOC_LITERAL(4, 49, 8) // "onCancel"

    },
    "ScenarioGenerationDialog\0onOutputDirectory\0"
    "\0onOK\0onCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScenarioGenerationDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScenarioGenerationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScenarioGenerationDialog *_t = static_cast<ScenarioGenerationDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onOutputDirectory(); break;
        case 1: _t->onOK(); break;
        case 2: _t->onCancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ScenarioGenerationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ScenarioGenerationDialog.data,
      qt_meta_data_ScenarioGenerationDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScenarioGenerationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScenarioGenerationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScenarioGenerationDialog.stringdata0))
        return static_cast<void*>(const_cast< ScenarioGenerationDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ScenarioGenerationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
