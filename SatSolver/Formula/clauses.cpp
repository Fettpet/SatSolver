
#include "clauses.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

/**********************************************************************************************
 *                              Constructor
 * ***********************************************************************************************/
Clauses::Clauses():
    numberLiterals(0)
{}

Clauses::Clauses(const std::set<Literal>& in):
    variables(in),
    numberLiterals(in.size())
{
    if(numberLiterals == 1){
        watchLiteral1 = *(variables.begin());
        watchLiteral2 = Literal(0, false);
    } else {
        std::set<Literal>::const_iterator it(variables.begin());
        watchLiteral1 = *it;
        ++it;
        watchLiteral2 = *it;
    }
}

Clauses::Clauses(const Clauses& other):
    variables(other.variables),
    numberLiterals(other.numberLiterals),
    watchLiteral1(other.watchLiteral1),
    watchLiteral2(other.watchLiteral2)
{}

Clauses::Clauses(const std::string& line){

// split
    std::vector<std::string> elems;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        elems.push_back(item);
    }
    for(std::string c: elems){
        int number;
        if(c[0] == '-'){
            number = std::stoi(c.substr(1));
            Literal l(number, true);
            variables.insert(l);
        } else {
            number = std::stoi(c);
            if(number == 0) break;
            Literal l(number, false);
            variables.insert(l);
        }
    }

    numberLiterals = variables.size();
// Watchliterals
    if(numberLiterals == 1){
        watchLiteral1 = *(variables.begin());
        watchLiteral2 = Literal(0, false);
    } else {
        std::set<Literal>::const_iterator it(variables.begin());
        watchLiteral1 = *it;
        ++it;
        watchLiteral2 = *it;
    }
}

/**************************************************************************************************
 *                                  getter
 * ***********************************************************************************************/
bool Clauses::contains(const Literal& l) const{
    return variables.find(l) != variables.end();
}

uint Clauses::getNumberLiterals() const{
    return numberLiterals;
}

Literal Clauses::getWatchLiteral1() const{
    return watchLiteral1;
}

Literal Clauses::getWatchLiteral2() const{
    return watchLiteral2;
}


const std::set<Literal>& Clauses::getLiterals()const{
    return variables;
}


/**************************************************************************************************
 *                      Setter
 * ***********************************************************************************************/

void Clauses::setWatchLiteral1(const Literal lit){
    watchLiteral1 = lit;
}

void Clauses::setWatchLiteral2(const Literal lit){
    watchLiteral2 = lit;
}

/**************************************************************************************************
                                        operator
  ************************************************************************************************/

Clauses& Clauses::operator=(const Clauses& other){
    numberLiterals = other.numberLiterals;
    watchLiteral1 = other.watchLiteral1;
    watchLiteral2 = other.watchLiteral2;
    variables = other.variables;
    return  *this;
}

/**************************************************************************************************
 *                                  Ausgabe
 * ***********************************************************************************************/

std::ostream& operator<<(std::ostream& out, const Clauses& cl){
    out << "[";
    for(Literal i: cl.variables){
        if(i.getSign())
            out << "-";
        out << i.getID() << ", ";
    }
    out << "]" << " wl (" << cl.watchLiteral1 << ", " << cl.watchLiteral2 << ")";
    return out;
}
