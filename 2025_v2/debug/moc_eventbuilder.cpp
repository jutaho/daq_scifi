/****************************************************************************
** Meta object code from reading C++ file 'eventbuilder.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../eventbuilder.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eventbuilder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSEventBuilderENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSEventBuilderENDCLASS = QtMocHelpers::stringData(
    "EventBuilder",
    "sigInit",
    "",
    "sigDeinit",
    "sigStartLogging",
    "sigStopLogging",
    "onNewData",
    "DataReceiver*",
    "receiver",
    "onInit",
    "onDeinit",
    "onStartLogging",
    "onStopLogging"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSEventBuilderENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,
       3,    0,   69,    2, 0x06,    2 /* Public */,
       4,    0,   70,    2, 0x06,    3 /* Public */,
       5,    0,   71,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   72,    2, 0x0a,    5 /* Public */,
       9,    0,   75,    2, 0x09,    7 /* Protected */,
      10,    0,   76,    2, 0x09,    8 /* Protected */,
      11,    0,   77,    2, 0x09,    9 /* Protected */,
      12,    0,   78,    2, 0x09,   10 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject EventBuilder::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSEventBuilderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSEventBuilderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSEventBuilderENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EventBuilder, std::true_type>,
        // method 'sigInit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigDeinit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigStartLogging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sigStopLogging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNewData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<DataReceiver *, std::false_type>,
        // method 'onInit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeinit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartLogging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStopLogging'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void EventBuilder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EventBuilder *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sigInit(); break;
        case 1: _t->sigDeinit(); break;
        case 2: _t->sigStartLogging(); break;
        case 3: _t->sigStopLogging(); break;
        case 4: _t->onNewData((*reinterpret_cast< std::add_pointer_t<DataReceiver*>>(_a[1]))); break;
        case 5: _t->onInit(); break;
        case 6: _t->onDeinit(); break;
        case 7: _t->onStartLogging(); break;
        case 8: _t->onStopLogging(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DataReceiver* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EventBuilder::*)();
            if (_t _q_method = &EventBuilder::sigInit; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EventBuilder::*)();
            if (_t _q_method = &EventBuilder::sigDeinit; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EventBuilder::*)();
            if (_t _q_method = &EventBuilder::sigStartLogging; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EventBuilder::*)();
            if (_t _q_method = &EventBuilder::sigStopLogging; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *EventBuilder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventBuilder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSEventBuilderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EventBuilder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void EventBuilder::sigInit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void EventBuilder::sigDeinit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void EventBuilder::sigStartLogging()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void EventBuilder::sigStopLogging()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
