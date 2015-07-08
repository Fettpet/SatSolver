/* Eine Klausel ist erfüllt wenn flag fulfilled true ist
 * Ein Conflikt ist da, wenn Counter auf 0 geht
 *
 *
 * */


#ifndef CLAUSES_H
#define CLAUSES_H
#include <set>
#include "literal.h"
#include <iostream>

class Clauses
{
private:
    std::set<Literal> variables;
    uint numberLiterals;
    Literal watchLiteral1, watchLiteral2;
    friend std::ostream& operator<<(std::ostream& out, const Clauses& cl);

public:

// Getter
    uint getNumberLiterals() const;
    Literal getWatchLiteral1() const;
    Literal getWatchLiteral2() const;
    const std::set<Literal>& getLiterals()const;
    bool contains(const Literal& l) const;
// Iterator
    std::set<Literal>::const_iterator begin() const{
        return variables.begin();
    }
    std::set<Literal>::const_iterator end() const{
        return variables.end();
    }
// Setter
    void setWatchLiteral1(const Literal lit);
    void setWatchLiteral2(const Literal lit);


    Clauses();
    Clauses(const std::set<Literal>& in);
    Clauses(const std::string& line);
    Clauses(const Clauses& other);
    ~Clauses(){}

    Clauses& operator=(const Clauses& other);
};


std::ostream& operator<<(std::ostream& out, const Clauses& cl);
#endif // CLAUSES_H
