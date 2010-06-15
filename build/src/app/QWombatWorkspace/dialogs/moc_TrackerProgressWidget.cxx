/****************************************************************************
** Meta object code from reading C++ file 'TrackerProgressWidget.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QWombatWorkspace/dialogs/TrackerProgressWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackerProgressWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrackerProgressWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   39,   22,   22, 0x0a,
      75,   22,   70,   22, 0x0a,
     100,   92,   22,   22, 0x0a,
     129,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TrackerProgressWidget[] = {
    "TrackerProgressWidget\0\0cancelPressed()\0"
    "_msecs\0setTimerFrequency(uint)\0uint\0"
    "timerFrequency()\0_thread\0"
    "setModelThread(ModelThread*)\0updateState()\0"
};

const QMetaObject TrackerProgressWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TrackerProgressWidget,
      qt_meta_data_TrackerProgressWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrackerProgressWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrackerProgressWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrackerProgressWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrackerProgressWidget))
        return static_cast<void*>(const_cast< TrackerProgressWidget*>(this));
    if (!strcmp(_clname, "Ui::TrackerProgressWidgetBase"))
        return static_cast< Ui::TrackerProgressWidgetBase*>(const_cast< TrackerProgressWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TrackerProgressWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cancelPressed(); break;
        case 1: setTimerFrequency((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: { uint _r = timerFrequency();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 3: setModelThread((*reinterpret_cast< ModelThread*(*)>(_a[1]))); break;
        case 4: updateState(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TrackerProgressWidget::cancelPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
