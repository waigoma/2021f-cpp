#ifndef HANOI03_3_H
#define HANOI03_3_H

#include <iostream>
#include <list>
#include <stdexcept>


enum POLE_ID {
    POLE_A,
    POLE_B,
    POLE_C
};


class Plate {
protected:
    int size;

public:
    Plate(int);
    int getSize() const;
};
inline int operator<(const Plate& p1, const Plate& p2) {
    return p1.getSize() < p2.getSize();
}
inline int operator>(const Plate& p1, const Plate& p2) {
    return p1.getSize() > p2.getSize();
}
inline std::ostream& operator<<(std::ostream& s, const Plate& p) {
    return s << p.getSize();
}


class Pole {
protected:
    std::string name;
    int size;
    const int maxSize;
    std::list<Plate> plates;
    POLE_ID id;

public:
    Pole(std::string, int);
    void init_stack();
    void clear_stack();
    Plate top() throw(std::out_of_range);
    Plate pop() throw(std::out_of_range);
    void push(Plate) throw(std::out_of_range);
    void move_from(Pole&) throw(std::out_of_range);
    std::string getName() const;
    int getSize() const;
    POLE_ID getId() const;
    void print() const;
    void show_art(int) const;
};
inline std::ostream& operator<<(std::ostream& s, const Pole& p) {
    return s << p.getName() << "(" << p.getSize() << ")";
}


class Board {
protected:
    int maxSize;
    std::list<Pole> poles;

public:
    Board(int n): maxSize(n) {};
    void initialize();
    void move(const std::string&, const std::string&);
    void move(POLE_ID, POLE_ID);
    void show_n_str();
    void show_aa();
    static void printHelp();
};
//inline std::ostream& operator<<(std::ostream& s, const Board& b) {
//    return s << b.poles[0] << " " << b.poles[1] << " " << b.poles[2];
//}


#endif //HANOI03_3_H