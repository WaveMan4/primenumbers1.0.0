/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Nov 30 04:10:56 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x05,
      41,   12,   11,   11, 0x05,
      69,   64,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     135,   11,   11,   11, 0x08,
     160,   11,   11,   11, 0x08,
     184,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     301,   11,   11,   11, 0x08,
     327,   11,   11,   11, 0x08,
     354,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0number\0updateDisplay(qint64)\0"
    "updateProgress(qint64)\0flag\0endThread(bool)\0"
    "on_stopButton_clicked()\0"
    "on_actionStop_triggered()\0"
    "on_startButton_clicked()\0"
    "on_exitButton_clicked()\0"
    "on_actionExit_triggered()\0"
    "on_toLine_textChanged(QString)\0"
    "on_fromLine_textChanged(QString)\0"
    "on_actionStart_triggered()\0"
    "updateDisplaySlot(qint64)\0"
    "updateProgressSlot(qint64)\0"
    "threadEndSlot(bool)\0"
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
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateDisplay((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: updateProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: endThread((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_stopButton_clicked(); break;
        case 4: on_actionStop_triggered(); break;
        case 5: on_startButton_clicked(); break;
        case 6: on_exitButton_clicked(); break;
        case 7: on_actionExit_triggered(); break;
        case 8: on_toLine_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: on_fromLine_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: on_actionStart_triggered(); break;
        case 11: updateDisplaySlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 12: updateProgressSlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 13: threadEndSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::updateDisplay(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::updateProgress(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::endThread(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
