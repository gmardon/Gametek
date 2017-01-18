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

    m_operators = (Operator *) malloc(256 * (sizeof(Operator_t)));
    m_operators[0x00] = (Operator) {0x00, "NOP", &Processor::NOP, 1};
    m_operators[0x05] = (Operator) {0x05, "DEC B", &Processor::DEC_B, 1};
    m_operators[0x08] = (Operator) {0x08, "LD (nn),SP", &Processor::LD_NN_SP, 1};
    m_operators[0x0C] = (Operator) {0x0C, "INC C", &Processor::INC_C, 1};
    m_operators[0x0E] = (Operator) {0x0E, "LD C,n", &Processor::LD_C_N, 1};
    m_operators[0x20] = (Operator) {0x20, "JR NZ,n", &Processor::JR_NZ_N, 1};
    m_operators[0x21] = (Operator) {0x21, "LD HL,nn", &Processor::LD_HL_NN, 1};
    m_operators[0x22] = (Operator) {0x22, "LDI (HL),A", &Processor::LDI_HL_A, 1};
    m_operators[0x23] = (Operator) {0x23, "INC HL", &Processor::INC_HL, 1};
    m_operators[0x31] = (Operator) {0x31, "LD SP,nn", &Processor::LD_SP_NN, 1};
    m_operators[0x32] = (Operator) {0x32, "LDD (HL),A", &Processor::LDD_HL_A, 1};
    m_operators[0x3E] = (Operator) {0x3E, "LD A,n", &Processor::LD_A_N, 1};
    m_operators[0x77] = (Operator) {0x77, "LD (HL),A", &Processor::LD_HL_A, 1};
    m_operators[0xAF] = (Operator) {0xAF, "XOR A", &Processor::XOR_A, 1};
    m_operators[0xE2] = (Operator) {0xE2, "LDH (C),A", &Processor::LDH_C_A, 1};
    m_operators[0xFE] = (Operator) {0xFE, "CP N", &Processor::CP_N, 1};
    m_operators[0xFF] = (Operator) {0xFF, "RST 38H", &Processor::RST_38H, 1};

    m_operatorsCB = (Operator *) malloc(256 * (sizeof(Operator_t)));
    m_operatorsCB[0x7C] = (Operator) {0x7C, "BIT 7,H", &Processor::BIT_7_H, 1};
}

