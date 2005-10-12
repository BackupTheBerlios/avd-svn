// See COPYING file for licensing information.
/**
 * \file testCell.cpp
 * Tests for the Cell class
 */

#include "sudoku.h"
#include <QtTest>

using namespace std;
using namespace sudoku;

class TestCell : public QObject {
	Q_OBJECT
private slots:
	void everything();
};

void TestCell::everything() {
	Cell myCell(0, undecided);
	
	VERIFY(myCell.getState() == undecided);
}

QTTEST_MAIN(TestCell);
#include "testCell.moc"