/****************************************************************************
** Meta object code from reading C++ file 'ConfiguratorWidget.h'
**
** Created: Tue Jun 15 18:44:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/lib/wombatui_qt/widgets/BodyConfigurator/ConfiguratorWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfiguratorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__ConfiguratorWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,   28,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   27,   27,   27, 0x09,
      78,   27,   27,   27, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__ConfiguratorWidget[] = {
    "wombat::ConfiguratorWidget\0\0_scale\0"
    "bodyScaleChanged(double)\0changeBodyScale()\0"
    "printNodeTree()\0"
};

const QMetaObject wombat::ConfiguratorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__ConfiguratorWidget,
      qt_meta_data_wombat__ConfiguratorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::ConfiguratorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::ConfiguratorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::ConfiguratorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__ConfiguratorWidget))
        return static_cast<void*>(const_cast< ConfiguratorWidget*>(this));
    if (!strcmp(_clname, "Ui::ConfiguratorWidgetBase"))
        return static_cast< Ui::ConfiguratorWidgetBase*>(const_cast< ConfiguratorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::ConfiguratorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: bodyScaleChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: changeBodyScale(); break;
        case 2: printNodeTree(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void wombat::ConfiguratorWidget::bodyScaleChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
