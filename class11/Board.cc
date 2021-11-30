#include "Board.h"

using namespace std;

// A: 5 4 3 2 1
// B: 0 0 0 0 0
// C: 0 0 0 0 0
void Board::initialize() {
    poles.clear();

    Pole a("A", maxSize);
    a.init_stack();
    poles.push_back(a);

    Pole b("B", maxSize);
    b.clear_stack();
    poles.push_back(b);

    Pole c("C", maxSize);
    c.clear_stack();
    poles.push_back(c);
}

void Board::move(const std::string& fromStr, const std::string& toStr) {
    POLE_ID fromId;
    POLE_ID toId;

    if (fromStr == "A") fromId = POLE_A;
    else if (fromStr == "B") fromId = POLE_B;
    else if (fromStr == "C") fromId = POLE_C;

    if (toStr == "A") toId = POLE_A;
    else if (toStr == "B") toId = POLE_B;
    else if (toStr == "C") toId = POLE_C;

    move(fromId, toId);
}

void Board::move(POLE_ID fromId, POLE_ID toId) {
    Pole* from;
    Pole* to;
    bool foundFrom = false;
    bool foundTo = false;
    for (Pole& p : poles) {
        if (p.getId() == fromId) {
            from = &p;
            foundFrom = true;
        }
        if (p.getId() == toId) {
            to = &p;
            foundTo = true;
        }
    }
    if (foundFrom && foundTo) from->move_from(*to);
    else throw std::out_of_range("Pole not found");
}

void Board::show_n_str() {
    for (auto& p : poles) {
        p.print();
    }
}

void Board::show_aa() {
    stringstream ss;
    stringstream ss1;
    stringstream ss2;
    ss << right << setfill(' ') << setw(maxSize + 1) << "|" << setw(2 * maxSize + 1) << "|" << setw(2 * maxSize + 1) << "|" << endl;
    addstr(ss.str().c_str());
    for (int i = maxSize - 1; i >= 0; i--) {
        for (const auto& pole : poles) {
            pole.show_art(i);
        }
        addstr("\n");
//        cout << endl;
    }
    ss1 << right << setfill('-') << setw(maxSize + 1)  << "+" << setfill('-') << setw(2 * maxSize + 1) << "+" << setfill('-') << setw(2 * maxSize + 1) << "+" << setfill('-') << setw(maxSize + 1) << "\n";
    ss2 << right << setfill(' ') << setw(maxSize + 1)  << "A" << setw(2 * maxSize + 1) << "B" << setw(2 * maxSize + 1) << "C" << setw(maxSize + 1) << "\n";
    addstr(ss1.str().c_str());
    addstr(ss2.str().c_str());
}

void Board::printHelp() {
    stringstream ss;
    stringstream ss1;
    stringstream ss2;
    stringstream ss3;
    stringstream ss4;
    ss  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    ss1  << left << setw(5)<< "H" << ": show this help" << endl;
    ss2  << left << setw(5)<< "Q" << ": exit game" << endl;
    ss3  << left << setw(5)<< "←" << ": Undo" << endl;
    ss4  << left << setw(5)<< "→" << ": Redo" << endl;
    addstr(ss.str().c_str());
    addstr(ss1.str().c_str());
    addstr(ss2.str().c_str());
    addstr(ss3.str().c_str());
    addstr(ss4.str().c_str());
}