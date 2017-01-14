//
// Created by gmardon on 14/01/17.
//

#ifndef GAMETEK_EIGHTBITREGISTER_HH
#define GAMETEK_EIGHTBITREGISTER_HH


#include <stdint-gcc.h>

class EightBitRegister {
public:
    EightBitRegister() : m_value(0) {}

    void setValue(uint8_t value);

    uint8_t getValue() const;

    void increment();

    void decrement();

private:
    uint8_t m_value;
};

#endif //GAMETEK_EIGHTBITREGISTER_HH
