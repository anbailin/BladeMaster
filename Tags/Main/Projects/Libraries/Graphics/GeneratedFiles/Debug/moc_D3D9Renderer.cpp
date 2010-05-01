/****************************************************************************
** Meta object code from reading C++ file 'D3D9Renderer.h'
**
** Created: Sat May 1 17:19:38 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/D3D9Renderer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'D3D9Renderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BM__D3D9Renderer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_BM__D3D9Renderer[] = {
    "BM::D3D9Renderer\0"
};

const QMetaObject BM::D3D9Renderer::staticMetaObject = {
    { &Renderer::staticMetaObject, qt_meta_stringdata_BM__D3D9Renderer,
      qt_meta_data_BM__D3D9Renderer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BM::D3D9Renderer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BM::D3D9Renderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BM::D3D9Renderer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BM__D3D9Renderer))
        return static_cast<void*>(const_cast< D3D9Renderer*>(this));
    return Renderer::qt_metacast(_clname);
}

int BM::D3D9Renderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Renderer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
