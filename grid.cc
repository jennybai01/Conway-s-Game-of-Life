#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "textdisplay.h"
#include "observer.h"
#include "grid.h"
using namespace std;

Grid::~Grid() {
	delete td;
	delete ob;
	if (cells) {
		cells->clear();
	}
	delete cells;
}

// sets up nxn grid, clears old grid if necessary
void Grid::init(size_t n) {
	this->n = n;
	if (!cells) {
	       cells = new vector<vector<Cell>>;
	} else {
		cells->clear();
	}
	// filling cells with Cells
	cells->reserve(n);
	vector<Cell> back;
	back.reserve(n);
	for (size_t r = 0; r < n; ++r) {
		for (size_t c = 0; c < n; ++c) {
			back.emplace_back(Cell(r, c));
		}
		cells->emplace_back(back);
		back.clear();
		back.reserve(n);
	}
	
	if (td) {
		delete td;
	} 

	td = new TextDisplay(n);

	for (size_t r = 0; r < n; ++r) { // attach neighbours
                for (size_t c = 0; c < n; ++c) {
			//cout << "CELL(" << c << ", " << r << "): MY NEIGHBOURS ARE: " << endl; //
			((*cells).at(r).at(c)).attach(td);
                        for (int add_r = -1; add_r <= 1; ++add_r) {
                                for (int add_c = -1; add_c <= 1; ++add_c) {
                                        if (within_grid(r+add_r, n) && within_grid(c+add_c, n)) {
						if (add_c == 0 && add_r == 0) {
							continue;
						} else {
							//cout << "\tcell(" << c+add_c << ", " << r+add_r << ")" << endl; //
                                                	(cells->at(r).at(c)).attach(&(cells->at(r+add_r).at(c+add_c)));
						}
                                        }
                                }
                        }
                }
        }
}

// marks cell at row r, col c as alive
void Grid::turnOn( size_t r, size_t c ) {
	(*cells).at(c).at(r).setLiving();
	cells->at(c).at(r).notify();
	for (size_t r = 0; r < n; ++r) {
		for (size_t c = 0; c < n; ++c) {
			cells->at(r).at(c).reset();
		}
	}
}

bool Grid::within_grid(int x, int n) {
	if (x >= 0 && x < n) {
		return true;
	}
	return false;
}

void Grid::tick() {
	for (size_t r = 0; r < n; ++r) { // notify observers
		for (size_t c = 0; c < n; ++c) {
			cells->at(r).at(c).notify(); // notifyObservers?? 
		}
	}
	
        for (size_t r = 0; r < n; ++r) { // recalculate
		for (size_t c = 0; c < n; ++c) {
                        (*cells).at(r).at(c).recalculate();
                }
        }

        for (size_t r = 0; r < n; ++r) { // notify observers
                for (size_t c = 0; c < n; ++c) {
                        cells->at(r).at(c).notify(); // notifyObservers??
                }
        }

	for (size_t r = 0; r < n; ++r) {
		for (size_t c = 0; c < n; ++c) {
			cells->at(r).at(c).reset();
		}
	}
}

// Uses the TextDisplay to output the grid information.
std::ostream & operator<<( std::ostream & out, const Grid & g ) {
	out << *(g.td);
	return out;
};
