/****************************************************************************
** Meta object code from reading C++ file 'ScalarSelectionWidget.h'
**
** Created: Tue Jun 15 18:44:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/wombatui_qt/widgets/ScalarSelectionWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScalarSelectionWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__ScalarSelectionWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   31,   30,   30, 0x05,
      70,   59,   30,   30, 0x05,

 // slots: signature, parameters, type, tag, flags
     116,   96,   30,   30, 0x0a,
     153,  147,   30,   30, 0x0a,
     173,  167,   30,   30, 0x0a,
     190,   31,   30,   30, 0x0a,
     211,  207,   30,   30, 0x0a,
     238,   30,  231,   30, 0x0a,
     244,   30,  231,   30, 0x0a,
     250,   30,  231,   30, 0x0a,
     269,   30,  261,   30, 0x0a,
     276,   31,   30,   30, 0x09,
     295,   31,   30,   30, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__ScalarSelectionWidget[] = {
    "wombat::ScalarSelectionWidget\0\0_value\0"
    "valueChanged(double)\0_value,_id\0"
    "valueChanged(double,uint)\0_min,_max,_stepSize\0"
    "setRange(double,double,double)\0_type\0"
    "setType(uint)\0_name\0setName(QString)\0"
    "setValue(double)\0_id\0setIdentifier(uint)\0"
    "double\0min()\0max()\0stepSize()\0QString\0"
    "name()\0sliderChanged(int)\0"
    "spinBoxChanged(double)\0"
};

const QMetaObject wombat::ScalarSelectionWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__ScalarSelectionWidget,
      qt_meta_data_wombat__ScalarSelectionWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::ScalarSelectionWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::ScalarSelectionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::ScalarSelectionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__ScalarSelectionWidget))
        return static_cast<void*>(const_cast< ScalarSelectionWidget*>(this));
    if (!strcmp(_clname, "Ui::ScalarSelectionWidgetBase"))
        return static_cast< Ui::ScalarSelectionWidgetBase*>(const_cast< ScalarSelectionWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::ScalarSelectionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: valueChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: setRange((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: setType((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: setIdentifier((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 7: { double _r = min();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 8: { double _r = max();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 9: { double _r = stepSize();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: sliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: spinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void wombat::ScalarSelectionWidget::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void wombat::ScalarSelectionWidget::valueChanged(double _t1, unsigned  _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
