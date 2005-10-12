// See COPYING file for licensing information.
/**
 * \file sudoku.cpp
 * Implementation of the classes needed for a sudoku game.
 */
#include "sudoku.h"
#include <iostream>
#include <string>
#include <cstdlib>

namespace std {
namespace sudoku {
	/**
	* Cell Constructor.
	* Initilize a cell setting its state (undecided by default) and initial possibility
	* \arg		P	initial cell possibility. optional argument, set to 0 (which means unset) by default.
	* If it's 0, all the range [1,9] will be added automatically the posibilities list
	* \arg		S	initial state. optional argument, set to undecided by default
	*/
	inline Cell::Cell(short unsigned int P, state S)
		: State(S)
	{
		if(P > 0) {
			Possibilities[0] = P;
			for(int i = 1; i < 9; i++)
				Possibilities[i] = 0;
			
			State = S;
		} else {
			for(int i = 0; i < 9; i++)
				Possibilities[i] = i + 1;
			
			State = undecided;
		}
	}
	
	/**
	 * Cell copy function
	 * \arg	copy	Reference to the cell to copy
	 */
	inline void Cell::copy(const Cell& copy)
	{
		State = copy.State;
		
		for(short unsigned int i = 0; i < 9; i++)
			Possibilities[i] = copy.Possibilities[i];
	}
	
	/**
	 * Cell copy function
	 * \arg	copy	Reference to the cell to copy
	 */
	inline Cell::Cell(const Cell& copy)
	{
		State = copy.State;
		
		for(short unsigned int i = 0; i < 9; i++)
			Possibilities[i] = copy.Possibilities[i];
	}
	
	/**
	 * Cell copy destructor
	 */
	inline Cell::~Cell() {
	}
	
	/**
	* Checks validity of a given posiblity.
	* Given possibility must be between 1 and 9.
	* \arg		myP				Value to check
	* \throw	domain_error	Thrown if an argument not within the range [1,9] is provided
	*/
	void Cell::check(short unsigned int myP) throw(domain_error) {
		if(myP >= 10 || myP == 0)
			throw domain_error("possibilities can only be in a range of short unsigned integers [1,9], " \
			"but it was attempted to use 0 or one of value over 9");
	}
	
	/**
	* Removes a given value from the possibilities list without checking the given value validity.
	* Removes the given value to the possibilities list if it's in there. If after performing the
	* elimination there's only one possibility left, State is automatically set to definitive.
	* \arg		myP				the value to remove
	* \throw	logic_error		Thrown if cell state is undecided instead of definitive
	*/
	void Cell::fastDelPossibility(short unsigned int myP) throw(logic_error) {
		for(int i = 0; i < 10; i++) {
			if(Possibilities[i] == 0)
				return;
			else if (Possibilities[i] == myP) {
				// Eliminate this value and shift to the left the remaining ones
				for(; i < 9; i++) {
					if(Possibilities[i + 1] == 0) {
						Possibilities[i] = 0;
						
						// If it's the only element left, automatically set it to definitive
						if(i == 1)
							State = definitive;
						
						break;
					} else
						Possibilities[i] = Possibilities[i + 1];
				}
				break;
			}
		}
		
		if(Possibilities[0] == 0) {
			throw logic_error("No possibility is left, all of them were deleted");
		}
	}
	
	/**
	* Adds a given possibility to the list without previously checking if the given value
	* is with [1, 9]. Adds the given value to the possibilities list if it's not there already.
	* \arg		myP				the value to add
	*/
	void Cell::fastAddPossibility(short unsigned int myP) {
		for(int i = 0; i < 10; i++) {
			// - If a possibility is set to 0, as it is by default, it means there are no more of them
			// in the rest of the array
			if(Possibilities[i] == 0) {
				Possibilities[i] = myP;
				return;
			} else if (Possibilities[i] == myP)
				return;
		}
	}
	
	/**
	* Returns wether a given value is possible or not without checking the given value validity.
	* \arg		myP	the value to test
	* \return 	true if the given value is in the posibilities list, or false if not.
	*/
	bool Cell::fastIsPossible(short unsigned int myP) const {
		for(int i = 0; i < 10; i++) {
			if(Possibilities[i] == 0)
				return false;
			else if (Possibilities[i] == myP)
				return true;
		}
		return false;
	}
	
