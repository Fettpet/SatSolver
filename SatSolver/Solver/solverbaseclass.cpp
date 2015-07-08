#include "solverbaseclass.h"

/**************************************************************************************************
 *                                  Constructor
 * ***********************************************************************************************/
SolverBaseClass::SolverBaseClass(Formula& formula):
    numberVariables(formula.getNumberOfVariables()), numberClauses(formula.getClauses().size()),
    form(formula), result(UNKNOWN)
{
    variableAssignment.resize(numberVariables+1, false);
    variableUsed.resize(numberVariables+1, false);
    LiteralOccur.resize((numberVariables+1)*2);
    variableDecision.resize(numberVariables+1, false);
    for(uint i=0; i<numberClauses; ++i){
        std::set<Literal>::const_iterator begin, end;
        begin = form.getClause(i)->begin();
        end = form.getClause(i)->end();

        for(std::set<Literal>::const_iterator it=begin; it!=end; ++it){

            LiteralOccur[(*it).getLit()].push_back(form.getClause(i));
        }
    }


}



SolverBaseClass::SolverBaseClass(const SolverBaseClass& formula):
    numberVariables(formula.numberVariables), numberClauses(formula.numberClauses),
    form(formula.form),
    variableAssignment(formula.variableAssignment),
    variableUsed(formula.variableUsed),
    LiteralOccur(formula.LiteralOccur),
    decisions(formula.decisions),
    result(formula.result)
{}

SolverBaseClass::~SolverBaseClass(){
    variableAssignment.reset();
    variableUsed.reset();
    variableDecision.reset();
}

/**************************************************************************************************
 *
 * ***********************************************************************************************/
/**
 Calculate a given formula.
 * @brief SolverBaseClass::calc
 * @return SAT
 *         UNSAT
*/

Result SolverBaseClass::calc(){
    uint setVars(0);
    Result res;
    Literal currentLiteral(0, false);
    while(true){
        currentLiteral = decide();
        if(currentLiteral.getID() > numberVariables){
            result = SAT;
            return SAT;
        }
        decisions.push_back(currentLiteral);
        variableUsed[currentLiteral.getID()] = true;
        variableAssignment[currentLiteral.getID()] = currentLiteral.getSign();
        res = setLiteral(currentLiteral);
        setVars++;
        if(res == CONFLICT){
            uint backtrackSteps = backtrack();
            if(backtrackSteps == 0){
                result = UNSAT;
                return UNSAT;
            }
            setVars -= backtrackSteps;
            continue;
        }

        if(setVars == numberVariables) {
            result = SAT;
            return SAT;
        }

    }
}



/**************************************************************************************************
 *                                  output
 * ***********************************************************************************************/
std::ostream& operator<<(std::ostream& out, const SolverBaseClass& solver){
    out << "c ";
    if(solver.result == SAT){
        out << "SAT";
        for(uint i=1; i<=solver.numberVariables;++i){
            out << " ";
            if(solver.variableAssignment[i]){
                out  << "-" << i;
            }else{
                out  << i;
            }
        }
    }
    if(solver.result == UNSAT){
        out << "UNSAT";
    }
    return out;
}


