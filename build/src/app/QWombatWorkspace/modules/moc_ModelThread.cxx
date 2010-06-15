/****************************************************************************
** Meta object code from reading C++ file 'ModelThread.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QWombatWorkspace/modules/ModelThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModelThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      24,   12,   12,   12, 0x05,
      38,   12,   12,   12, 0x05,
      48,   12,   12,   12, 0x05,
      67,   12,   12,   12, 0x05,
      91,   12,   12,   12, 0x05,
     117,   12,   12,   12, 0x05,
     134,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     159,  152,   12,   12, 0x0a,
     219,  204,   12,   12, 0x0a,
     264,   12,   12,   12, 0x0a,
     278,   12,   12,   12, 0x0a,
     297,   12,   12,   12, 0x0a,
     313,   12,   12,   12, 0x0a,
     339,   12,   12,   12, 0x0a,
     354,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ModelThread[] = {
    "ModelThread\0\0initDone()\0bodyChanged()\0"
    "stopped()\0voxelspaceLoaded()\0"
    "particleFilterCreated()\0"
    "particleFilterDestroyed()\0trackerRunning()\0"
    "trackerSleeping()\0_state\0"
    "setBodyState(const wombat::BodyStateVector*)\0"
    "_name,_x,_y,_z\0"
    "resizeBodyPart(QString,double,double,double)\0"
    "rebuildBody()\0testIntersection()\0"
    "startTracking()\0startSingleStepTracking()\0"
    "stopTracking()\0updateByProject()\0"
};

const QMetaObject ModelThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ModelThread,
      qt_meta_data_ModelThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModelThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModelThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModelThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModelThread))
        return static_cast<void*>(const_cast< ModelThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ModelThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: initDone(); break;
        case 1: bodyChanged(); break;
        case 2: stopped(); break;
        case 3: voxelspaceLoaded(); break;
        case 4: particleFilterCreated(); break;
        case 5: particleFilterDestroyed(); break;
        case 6: trackerRunning(); break;
        case 7: trackerSleeping(); break;
        case 8: setBodyState((*reinterpret_cast< const wombat::BodyStateVector*(*)>(_a[1]))); break;
        case 9: resizeBodyPart((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 10: rebuildBody(); break;
        case 11: testIntersection(); break;
        case 12: startTracking(); break;
        case 13: startSingleStepTracking(); break;
        case 14: stopTracking(); break;
        case 15: updateByProject(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ModelThread::initDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ModelThread::bodyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ModelThread::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ModelThread::voxelspaceLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ModelThread::particleFilterCreated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ModelThread::particleFilterDestroyed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ModelThread::trackerRunning()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ModelThread::trackerSleeping()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