	/**
	 * States if it would be allowed or not to try to eliminate a possibility
	 */
	bool Cell::fastCanDel(short unsigned int myP)  const {
		if (State == undecided)
			return true;
		else if (myP == Possibilities[0]) {
			return false;
		}
// 		printf(">> myP = %i vs. Possibilities[0] = %i\n", myP, Possibilities[0]);
		
		return true;
	}
	
	/**
	* Sets the definitive value of the cell.
	* \arg		myP				the value to set
	*/
	inline void Cell::fastSet(short unsigned int myP) {
		State = definitive;
		Possibilities[0] = myP;
		Possibilities[1] = 0; // the list "ends" in the first element set to zero
	}
	
	/**
	* Returns the available possibilities to the user.
	*/
	inline short unsigned int* Cell::getPossibilities() {
		return Possibilities;
	}
	
	/**
	* Adds a given possibility to the list.
	* Adds the given value to the possibilities list if it's not there already.
	* \arg		myP				the value to add
	* \throw	domain_error	Thrown if myP is not within the range [1,9]
	*/
	void Cell::addPossibility(short unsigned int myP) throw(domain_error) {
		
		check(myP); // this can throw domain_error
		
		fastAddPossibility(myP);
	}
	
	/**
	* Sets the definitive value of the cell.
	* \arg		myP				the value to set
	* \throw	domain_error	Thrown if myP is not within the range [1,9], and also thrown if
	* we try to set a value which is not part of the possibilities list
	*/
	inline void Cell::set(short unsigned int myP) throw(domain_error) {
	
		check(myP); // this can throw domain_error
		
		if(!fastIsPossible(myP))
			throw domain_error("Attempted to set a definitive value to a cell which was not within " \
			"the possibilities list of the cell");
		
		fastSet(myP);
	}
	
	
	
	
	/**
	* Gets the definitive value of the cell.
	* This can only be done if the cell state is definitive.
	* \return	Returns the definitive value of the cell
	* \throw	logic_error		Thrown if cell state is undecided instead of definitive
	*/
	inline short unsigned int Cell::get() throw(logic_error) {
		if(State == definitive)
			return Possibilities[0];
		else
			throw logic_error("Tried to get cell value when it's still undecided");
	}
	
	/**
	* Removes a given value from the possibilities list.
	* Removes the given value to the possibilities list if it's in there.
	* If a given value is not within [1,9], we won't even try to delete it.
	* \arg		myP				the value to remove
	* \throw 	logic_error		Thrown if no possibility is left, all of them were deleted
	*/
	void Cell::delPossibility(short unsigned int myP) throw(logic_error) {
		try {
			check(myP);
		} catch(...) {
			return;
		}
		
		fastDelPossibility(myP); // this can throw logic_error
	}
	
	/**
	* Returns wether a given value is possible or not
	* If the argument is out of the range [1, 9] it returns directly false.
	* \arg		myP		the value to test
	* \return 	true if the given value is in the posibilities list, or false if not.
	*/
	bool Cell::isPossible(short unsigned int myP) const {
		try {
			check(myP);
		} catch(...) {
			return false;
		}
		
 		return fastIsPossible(myP);
	}
	
	/**
	* Returns current Cell state.
	* It can be either undecided or definitive.
	* \return Current cell state.
	*/
	inline state Cell::getState() const {
		return State;
	}
	
	/**
	* Sets cell state.
	* It can be set to either undecided or definitive.
	* \arg	cell state to be set
	*/
	inline void Cell::setState(state S) {
		
		// Clean the possiblities list if needed
		if(State == definitive && S == undecided)
		{
			// Note that as we always need at least one value in the possiblities list
			// we keep the first one (Possibilities[0])
			for(int i = 1; i < 9; i++)
				Possibilities[i] = 0;
		}
		
		State = S;
	}
	
	/**
	* Cell brought to the broadest state: state undecided and all possibilities.
	*/
	inline void Cell::erase() {
		State = undecided;
		
		for(int i = 0; i < 9; i++)
			Possibilities[i] = i + 1;
	}
	
