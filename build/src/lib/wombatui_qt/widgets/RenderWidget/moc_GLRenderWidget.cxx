/****************************************************************************
** Meta object code from reading C++ file 'GLRenderWidget.h'
**
** Created: Tue Jun 15 18:44:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/lib/wombatui_qt/widgets/RenderWidget/GLRenderWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLRenderWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__GLRenderWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      46,   23,   23,   23, 0x0a,
      71,   64,   23,   23, 0x0a,
      91,   23,   23,   23, 0x2a,
     114,  107,   23,   23, 0x09,
     136,  107,   23,   23, 0x09,
     164,  107,   23,   23, 0x09,
     185,   23,   23,   23, 0x09,
     199,   23,   23,   23, 0x09,
     224,   23,   23,   23, 0x09,
     252,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__GLRenderWidget[] = {
    "wombat::GLRenderWidget\0\0toggleRenderEngines()\0"
    "saveFrameBuffer()\0_pause\0pausePlayback(bool)\0"
    "pausePlayback()\0_state\0toggleWireframe(bool)\0"
    "toggleBackgroundColor(bool)\0"
    "toggleShowMeta(bool)\0togglePause()\0"
    "setLowQualityRendering()\0"
    "setMediumQualityRendering()\0"
    "setHighQualityRendering()\0"
};

const QMetaObject wombat::GLRenderWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_wombat__GLRenderWidget,
      qt_meta_data_wombat__GLRenderWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::GLRenderWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::GLRenderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::GLRenderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__GLRenderWidget))
        return static_cast<void*>(const_cast< GLRenderWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int wombat::GLRenderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: toggleRenderEngines(); break;
        case 1: saveFrameBuffer(); break;
        case 2: pausePlayback((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: pausePlayback(); break;
        case 4: toggleWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: toggleBackgroundColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: toggleShowMeta((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: togglePause(); break;
        case 8: setLowQualityRendering(); break;
        case 9: setMediumQualityRendering(); break;
        case 10: setHighQualityRendering(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
