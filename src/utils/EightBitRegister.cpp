//
// Created by gmardon on 14/01/17.
//

#include "EightBitRegister.hh"

void EightBitRegister::setValue(uint8_t value)
{
    this->m_value = value;
}

uint8_t EightBitRegister::getValue() const
{
    return m_value;
}

void EightBitRegister::increment()
{
    this->m_value++;
}

void EightBitRegister::decrement()
{
    this->m_value--;
}