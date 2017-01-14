//
// Created by gmardon on 14/01/17.
//

#include "SixteenBitRegister.hh"

void SixteenBitRegister::setLow(uint8_t low)
{
    this->m_low.SetValue(low);
}

uint8_t SixteenBitRegister::getLow() const
{
    return m_low.GetValue();
}

inline void SixteenBitRegister::setHigh(uint8_t high)
{
    this->m_High.SetValue(high);
}

u8 SixteenBitRegister::getHigh() const
{
    return m_High.GetValue();
}

EightBitRegister* SixteenBitRegister::getHighRegister()
{
    return &m_High;
}

EightBitRegister* SixteenBitRegister::getLowRegister()
{
    return &m_Low;
}

void SixteenBitRegister::setValue(uint16_t value)
{
    m_Low.SetValue((uint8_t) (value & 0xFF));
    m_High.SetValue((uint8_t) ((value >> 8) & 0xFF));
}

uint16_t SixteenBitRegister::getValue() const
{
    uint8_t high = m_High.GetValue();
    uint8_t low = m_Low.GetValue();

    return (high << 8) + low;
}

void SixteenBitRegister::increment()
{
    uint16_t value = this->GetValue();
    value++;
    this->SetValue(value);
}

void SixteenBitRegister::decrement()
{
    u16 value = this->GetValue();
    value--;
    this->SetValue(value);
}