/****************************************************************************
** Meta object code from reading C++ file 'QPlaybackControl.h'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/wombatui_qt/widgets/QPlaybackControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPlaybackControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__QPlaybackControl[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x05,
      40,   25,   25,   25, 0x05,
      55,   25,   25,   25, 0x05,
      69,   25,   25,   25, 0x05,
      87,   25,   25,   25, 0x05,
     101,   25,   25,   25, 0x05,
     118,   25,   25,   25, 0x05,
     136,   25,   25,   25, 0x05,
     161,  152,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
     189,  184,   25,   25, 0x0a,
     223,  216,   25,   25, 0x0a,
     248,  242,   25,   25, 0x0a,
     278,   25,   25,   25, 0x0a,
     294,  290,   25,   25, 0x0a,
     309,  242,   25,   25, 0x0a,
     328,   25,   25,   25, 0x0a,
     341,   25,   25,   25, 0x0a,
     353,   25,   25,   25, 0x0a,
     366,   25,   25,   25, 0x09,
     398,  391,   25,   25, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__QPlaybackControl[] = {
    "wombat::QPlaybackControl\0\0playPressed()\0"
    "pausePressed()\0stopPressed()\0"
    "previousPressed()\0nextPressed()\0"
    "forwardPressed()\0backwardPressed()\0"
    "recordPressed()\0_frameId\0"
    "frameRequested(size_t)\0_fps\0"
    "setFramesPerSecond(double)\0_count\0"
    "setNumFrames(uint)\0_time\0"
    "setTotalTimeInSeconds(double)\0nextFrame()\0"
    "_id\0gotoFrame(int)\0gotoSecond(double)\0"
    "setPlaying()\0setPaused()\0setStopped()\0"
    "handlePlayPausePressed()\0_value\0"
    "handleSliderPositionChanged(int)\0"
};

const QMetaObject wombat::QPlaybackControl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__QPlaybackControl,
      qt_meta_data_wombat__QPlaybackControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::QPlaybackControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::QPlaybackControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::QPlaybackControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__QPlaybackControl))
        return static_cast<void*>(const_cast< QPlaybackControl*>(this));
    if (!strcmp(_clname, "Ui::PlaybackControlBase"))
        return static_cast< Ui::PlaybackControlBase*>(const_cast< QPlaybackControl*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::QPlaybackControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playPressed(); break;
        case 1: pausePressed(); break;
        case 2: stopPressed(); break;
        case 3: previousPressed(); break;
        case 4: nextPressed(); break;
        case 5: forwardPressed(); break;
        case 6: backwardPressed(); break;
        case 7: recordPressed(); break;
        case 8: frameRequested((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 9: setFramesPerSecond((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: setNumFrames((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 11: setTotalTimeInSeconds((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: nextFrame(); break;
        case 13: gotoFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: gotoSecond((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: setPlaying(); break;
        case 16: setPaused(); break;
        case 17: setStopped(); break;
        case 18: handlePlayPausePressed(); break;
        case 19: handleSliderPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void wombat::QPlaybackControl::playPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void wombat::QPlaybackControl::pausePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void wombat::QPlaybackControl::stopPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void wombat::QPlaybackControl::previousPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void wombat::QPlaybackControl::nextPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void wombat::QPlaybackControl::forwardPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void wombat::QPlaybackControl::backwardPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void wombat::QPlaybackControl::recordPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void wombat::QPlaybackControl::frameRequested(size_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
