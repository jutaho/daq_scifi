/****************************************************************************
** Meta object code from reading C++ file 'display.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../display.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'display.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSBPMDisplayENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSBPMDisplayENDCLASS = QtMocHelpers::stringData(
    "BPMDisplay",
    "showEvent",
    "",
    "QShowEvent*",
    "event",
    "onButtonClicked",
    "QAbstractButton*",
    "button",
    "onSaveBackgroundClicked",
    "onLoadBackgroundClicked",
    "onCheckBoxStateChanged",
    "state",
    "onSaveCalibrationClicked",
    "onLoadCalibrationClicked",
    "onCalibrationCheckBoxChanged",
    "onExpertModeStateChanged",
    "updateMean",
    "value",
    "updateRms",
    "updateMax",
    "updateStatus"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBPMDisplayENDCLASS[] = {

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
       8,    0,   98,    2, 0x0a,    5 /* Public */,
       9,    0,   99,    2, 0x0a,    6 /* Public */,
      10,    1,  100,    2, 0x0a,    7 /* Public */,
      12,    0,  103,    2, 0x0a,    9 /* Public */,
      13,    0,  104,    2, 0x0a,   10 /* Public */,
      14,    1,  105,    2, 0x0a,   11 /* Public */,
      15,    1,  108,    2, 0x0a,   13 /* Public */,
      16,    1,  111,    2, 0x0a,   15 /* Public */,
      18,    1,  114,    2, 0x0a,   17 /* Public */,
      19,    1,  117,    2, 0x0a,   19 /* Public */,
      20,    1,  120,    2, 0x0a,   21 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::UShort,   17,
    QMetaType::Void, QMetaType::UShort,   17,
    QMetaType::Void, QMetaType::UShort,   17,
    QMetaType::Void, QMetaType::UShort,   17,

       0        // eod
};

Q_CONSTINIT const QMetaObject BPMDisplay::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSBPMDisplayENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBPMDisplayENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBPMDisplayENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BPMDisplay, std::true_type>,
        // method 'showEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QShowEvent *, std::false_type>,
        // method 'onButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractButton *, std::false_type>,
        // method 'onSaveBackgroundClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLoadBackgroundClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCheckBoxStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onSaveCalibrationClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLoadCalibrationClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCalibrationCheckBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onExpertModeStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateMean'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned short, std::false_type>,
        // method 'updateRms'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned short, std::false_type>,
        // method 'updateMax'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned short, std::false_type>,
        // method 'updateStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned short, std::false_type>
    >,
    nullptr
} };

void BPMDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BPMDisplay *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showEvent((*reinterpret_cast< std::add_pointer_t<QShowEvent*>>(_a[1]))); break;
        case 1: _t->onButtonClicked((*reinterpret_cast< std::add_pointer_t<QAbstractButton*>>(_a[1]))); break;
        case 2: _t->onSaveBackgroundClicked(); break;
        case 3: _t->onLoadBackgroundClicked(); break;
        case 4: _t->onCheckBoxStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->onSaveCalibrationClicked(); break;
        case 6: _t->onLoadCalibrationClicked(); break;
        case 7: _t->onCalibrationCheckBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->onExpertModeStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->updateMean((*reinterpret_cast< std::add_pointer_t<ushort>>(_a[1]))); break;
        case 10: _t->updateRms((*reinterpret_cast< std::add_pointer_t<ushort>>(_a[1]))); break;
        case 11: _t->updateMax((*reinterpret_cast< std::add_pointer_t<ushort>>(_a[1]))); break;
        case 12: _t->updateStatus((*reinterpret_cast< std::add_pointer_t<ushort>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *BPMDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BPMDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBPMDisplayENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int BPMDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
