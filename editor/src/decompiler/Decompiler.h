//
// Created by gmardon on 25/01/17.
//

#ifndef GAMETEK_DECOMPILER_H
#define GAMETEK_DECOMPILER_H

#include <iostream>

struct Operator_t {
    unsigned char id;
    std::string name;
};
typedef Operator_t Operator;
class Decompiler {
public:
    Decompiler();

    std::string decompile(const std::string file);
    Operator *getOperators() const;
private:
    Operator *m_operators;
};


#endif //GAMETEK_DECOMPILER_H
