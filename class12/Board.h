#ifndef BOARD_H
#define BOARD_H

#include <windows.h>
#include <unistd.h>
#include <iterator>
#include "Pole.h"

class Board {
protected:
    int maxSize;
    std::vector<Pole> poles;
    std::vector<Pole> polesCopy;
    std::vector<std::vector<POLE_ID>> solutions;
    std::string poleNames[3] = {"A", "B", "C"};

public:
    Board(int n): maxSize(n) {};
    void initialize();
    void move(const std::string&, const std::string&);
    void move(POLE_ID, POLE_ID);
    void solve(int, POLE_ID, POLE_ID, POLE_ID);
    void solve();
    void show_n_str();
    void show_aa();
    void printHelp();
    void printSolutions();
    void animation();

    void cursesPrintHelp();
    void cursesShow_aa();
    void cursesAnimation(int);
    std::vector<std::vector<POLE_ID>> getSolutions();

    void poleBackup();
    void poleRestore();
};


#endif //BOARD_H
