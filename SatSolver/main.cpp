#include <iostream>
#include "IO/io.h"
#include <sstream>
#include "Solver/stcalculus.h"
#include "Solver/solverbaseclass.h"
#include "Solver/dpllsolver.h"
#include "Solver/cdclsolver.h"
#include <boost/timer.hpp>
#include <fstream>

using namespace std;

int main()
{
    std::fstream data;
    data.open("/home/fettpet/SatSolver.html", std::ios::out);
    data << "<html><body><table border=\"1\">" << std::endl;
    data << "<tr><th>Instance</th><th>time CDCL</th><th>time DPLL</th><tr>" << std::endl;
    //std::cout << "Formel begin" << std::endl << IO::readFromFile("/home/fettpet/pp.dimacs") << std::endl;
    DPLLSolver solver(IO::readFromFile("/home/fettpet/pp.dimacs"));
    solver.calc();
    std::cout << solver << std::endl;
    std::cout << "Decisions:  " << solver.getDecisions() << std::endl;
    std::cout << "Backtracks: " << solver.getBacktracks() << std::endl;

    for(int i=1; i<=95;++i){
        std::stringstream str;
        str << "/home/fettpet/Dropbox/Programmieren/_P025_SatSolver/Instances/outtable3-001.txt." << i << ".cnf";
        std::cout << str.str() << std::endl;
        data << "<tr><th>" << str.str() << "</th><th>";
        boost::timer timer;
        CDCLSolver solver(IO::readFromFile(str.str()));
        Result r = solver.calc();
        data << timer.elapsed() << "</th><th>";


        DPLLSolver solver2(IO::readFromFile(str.str()));
        r = solver2.calc();
        data << timer.elapsed() << "</th><tr>" << std::endl;

    }
    for(int i=1; i<=95;++i){
        std::stringstream str;
        str << "/home/fettpet/Dropbox/Programmieren/_P025_SatSolver/Instances/outtable4-01.txt." << i << ".cnf";
        std::cout << str.str() << std::endl;
        data << "<tr><th>" << str.str() << "</th><th>";
        boost::timer timer;
        CDCLSolver solver(IO::readFromFile(str.str()));
        Result r = solver.calc();
        data << timer.elapsed() << "</th><th>";


        DPLLSolver solver2(IO::readFromFile(str.str()));
        r = solver2.calc();
        data << timer.elapsed() << "</th><tr>" << std::endl;
    }
    for(int i=1; i<=95;++i){

        std::stringstream str;
        str << "/home/fettpet/Dropbox/Programmieren/_P025_SatSolver/Instances/outtable5-01.txt." << i << ".cnf";
        std::cout << str.str() << std::endl;
        data << "<tr><th>" << str.str() << "</th><th>";
        boost::timer timer;
        CDCLSolver solver(IO::readFromFile(str.str()));
        Result r = solver.calc();
        data << timer.elapsed() << "</th><th>";


        DPLLSolver solver2(IO::readFromFile(str.str()));
        r = solver2.calc();
        data << timer.elapsed() << "</th><tr>" << std::endl;



    }
       data << "</table></body></html>" << std::endl;
       data.close();

//*/
    //STCalculus calc;
   // Result res = calc.calc(con);
   // if(res == UNSAT){
   //     std::cout << "UNSAT";
   // }
   // if(res == SAT){
   //     std::cout << "SAT";
   // }
//    cout << "Hello World!" << endl;
    return 0;
}

