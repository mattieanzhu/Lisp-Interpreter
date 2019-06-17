#include <iostream>
#include <vector>
#include <string>
#include "file1.h"
#include "common.h"

std::vector<std::string> allAtoms;
std::vector<int> parenthesisIndexes;
std::vector<std::string> atomsToBeEvaluated;
std::vector<std::string> currExpr;
int atomsEvaluated = 0;
int OpenCloseCount = 0;
bool StillValid = true;
std::string file1String = inputString();
void getNextToken(std::string fileString);
bool isValid(std::string token);
bool isNumeric(std::string token);
void Push();
void Parse(std::string current);
void Evaluate(std::vector<std::string> curr);
void evalCar(std::vector<std::string> curr);
void evalCdr(std::vector<std::string> curr);
void evalCons(std::vector<std::string> curr);
void evalAtom(std::vector<std::string> curr);
void evalInt(std::vector<std::string> curr);
void evalNull(std::vector<std::string> curr);
void evalEq(std::vector<std::string> curr);
void evalPlus(std::vector<std::string> curr);
void evalMinus(std::vector<std::string> curr);
void evalTimes(std::vector<std::string> curr);
void evalLess(std::vector<std::string> curr);
void evalGreater(std::vector<std::string> curr);
void evalQuote(std::vector<std::string> curr);
void printValue();

int main(){
    getNextToken(file1String);
    Push();
}

void Push(){
    for(int i=0; i<allAtoms.size(); i++){
        Parse(allAtoms[i]);
    }
}

void Parse(std::string current){
    if(current == "("){
        atomsToBeEvaluated.push_back(current);
        OpenCloseCount++;
        parenthesisIndexes.push_back(atomsToBeEvaluated.size()-1);
    }
    else if(current == ")"){
        atomsToBeEvaluated.push_back(current);
        OpenCloseCount--;
        for(int i=parenthesisIndexes[parenthesisIndexes.size()-1]; i<=atomsToBeEvaluated.size()-1; i++){
            currExpr.push_back(atomsToBeEvaluated[i]);
            atomsEvaluated++;
        }
        parenthesisIndexes.pop_back();
        Evaluate(currExpr);
        currExpr.clear();
        if(OpenCloseCount == 0){
            if(StillValid == true){
                printValue();
                atomsToBeEvaluated.clear();
            }
        }
    }
    else{
        atomsToBeEvaluated.push_back(current);
    }
}

void Evaluate(std::vector<std::string> curr){
    if(curr[1] == "CAR"){
        evalCar(curr);
    }
    else if(curr[1] == "CDR"){
        evalCdr(curr);
    }
    else if(curr[1] == "CONS"){
        evalCons(curr);
    }
    else if(curr[1] == "ATOM"){
        evalAtom(curr);
    }
    else if(curr[1] == "INT"){
        evalInt(curr);
    }
    else if(curr[1] == "NULL"){
        evalNull(curr);
    }
    else if(curr[1] == "EQ"){
        evalEq(curr);
    }
    else if(curr[1] == "PLUS"){
        evalPlus(curr);
    }
    else if(curr[1] == "TIMES"){
        evalTimes(curr);
    }
    else if(curr[1] == "MINUS"){
        evalMinus(curr);
    }
    else if(curr[1] == "LESS"){
        evalLess(curr);
    }
    else if(curr[1] == "GREATER"){
        evalGreater(curr);
    }
    else if(curr[1] == "QUOTE"){
        evalQuote(curr);
    }
    else{
        atomsToBeEvaluated.clear();
        std::cerr << "ERROR: Invalid command";
        StillValid = false;
    }
}

void evalQuote(std::vector<std::string> curr){
    if(OpenCloseCount == 0){
        std::string value;
        if(curr.size() > 3){
            for(int i=2; i<curr.size()-1; i++){
                value += curr[i];
                value += " ";
            }
            value.pop_back();
            while(atomsEvaluated > 0){
                atomsToBeEvaluated.pop_back();
                atomsEvaluated--;
            }
            atomsToBeEvaluated.push_back(value);
        }
        else{
            std::cerr << "ERROR: Invalid token";
            StillValid = false;
        }
    }
    if(OpenCloseCount != 0){
        std::vector<std::string> values;
        if(curr.size() > 4){
            for(int i=3; i<curr.size()-1; i++){
                values.push_back(curr[i]);
            }
            while(atomsEvaluated > 0){
                atomsToBeEvaluated.pop_back();
                atomsEvaluated--;
            }
            for(int i=0; i<values.size(); i++){
                atomsToBeEvaluated.push_back(values[i]);
            }
        }
        else{
            std::cerr << "ERROR: Invalid token";
            StillValid = false;
        }
    }
}

