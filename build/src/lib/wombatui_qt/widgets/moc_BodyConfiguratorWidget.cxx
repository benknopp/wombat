/****************************************************************************
** Meta object code from reading C++ file 'BodyConfiguratorWidget.h'
**
** Created: Tue Jun 15 18:44:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/wombatui_qt/widgets/BodyConfiguratorWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BodyConfiguratorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__BodyConfiguratorWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   32,   31,   31, 0x05,
      99,   84,   31,   31, 0x05,
     145,   31,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
     166,  159,   31,   31, 0x0a,
     182,   31,   31,   31, 0x0a,
     194,   31,   31,   31, 0x0a,
     206,   31,   31,   31, 0x0a,
     226,  220,   31,   31, 0x0a,
     254,   31,   31,   31, 0x0a,
     270,   31,   31,   31, 0x0a,
     296,  286,   31,   31, 0x0a,
     319,   31,   31,   31, 0x0a,
     337,   31,   31,   31, 0x0a,
     370,  356,   31,   31, 0x09,
     412,  406,   31,   31, 0x09,
     449,  406,   31,   31, 0x09,
     495,  484,   31,   31, 0x09,
     525,  484,   31,   31, 0x09,
     554,   31,   31,   31, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__BodyConfiguratorWidget[] = {
    "wombat::BodyConfiguratorWidget\0\0_state\0"
    "stateChanged(const wombat::BodyStateVector*)\0"
    "_name,_x,_y,_z\0"
    "bodyPartResized(QString,double,double,double)\0"
    "seedChanged()\0_index\0loadState(uint)\0"
    "loadState()\0saveState()\0deleteState()\0"
    "_item\0showState(QListWidgetItem*)\0"
    "saveBodySizes()\0loadBodySizes()\0"
    "_filename\0loadBodySizes(QString)\0"
    "readProjectData()\0writeProjectData()\0"
    "_item,_column\0itemActivated(QTreeWidgetItem*,int)\0"
    "_node\0bodyJointNodeSelected(BodyJointNode)\0"
    "bodyPartNodeSelected(BodyPartNode)\0"
    "_value,_id\0bodyJointChanged(double,uint)\0"
    "bodySizeChanged(double,uint)\0"
    "setSeedPoint()\0"
};

const QMetaObject wombat::BodyConfiguratorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__BodyConfiguratorWidget,
      qt_meta_data_wombat__BodyConfiguratorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::BodyConfiguratorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::BodyConfiguratorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::BodyConfiguratorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__BodyConfiguratorWidget))
        return static_cast<void*>(const_cast< BodyConfiguratorWidget*>(this));
    if (!strcmp(_clname, "Ui::BodyConfiguratorWidgetBase"))
        return static_cast< Ui::BodyConfiguratorWidgetBase*>(const_cast< BodyConfiguratorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::BodyConfiguratorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< const wombat::BodyStateVector*(*)>(_a[1]))); break;
        case 1: bodyPartResized((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 2: seedChanged(); break;
        case 3: loadState((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: loadState(); break;
        case 5: saveState(); break;
        case 6: deleteState(); break;
        case 7: showState((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: saveBodySizes(); break;
        case 9: loadBodySizes(); break;
        case 10: loadBodySizes((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: readProjectData(); break;
        case 12: writeProjectData(); break;
        case 13: itemActivated((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: bodyJointNodeSelected((*reinterpret_cast< const BodyJointNode(*)>(_a[1]))); break;
        case 15: bodyPartNodeSelected((*reinterpret_cast< const BodyPartNode(*)>(_a[1]))); break;
        case 16: bodyJointChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 17: bodySizeChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 18: setSeedPoint(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void wombat::BodyConfiguratorWidget::stateChanged(const wombat::BodyStateVector * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void wombat::BodyConfiguratorWidget::bodyPartResized(const QString _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void wombat::BodyConfiguratorWidget::seedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
