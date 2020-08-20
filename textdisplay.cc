#include <cstddef> // defines size_t i.e. an unsigned int
#include <iostream>
#include <vector>
#include "observer.h"
#include "cell.h"
#include "subject.h"
#include "info.h"
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(size_t n): n{n} {
	vector<char> back;
	back.reserve(n);
	for (size_t x = 0; x < n; ++x) {
		back.emplace_back('_');
	}

	theDisplay.reserve(n);
	for (size_t x = 0; x < n; ++x) {
		theDisplay.emplace_back(back);
	}
}

void TextDisplay::notify(Subject & whoNotified) {
	int r = whoNotified.getInfo().row;
	int c = whoNotified.getInfo().col;
	if ((whoNotified.getInfo()).state == State::Alive) {
		theDisplay[r][c] = 'X';
	} else {
		theDisplay[r][c] = '_';
	}
}

void TextDisplay::notify() {} //

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for (size_t r = 0; r < td.n; ++r) {
		for (size_t c = 0; c < td.n; ++c) {
			cout << td.theDisplay.at(r).at(c);
			if (c == td.n - 1) {
				cout << endl;
			}
		}
	}
	return out;
}