	/**
	* Returns the requested element.
	* \arg		i	'x' index
	* \return	An array of 3 pointers to Cells corresponding with those of the Box that
	*	have the requested 'x' index.
	* \throw	domain_error	Thrown if 'i' argument is not within the range [0,2]
	*/
	Cell** Box::operator[] (short unsigned int i) throw(domain_error) {
		if(i < 3)
			return elements[i];
		else
			throw domain_error("Tried to access to an illegal array 'x' index for the elements of a Box");
	}
	
	/**
	* Removes a given value from the possibilities list of every cell in the Box but from a given one.
	* Removes the given value from the possibilities lists if it's in there.
	* If a given value is not within [1,9], we won't even try to delete it.
	* \arg		cell	Cell reference to the cell not to update
	* \arg		myP				the value to remove
	 * \throw 	logic_error		Thrown if no possibility is left in any of the cells
	*/
	void Box::delPossibility(short unsigned int myP, Cell &cell) throw(logic_error) {
		try {
			Cell::check(myP);
		} catch(...) {
			return;
		}
		
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				if(elements[i][j] != &cell)
					elements[i][j]->fastDelPossibility(myP); // this can throw logic_error
	}
	
	
	/**
	* Adds a given possibility to the possibilities list of each cell of the box
	* \arg		myP				the value to remove
	 * \throw 	domain_error	Thrown if a given value is not within [1,9]
	*/
	void Box::addPossibility(short unsigned int myP) {
		try {
			Cell::check(myP);
		} catch(...) {
			return;
		}
		
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				elements[i][j]->fastAddPossibility(myP);
	}
	
	/**
	* Returns wether a given value is possible in at least one of the cells of the Box, without testing
	* the given cell. If the value is out of the range [1, 9] it returns directly false.
	* \arg		myP		the value to test
	* \arg		cell	Cell reference to the cell not to check
	* \return 	flase if the given value is in not possible in any other cell in the Box.
	*/
	bool Box::isPossible(short unsigned int myP, Cell& cell) const {
		try {
			Cell::check(myP);
		} catch(...) {
			return false;
		}
		
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				if(elements[i][j] != &cell && elements[i][j]->isPossible(myP))
					return true;
		
		return false;
	}
	
	/**
	 * States if it would be allowed or not to try to eliminate a possibility in all of the
	 * cells but the given one
	* \arg		myP		the value to test
	* \arg		cell	Cell reference to the cell not to check
	 */
	bool Box::canDel(short unsigned int myP, Cell& cell) const {
		try {
			Cell::check(myP);
		} catch(...) {
			return true;
		}
		
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				if(elements[i][j] != &cell && !elements[i][j]->fastCanDel(myP))
					return false;
		
		return true;
	}
	
	/**
	* Automatic conversion operator used to access transparently to Line elements.
	* \return An array of 9 pointers to Cells correspoding to the Line elements.
	*/
	Line::operator Cell**() {
		return elements;
	}
	
	/**
	* Deletes the list of pointers to Cells correspoding to the Line elements, which
	* should had been previously dynamically allocated and should not to have been deallocated yet.
	*/
	void Line::deleteAll() {
		for(short unsigned int i = 0; i < 9; i++)
			delete elements[i];
	}
	
	/**
	* Removes a given value from the possibilities list of every cell in the Line but a given cell.
	* Removes the given value from the possibilities lists if it's in there.
	* If a given value is not within [1,9], we won't even try to delete it.
	* \arg		myP				the value to remove
	* \arg		cell	Cell reference to the cell not to update
	 * \throw 	logic_error		Thrown if no possibility is left in any of the cells
	*/
	void Line::delPossibility(short unsigned int myP, Cell& cell) throw(logic_error) {
		try {
			Cell::check(myP);
		} catch(...) {
			return;
		}
		
		for(int i = 0; i < 9; i++)
			if(elements[i] != &cell)
				elements[i]->fastDelPossibility(myP); // this can throw logic_error
			
		
	}
	
	/**
	* Adds a given possibility to the possibilities list of each cell of the Line
	* \arg		myP				the value to remove
	 * \throw 	domain_error	Thrown if a given value is not within [1,9]
	*/
	void Line::addPossibility(short unsigned int myP) {
		try {
			Cell::check(myP);
		} catch(...) {
			return;
		}
		
		for(int i = 0; i < 3; i++)
			elements[i]->fastAddPossibility(myP);
	}
	
