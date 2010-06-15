/****************************************************************************
** Meta object code from reading C++ file 'PtcReaderThread.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QWombatWorkspace/threads/PtcReaderThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PtcReaderThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__PtcReaderThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,   25,   24,   24, 0x05,
      55,   24,   24,   24, 0x05,
      80,   68,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
     112,  105,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_wombat__PtcReaderThread[] = {
    "wombat::PtcReaderThread\0\0_filename\0"
    "fileOpened(QString)\0fileClosed()\0"
    "_frameIndex\0voxelspaceLoaded(size_t)\0"
    "_index\0readVoxelspace(size_t)\0"
};

const QMetaObject wombat::PtcReaderThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_wombat__PtcReaderThread,
      qt_meta_data_wombat__PtcReaderThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::PtcReaderThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::PtcReaderThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::PtcReaderThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__PtcReaderThread))
        return static_cast<void*>(const_cast< PtcReaderThread*>(this));
    return QThread::qt_metacast(_clname);
}

int wombat::PtcReaderThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fileOpened((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: fileClosed(); break;
        case 2: voxelspaceLoaded((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 3: readVoxelspace((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void wombat::PtcReaderThread::fileOpened(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void wombat::PtcReaderThread::fileClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void wombat::PtcReaderThread::voxelspaceLoaded(size_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
