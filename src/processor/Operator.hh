//
// Created by gmardon on 16/01/17.
//

#ifndef GAMETEK_OPERATOR_HH
#define GAMETEK_OPERATOR_HH
#include <iostream>

class Processor;

struct Operator_t {
    unsigned char id;
    std::string name;
    void (Processor::*function)();
    unsigned int cycles;
};

typedef Operator_t Operator;


#endif //GAMETEK_OPERATOR_HH