uint8_t Processor::tick() {
    if (m_gametek->getState() != HALT) {
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

    Operator *targetOperators;
    if (isCB) {
        printf("[PC: %04X][Found: 0x%02X] Use CB operators\n", m_PC.getValue() - 1, opcode);
        opcode = retrieveOPCode();
        targetOperators = m_operatorsCB;
    } else
        targetOperators = m_operators;
    printf("[PC: %04X]", m_PC.getValue() - 1);
    printf("[Found: 0x%02X] %s\n", opcode, targetOperators[opcode].name.c_str());
    auto ptrRef = targetOperators[opcode].function;
    (this->*ptrRef)();
}

void Processor::updateRealtimeClock() {
    time(&m_RTC);
}

time_t Processor::getRealtimeClock() {
    return m_RTC;
}

void Processor::clearAllFlags() {
    setFlag((uint8_t) FLAG_NONE);
}

void Processor::toggleZeroFlagFromResult(uint8_t result) {
    if (result == 0)
        toggleFlag((uint8_t) FLAG_ZERO);
}

void Processor::setFlag(uint8_t flag) {
    m_AF.setLow(flag);
}

void Processor::flipFlag(uint8_t flag) {
    m_AF.setLow(m_AF.getLow() ^ flag);
}

void Processor::toggleFlag(uint8_t flag) {
    m_AF.setLow(m_AF.getLow() | flag);
}

void Processor::untoggleFlag(uint8_t flag) {
    m_AF.setLow(m_AF.getLow() & (~flag));
}

bool Processor::isSetFlag(uint8_t flag) {
    return (m_AF.getLow() & flag) != 0;
}

void Processor::NOP() {

}

void Processor::LD_SP_NN() {
    m_SP.setLow(m_memory->read(m_PC.getValue()));
    m_PC.increment();
    m_SP.setHigh(m_memory->read(m_PC.getValue()));
    m_PC.increment();
}

void Processor::XOR_A() {
    OP_XOR(m_AF.getHigh());
}

void Processor::INC_C() {
    OP_INC(m_BC.getLowRegister());
}

void Processor::LD_HL_A() {
    OP_LD(m_HL.getValue(), m_AF.getHigh());
}

void Processor::CP_N() {
    OP_CP(m_memory->read(m_PC.getValue()));
    m_PC.increment();
}

void Processor::RST_38H() {
    stackPush(&m_PC);
    m_PC.setValue(0x0038);
}

void Processor::LD_A_N() {
    OP_LD(m_AF.getHighRegister(), m_PC.getValue());
    m_PC.increment();
}

void Processor::LD_NN_SP() {
    uint8_t l = m_memory->read(m_PC.getValue());
    m_PC.increment();
    uint8_t h = m_memory->read(m_PC.getValue());
    m_PC.increment();
    uint16_t address = ((h << 8) + l);
    m_memory->write(address, m_SP.getLow());
    m_memory->write(address + 1, m_SP.getHigh());
}

void Processor::LDI_HL_A() {
    OP_LD(m_HL.getValue(), m_AF.getHigh());
    m_HL.increment();
}

void Processor::LD_HL_NN() {
    OP_LD(m_HL.getLowRegister(), m_PC.getValue());
    m_PC.increment();
    OP_LD(m_HL.getHighRegister(), m_PC.getValue());
    m_PC.increment();
}

void Processor::LDD_HL_A() {
    OP_LD(m_HL.getValue(), m_AF.getHigh());
    m_HL.decrement();
}

void Processor::INC_HL() {
    m_HL.increment();
}

void Processor::OP_INC(EightBitRegister *reg) {
    uint8_t result = reg->getValue() + 1;
    reg->setValue(result);
    isSetFlag(FLAG_CARRY) ? setFlag(FLAG_CARRY) : clearAllFlags();
    toggleZeroFlagFromResult(result);
    if ((result & 0x0F) == 0x00)
        toggleFlag(FLAG_HALF);
}


void Processor::LDH_C_A() {
    OP_LD(static_cast<uint16_t> (0xFF00 + m_BC.getLow()), m_AF.getHigh());
}

void Processor::DEC_B() {
    OP_DEC(m_BC.getHighRegister());
}

void Processor::BIT_7_H() {
    OP_BIT(m_HL.getHighRegister(), 7);
}

void Processor::LD_C_N() {
    OP_LD(m_BC.getLowRegister(), m_PC.getValue());
    m_PC.increment();
}

void Processor::JR_NZ_N() {
    if (!isSetFlag(FLAG_ZERO)) {
        m_PC.setValue(m_PC.getValue() + 1 + (static_cast<int8_t > (m_memory->read(m_PC.getValue()))));
        //m_branchTaken = true;
    } else
        m_PC.increment();
}

void Processor::ADD_HL(uint8_t number) {
    int result = m_HL.getValue() + number;
    isSetFlag(FLAG_ZERO) ? setFlag(FLAG_ZERO) : clearAllFlags();
    if (result & 0x10000) {
        toggleFlag(FLAG_CARRY);
    }
    if ((m_HL.getValue() ^ number ^ (result & 0xFFFF)) & 0x1000) {
        toggleFlag(FLAG_HALF);
    }
    m_HL.setValue(static_cast<uint16_t > (result));
}

void Processor::OP_BIT(EightBitRegister *reg, int bit) {
    if (((reg->getValue() >> bit) & 0x01) == 0) {
        toggleFlag(FLAG_ZERO);
    } else {
        untoggleFlag(FLAG_ZERO);
    }
    toggleFlag(FLAG_HALF);
    untoggleFlag(FLAG_SUB);
}

void Processor::OP_XOR(uint8_t number) {
    uint8_t result = m_AF.getHigh() ^number;
    m_AF.setHigh(result);
    clearAllFlags();
    toggleZeroFlagFromResult(result);
}


void Processor::OP_DEC(EightBitRegister *reg) {
    uint8_t result = reg->getValue() - 1;
    reg->setValue(result);
    isSetFlag(FLAG_CARRY) ? setFlag(FLAG_CARRY) : clearAllFlags();
    toggleFlag(FLAG_SUB);
    toggleZeroFlagFromResult(result);
    if ((result & 0x0F) == 0x0F) {
        toggleFlag(FLAG_HALF);
    }
}

void Processor::OP_CP(uint8_t number) {
    setFlag(FLAG_SUB);
    if (m_AF.getHigh() < number) {
        toggleFlag(FLAG_CARRY);
    }
    if (m_AF.getHigh() == number) {
        toggleFlag(FLAG_ZERO);
    }
    if (((m_AF.getHigh() - number) & 0xF) > (m_AF.getHigh() & 0xF)) {
        toggleFlag(FLAG_HALF);
    }
}

void Processor::OP_LD(uint16_t address, uint8_t reg) {
    m_memory->write(address, reg);
}

void Processor::OP_LD(EightBitRegister *reg, uint16_t address) {
    reg->setValue(m_memory->read(address));
}

void Processor::stackPush(SixteenBitRegister *reg) {
    m_SP.decrement();
    m_memory->write(m_SP.getValue(), reg->getHigh());
    m_SP.decrement();
    m_memory->write(m_SP.getValue(), reg->getLow());
}

void Processor::stackPop(SixteenBitRegister *reg) {
    reg->setLow(m_memory->read(m_SP.getValue()));
    m_SP.increment();
    reg->setHigh(m_memory->read(m_SP.getValue()));
    m_SP.increment();
}