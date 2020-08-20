#include <cstddef> // defines size_t i.e. an unsigned int
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "cell.h"
using namespace std;

Cell::Cell(size_t r, size_t c): r{r}, c{c}, state{State::Dead}, neighbours{0} {} // state initialized as dead??

void Cell::setLiving() {
	state = State::Alive;
}

void Cell::reset() { // # of alive neighbours is reset to 0
	neighbours = 0;
}

    // Grid calls this to get me to notify my neighbours if I'm alive.
    // Also needs to be called when state is set to be alive so displays are notified.
void Cell::notify() {
	notifyObservers();
}

    // My neighbours will call this to let me know if they're alive.
void Cell::notify(Subject & whoNotified) {
	if (whoNotified.getInfo().state == State::Alive) {
		neighbours += 1;
	}
}

    // Reassess my living-or-dead status, based on info from neighbours.
void Cell::recalculate() {
	//cout << "i am cell(" << r << ", " << c << ") and i was "; //
	if (state == State::Alive) {
		//cout << "alive. "; //
		if (neighbours != 2 && neighbours != 3) {
			state = State::Dead;
		}
	} else {
		//cout << "dead. "; //
		if (neighbours == 3) {
			state = State::Alive;
		}
	}
	/*cout << "because i had " << neighbours << " neighbours, i am now "; //
	if (state == State::Alive) {
		cout << "alive." << endl; //
	} else {
		cout << "dead." << endl; //
	}*/
}

    // Observer calls this to get information about cell.
Info Cell::getInfo() const {
	return Info{state, r, c};
}
