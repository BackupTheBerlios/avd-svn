// See COPYING file for licensing information.
/**
 * \file testsudoku.cpp
 * Tests for the classes inside src/sudoku.cpp
 */

#include "testsudoku.h"
#include "../src/sudoku.cpp"

using namespace std;
using namespace sudoku;

void TestCell::newDelete() {
	{
		Cell myCell(1); // constructor called here
	} // destructor called here
}


void TestCell::possibilities_data(QtTestTable &t) {
	short unsigned int arr1[2] = {1, 2}, arr2[2] = {1, 2};
	
	t.defineElement("ushort", "e1");
	t.defineElement("ushort", "e2");
	
    *t.newData("constructor with no args") <<  arr1[0] << arr2[0];
    *t.newData("constructor with no args") <<  arr1[1] << arr2[1];
}

void TestCell::possibilities() {
    FETCH(ushort, e1);
    FETCH(ushort, e2);
	
	COMPARE(e1, e2);
}

QTTEST_APPLESS_MAIN(TestCell);