void evalCar(std::vector<std::string> curr){
    std::string value;
    if(curr.size() != 5){
        atomsToBeEvaluated.clear();
    }
    else{
        value = curr[2];
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
}

void evalCdr(std::vector<std::string> curr){
    std::string value;
    if(curr.size() != 5){
        atomsToBeEvaluated.clear();
    }
    else{
        value += curr[3];
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
}

void evalCons(std::vector<std::string> curr){
    if(OpenCloseCount == 0){
        std::string value;
        if(curr.size() >= 4){
            value += "(";
            for(int i=2; i<curr.size()-1; i++){
                if(curr[i] != "NIL"){
                    value += curr[i];
                    value += " ";
                }
            }
            value.pop_back();
            value += ")";
            while(atomsEvaluated > 0){
                atomsToBeEvaluated.pop_back();
                atomsEvaluated--;
            }
            for(int i=1; i<value.size()-1; i++){
                if(value[i] == '(' || value[i] == ')'){
                    value.erase(value[i]);
                }
            }
            atomsToBeEvaluated.push_back(value);
        }
        else{
            std::cerr << "ERROR: Invalid token";
            StillValid = false;
        }
    }
    if(OpenCloseCount != 0){
        std::vector<std::string> values;
        if(curr.size() >= 4){
            for(int i=2; i<curr.size()-1; i++){
                if(curr[i] != "NIL"){
                    values.push_back(curr[i]);
                }
            }
            while(atomsEvaluated > 0){
                atomsToBeEvaluated.pop_back();
                atomsEvaluated--;
            }
            for(int i=0; i<values.size(); i++){
                atomsToBeEvaluated.push_back(values[i]);
            }
        }
        else{
            std::cerr << "ERROR: Invalid token";
            StillValid = false;
        }
    }
}

void evalAtom(std::vector<std::string> curr){
    std::string value;
    if(curr.size() > 3){
        if(curr.size() == 4 && isValid(curr[2])){
            value += "T";
        }
        else{
            value += "NIL";
        }
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void evalInt(std::vector<std::string> curr){
    std::string value;
    if(curr.size() > 3){
        if(curr.size() == 4 && isNumeric(curr[2])){
            value += "T";
        }
        else{
            value += "NIL";
        }
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void evalEq(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 5 && isValid(curr[2]) && isValid(curr[3])){
        if(curr[2] == curr[3]){
            value += "T";
        }
        else{
            value += "NIL";
        }
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void evalLess(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 5 && isNumeric(curr[2]) && isNumeric(curr[3])){
        int a = std::stoi(curr[2]);
        int b = std::stoi(curr[3]);
        if(a < b){
            value += "T";
        }
        else{
            value += "NIL";
        }
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: undefined";
        StillValid = false;
    }
}

void evalNull(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 4 && curr[2] == "NIL"){
        value += "T";
    }
    else{
        value += "NIL";
    }
    while(atomsEvaluated > 0){
        atomsToBeEvaluated.pop_back();
        atomsEvaluated--;
    }
    atomsToBeEvaluated.push_back(value);
}

void evalPlus(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 5 && isNumeric(curr[2]) && isNumeric(curr[3])){
        int a = std::stoi(curr[2]);
        int b = std::stoi(curr[3]);
        int c = a+b;
        value = std::to_string(c);
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void evalTimes(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 5 && isNumeric(curr[2]) && isNumeric(curr[3])){
        int a = std::stoi(curr[2]);
        int b = std::stoi(curr[3]);
        int c = a*b;
        value = std::to_string(c);
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void evalMinus(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 5 && isNumeric(curr[2]) && isNumeric(curr[3])){
        int a = std::stoi(curr[2]);
        int b = std::stoi(curr[3]);
        int c = a-b;
        value = std::to_string(c);
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void evalGreater(std::vector<std::string> curr){
    std::string value;
    if(curr.size() == 5 && isNumeric(curr[2]) && isNumeric(curr[3])){
        int a = std::stoi(curr[2]);
        int b = std::stoi(curr[3]);
        if(a > b){
            value += "T";
        }
        else{
            value += "NIL";
        }
        while(atomsEvaluated > 0){
            atomsToBeEvaluated.pop_back();
            atomsEvaluated--;
        }
        atomsToBeEvaluated.push_back(value);
    }
    else{
        std::cerr << "ERROR: Invalid token";
        StillValid = false;
    }
}

void printValue(){
    for(int i=0; i<atomsToBeEvaluated.size(); i++){
        if(!atomsToBeEvaluated[i].empty()){
            std::cout << atomsToBeEvaluated[i] << std::endl;
        }
    }
}

void getNextToken(std::string fileString){
    std::string token;
    for(int i=0; i<file1String.size(); i++){
        if(file1String[i] == '('){
            if(!token.empty()){
                allAtoms.push_back(token);
            }
            allAtoms.push_back("(");
            token.clear();
        }
        else if(file1String[i] == ')'){
            if(!token.empty()){
                allAtoms.push_back(token);
            }
            allAtoms.push_back(")");
            token.clear();
        }
        else if(file1String[i] != ' '){
            token += file1String[i];
        }
        else if(file1String[i] == ' '){
            if(!token.empty()){
                allAtoms.push_back(token);
            }
            token.clear();
        }
    }
    if(!token.empty()){
        allAtoms.push_back(token);
    }
}

bool isValid(std::string token){
    if(isNumeric(token)){
        return true;
    }
    else if(isupper(token[0])){
        bool isLiteral = true;
        for(int i=1; i<token.size(); i++){
            if(!isdigit(token[i]) && !isupper(token[i])){
                isLiteral = false;
                break;
            }
        }
        if(isLiteral == true){
            return true;
        }
        else{
            std::cerr << "ERROR: Invalid token " << token << std::endl;
            return false;
        }
    }
    return false;
}

bool isNumeric(std::string token){
    if(isdigit(token[0]) || token[0] == '-'){
        bool numeric = true;
        for(int i=1; i<token.size(); i++){
            if(!isdigit(token[i])){
                numeric = false;
                break;
            }
        }
        if(numeric == true){
            return true;
        }
        else{
            std::cerr << "ERROR: Invalid token " << token << std::endl;
            return false;
        }
    }
    return false;
}


