// See COPYING file for licensing information.
/**
 * \file sudoku.h
 * Definition of the classes needed for a sudoku game.
 */

#ifndef SUDOKU_H
#define SUDOKU_H
	
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cstdio>


namespace std {
namespace sudoku {
	class Display;
	
	typedef enum{undecided,definitive} state;
	typedef enum{cols,rows,boxes} tGet;
	
	
	class Cell {
		state State;
		short unsigned int Possibilities[9];
		
		friend class Box;
		friend class Line;
		friend class Solver;
		friend class Generator;
		friend class Display;
		
		static void check(short unsigned int myP) throw(domain_error);
		void fastDelPossibility(short unsigned int myP) throw(logic_error);
		bool fastCanDel(short unsigned int myP) const;
		void fastAddPossibility(short unsigned int myP);
		bool fastIsPossible(short unsigned int myP) const;
		void fastSet(short unsigned int myP);
		
	public:
		Cell(short unsigned int P = 0, state S = undecided);
		Cell(const Cell& copy);
		void copy(const Cell& copy);
		~Cell();
		
		short unsigned int* getPossibilities();
		void addPossibility(short unsigned int myP) throw(domain_error);
		void delPossibility(short unsigned int myP) throw(logic_error);
		void set(short unsigned int myP) throw(domain_error);
		short unsigned int get() throw(logic_error);
		bool isPossible(short unsigned int myP) const;
		state getState() const;
		void setState(state S);
		void erase();
	};
	
	class Box {
		Cell *elements[3][3];
		
	public:
		Cell** operator[] (short unsigned int i) throw(domain_error);
		
		void delPossibility(short unsigned int myP, Cell& cell) throw(logic_error);
		void addPossibility(short unsigned int myP);
		bool isPossible(short unsigned int myP, Cell& cell) const;
		bool canDel(short unsigned int myP, Cell& cell) const;
	};
	
	class Line {
		Cell *elements[9];
		
	public:
		operator Cell**();
		
		void delPossibility(short unsigned int myP, Cell& cell) throw(logic_error);
		void addPossibility(short unsigned int myP);
		bool isPossible(short unsigned int myP, Cell& cell) const;
		bool canDel(short unsigned int myP, Cell& cell) const;
		void deleteAll();
		Cell copy(short unsigned int i) const throw(domain_error);
	};
	
	class Board {
		Line Cols[9], Rows[9];
		Box Boxes[3][3];
		
		friend class Solver;
		friend class Generator;
		
	public:
		Board();
		Board(Board* solution, short unsigned int solvedCells = 30);
		Board(const Board& copy);
		~Board();
		
		Line& operator[](short unsigned int i) throw (domain_error);
		
		state getState();
		Line& getCol(short unsigned int i) throw(domain_error);
		Line& getRow(short unsigned int i) throw(domain_error);
		Box& getBox(short unsigned int i, short unsigned int j) throw(domain_error);
		Cell& getCell(short unsigned int i, short unsigned int j) throw(domain_error);
		void setCell(short unsigned int i, short unsigned int j, short unsigned int value) throw(domain_error);
	};
	
	class Solver {
	 	Solver();
		
		static void updatePossibilities(Board& Sudoku) throw(logic_error);
		static bool solveCell(Cell& cell, Line& row, Line& col, Box& box) throw(domain_error, logic_error);
	public:
		static void resolve(Board& Sudoku);
	};
	
	class Display {
		Display();
	public:
		static void show(Board& Sudoku);
	};
	
	class Generator {
	 	Generator();
	public:
		static bool solveCell(Cell& cell, Line& row, Line& col, Box& box, short unsigned int sol) throw(domain_error, logic_error);
		static short unsigned int nextValue(short unsigned int mod = 10, unsigned short int min = 1);
		
	};
}
}
#endif
