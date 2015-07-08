#include "stcalculus.h"

/**************************************************************************************************
 *                                      Constructor
 * ***********************************************************************************************/

STCalculus::STCalculus( Formula t):
    SolverBaseClass(t), decisionsCount(0), backtracksCount(0),currentID(0)
{}


STCalculus::STCalculus(const STCalculus& other):
    SolverBaseClass(other), currentID(other.currentID)
{}
/**************************************************************************************************
 *                              Decision
 * ***********************************************************************************************/
uint STCalculus::backtrack(){
    uint backSteps(0);
    Literal lit;
    backtracksCount++;
    for(;currentID>0;--currentID){
        backSteps++;
        lit = decisions.back();//[decisions.size()-1];
        decisions.pop_back();

        variableUsed[lit.getID()] = false;

        if(!variableAssignment[lit.getID()]){
            variableAssignment[lit.getID()] = true;
            --currentID;
       //     std::cout << variableAssignment << std::endl;
            return backSteps;
        } else{
            variableAssignment[lit.getID()] = false;

        }
    }
    return 0;
}

Literal STCalculus::decide(){
    currentID++;
    decisionsCount++;
    return Literal(currentID, variableAssignment[currentID]);
}

/**
Schaut in den Clauseln nach Konflikt literalen
 * @brief STCalculus::setLiteral
 * @param lit
 * @return
 */

Result STCalculus::setLiteral(const Literal& lit){
    bool problemLit1, problemLit2;
    for(std::shared_ptr<Clauses> cl: LiteralOccur[lit.getLit()]){
// Unit

        if(cl->getNumberLiterals() == 1) {
       //     if((lit == cl->getWatchLiteral1())) continue;
            return CONFLICT;
        }

// Nachschauen ob das Konflik literal angeschaut wird
        problemLit1 = variableUsed[cl->getWatchLiteral1().getID()] && (variableAssignment[cl->getWatchLiteral1().getID()] != cl->getWatchLiteral1().getSign());
        problemLit2 = variableUsed[cl->getWatchLiteral2().getID()] && (variableAssignment[cl->getWatchLiteral2().getID()] != cl->getWatchLiteral2().getSign());
// Binary clause

        if(cl->getNumberLiterals() == 2){
//            std::cout << "Problem1: " << problemLit1 << variableAssignment[cl->getWatchLiteral1().getID()] << " Problem2: " << problemLit2 << variableAssignment[cl->getWatchLiteral2().getID()] << *cl << std::endl;
            if(problemLit1 && problemLit2){
                return CONFLICT;
            }
        }

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
    }
    return UNKNOWN;
}
