//
// Created by gmardon on 13/01/17.
//

#include <zconf.h>
#include "Processor.hh"
#include "../opcode.hh"

Processor::Processor(Memory *memory) {
    this->m_memory = memory;
    m_halt = false;
    m_duringBootROM = true;
    m_head = 0;
}

uint8_t Processor::tick() {
    if (!m_halt) {
        if (m_duringBootROM) {
            uint16_t pc_before = m_memory->read(m_head++);
            executeOPCode(m_memory->read(m_head++));
            uint16_t pc_after = m_memory->read(m_head++);
            if ((pc_before == 0xFE) && (pc_after == 0x100))
                m_duringBootROM = false;
        } else
            executeOPCode(m_memory->read(m_head++));
    } else {
        printf("Halt requested..");
    }
    usleep(100000);

}

void Processor::executeOPCode(uint8_t opcode) {
    bool isCB = (opcode == 0xCB);

    if (isCB)
    {
       // opcodeTable = m_OPCodesCB;
        opcode = m_memory->read(m_head++);
    }
    else
        //opcodeTable = m_OPCodes;
    printf("[%d] %s\n", opcode, opCodeNames[opcode]);
}

void Processor::updateRealtimeClock() {
    time(&m_RTC);
}

time_t Processor::getRealtimeClock() {
    return m_RTC;
}