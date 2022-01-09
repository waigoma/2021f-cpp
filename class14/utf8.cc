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
    if (is_2byte()) return 2;
    else if (is_4byte()) return 4;
    else if (is_5byte()) return 5;
    else if (is_6byte()) return 6;
    else if (is_3byte()) return 3;
    else return 1;
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

int utf8::characterType() const {
    if (countBytes() == 1) return utf8::ALPHANUMERIC;
    else if (countBytes() == 3) {
        if (0xE3 == byte[0]) {
            if (0x81 == byte[1] && 0x81 <= byte[2] || 0x82 == byte[1] && byte[2] <= 0x96) return utf8::HIRAGANA;
            if (0x82 == byte[1] && 0xA1 <= byte[2] || 0x83 == byte[1] && byte[2] <= 0xB6) return utf8::KATAKANA;
        } else if (0xE4 == byte[0]) {
            if (0xB8 == byte[1] && 0x80 <= byte[2] || 0xB9 <= byte[1]) return utf8::KANJI;
        } else if (0xE5 <= byte[0]) return utf8::KANJI;
    }
    return -1;
}
