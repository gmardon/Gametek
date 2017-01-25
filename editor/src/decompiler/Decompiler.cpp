//
// Created by gmardon on 25/01/17.
//

#include <cstring>
#include "Decompiler.h"
#include "../../../src/cartridge/Cartridge.hh"
#include <sstream>

Decompiler::Decompiler() {
    m_operators = (Operator *) malloc(256 * (sizeof(Operator_t)));
    memset(m_operators, 0, 256 * (sizeof(Operator_t)));

    m_operators[0x00] = (Operator) {0x00, "NOP"};
    m_operators[0x05] = (Operator) {0x05, "DEC B"};
    m_operators[0x06] = (Operator) {0x06, "LD B,n"};
    m_operators[0x08] = (Operator) {0x08, "LD (nn),SP"};
    m_operators[0x0C] = (Operator) {0x0C, "INC C"};
    m_operators[0x0E] = (Operator) {0x0E, "LD C,n"};
    m_operators[0x11] = (Operator) {0x11, "LD DE,nn"};
    m_operators[0x17] = (Operator) {0x17, "RL A"};
    m_operators[0x1A] = (Operator) {0x1A, "LD A,(DE)"};
    m_operators[0x20] = (Operator) {0x20, "JR NZ,n"};
    m_operators[0x21] = (Operator) {0x21, "LD HL,nn"};
    m_operators[0x22] = (Operator) {0x22, "LDI (HL),A"};
    m_operators[0x23] = (Operator) {0x23, "INC HL"};
    m_operators[0x31] = (Operator) {0x31, "LD SP,nn"};
    m_operators[0x32] = (Operator) {0x32, "LDD (HL),A"};
    m_operators[0x3E] = (Operator) {0x3E, "LD A,n"};
    m_operators[0x4F] = (Operator) {0x4F, "LD C,L"};
    m_operators[0x77] = (Operator) {0x77, "LD (HL),A"};
    m_operators[0xAF] = (Operator) {0xAF, "XOR A"};
    m_operators[0xC1] = (Operator) {0xC1, "POP BC"};
    m_operators[0xC5] = (Operator) {0xC5, "PUSH BC"};
    m_operators[0xCD] = (Operator) {0xCD, "CALL nn"};
    m_operators[0xE0] = (Operator) {0xE0, "LDH (n),A"};
    m_operators[0xE2] = (Operator) {0xE2, "LDH (C),A"};
    m_operators[0xFE] = (Operator) {0xFE, "CP N"};
    m_operators[0xFF] = (Operator) {0xFF, "RST 38H"};
}

std::string Decompiler::decompile(const std::string file) {
    std::stringstream content;
    Cartridge *cartridge = new Cartridge();
    cartridge->readFromFile(file);

    uint8_t *buffer = cartridge->getROM();
    int index = 0x100;
    while (index < 0x200) {
        if (m_operators[buffer[index]].name == "") {
            content << m_operators[buffer[index]].name << std::endl;
        }
        index++;
    }
    return content.str();
}

