#include "io.h"
#include <fstream>

IO::IO()
{
}

/**************************************************************************************************
 *                      IO
 * ***********************************************************************************************/
Formula IO::readFromFile(const std::string fileName){
    Formula result;
    uint numberVars;
    std::fstream data;
    data.open(fileName, std::ios::in);
    if(!data.is_open()){
        std::cout << "Could not open: " << fileName;
        exit(1);
    }
    while(!data.eof()){
        std::string line;
        getline(data, line);
        if(line.empty()) continue;
        if(line[0] == 'c' || line[0] == 'C') continue;
// Header line
        if(line[0] == 'p'){
            line = line.substr(line.find(" ")+1);
            line = line.substr(line.find(" ")+1);
            numberVars = std::stoi(line.substr(0, line.find(" ")));

            result.setNumberOfVariables(numberVars);
            continue;
        }

        result.addClauses(Clauses(line));


    }

    return result;
}
