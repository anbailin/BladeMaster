/****************************************************************************
** Meta object code from reading C++ file 'GameApplication.h'
**
** Created: Wed Apr 21 14:45:20 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GamePrivate.h"
#include "..\..\Src\GameApplication.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameApplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BM__GameApplication[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x09,
      28,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_BM__GameApplication[] = {
    "BM::GameApplication\0\0Exit()\0Tick()\0"
};

const QMetaObject BM::GameApplication::staticMetaObject = {
    { &Application::staticMetaObject, qt_meta_stringdata_BM__GameApplication,
      qt_meta_data_BM__GameApplication, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BM::GameApplication::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BM::GameApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BM::GameApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BM__GameApplication))
        return static_cast<void*>(const_cast< GameApplication*>(this));
    return Application::qt_metacast(_clname);
}

int BM::GameApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Application::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Exit(); break;
        case 1: Tick(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
