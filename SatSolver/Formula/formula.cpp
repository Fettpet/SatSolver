#include "formula.h"


/**************************************************************************************************
 *                              Construktor
 * ***********************************************************************************************/
Formula::Formula():
numberOfClauses(0),
numberOfVariables(0)
{}

Formula::Formula(const Formula& other):
    clauses(other.clauses),
    numberOfClauses(other.numberOfClauses),
    numberOfVariables(other.numberOfVariables)

{}


/**************************************************************************************************
 *                                  Setter
 * ***********************************************************************************************/

void Formula::addClauses(const Clauses& c){
    std::shared_ptr<Clauses> buffer = std::shared_ptr<Clauses>(new Clauses(c));
    clauses.push_back(buffer);
    numberOfClauses++;
}


void Formula::setNumberOfVariables(uint number){
    numberOfVariables = number;
}



/**************************************************************************************************
 *                  getter
 * ***********************************************************************************************/
std::shared_ptr<Clauses> Formula::getClause(uint nr){
    return clauses[nr];
}

const std::vector<std::shared_ptr<Clauses> >& Formula::getClauses()const{
    return clauses;
}

uint Formula::getNumberOfVariables()const{
    return numberOfVariables;
}

uint Formula::getNumberOfClauses()const{
    return numberOfClauses;
}

/**************************************************************************************************
 *                                          Io
 * ***********************************************************************************************/


std::ostream& operator<<(std::ostream& out, const Formula& cl){
    for(const std::shared_ptr<Clauses> c: cl.clauses){
        out << c << std::endl;
    }
    return out;
}
