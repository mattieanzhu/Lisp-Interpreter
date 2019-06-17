#include "file1.h"
#include "common.h"
#include <iostream>
#include <string>

std::string inputString(){
    std::string theInputString;
    getline(std::cin, theInputString,(char) std::cin.eof());
    return theInputString;
}
