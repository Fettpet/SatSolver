#ifndef STCALCULUS_H
#define STCALCULUS_H
#include "Solver/solverbaseclass.h"
#include <iostream>

class STCalculus: public SolverBaseClass
{
public:
    STCalculus( Formula t);
    STCalculus(const STCalculus& other);

    virtual Literal decide();
    virtual uint backtrack();
  //  Result backtrack( FormulaContainer& form, uint level);

    virtual Result setLiteral(const Literal& lit);
    virtual void clauseChanges(Clauses* c){}
  //  void undoLiteral(FormulaContainer& form,uint ID, bool flag);

    long getDecisions() const{
        return decisionsCount;
    }

    long getBacktracks() const{
        return backtracksCount;
    }

protected:
    long decisionsCount, backtracksCount;
    uint currentID;
};


#endif // STCALCULUS_H
