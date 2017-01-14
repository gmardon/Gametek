//
// Created by gmardon on 14/01/17.
//

#ifndef GAMETEK_SIXTEENBITREGISTER_HH
#define GAMETEK_SIXTEENBITREGISTER_HH

#include "EightBitRegister.hh"

class SixteenBitRegister {
public:
    SixteenBitRegister() {}

    void setLow(uint8_t low);

    uint8_t getLow() const;

    void setHigh(uint8_t high);

    uint8_t getHigh() const;

    EightBitRegister *getHighRegister();

    EightBitRegister *getLowRegister();

    void setValue(uint16_t value);

    uint16_t getValue() const;

    void increment();

    void decrement();

private:
    EightBitRegister m_high;
    EightBitRegister m_low;
};

#endif //GAMETEK_SIXTEENBITREGISTER_HH
