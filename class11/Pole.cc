#include "Pole.h"

using namespace std;

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
        Plate plate(maxSize - i);
        plates.push_back(plate);
    }
    size = maxSize;
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

void Pole::show_art(int n) const {
    int fill = 0;
    int padding = (2 * maxSize + 1 - fill) / 2;
    if (n >= size) {
        cout << right << setfill(' ') << setw(padding) << "" << setfill('|') << setw(1) << "" << setfill(' ') << setw(padding) << "";
        return;
    }

    fill = (2 * plates[n].getSize() - 1) < 0 ? 0 : (2 * plates[n].getSize() - 1);
    padding = (2 * maxSize + 1 - fill) / 2;
    cout << right << setfill(' ') << setw(padding) << "" << setfill('x') << setw(fill) << "" << setfill(' ') << setw(padding) << "";
}