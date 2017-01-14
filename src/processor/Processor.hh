//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_PROCESSOR_HH
#define GAMETEK_PROCESSOR_HH


#include <stdint-gcc.h>
#include "../memory/Memory.hh"

class Processor {
public:
    Processor(Memory *memory);

    void updateRealtimeClock();
    time_t getRealtimeClock();
    uint8_t tick();
private:
    void executeOPCode(uint8_t opcode);

    bool m_halt;
    uint16_t m_head;
    Memory *m_memory;
    time_t m_RTC;
    bool m_duringBootROM;
};


#endif //GAMETEK_PROCESSOR_HH
