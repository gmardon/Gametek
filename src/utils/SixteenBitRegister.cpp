//
// Created by gmardon on 14/01/17.
//

#include "SixteenBitRegister.hh"

void SixteenBitRegister::setLow(uint8_t low)
{
    this->m_low.setValue(low);
}

uint8_t SixteenBitRegister::getLow() const
{
    return m_low.getValue();
}

void SixteenBitRegister::setHigh(uint8_t high)
{
    this->m_high.setValue(high);
}

uint8_t SixteenBitRegister::getHigh() const
{
    return m_high.getValue();
}

EightBitRegister* SixteenBitRegister::getHighRegister()
{
    return &m_high;
}

EightBitRegister* SixteenBitRegister::getLowRegister()
{
    return &m_low;
}

void SixteenBitRegister::setValue(uint16_t value)
{
    m_low.setValue((uint8_t) (value & 0xFF));
    m_high.setValue((uint8_t) ((value >> 8) & 0xFF));
}

uint16_t SixteenBitRegister::getValue() const
{
    uint8_t high = m_high.getValue();
    uint8_t low = m_low.getValue();

    return (high << 8) + low;
}

void SixteenBitRegister::increment()
{
    uint16_t value = this->getValue();
    value++;
    this->setValue(value);
}

void SixteenBitRegister::decrement()
{
    uint16_t value = this->getValue();
    value--;
    this->setValue(value);
}