#ifndef SOLVERBASECLASS_H
#define SOLVERBASECLASS_H
#include "Formula/literal.h"
#include "Formula/formula.h"
#include <deque>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <memory>

enum Result{SAT, UNSAT, UNKNOWN, CONFLICT, UNIT};

class SolverBaseClass
{
public:
    SolverBaseClass( Formula& formula);
    SolverBaseClass(const SolverBaseClass& formula);

    virtual Result calc();

    /**
      Berechnet das Literal, welches als nächstes gesetzt werden soll
     * @brief decide
     * @return
     */
    virtual Literal decide() = 0;
    /**

     * @brief clauseChanges
     * @param c: Die Clause die verändert wurde.

    */

    virtual void clauseChanges(Clauses* c) = 0;
    /**
      Geht zurück
     * @brief backtrack
     * @return Anzahl der Schritte zurück
     */
    virtual uint backtrack() = 0;
    /**
      Führt änderungen in der Datenstruktur durch
     * @brief setLiteral
     * @param other
     * @return UNKNOWN: Falls nicht bekannt ob SAT oder nicht
     *         CONFLICT: Kann nicht weiter machen, da Conflict
     */
    virtual Result setLiteral(const Literal& lit) = 0;
    void showRemainingClauses();
    ~SolverBaseClass();
protected:
    uint numberVariables, numberClauses;
    Formula form;
    boost::dynamic_bitset<> variableAssignment;
    boost::dynamic_bitset<> variableUsed;
    boost::dynamic_bitset<> variableDecision;
    std::vector< std::deque<std::shared_ptr<Clauses> > > LiteralOccur;
    std::deque<Literal> decisions;

private:
    Result result;

    friend std::ostream& operator<<(std::ostream& out, const SolverBaseClass& solver);

};

std::ostream& operator<<(std::ostream& out, const SolverBaseClass& solver);


#endif // SOLVERBASECLASS_H
