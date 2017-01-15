//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_PROCESSOR_HH
#define GAMETEK_PROCESSOR_HH

#include <stdint-gcc.h>
#include "../memory/Memory.hh"
#include "../utils/SixteenBitRegister.hh"

class Gametek;

class Processor {
public:
    Processor(Gametek *gametek);

    void updateRealtimeClock();

    time_t getRealtimeClock();

    uint8_t tick();

private:
    void executeOPCode(uint8_t opcode);

    uint8_t retrieveOPCode();

    Memory *m_memory;
    Cartridge *m_cartridge;
    Gametek *m_gametek;
    time_t m_RTC;
    SixteenBitRegister m_AF;
    SixteenBitRegister m_BC;
    SixteenBitRegister m_DE;
    SixteenBitRegister m_HL;
    SixteenBitRegister m_SP;
    SixteenBitRegister m_PC;
};


#endif //GAMETEK_PROCESSOR_HH