	/**
	* Returns wether a given value is possible in at least one of the cells of the Line, without testing
	* the given cell. If the value is out of the range [1, 9] it returns directly false.
	* \arg		myP		the value to test
	* \arg		cell	Cell reference to the cell not to check
	* \return 	flase if the given value is in not possible in any other cell in the Line.
	*/
	bool Line::isPossible(short unsigned int myP, Cell& cell) const {
		try {
			Cell::check(myP);
		} catch(...) {
			return false;
		}
		
		for(int i = 0; i < 9; i++)
			if(elements[i] != &cell && elements[i]->isPossible(myP))
				return true;
		
		return false;
	}
	
	/**
	 * States if it would be allowed or not to try to eliminate a possibility in all of the
	 * cells but the given one
	* \arg		myP		the value to test
	* \arg		cell	Cell reference to the cell not to check
	 */
	bool Line::canDel(short unsigned int myP, Cell& cell) const {
		try {
			Cell::check(myP);
		} catch(...) {
			return true;
		}
		
		for(int i = 0; i < 9; i++)
				if(elements[i] != &cell && !elements[i]->fastCanDel(myP))
					return false;
		
		return true;
	}
	
	/**
	 * Returns a copy of the Cell with index i within elements array
	 * \arg	i	Index of the Cell to copy
	 * \throw	domain_error If the index is not within the range [0,8]
	 * \return	Using the copy constructor, copies
	 */
	Cell Line::copy(short unsigned int i) const throw(domain_error) {
		Cell::check(i - 1);
		
		Cell c = *elements[i];
		return c;
	}
	
	/**
	* Constructor for a sudoku Board.
	* Initialises the lists of columns, rows and boxes with empty dynamically allocated Cells.
	* Note that each cell is pointed by one column, one row and one box.
	*/
	Board::Board() {
		for(short unsigned int i = 0, ii = 0, I = 0; I < 9; I++, (I % 3 == 0) ? i++ : i, ii = I % 3) {
			for(short unsigned int j = 0, jj = 0, J = 0; J < 9; J++, (J % 3 == 0) ? j++ : j, jj = J % 3) {
 				Boxes[i][j][ii][jj] = new Cell();
 				Rows[I][J] = Boxes[i][j][ii][jj];
 				Cols[J][I] = Rows[I][J];
			}
		}
	}
	/**
	 * Constructor for a random sudoku board.
	 * Creates randomly a solveable game.
	 * \arg	solution	Board where the solution to this random game will be stored
	 * \arg	solvedCells	Nomber of cells solved in the created game
	 */
	Board::Board(Board* solution, short unsigned int solvedCells) {
		bool iterate = true;
		short unsigned int tolerance = 30;
		
		// initialize the cells
		for(short unsigned int i = 0, ii = 0, I = 0; I < 9; I++, (I % 3 == 0) ? i++ : i, ii = I % 3) {
			for(short unsigned int j = 0, jj = 0, J = 0; J < 9; J++, (J % 3 == 0) ? j++ : j, jj = J % 3) {
 				Rows[I][J] = new Cell();
 				Boxes[i][j][ii][jj] = Rows[I][J];
 				Cols[J][I] = Rows[I][J];
			}
		}
		
		// In each iteration, a potential "game" is created from scratch (a clean board), and the loop
		// iterates till it creates a solveable game
		while(iterate) {
			// Erase board cells
			for(short unsigned I = 0; I < 9; I++)
				for(short unsigned int J = 0; J < 9; J++)
 					Rows[I][J]->erase();
			
			short unsigned int state = 0;
			bool solved;
			
			// Set a cell a new cell is set to definitive state
			while(state < solvedCells) {
				short unsigned int I, J, i, j, val;
				
				// Pseudo randomly Locate an undecided cell
				do {
					I = Generator::nextValue(9,0);
					J = Generator::nextValue(9,0);
					i = I / 3;
					j = J / 3;
				} while (Rows[I][J]->getState());
				
				short unsigned int tries = 0;
				solved = false;
				
				// Try <tolerance> times to solve it with randomly generated values
				do {
					tries++;
					val = Generator::nextValue();
					solved = Generator::solveCell(*Rows[I][J], Rows[I], Cols[J], Boxes[i][j], val);
				} while (!solved && tries < tolerance);
				
				
				// If after <tolerance> we couldn't solve the cell, we asume the cell
				// is not solveable and thus the game is invalid, so we'll restart
				// the creation of the game
				if(!solved)
					//reiterate
					break;
				else
					// A cell was successfully set to a definitive state
					state++;
			}
			
			// We successfully set <solvedCells> number of cells to a definitive
			// state, but the game created might be still unsolveable. so we'll try
			// to solve it. If it's not solveable, restart the creation of the game
			// from scratch.  But ff it's a valid game this constructor has finished
			// its  task
			if(solved) {
				for(short unsigned int I = 0; I < 9; I++)
					for(short unsigned int J = 0; J < 9; J++)
						solution->Rows[I][J]->copy(*Rows[I][J]);
				
				try {
					Solver::resolve(*solution); // this might throw some exceptions if the game is unsolveable
					
					// Valid game found!
					if (solution->getState() == definitive)
						iterate = false;
				} catch (...) {
					// Exceptions thrown -> game unsolveable -> reiterate -> Erase the board and reiterate
				}
			}
		}
	}
	
