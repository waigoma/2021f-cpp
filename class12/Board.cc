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

    poleBackup();

    for (const auto& s : solutions) {
        Sleep(1000);
        system("clear");
        move(s[0], s[1]);
        show_aa();
    }

    poleRestore();
}

void Board::printHelp() {
    cout  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    cout  << left << setw(5)<< "H" << ": show this help" << endl;
    cout  << left << setw(5)<< "Q" << ": exit game" << endl;
}

void Board::cursesShow_aa() {
    stringstream ss;
    stringstream ss1;
    stringstream ss2;
    ss << right << setfill(' ') << setw(maxSize + 1) << "|" << setw(2 * maxSize + 1) << "|" << setw(2 * maxSize + 1) << "|" << endl;
    addstr(ss.str().c_str());
    for (int i = maxSize - 1; i >= 0; i--) {
        for (const auto& pole : poles) {
            pole.cursesShow_art(i);
        }
        addstr("\n");
//        cout << endl;
    }
    ss1 << right << setfill('-') << setw(maxSize + 1)  << "+" << setfill('-') << setw(2 * maxSize + 1) << "+" << setfill('-') << setw(2 * maxSize + 1) << "+" << setfill('-') << setw(maxSize + 1) << "\n";
    ss2 << right << setfill(' ') << setw(maxSize + 1)  << "A" << setw(2 * maxSize + 1) << "B" << setw(2 * maxSize + 1) << "C" << setw(maxSize + 1) << "\n";
    addstr(ss1.str().c_str());
    addstr(ss2.str().c_str());
}

void Board::cursesAnimation(int n) {
    move(solutions[n][0], solutions[n][1]);
    cursesShow_aa();
}

void Board::cursesPrintHelp() {
    stringstream ss;
    stringstream ss1;
    stringstream ss2;
    stringstream ss3;
    stringstream ss4;
    ss  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    ss1  << left << setw(5)<< "H" << ": show this help" << endl;
    ss2  << left << setw(5)<< "Q" << ": exit game" << endl;
    ss3  << left << setw(5)<< "???" << ": Undo" << endl;
    ss4  << left << setw(5)<< "???" << ": Redo" << endl;
    addstr(ss.str().c_str());
    addstr(ss1.str().c_str());
    addstr(ss2.str().c_str());
    addstr(ss3.str().c_str());
    addstr(ss4.str().c_str());
}

void Board::poleBackup() {
    polesCopy.clear();
    copy(poles.begin(), poles.end(), back_inserter(polesCopy));
}

void Board::poleRestore() {
    poles.clear();
    copy(polesCopy.begin(), polesCopy.end(), back_inserter(poles));
}

std::vector<std::vector<POLE_ID>> Board::getSolutions() {
    return solutions;
}

void Board::solveCurses() {
    solutions.clear();
    poleBackup();

    solveCurses(POLE_NULL, POLE_NULL, 100);

    poleRestore();

    vector<vector<POLE_ID>> tmp;
    solutions.pop_back();
    for (vector<POLE_ID> s : solutions) {
        tmp.push_back(solutions.back());
        solutions.pop_back();
    }

    solutions.clear();
    copy(tmp.begin(), tmp.end(), back_inserter(solutions));
}

bool Board::solveCurses(POLE_ID from, POLE_ID to, int last) {
    POLE_ID from_id = POLE_NULL;
    POLE_ID to_id = POLE_NULL;
    if (poles[POLE_C].getSize() == maxSize) {
        solutions.push_back({from, to});
        return true;
    }
    vector<vector<POLE_ID>> nextMove({{POLE_A, POLE_C}, {POLE_A, POLE_B}, {POLE_B, POLE_C}, {POLE_B, POLE_A}, {POLE_C, POLE_B}, {POLE_C, POLE_A}});
    for (vector<POLE_ID> next : nextMove) {
        if (from != POLE_NULL && to != POLE_NULL) {
            if (next[0] == to && next[1] == from) continue;
        }
        if (poles[next[0]].getSize() != 0) {
            if (last == poles[next[0]].top().getSize()) {
                from_id = next[0];
                to_id = next[1];
                continue;
            }
        }
        if (!moveBool(next[0], next[1])) continue;
//        solveCurses(next[0], next[1]);
        if (solveCurses(next[0], next[1], poles[next[1]].top().getSize())) {
            solutions.push_back({from, to});
            if (poles[POLE_C].getSize() == maxSize) return true;
        }
    }
    moveBool(from_id, to_id);
    if (solveCurses(from_id, to_id, 100)) {
        solutions.push_back({from, to});
        if (poles[POLE_C].getSize() == maxSize) return true;
    }
    return false;
}

bool Board::moveBool(POLE_ID from, POLE_ID to) {
    try {
        move(from, to);
    } catch (const exception& e) {
        return false;
    }
    return true;
}
