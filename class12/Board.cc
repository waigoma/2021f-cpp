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

void Board::solve(int n, POLE_ID from, POLE_ID to, POLE_ID tmp) {
    if (n == 1) {
        vector<POLE_ID> p = {from, to};
        solutions.push_back(p);
//        std::cout << "Move disk 1 from " << from << " to " << to << std::endl;
        return;
    }
    solve(n - 1, from, tmp, to);
    vector<POLE_ID> p = {from, to};
    solutions.push_back(p);
//    std::cout << "Move disk " << n << " from " << from << " to " << to << std::endl;
    solve(n - 1, tmp, to, from);
}

void Board::solve() {
//    vector<Pole> tmpPoles = poles;
    solutions.clear();
    solve(maxSize, POLE_A, POLE_C, POLE_B);
//    poles = tmpPoles;
}

void Board::printSolutions() {
    for (const auto& s : solutions) {
        std::cout << poleNames[s[0]] << " -> " << poleNames[s[1]] << std::endl;
    }
}

void Board::show_n_str() {
    for (auto& p : poles) {
        p.print();
    }
}

void Board::show_aa() {
    cout << right << setfill(' ') << setw(maxSize + 1) << "|" << setw(2 * maxSize + 1) << "|" << setw(2 * maxSize + 1) << "|" << endl;
    for (int i = maxSize - 1; i >= 0; i--) {
        for (const auto& pole : poles) {
            pole.show_art(i);
        }
        cout << endl;
    }
    cout << right << setfill('-') << setw(maxSize + 1)  << "+" << setfill('-') << setw(2 * maxSize + 1) << "+" << setfill('-') << setw(2 * maxSize + 1) << "+" << setfill('-') << setw(maxSize + 1) << "\n";
    cout << right << setfill(' ') << setw(maxSize + 1)  << "A" << setw(2 * maxSize + 1) << "B" << setw(2 * maxSize + 1) << "C" << setw(maxSize + 1) << "\n";
}

void Board::animation() {
    system("clear");
    show_aa();

    vector<Pole> polesCopy;
    copy(poles.begin(), poles.end(), back_inserter(polesCopy));

    for (const auto& s : solutions) {
        Sleep(1000);
        system("clear");
        move(s[0], s[1]);
        show_aa();
    }

    poles.clear();
    copy(polesCopy.begin(), polesCopy.end(), back_inserter(poles));
}

void Board::printHelp() {
    cout  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    cout  << left << setw(5)<< "H" << ": show this help" << endl;
    cout  << left << setw(5)<< "Q" << ": exit game" << endl;
}