//
// Created by gmardon on 13/01/17.
//

#include <zconf.h>
#include "Processor.hh"
#include "../Gametek.hh"

Processor::Processor(Gametek *gametek) {
    m_memory = gametek->getMemory();
    m_cartridge = gametek->getCartridge();
    m_gametek = gametek;
    if (m_gametek->getState() == BOOT)
        m_PC.setValue(0x0);
    else // set this after Boot ROM
        m_PC.setValue(0x100);
    m_SP.setValue(0xFFFE);
    if (m_cartridge->isGBC())
        m_AF.setValue(0x11B0);
    else
        m_AF.setValue(0x01B0);
    m_BC.setValue(0x0013);
    m_DE.setValue(0x00D8);
    m_HL.setValue(0x014D);
}

uint8_t Processor::tick() {
    if (!m_gametek->getState() == HALT) {
        if (m_gametek->getState() == BOOT) {
            uint16_t pc_before = m_memory->read(m_PC.getValue());
            executeOPCode(retrieveOPCode());
            uint16_t pc_after = m_memory->read(m_PC.getValue());
            if ((pc_before == 0xFE) && (pc_after == 0x100))
                m_gametek->setState(IN_GAME);
        } else
            executeOPCode(retrieveOPCode());
    } else {
        printf("Halt requested..");
    }
    usleep(100000);

}

uint8_t Processor::retrieveOPCode() {
    uint8_t opcode = m_memory->read(m_PC.getValue());
    m_PC.increment();

    /*if (m_bSkipPCBug)
    {
        m_bSkipPCBug = false;
        PC.Decrement();
    }*/

    return opcode;
}


void Processor::executeOPCode(uint8_t opcode) {
    bool isCB = (opcode == 0xCB);

    /*if (isCB)
    {
       // opcodeTable = m_OPCodesCB;
        //opcode = m_memory->read(m_head++);
    }
    else*/
    //opcodeTable = m_OPCodes;
    // printf("[%d] %s\n", opcode, opCodeNames[opcode]);
}

void Processor::updateRealtimeClock() {
    time(&m_RTC);
}

time_t Processor::getRealtimeClock() {
    return m_RTC;
}