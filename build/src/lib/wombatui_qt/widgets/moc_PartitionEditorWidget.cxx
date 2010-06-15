/****************************************************************************
** Meta object code from reading C++ file 'PartitionEditorWidget.h'
**
** Created: Tue Jun 15 18:44:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/wombatui_qt/widgets/PartitionEditorWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PartitionEditorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__PartitionEditorWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   30,   30,   30, 0x0a,
      49,   30,   30,   30, 0x0a,
      67,   30,   30,   30, 0x0a,
      86,   30,   30,   30, 0x0a,
     110,   30,   30,   30, 0x0a,
     133,   30,   30,   30, 0x0a,
     152,   30,   30,   30, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_wombat__PartitionEditorWidget[] = {
    "wombat::PartitionEditorWidget\0\0"
    "createPartition()\0deletePartition()\0"
    "reloadPartitions()\0writePartitionMembers()\0"
    "readPartitionMembers()\0verifyPartitions()\0"
    "createPartitionScheme()\0"
};

const QMetaObject wombat::PartitionEditorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__PartitionEditorWidget,
      qt_meta_data_wombat__PartitionEditorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::PartitionEditorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::PartitionEditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::PartitionEditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__PartitionEditorWidget))
        return static_cast<void*>(const_cast< PartitionEditorWidget*>(this));
    if (!strcmp(_clname, "Ui::PartitionEditorWidgetBase"))
        return static_cast< Ui::PartitionEditorWidgetBase*>(const_cast< PartitionEditorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::PartitionEditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createPartition(); break;
        case 1: deletePartition(); break;
        case 2: reloadPartitions(); break;
        case 3: writePartitionMembers(); break;
        case 4: readPartitionMembers(); break;
        case 5: verifyPartitions(); break;
        case 6: createPartitionScheme(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
