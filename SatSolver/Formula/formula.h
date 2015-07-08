#ifndef FORMULA_H
#define FORMULA_H
#include "clauses.h"
#include <vector>
#include <iostream>
#include <memory>

class Formula
{
private:
    std::vector<std::shared_ptr<Clauses> > clauses;
    uint numberOfClauses;
    uint numberOfVariables;

public:
// Constructors
    Formula();
    Formula(const Formula& other);
    ~Formula(){}
// Getter
    const std::vector<std::shared_ptr<Clauses> >& getClauses()const;
    std::shared_ptr<Clauses> getClause(uint nr);
    uint getNumberOfVariables()const;
    uint getNumberOfClauses()const;
// Setter
    void addClauses(const Clauses& c);
    void setNumberOfVariables(uint number);


    friend std::ostream& operator<<(std::ostream& out, const Formula& cl);
};


std::ostream& operator<<(std::ostream& out, const Formula& cl);
#endif // FORMULA_H
