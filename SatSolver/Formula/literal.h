/**
  Build Up ID: The first bit is the sign. The rest is the number.
*/

#ifndef LITERAL_H
#define LITERAL_H
#include <iostream>

typedef unsigned int uint;
#define __SIGNBIT__ 1
#define __MAXLITERAL__ __UINT32_MAX__ -1

class Literal
{
private:
    uint ID;

public:
    uint getID() const{
        return ID >> __SIGNBIT__;
    }
    uint getLit()const{
        return ID;
    }
    bool getSign() const{
        return ID & __SIGNBIT__;
    }
    void setSign(const uint _sign){
        ID = (ID & (__MAXLITERAL__)) | _sign;
    }

    bool operator<(const Literal& other) const{
        return ID < other.ID;
    }
    void switchSign(){
        ID = ID ^ 1;
    }

    Literal(uint _ID, bool _sign)
    {
        ID = (_ID << 1) | _sign;
    }

    Literal(){
        ID = 0;
    }

    Literal(const Literal& lit){
        ID = lit.ID;
    }

    Literal& operator=(const Literal& other){
        ID = other.ID;
        return *this;
    }

    bool operator ==(const Literal& other) const{
        return other.ID == ID;
    }
};

inline std::ostream& operator<<(std::ostream& out, const Literal& lit){
    out << (lit.getSign()?"-":"") << lit.getID();
    return out;
}

#endif // LITERAL_H
