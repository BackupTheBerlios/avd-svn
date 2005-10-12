// See COPYING file for licensing information.
/**
 * \file sudokizer.cpp
 * Main program loop.
 */
 
/**
 * \mainpage Sudokizer documentation
 * Sudokizer is an Edulix artifact
 *
 * \section intro_sec Introduction
 * This is the documention extracted from the very source code of this program. Sudokizer is a
 * test program which resolves sudokus and it has been developed as an exercise where to put some
 * developing knowledge into practicse, like the use of <a href="http://www.scons.org/">scons</a>
 * (a software construction tool), <a href="http://www.doxygen.org">doxygen</a> (a code
 * documentation system), <a href="http://doc.trolltech.com/solutions/4/qttestlib/">QTestLib</a>
 * (an unit test library), <a href="http://subversion.tigris.org/">subversion</a> (a control
 * version system).
 * 
 * \section design_overview Design Overview
 */

#include "sudoku.h"
#include <iostream>

using namespace std;
using namespace sudoku;

/**
 * Main program loop.
 * \param	argc	number of command line arguments
 * \param	argv	list of arguments
 */
int main(int argc, char** argv) {
		
// 		Board game;
// 		
// 		game[0][0]->set(1);
// 		game[0][2]->set(5);
// 		game[0][3]->set(2);
// 		game[0][5]->set(8);
// 		game[0][6]->set(6);
// 		
// 		game[1][3]->set(9);
// 		game[1][5]->set(7);
// 		game[1][6]->set(8);
// 		game[1][8]->set(2);
// 		
// 		game[2][5]->set(1);
// 		game[2][6]->set(7);
// 		
// 		game[3][0]->set(9);
// 		game[3][1]->set(5);
// 		game[3][2]->set(7);
// 		game[3][6]->set(1);
// 		
// 		game[4][1]->set(6);
// 		game[4][2]->set(8);
// 		game[4][5]->set(9);
// 		game[4][6]->set(3);
// 		
// 		game[5][0]->set(3);
// 		game[5][7]->set(7);
// 		
// 		game[6][2]->set(1);
// 		game[6][4]->set(3);
// 		game[6][8]->set(7);
// 		
// 		game[7][2]->set(6);
// 		game[7][6]->set(2);
// 		game[7][7]->set(4);
// 		
// 		game[8][1]->set(9);
// 		game[8][3]->set(6);
// 		game[8][4]->set(1);
// 		
		// Doesn't work yet: 48 unwind:
		/* 
		game[0][5]->set(3);
		game[0][7]->set(6);
		
		game[1][7]->set(1);
		
		game[2][1]->set(9);
		game[2][2]->set(7);
		game[2][3]->set(5);
		game[2][7]->set(8);
		
		game[3][5]->set(9);
		game[3][6]->set(2);
		
		game[4][2]->set(8);
		game[4][4]->set(7);
		game[4][6]->set(4);
		
		game[5][2]->set(3);
		game[5][4]->set(6);
		
		game[6][1]->set(1);
		game[6][5]->set(2);
		game[6][6]->set(8);
		game[6][7]->set(9);
		
		game[7][1]->set(4);
		
		game[8][1]->set(5);
		game[8][3]->set(1);
		*/
		
		// Works fine: Naked single/Single Candidate:
		/*
		game[1][6]->set(1);
		
		game[2][6]->set(7);
		
		game[3][6]->set(2);
		game[3][7]->set(9);
		
		game[4][8]->set(4);
		
		game[5][1]->set(8);
		game[5][2]->set(3);
		
		game[6][6]->set(5);
		*/
		
		// Works fine: Hidden single/Unique Candidate:
		/*
		game[1][3]->set(2);
		
		game[3][4]->set(6);
		
		game[5][4]->set(8);
		
		game[8][5]->set(2);
		*/
		
		
// 		Display::show(game);
		
		Board solution;
		Board Sudoku = Board(&solution, 30);
		Display::show(Sudoku);
		cout << "Hit <Enter> to resolve" << endl;
		getchar();
		Display::show(solution);
		getchar();
		
		return 0;
	}
