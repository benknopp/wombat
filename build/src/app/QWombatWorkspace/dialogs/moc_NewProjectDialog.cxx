/****************************************************************************
** Meta object code from reading C++ file 'NewProjectDialog.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/app/QWombatWorkspace/dialogs/NewProjectDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewProjectDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewProjectDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      29,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   17,   17,   17, 0x09,
      59,   17,   17,   17, 0x09,
      79,   17,   17,   17, 0x09,
      99,   17,   17,   17, 0x09,
     119,   17,   17,   17, 0x09,
     132,   17,   17,   17, 0x09,
     148,   17,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_NewProjectDialog[] = {
    "NewProjectDialog\0\0accepted()\0rejected()\0"
    "modelModeChanged()\0setMatlabModelDir()\0"
    "setMatlabBodyFile()\0setNativeBodyFile()\0"
    "setPtcFile()\0cancelRequest()\0okRequest()\0"
};

const QMetaObject NewProjectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewProjectDialog,
      qt_meta_data_NewProjectDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewProjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewProjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewProjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewProjectDialog))
        return static_cast<void*>(const_cast< NewProjectDialog*>(this));
    if (!strcmp(_clname, "Ui::NewProjectDialogBase"))
        return static_cast< Ui::NewProjectDialogBase*>(const_cast< NewProjectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewProjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: accepted(); break;
        case 1: rejected(); break;
        case 2: modelModeChanged(); break;
        case 3: setMatlabModelDir(); break;
        case 4: setMatlabBodyFile(); break;
        case 5: setNativeBodyFile(); break;
        case 6: setPtcFile(); break;
        case 7: cancelRequest(); break;
        case 8: okRequest(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void NewProjectDialog::accepted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NewProjectDialog::rejected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
