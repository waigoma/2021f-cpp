#ifndef PLATE_H
#define PLATE_H

#include <iostream>

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


#endif //PLATE_H
