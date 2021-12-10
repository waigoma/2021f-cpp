#ifndef POLE_H
#define POLE_H

#include <vector>
#include <stdexcept>
#include <iomanip>
#include "Plate.h"

enum POLE_ID {
    POLE_A,
    POLE_B,
    POLE_C,
    POLE_NULL
};

class Pole {
protected:
    std::string name;
    int size;
    const int maxSize;
    std::vector<Plate> plates;
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

    void cursesShow_art(int n) const;
};
inline std::ostream& operator<<(std::ostream& s, const Pole& p) {
    return s << p.getName() << "(" << p.getSize() << ")";
}


#endif //POLE_H
