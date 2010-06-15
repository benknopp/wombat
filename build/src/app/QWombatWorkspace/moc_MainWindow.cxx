/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/app/QWombatWorkspace/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   11,   11,   11, 0x05,
      44,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   11,   11,   11, 0x09,
      82,   11,   11,   11, 0x09,
      96,   11,   11,   11, 0x09,
     111,   11,   11,   11, 0x09,
     133,   11,   11,   11, 0x09,
     147,   11,   11,   11, 0x09,
     163,   11,   11,   11, 0x09,
     178,   11,   11,   11, 0x09,
     197,   11,   11,   11, 0x09,
     212,   11,   11,   11, 0x09,
     230,   11,   11,   11, 0x09,
     242,   11,   11,   11, 0x09,
     262,   11,   11,   11, 0x09,
     282,   11,   11,   11, 0x09,
     315,   11,   11,   11, 0x09,
     337,   11,   11,   11, 0x09,
     358,   11,   11,   11, 0x09,
     384,   11,   11,   11, 0x09,
     401,   11,   11,   11, 0x09,
     420,   11,   11,   11, 0x09,
     439,   11,   11,   11, 0x09,
     469,   11,   11,   11, 0x09,
     501,   11,   11,   11, 0x09,
     524,   11,   11,   11, 0x09,
     548,   11,   11,   11, 0x09,
     573,   11,   11,   11, 0x09,
     593,   11,   11,   11, 0x09,
     616,   11,   11,   11, 0x09,
     656,  639,   11,   11, 0x09,
     687,  639,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0projectOpened()\0projectClosed()\0"
    "projectModified()\0newProjectRequest()\0"
    "openProject()\0setupProject()\0"
    "closeAndSaveProject()\0saveProject()\0"
    "saveProjectAs()\0closeProject()\0"
    "toggleFullscreen()\0toggleLogger()\0"
    "showPreferences()\0showAbout()\0"
    "updateWindowTitle()\0updateWindowState()\0"
    "writeBodyStateToCurrentProject()\0"
    "startProjectThreads()\0stopProjectThreads()\0"
    "initModelControllerDone()\0drawBodyVoxels()\0"
    "calculateWeights()\0updateVoxelspace()\0"
    "handleParticleFilterCreated()\0"
    "handleParticleFilterDestroyed()\0"
    "handleTrackerRunning()\0handleTrackerSleeping()\0"
    "handleBodyScaleChanged()\0handleBodyChanged()\0"
    "handlePtcFileChanged()\0updateMdiWindowState()\0"
    "_voxelspaceIndex\0handleVoxelspaceLoaded(size_t)\0"
    "requestVoxelspace(size_t)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Ui::MainWindowBase"))
        return static_cast< Ui::MainWindowBase*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: projectOpened(); break;
        case 1: projectClosed(); break;
        case 2: projectModified(); break;
        case 3: newProjectRequest(); break;
        case 4: openProject(); break;
        case 5: setupProject(); break;
        case 6: closeAndSaveProject(); break;
        case 7: saveProject(); break;
        case 8: saveProjectAs(); break;
        case 9: closeProject(); break;
        case 10: toggleFullscreen(); break;
        case 11: toggleLogger(); break;
        case 12: showPreferences(); break;
        case 13: showAbout(); break;
        case 14: updateWindowTitle(); break;
        case 15: updateWindowState(); break;
        case 16: writeBodyStateToCurrentProject(); break;
        case 17: startProjectThreads(); break;
        case 18: stopProjectThreads(); break;
        case 19: initModelControllerDone(); break;
        case 20: drawBodyVoxels(); break;
        case 21: calculateWeights(); break;
        case 22: updateVoxelspace(); break;
        case 23: handleParticleFilterCreated(); break;
        case 24: handleParticleFilterDestroyed(); break;
        case 25: handleTrackerRunning(); break;
        case 26: handleTrackerSleeping(); break;
        case 27: handleBodyScaleChanged(); break;
        case 28: handleBodyChanged(); break;
        case 29: handlePtcFileChanged(); break;
        case 30: updateMdiWindowState(); break;
        case 31: handleVoxelspaceLoaded((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 32: requestVoxelspace((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::projectOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::projectClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::projectModified()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
