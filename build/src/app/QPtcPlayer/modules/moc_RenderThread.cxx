/****************************************************************************
** Meta object code from reading C++ file 'RenderThread.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QPtcPlayer/modules/RenderThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__RenderThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      32,   21,   21,   21, 0x05,
      41,   21,   21,   21, 0x05,
      60,   51,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   21,   21,   21, 0x0a,
      86,   21,   21,   21, 0x0a,
      94,   21,   21,   21, 0x0a,
     101,   51,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_wombat__RenderThread[] = {
    "wombat::RenderThread\0\0playing()\0"
    "paused()\0stopped()\0_frameId\0"
    "frameLoaded(ulong)\0play()\0pause()\0"
    "stop()\0gotoFrame(int)\0"
};

const QMetaObject wombat::RenderThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_wombat__RenderThread,
      qt_meta_data_wombat__RenderThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::RenderThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::RenderThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::RenderThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__RenderThread))
        return static_cast<void*>(const_cast< RenderThread*>(this));
    return QThread::qt_metacast(_clname);
}

int wombat::RenderThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playing(); break;
        case 1: paused(); break;
        case 2: stopped(); break;
        case 3: frameLoaded((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 4: play(); break;
        case 5: pause(); break;
        case 6: stop(); break;
        case 7: gotoFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void wombat::RenderThread::playing()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void wombat::RenderThread::paused()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void wombat::RenderThread::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void wombat::RenderThread::frameLoaded(unsigned long _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
