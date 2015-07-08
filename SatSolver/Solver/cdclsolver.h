#ifndef CDCLSOLVER_H
#define CDCLSOLVER_H
#include "dpllsolver.h"

class CDCLSolver : public DPLLSolver
{
public:

    CDCLSolver( Formula t);
    CDCLSolver(const CDCLSolver& other);
    virtual uint backtrack();
  //  Result backtrack( FormulaContainer& form, uint level);

    virtual Result setLiteral(const Literal& lit);
    virtual void clauseChanges(Clauses* c){}
  //  void undoLiteral(FormulaContainer& form,uint ID, bool flag);
    void printTrack() const;
protected:
    std::vector<std::shared_ptr<Clauses> > reasonClause;
    Clauses learnedClause;
private:
    void conflictAnalyse(const std::shared_ptr<Clauses> cl);
    Clauses resolution(const Clauses& cl1, const std::shared_ptr<Clauses> cl2, Literal lit);
    void learnClauses(const Clauses& cl);
};

#endif // CDCLSOLVER_H
