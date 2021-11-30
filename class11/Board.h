#ifndef BOARD_H
#define BOARD_H

#include "Pole.h"

class Board {
protected:
    int maxSize;
    std::vector<Pole> poles;

public:
    Board(int n): maxSize(n) {};
    void initialize();
    void move(const std::string&, const std::string&);
    void move(POLE_ID, POLE_ID);
    void show_n_str();
    void show_aa();
    void printHelp();
};


#endif //BOARD_H
