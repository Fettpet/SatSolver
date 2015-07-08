#ifndef DPLLSOLVER_H
#define DPLLSOLVER_H
#include "Solver/stcalculus.h"
#include "Formula/literal.h"
#include <deque>

class DPLLSolver: public STCalculus
{
public:
    DPLLSolver( Formula t);
    DPLLSolver(const DPLLSolver& other);
    ~DPLLSolver();
    virtual Literal decide();
    virtual uint backtrack();
  //  Result backtrack( FormulaContainer& form, uint level);

    virtual Result setLiteral(const Literal& lit);
    virtual void clauseChanges(Clauses* c){}
  //  void undoLiteral(FormulaContainer& form,uint ID, bool flag);

protected:
    std::deque<Literal> UnitList;
    boost::dynamic_bitset<> decisionLiteral;
    uint currentID;
    bool isDecisionLiteral(const Literal& other)const;
};


#endif // DPLLSOLVER_H
