/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "showEvent",
    "",
    "QShowEvent*",
    "event",
    "closeEvent",
    "QCloseEvent*",
    "on_timer",
    "on_pushLogSettings_pressed",
    "on_actionConnect_triggered",
    "on_actionDisconnect_triggered",
    "on_actionHost_IP_triggered",
    "on_actionTrigger_config_triggered",
    "on_actionDevices_triggered",
    "on_pushRun_pressed",
    "on_pushLogging_pressed",
    "on_pushDisplay_pressed",
    "on_pushButton_exit_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x0a,    1 /* Public */,
       5,    1,   95,    2, 0x0a,    3 /* Public */,
       7,    0,   98,    2, 0x0a,    5 /* Public */,
       8,    0,   99,    2, 0x08,    6 /* Private */,
       9,    0,  100,    2, 0x08,    7 /* Private */,
      10,    0,  101,    2, 0x08,    8 /* Private */,
      11,    0,  102,    2, 0x08,    9 /* Private */,
      12,    0,  103,    2, 0x08,   10 /* Private */,
      13,    0,  104,    2, 0x08,   11 /* Private */,
      14,    0,  105,    2, 0x08,   12 /* Private */,
      15,    0,  106,    2, 0x08,   13 /* Private */,
      16,    0,  107,    2, 0x08,   14 /* Private */,
      17,    0,  108,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'showEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QShowEvent *, std::false_type>,
        // method 'closeEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCloseEvent *, std::false_type>,
        // method 'on_timer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushLogSettings_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionConnect_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionDisconnect_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionHost_IP_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionTrigger_config_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionDevices_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushRun_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushLogging_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushDisplay_pressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_exit_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->showEvent((*reinterpret_cast< std::add_pointer_t<QShowEvent*>>(_a[1]))); break;
        case 1: _t->closeEvent((*reinterpret_cast< std::add_pointer_t<QCloseEvent*>>(_a[1]))); break;
        case 2: _t->on_timer(); break;
        case 3: _t->on_pushLogSettings_pressed(); break;
        case 4: _t->on_actionConnect_triggered(); break;
        case 5: _t->on_actionDisconnect_triggered(); break;
        case 6: _t->on_actionHost_IP_triggered(); break;
        case 7: _t->on_actionTrigger_config_triggered(); break;
        case 8: _t->on_actionDevices_triggered(); break;
        case 9: _t->on_pushRun_pressed(); break;
        case 10: _t->on_pushLogging_pressed(); break;
        case 11: _t->on_pushDisplay_pressed(); break;
        case 12: _t->on_pushButton_exit_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
