#include "hanoi03-1n.h"
#include <iomanip>

using namespace std;

// Plate
Plate::Plate(int num): size(num) {}

int Plate::getSize() const {
    return size;
}
// ---

// Pole
Pole::Pole(std::string nm, int size): name(std::move(nm)), size(size), maxSize(size) {
    if (name == "A") {
        id = POLE_A;
    } else if (name == "B") {
        id = POLE_B;
    } else if (name == "C") {
        id = POLE_C;
    }
}

void Pole::init_stack() {
    plates.clear();
    for (int i = 0; i < maxSize; i++) {
//        std::cout << "Plate " << maxSize - i << " : ";
        Plate plate(maxSize - i);
        plates.push_back(plate);
    }
    size = maxSize;
//    std::cout << std::endl;
}


void Pole::clear_stack() {
    plates.clear();
    size = 0;
}

Plate Pole::top() throw(std::out_of_range) {
    if (size == 0) {
        throw std::out_of_range("Pole is empty");
    }
    return plates.back();
}

Plate Pole::pop() throw(std::out_of_range) {
    if (size-- == 0) {
        throw std::out_of_range("Pole is empty");
    }
    Plate p = plates.back();
    plates.pop_back();
    return p;
}

void Pole::push(Plate p) throw(std::out_of_range) {
    if (size + 1 > maxSize) {
        throw std::out_of_range("Pole is full");
    }
    plates.push_back(p);
    size++;
}

void Pole::move_from(Pole& to) throw(std::out_of_range) {
    if (id == to.id) {
        throw std::out_of_range("Can not move to itself");
    }
    if (size == 0) {
        throw std::out_of_range("From Pole is empty");
    }
    if (to.size + 1 > to.maxSize) {
        throw std::out_of_range("Pole is full");
    }
    if (to.size != 0) {
        if (to.top() < top()) {
            throw std::out_of_range("Can not move");
        }
    }
    to.push(pop());
}

std::string Pole::getName() const {
    return name;
}

int Pole::getSize() const {
    return size;
}

POLE_ID Pole::getId() const {
    return id;
}

void Pole::print() const {
    std::cout << name << ": ";
    for (auto p : plates) {
        std::cout << p.getSize() << " ";
    }
    for (int i = 0; i < maxSize - size; i++) {
        std::cout << "0 ";
    }
    std::cout << std::endl;
}
// ---

// Board (5)
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

}

void Board::printHelp() {
    cout  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    cout  << left << setw(5)<< "H" << ": show this help" << endl;
    cout  << left << setw(5)<< "Q" << ": exit game" << endl;
}

int main() {
    int diskSize;
    int step = 0;
    cout << "円盤の枚数> "; cin >> diskSize;
    Board boardc(diskSize);
    boardc.initialize();

    string x, y;
    boardc.show_n_str();

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "R" || x == "r") {
            boardc.initialize();
            boardc.show_n_str();
            continue;
        }
        if (x == "H" || x == "h") {
            boardc.printHelp();
            continue;
        }

        cin >> y;
        boardc.move(x, y);
        boardc.show_n_str();
        if (step++ >= 99) break;
    }
}
