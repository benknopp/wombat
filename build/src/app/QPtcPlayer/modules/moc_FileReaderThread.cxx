/****************************************************************************
** Meta object code from reading C++ file 'FileReaderThread.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QPtcPlayer/modules/FileReaderThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileReaderThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__FileReaderThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x05,
      39,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   52,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_wombat__FileReaderThread[] = {
    "wombat::FileReaderThread\0\0fileOpened()\0"
    "fileClosed()\0_frameId,_data\0"
    "getFrameData(int,PtcFrameData**)\0"
};

const QMetaObject wombat::FileReaderThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_wombat__FileReaderThread,
      qt_meta_data_wombat__FileReaderThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::FileReaderThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::FileReaderThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::FileReaderThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__FileReaderThread))
        return static_cast<void*>(const_cast< FileReaderThread*>(this));
    return QThread::qt_metacast(_clname);
}

int wombat::FileReaderThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fileOpened(); break;
        case 1: fileClosed(); break;
        case 2: getFrameData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< PtcFrameData**(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void wombat::FileReaderThread::fileOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void wombat::FileReaderThread::fileClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
