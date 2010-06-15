/****************************************************************************
** Meta object code from reading C++ file 'TrackerControlWidget.h'
**
** Created: Tue Jun 15 18:44:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/wombatui_qt/widgets/TrackerControlWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackerControlWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__TrackerControlWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x05,
      51,   29,   29,   29, 0x05,
      72,   29,   29,   29, 0x05,
      85,   29,   29,   29, 0x05,
     102,   29,   29,   29, 0x05,
     116,   29,   29,   29, 0x05,
     135,   29,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
     158,   29,   29,   29, 0x0a,
     176,   29,   29,   29, 0x0a,
     195,   29,   29,   29, 0x09,
     215,   29,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__TrackerControlWidget[] = {
    "wombat::TrackerControlWidget\0\0"
    "rasterizeRequested()\0weightingRequested()\0"
    "runClicked()\0oneStepClicked()\0"
    "stopClicked()\0parameterChanged()\0"
    "updateParticleFilter()\0readProjectData()\0"
    "writeProjectData()\0updateProjectData()\0"
    "printProjectMap()\0"
};

const QMetaObject wombat::TrackerControlWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__TrackerControlWidget,
      qt_meta_data_wombat__TrackerControlWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::TrackerControlWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::TrackerControlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::TrackerControlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__TrackerControlWidget))
        return static_cast<void*>(const_cast< TrackerControlWidget*>(this));
    if (!strcmp(_clname, "Ui::TrackerControlWidgetBase"))
        return static_cast< Ui::TrackerControlWidgetBase*>(const_cast< TrackerControlWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::TrackerControlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rasterizeRequested(); break;
        case 1: weightingRequested(); break;
        case 2: runClicked(); break;
        case 3: oneStepClicked(); break;
        case 4: stopClicked(); break;
        case 5: parameterChanged(); break;
        case 6: updateParticleFilter(); break;
        case 7: readProjectData(); break;
        case 8: writeProjectData(); break;
        case 9: updateProjectData(); break;
        case 10: printProjectMap(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void wombat::TrackerControlWidget::rasterizeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void wombat::TrackerControlWidget::weightingRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void wombat::TrackerControlWidget::runClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void wombat::TrackerControlWidget::oneStepClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void wombat::TrackerControlWidget::stopClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void wombat::TrackerControlWidget::parameterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void wombat::TrackerControlWidget::updateParticleFilter()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