	/**
	 * Copy-Constructor for a sudoku Board. Creates an exact copy of the given one.
	 * \arg	copy	Reference to the board to copy
	 */
	Board::Board(const Board& copy) {
		for(short unsigned int i = 0, ii = 0, I = 0; I < 9; I++, (I % 3 == 0) ? i++ : i, ii = I % 3) {
			for(short unsigned int j = 0, jj = 0, J = 0; J < 9; J++, (J % 3 == 0) ? j++ : j, jj = J % 3) {
				const Line l = copy.Rows[I];
				Cell c = l.copy(J);
 				Boxes[i][j][ii][jj] = new Cell(c);
 				Rows[I][J] = Boxes[i][j][ii][jj];
 				Cols[J][I] = Rows[I][J];
			}
		}
	}
	
	
	/**
	* Destructor fro a sudoku Board.
	* Dynamically deallocate Board cells, which had been allocated in the constructor call.
	*/
	Board::~Board() {
		for(short unsigned int i = 0; i < 10; i++) {
 			Rows[i].deleteAll();
		}
	}
	
	/**
	 * Accessor to Board Rows.
	 * This can be easily used together with the accessor to Line elements to
	 * access directly to Board elements doing myBoard[row][col].
	 * \arg	i	row index to be accesed.
	 * \return	Requested Row reference.
	 * \throw	domain_error	Thrown if 'i' is not within the range [0,8]
	 */
	inline Line& Board::operator[](short unsigned int i) throw (domain_error) {
		if(i < 9)
			return Rows[i];
		else
			throw domain_error("Attempted to access to a non-existant column with an out-of-range 'x' index");
	}
	
	/**
	 * Returns true if all cells are set to definitive
	 */
	state Board::getState() {
		
		for(short unsigned int i = 0; i < 9; i++)
			for(short unsigned int j = 0; j < 9; j++)
				if(Rows[i][j]->getState() == undecided)
					return undecided;
		
		return definitive;
	}
	
	/**
	 * Accessor to Board Columns.
	 * This can be easily used together with the accessor to Line elements to
	 * access directly to Board elements doing myBoard[col][row].
	 * \arg	i	col index to be accesed.
	 * \return	Requested Column reference.
	 * \throw	domain_error	Thrown if 'i' is not within the range [0,8]
	 */
	inline Line& Board::getCol(short unsigned int i) throw(domain_error) {
		if (i < 9)
			return Cols[i];
		else
			throw domain_error("Attempted to access to a non-existant column with an out-of-range 'x' index");
	}
	
	/**
	* Return the request Row
	* \arg	i	row index of the row within the board
	* \return 	A Line object reference correspoding with the requested Row
	* \throw	domain_error	Thrown if 'i' is not within the range [0,8]
	*/
	inline Line& Board::getRow(short unsigned int i) throw(domain_error) {
		if (i < 9)
			return Rows[i];
		else
			throw domain_error("Attempted to access to a non-existant Row with an out-of-range 'y' index");
	}
	
