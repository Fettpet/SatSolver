#include "cdclsolver.h"

/**************************************************************************************************
 *                                      Constructor
 * ***********************************************************************************************/

CDCLSolver::CDCLSolver( Formula t):
    DPLLSolver(t)
{
    reasonClause.resize(t.getNumberOfVariables()*2+2);
    for(std::shared_ptr<Clauses> c: t.getClauses()){
        if(c->getNumberLiterals() == 1){

            reasonClause[c->getWatchLiteral1().getLit()] = c;
        }
    }
}


CDCLSolver::CDCLSolver(const CDCLSolver& other):
    DPLLSolver(other), reasonClause(other.reasonClause)
{}


/**************************************************************************************************
 *                              Decision
 * ***********************************************************************************************/
uint CDCLSolver::backtrack(){
    if(learnedClause.getNumberLiterals() == 1){
        UnitList.clear();
        UnitList.push_back(learnedClause.getWatchLiteral1());
        uint numberStartClear(0);
        for(;numberStartClear<decisions.size(); ++numberStartClear){
            if(isDecisionLiteral(decisions[numberStartClear])) break;
        }
        numberStartClear = decisions.size() - numberStartClear;
        for(int i=0; i<numberStartClear; ++i){
            variableUsed[decisions.back().getID()] = false;
            decisions.pop_back();
        }


        return numberStartClear;
    }
    uint backSteps(0);
    bool hasFounded(false);
    Literal lit, containsLit, foundedLit;
    backtracksCount++;
    while(!decisions.empty()){
        backSteps++;
        lit = decisions.back();
        variableUsed[lit.getID()] = false;
        reasonClause[lit.getLit()] = NULL;
        decisions.pop_back();
        containsLit = lit;
        containsLit.switchSign();
        if(learnedClause.contains(containsLit)){
            foundedLit = containsLit;
            hasFounded = true;
            reasonClause[containsLit.getLit()] = form.getClause(form.getNumberOfClauses()-1);
            //foundedLit.switchSign();
        }
        if(isDecisionLiteral(lit) && hasFounded){
            variableUsed[foundedLit.getID()] = false;
            UnitList.clear();
            UnitList.push_back(foundedLit);

            return backSteps;

        }

    }

    return 0;
}

/**
Schaut in den Clauseln nach Konflikt literalen
 * @brief CDCLSolver::setLiteral
 * @param lit
 * @return
 */

Result CDCLSolver::setLiteral(const Literal& lit){
    bool problemLit1, problemLit2;
    for(std::shared_ptr<Clauses > cl: LiteralOccur[lit.getLit() ^1]){
// Unit

        if(cl->getNumberLiterals() == 1) {

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
// Falls das Literal auf false abgebildet ist, wird es ausgeschlosen
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
// Falls das Literal auf false abgebildet ist, wird es ausgeschlosen
                if(variableUsed[litClause.getID()] && (variableAssignment[litClause.getID()] != litClause.getSign())) continue;

                cl->setWatchLiteral2(litClause);

                problemLit2 = false;
                break;
            }
        }

        if(problemLit1 && problemLit2){

            conflictAnalyse(cl);
            return CONFLICT;
        }
        if(problemLit1){

            reasonClause[cl->getWatchLiteral2().getLit()  ] = cl;
            UnitList.push_back(cl->getWatchLiteral2());
        }
        if(problemLit2){
            if(cl->getNumberLiterals() > 2){

            }
       //     std::cout << "Literal: " << cl->getWatchLiteral1() << "ReasonClause:" << *cl << std::endl;
            reasonClause[cl->getWatchLiteral1().getLit()] = cl;
            UnitList.push_back(cl->getWatchLiteral1());
        }
    }
    return UNKNOWN;
}


/**************************************************************************************************
 *                          Resolution
 * ***********************************************************************************************/
Clauses CDCLSolver::resolution(const Clauses& cl1, const std::shared_ptr<Clauses> cl2, Literal lit){
    std::set<Literal> litSet;
    for(const Literal& l: cl1){
        if((lit.getID() != l.getID())){
            litSet.insert(l);
        }
    }
    for(const Literal& l: *cl2){
        if(lit.getID() != l.getID()){
            litSet.insert(l);
        }
    }
    return Clauses(litSet);
}

void CDCLSolver::learnClauses(const Clauses& cl){
    form.addClauses(cl);
    std::shared_ptr<Clauses> learnClause = form.getClause(form.getNumberOfClauses()-1);
    for(const Literal& lit: *learnClause){
        LiteralOccur[lit.getLit()].push_back(learnClause);
    }
}

void CDCLSolver::conflictAnalyse(const std::shared_ptr<Clauses> cl){
    learnedClause = *cl;
    for(const Literal& l: *cl){

        learnedClause = resolution(learnedClause, reasonClause[l.getLit() ^ 1], l);
    }
    learnClauses(learnedClause);
}

/**************************************************************************************************
 *                          Debugging
 * ***********************************************************************************************/
void CDCLSolver::printTrack() const{
    std::cout << "Literal \t\t Decision \t\t ReasonClause" <<std::endl;
    for(uint i=0; i<decisions.size(); ++i){
        std::cout << decisions[i] << "\t\t";
        std::cout << (isDecisionLiteral(decisions[i])?"True":"False") << "\t\t";
        if(!isDecisionLiteral(decisions[i])){
            std::cout << *(reasonClause[decisions[i].getLit()]);
        }
        std::cout << std::endl;
        //std::cerr << (!DecisionLiteral[i]?(*(reasonClause[decisions[i].getLit()])):Clauses()) << std::endl;
    }
}

