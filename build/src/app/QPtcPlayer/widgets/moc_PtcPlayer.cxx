/****************************************************************************
** Meta object code from reading C++ file 'PtcPlayer.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QPtcPlayer/widgets/PtcPlayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PtcPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__PtcPlayer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   19,   18,   18, 0x0a,
      48,   18,   18,   18, 0x0a,
      71,   62,   18,   18, 0x0a,
     105,   96,   18,   18, 0x0a,
     126,   18,   18,   18, 0x0a,
     140,   18,   18,   18, 0x09,
     147,   18,   18,   18, 0x09,
     155,   18,   18,   18, 0x09,
     162,   18,   18,   18, 0x09,
     172,   18,   18,   18, 0x09,
     183,   18,   18,   18, 0x09,
     190,   18,   18,   18, 0x09,
     201,   18,   18,   18, 0x09,
     208,   18,   18,   18, 0x09,
     221,   18,   18,   18, 0x09,
     228,   18,   18,   18, 0x09,
     242,   18,   18,   18, 0x09,
     255,   18,   18,   18, 0x09,
     274,  263,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__PtcPlayer[] = {
    "wombat::PtcPlayer\0\0_filename\0"
    "setSource(QString)\0renderFrame()\0"
    "_frameId\0handleFrameLoaded(ulong)\0"
    "_message\0showMessage(QString)\0"
    "updateState()\0play()\0pause()\0stop()\0"
    "forward()\0backward()\0next()\0previous()\0"
    "open()\0screenshot()\0info()\0coordsystem()\0"
    "fullscreen()\0about()\0_numFrames\0"
    "numFramesChanged(size_t)\0"
};

const QMetaObject wombat::PtcPlayer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_wombat__PtcPlayer,
      qt_meta_data_wombat__PtcPlayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::PtcPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::PtcPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::PtcPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__PtcPlayer))
        return static_cast<void*>(const_cast< PtcPlayer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int wombat::PtcPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setSource((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: renderFrame(); break;
        case 2: handleFrameLoaded((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 3: showMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: updateState(); break;
        case 5: play(); break;
        case 6: pause(); break;
        case 7: stop(); break;
        case 8: forward(); break;
        case 9: backward(); break;
        case 10: next(); break;
        case 11: previous(); break;
        case 12: open(); break;
        case 13: screenshot(); break;
        case 14: info(); break;
        case 15: coordsystem(); break;
        case 16: fullscreen(); break;
        case 17: about(); break;
        case 18: numFramesChanged((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