	/**
	* Return the request Box
	* \arg	i	row index of the Box within the board.
	* \arg	J	col index of the Box within the board.
	* \return 	A Box object reference correspoding with the requested one
	* \throw	domain_error	Thrown if 'i' and/or 'j' arguments are not within the range [0,2]
	*/
	inline Box& Board::getBox(short unsigned int i,short unsigned int j) throw(domain_error) {
		if (i < 3 && j < 3)
			return Boxes[i][j];
		else
			throw domain_error("Tried to get to a non existant Box by invalid suplied 'x' and 'y' indexes");
	}
	
	/**
	* Return the request Cell
	* \arg	i	'x' index of the Cell within the board.
	* \arg	J	'Y' index of the Cell within the board.
	* \return 	A Cell object reference correspoding with the requested one
	* \throw	domain_error	Thrown if 'i' and/or 'j' arguments isare not within the range [0,8]
	*/
	inline Cell& Board::getCell(short unsigned int i, short unsigned int j) throw(domain_error) {
		if (i < 9 && j < 9) {
			Cell** cell = Rows[i];
			return *cell[j];
		} else
			throw domain_error("Tried to get to a non existant Cell providing invalid 'x' and 'y' indexes");
	}
	
	
	/**
	* Return the request Cell
	* \arg	i	row index of the Cell within the board.
	* \arg	J	col index of the Cell within the board.
	* \return 	A Cell object reference correspoding with the requested one
	* \throw	domain_error	Thrown if 'i' and/or 'j' arguments isare not within the range [0,8],
	*							or if the given value is not inside the cell posibilities list
	*/
	inline void Board::setCell(short unsigned int i, short unsigned int j, short unsigned int value) throw(domain_error) {
		if (i < 9 && j < 9) {
			Rows[i][j]->set(value); // this can throw domain_error
		} else
			throw domain_error("Tried to set to a non existant Cell providing invalid 'x' and 'y' indexes");
	}
	
	/**
	 * Update cells posibilities
	 * \throw 	logic_error		Thrown if no possibility is left in any of the cells or
	 */
	void Solver::updatePossibilities(Board& Sudoku) throw(logic_error) {
		for(short unsigned int i = 0, I = 0; I < 9; I++, (I % 3 == 0) ? i++ : i) {
			for(short unsigned int j = 0, J = 0; J < 9; J++, (J % 3 == 0) ? j++ : j) {
				Cell& cell = *(Sudoku.Rows[I][J]);
				
				if(cell.getState() == definitive)
				{
					short unsigned int p = cell.get();
					Sudoku.Boxes[i][j].delPossibility(p, cell); // this can throw logic_error
 					Sudoku.Rows[I].delPossibility(p, cell); // this can throw logic_error
 					Sudoku.Cols[J].delPossibility(p, cell); // this can throw logic_error
				}
			}
		}
	}
	
	/**
	 * Resolve and set the final state of cell if possible, or at least eliminate some possibilities.
	 * After performing the solving operation, this function automatically updates the row, column
	 * and box where it resides.
	 * \arg	cell	reference to the cell to solve
	 * \arg	row		reference to the row in which the cell resides
	 * \arg	col		reference to the column in which the cell resides
	 * \arg	box		reference to the box in which the cell resides
	 * \return 		true if the any of success happened, or false otherwise
	 * \throw 	logic_error		Thrown if no possibility is left in any of the cells tested
	 * \throw 	domain_error	Thrown if cell is already set and it's attempted to set it
	 *							to a different value
	 */
	bool Solver::solveCell(Cell& cell, Line& row, Line& col, Box& box) throw(domain_error, logic_error) {
		
		short unsigned int* Possibilities = cell.getPossibilities();
		
		for(int i = 0; Possibilities[i] != 0 && i < 9; i++) {
			short unsigned int pos = Possibilities[i];
			
			if(!row.isPossible(pos, cell)) {
				cell.set(pos); // this can throw domain_error
				col.delPossibility(pos, cell); // this can throw logic_error
				box.delPossibility(pos, cell); // this can throw logic_error
				return true;
			} else if(!col.isPossible(pos, cell)) {
				cell.set(pos); // this can throw domain_error
				row.delPossibility(pos, cell); // this can throw logic_error
				box.delPossibility(pos, cell); // this can throw logic_error
				return true;
			} else if(!box.isPossible(pos, cell)) {
				cell.set(pos); // this can throw domain_error
				col.delPossibility(pos, cell); // this can throw logic_error
				row.delPossibility(pos, cell); // this can throw logic_error
				return true;
			}
		}
		
		return false;
	}
	
