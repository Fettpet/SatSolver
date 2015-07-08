#include "dpllsolver.h"

/**************************************************************************************************
 *                                      Constructor
 * ***********************************************************************************************/

DPLLSolver::DPLLSolver( Formula t):
    STCalculus(t),currentID(1)
{
    for(std::shared_ptr<Clauses> c: t.getClauses()){
        if(c->getNumberLiterals() == 1){
            UnitList.push_back(c->getWatchLiteral1());
        }
    }
    decisionLiteral.resize(form.getNumberOfVariables()+1, false);

}


DPLLSolver::DPLLSolver(const DPLLSolver& other):
    UnitList(other.UnitList),
    decisionLiteral(other.decisionLiteral),
    STCalculus(other), currentID(other.currentID)
{}

DPLLSolver::~DPLLSolver(){
    decisionLiteral.reset();
}

/**************************************************************************************************
 *                      Getter
 * ***********************************************************************************************/
bool DPLLSolver::isDecisionLiteral(const Literal& other)const{
    return decisionLiteral[other.getID()];
}

/**************************************************************************************************
 *                              Decision
 * ***********************************************************************************************/
uint DPLLSolver::backtrack(){
    std::cout << "Backtrack DecisionLiterals: "<< std::endl;
    std::cout << decisionLiteral << std::endl;
    uint backSteps(0);
    Literal lit;
    backtracksCount++;
    while(!decisions.empty()){
        backSteps++;
        variableUsed[decisions.back().getID()] = false;
        if(isDecisionLiteral(decisions.back())){
            lit = decisions.back();
            decisions.pop_back();
            lit.switchSign();
            variableUsed[lit.getID()] = false;
            UnitList.clear();
            UnitList.push_back(lit);
            std::cout << "Backtrack Literal:" << lit << std::endl;
            return backSteps+1;
        }
        decisions.pop_back();
    }

    return 0;
}

Literal DPLLSolver::decide(){
    Literal res;
    while(!UnitList.empty()){
        res = UnitList.front();
        UnitList.pop_front();
        if(variableUsed[res.getID()]) continue;
        decisionLiteral[res.getID()] = false;
    //    std::cout << "UNIT: " << res << ", " << res.getLit() << std::endl;
        return res;
    }

    currentID = 1;
    while(variableUsed[currentID])
        currentID++;
    if(currentID > numberVariables){
        std::cout << variableUsed << std::endl;
        std::cout << decisionLiteral << std::endl;
   //     std::cout << "Something wrong";
    }
    decisionsCount++;
    decisionLiteral[currentID] = true;
 //   std::cout << "Decision" << Literal(currentID, variableAssignment[currentID]) << std::endl;
    return Literal(currentID, variableAssignment[currentID]);
}

/**
Schaut in den Clauseln nach Konflikt literalen
 * @brief DPLLSolver::setLiteral
 * @param lit
 * @return
 */

Result DPLLSolver::setLiteral(const Literal& lit){
    bool problemLit1, problemLit2;
    for(std::shared_ptr<Clauses> cl: LiteralOccur[lit.getLit() ^ 1]){
// Unit

        if(cl->getNumberLiterals() == 1) {
       //     if((lit == cl->getWatchLiteral1())) continue;
            return CONFLICT;
        }

// Nachschauen ob das Konflik literal angeschaut wird
        problemLit1 = false; //variableUsed[cl->getWatchLiteral1().getID()] && (variableAssignment[cl->getWatchLiteral1().getID()] != cl->getWatchLiteral1().getSign());
        problemLit2 = false; //variableUsed[cl->getWatchLiteral2().getID()] && (variableAssignment[cl->getWatchLiteral2().getID()] != cl->getWatchLiteral2().getSign());
// Binary clause

        if((lit.getID() == cl->getWatchLiteral1().getID()) && (lit.getSign() != cl->getWatchLiteral1().getSign())){
            problemLit1 = true;
// Nach neuem Literal suchen
            for(Literal litClause: *cl){
// Überwachte werden ausgeschlossen
                if(litClause == cl->getWatchLiteral1()) continue;
                if(litClause == cl->getWatchLiteral2()) continue;
// Falls das Literal auf true abgebildet ist, wird es ausgeschlosen
                if(variableUsed[litClause.getID()] && (variableAssignment[litClause.getID()] != litClause.getSign())) continue;
                cl->setWatchLiteral1(litClause);
                problemLit1 = false;
                break;
            }
        }

        if((lit.getID() == cl->getWatchLiteral2().getID()) && (lit.getSign() != cl->getWatchLiteral2().getSign())){
            problemLit2 = true;
// Nach neuem Literal suchen
            for(Literal litClause: *cl){
// Überwachte werden ausgeschlossen
                if(litClause == cl->getWatchLiteral1()) continue;
                if(litClause == cl->getWatchLiteral2()) continue;
// Falls das Literal auf true abgebildet ist, wird es ausgeschlosen
                if(variableUsed[litClause.getID()] && (variableAssignment[litClause.getID()] != litClause.getSign())) continue;
                cl->setWatchLiteral2(litClause);
                problemLit2 = false;
                break;
            }
        }

        if(problemLit1 && problemLit2){
            return CONFLICT;
        }
        if(problemLit1){

            UnitList.push_back(cl->getWatchLiteral2());
        }
        if(problemLit2){
            UnitList.push_back(cl->getWatchLiteral1());
        }
    }
    return UNKNOWN;
}
