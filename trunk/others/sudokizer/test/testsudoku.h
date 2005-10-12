// See COPYING file for licensing information.
/**
 * \file testsudoku.h
 * Definition of the tests for the classes inside src/sudoku.h
 */

#ifndef TESTSUDOKU_H
#define TESTSUDOKU_H

#include <QtTest>
#include "../src/sudoku.h"

namespace std {
namespace sudoku {
	class TestCell: public QObject
	{
			Q_OBJECT
		private slots:
			void newDelete();
			void possibilities_data(QtTestTable &t);
			void possibilities();
	};
}
}

#endif