	/**
	 * Resolves a Sudoku game.
	 * \return true if it resolved the game, false otherwise.
	 */
	void Solver::resolve(Board& Sudoku) {
		bool loop = true, temp;
		
		updatePossibilities(Sudoku);
		
		while(loop) {
			loop = false;
			
			for(short unsigned int i = 0, I=0; I < 9; I++, (I % 3 == 0) ? i++ : i) {
				for(short unsigned int j = 0, J = 0; J < 9; J++, (J % 3 == 0) ? j++ : j) {
					if (Sudoku.Rows[I][J]->getState() == undecided) {
						temp = solveCell(*Sudoku.Rows[I][J], Sudoku.Rows[I], Sudoku.Cols[J], Sudoku.Boxes[i][j]);
						
						if(temp && !loop)
							loop = true;
					}
				}
			}
		}
	}
	
	/**
	 * Prints the sudoku board in the command line
	 * Shows the first possiblity for each cell (even if its final value is still undecided).
	 */
	void Display::show(Board& Sudoku) {
		
		system("clear");
		string lineSeparator1("---||---|---|---||---|---|---||---|---|---||\n"),
			lineSeparator2("===||###|###|###||###|###|###||###|###|###||\n");
		
		cout << "y\\x|| 1 | 2 | 3 || 4 | 5 | 6 || 7 | 8 | 9 ||\n";
		cout << lineSeparator2;
		
		for(int i = 0; i < 9; i++) {
			cout << " " << i+1 << " || ";
			for(int j = 0; j < 9; j++) {
				Cell& cell = *Sudoku[i][j];
				
				if(cell.State == definitive)
					cout << cell.Possibilities[0];
				else
					cout << " ";
				
				if((j + 1) % 3 == 0)
					cout << " || ";
				else
					cout << " | ";
				
			}
			if((i + 1) % 3 == 0)
				cout << endl << lineSeparator2;
			else
				cout << endl << lineSeparator1;
		}
	}
	
	/**
	 * Pseudo randomly creates a value between 1 and 3. It uses rand()
	 * srand() and ctime() to create the value.
	 * \return psuedo random number
	 */
	short unsigned int Generator::nextValue(short unsigned int mod, unsigned short int min) {
		static bool firstTime;
		if(!firstTime)
		{
			srand((unsigned)time(0));
			firstTime = true;
		}
		float f = static_cast<float>(rand()) / RAND_MAX;
		short unsigned int i = (min + static_cast<short unsigned int>(mod * f)) % mod;
		
		return i;
	}
	
	/**
	 * Set the cell to given state if possible.
	 * After performing the solving operation, this function automatically updates the row, column
	 * and box where it resides.
	 * \arg	cell	reference to the cell to solve
	 * \arg	row		reference to the row in which the cell resides
	 * \arg	col		reference to the column in which the cell resides
	 * \arg	box		reference to the box in which the cell resides
	 * \arg sol		Value to set the cell if possible
	 * \return 		true if the any of success happened, or false otherwise
	 * \throw 	logic_error		Thrown if no possibility is left in any of the cells tested
	 */
	bool Generator::solveCell(Cell& cell, Line& row, Line& col, Box& box, short unsigned int sol) throw(domain_error, logic_error) {
		if(cell.isPossible(sol) && row.canDel(sol, cell) && col.canDel(sol, cell) && box.canDel(sol, cell)) {
			cell.set(sol); // this can theoretically throw domain_error but shouldn't
			row.delPossibility(sol, cell); // this can throw logic_error
			col.delPossibility(sol, cell); // this can throw logic_error
			box.delPossibility(sol, cell); // this can throw logic_error
			return true;
		}
		
		return false;
	}
}
}

