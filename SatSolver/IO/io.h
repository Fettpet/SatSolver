#ifndef IO_H
#define IO_H
#include "../Formula/formula.h"
#include <string>

class IO
{
public:
    IO();
    static Formula readFromFile(const std::string fileName);
private:

};

#endif // IO_H
