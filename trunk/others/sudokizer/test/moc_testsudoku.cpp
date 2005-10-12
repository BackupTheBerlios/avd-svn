/****************************************************************************
** Meta object code from reading C++ file 'testsudoku.h'
**
** Created: Tue Oct 11 16:12:06 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testsudoku.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testsudoku.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_std__sudoku__TestCell[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      37,   35,   22,   22, 0x08,
      70,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_std__sudoku__TestCell[] = {
    "std::sudoku::TestCell\0\0newDelete()\0t\0"
    "possibilities_data(QtTestTable&)\0possibilities()\0"
};

const QMetaObject std::sudoku::TestCell::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_std__sudoku__TestCell,
      qt_meta_data_std__sudoku__TestCell, 0 }
};

const QMetaObject *std::sudoku::TestCell::metaObject() const
{
    return &staticMetaObject;
}

void *std::sudoku::TestCell::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_std__sudoku__TestCell))
	return static_cast<void*>(const_cast<TestCell*>(this));
    return QObject::qt_metacast(_clname);
}

int std::sudoku::TestCell::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newDelete(); break;
        case 1: possibilities_data(*(QtTestTable*)_a[1]); break;
        case 2: possibilities(); break;
        }
        _id -= 3;
    }
    return _id;
}
