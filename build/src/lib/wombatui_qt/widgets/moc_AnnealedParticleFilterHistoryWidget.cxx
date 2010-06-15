/****************************************************************************
** Meta object code from reading C++ file 'AnnealedParticleFilterHistoryWidget.h'
**
** Created: Tue Jun 15 18:44:16 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/lib/wombatui_qt/widgets/AnnealedParticleFilterHistoryWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnnealedParticleFilterHistoryWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wombat__AnnealedParticleFilterHistoryWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      52,   45,   44,   44, 0x05,
     109,   45,   44,   44, 0x05,

 // slots: signature, parameters, type, tag, flags
     179,   44,   44,   44, 0x09,
     198,   44,   44,   44, 0x09,
     227,   44,   44,   44, 0x09,
     263,   44,   44,   44, 0x09,
     298,   44,   44,   44, 0x09,
     317,   44,   44,   44, 0x09,
     356,  349,   44,   44, 0x09,
     387,  349,   44,   44, 0x09,
     419,  349,   44,   44, 0x09,
     447,  349,   44,   44, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_wombat__AnnealedParticleFilterHistoryWidget[] = {
    "wombat::AnnealedParticleFilterHistoryWidget\0"
    "\0_state\0"
    "requestBodyConfiguration(const wombat::BodyStateVector*)\0"
    "requestCopyBodyConfigurationToProject(const wombat::BodyStateVector*)\0"
    "updateTreeWidget()\0showCurrentItemInformation()\0"
    "applyCurrentParticleConfiguration()\0"
    "copyCurrentParticleConfiguration()\0"
    "saveToMatlabFile()\0findBestParticleConfiguration()\0"
    "_index\0showTimestepInformation(ulong)\0"
    "showPartitionInformation(ulong)\0"
    "showLayerInformation(ulong)\0"
    "showParticleInformation(ulong)\0"
};

const QMetaObject wombat::AnnealedParticleFilterHistoryWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_wombat__AnnealedParticleFilterHistoryWidget,
      qt_meta_data_wombat__AnnealedParticleFilterHistoryWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wombat::AnnealedParticleFilterHistoryWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wombat::AnnealedParticleFilterHistoryWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wombat::AnnealedParticleFilterHistoryWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wombat__AnnealedParticleFilterHistoryWidget))
        return static_cast<void*>(const_cast< AnnealedParticleFilterHistoryWidget*>(this));
    if (!strcmp(_clname, "Ui::AnnealedParticleFilterHistoryWidgetBase"))
        return static_cast< Ui::AnnealedParticleFilterHistoryWidgetBase*>(const_cast< AnnealedParticleFilterHistoryWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int wombat::AnnealedParticleFilterHistoryWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: requestBodyConfiguration((*reinterpret_cast< const wombat::BodyStateVector*(*)>(_a[1]))); break;
        case 1: requestCopyBodyConfigurationToProject((*reinterpret_cast< const wombat::BodyStateVector*(*)>(_a[1]))); break;
        case 2: updateTreeWidget(); break;
        case 3: showCurrentItemInformation(); break;
        case 4: applyCurrentParticleConfiguration(); break;
        case 5: copyCurrentParticleConfiguration(); break;
        case 6: saveToMatlabFile(); break;
        case 7: findBestParticleConfiguration(); break;
        case 8: showTimestepInformation((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 9: showPartitionInformation((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 10: showLayerInformation((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 11: showParticleInformation((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void wombat::AnnealedParticleFilterHistoryWidget::requestBodyConfiguration(const wombat::BodyStateVector * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void wombat::AnnealedParticleFilterHistoryWidget::requestCopyBodyConfigurationToProject(const wombat::BodyStateVector * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
