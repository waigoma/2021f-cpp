#include "utf8.h"
#include <sstream>

utf8::utf8(unsigned char x0, unsigned char x1, unsigned char x2, unsigned char x3, unsigned char x4, unsigned char x5) {
    byte[0] = x0; byte[1] = x1; byte[2] = x2; byte[3] = x3; byte[4] = x4; byte[5] = x5;
}

utf8::utf8(const unsigned char *xp) {
    int i = 0;
    byte[0] = xp[0];
    for (i = 1; i < countBytes(); i++) byte[i] = xp[i];
    for (; i < 6; i++) byte[i] = '\0';
}

utf8::utf8(const char *xp) {
    int i = 0;
    byte[0] = xp[0];
    for (i = 1; i < countBytes(); i++) byte[i] = xp[i];
    for (; i < 6; i++) byte[i] = '\0';
}

int utf8::countBytes() const {
    if (is_1byte()) return 1;
    else if (is_2byte()) return 2;
    else if (is_3Byte()) return 3;
    else if (is_4Byte()) return 4;
    else if (is_5Byte()) return 5;
    else return 6;
}

std::istream &operator>>(std::istream& ios, utf8 &uc) {
    uc = utf8();
    ios >> uc.byte[0];
    for (int i = 1; i < uc.countBytes(); i++) ios >> uc.byte[i];
    return ios;
}

std::ostream &operator<<(std::ostream& ios, const utf8& uc) {
    for (int i = 0; i < uc.countBytes(); i++) ios << uc.byte[i];
    return ios;
}

std::ostream &operator<<(std::ostream& ios, const utf8* up) {
    while (!up->is_null()) {
        ios << *up;
        up++;
    }
    return ios;
}

bool utf8::operator<(const utf8& a) const {
    std::stringstream thisStream;
    std::stringstream aStream;
    int thisInt;
    int aInt;
    for (int i = 0; i < this->countBytes(); i++) thisStream << std::hex << (int) this->byte[i];
    for (int i = 0; i < a.countBytes(); i++) aStream << std::hex << (int) a.byte[i];
    thisStream >> thisInt;
    aStream >> aInt;
    return thisInt < aInt;
}

bool utf8::operator<=(const utf8& a) const {
    std::stringstream thisStream;
    std::stringstream aStream;
    int thisInt;
    int aInt;
    for (int i = 0; i < this->countBytes(); i++) thisStream << std::hex << (int) this->byte[i];
    for (int i = 0; i < a.countBytes(); i++) aStream << std::hex << (int) a.byte[i];
    thisStream >> thisInt;
    aStream >> aInt;
    return thisInt <= aInt;
}

bool utf8::operator>(const utf8& a) const {
    std::stringstream thisStream;
    std::stringstream aStream;
    int thisInt;
    int aInt;
    for (int i = 0; i < this->countBytes(); i++) thisStream << std::hex << (int) this->byte[i];
    for (int i = 0; i < a.countBytes(); i++) aStream << std::hex << (int) a.byte[i];
    thisStream >> thisInt;
    aStream >> aInt;
    return thisInt > aInt;
}

bool utf8::operator>=(const utf8& a) const {
    std::stringstream thisStream;
    std::stringstream aStream;
    int thisInt;
    int aInt;
    for (int i = 0; i < this->countBytes(); i++) thisStream << std::hex << (int) this->byte[i];
    for (int i = 0; i < a.countBytes(); i++) aStream << std::hex << (int) a.byte[i];
    thisStream >> thisInt;
    aStream >> aInt;
    return thisInt >= aInt;
}

bool utf8::operator==(const utf8 &a) const{
    for (int i = 0; i < countBytes(); i++){
        if (byte[i] == a.byte[i]){
            continue;
        } else {
            return false;
        }
    }
    return true;
}