//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_PROCESSOR_HH
#define GAMETEK_PROCESSOR_HH

#include <stdint-gcc.h>
#include <vector>
#include "../memory/Memory.hh"
#include "../utils/SixteenBitRegister.hh"
#include "../Gametek.hh"
#include "Operator.hh"

class Gametek;
class Memory;
class Cartridge;

class Processor {
public:
    Processor(Gametek *gametek);

    void updateRealtimeClock();

    time_t getRealtimeClock();

    uint8_t tick();

    const SixteenBitRegister &getPC() const;
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

private:
    Operator *m_operators;
    Operator *m_operatorsCB;

protected:
    void clearAllFlags();
    void toggleZeroFlagFromResult(uint8_t result);
    void setFlag(uint8_t flag);
    void flipFlag(uint8_t flag);
    void toggleFlag(uint8_t flag);
    void untoggleFlag(uint8_t flag);
    bool isSetFlag(uint8_t flag);
    void ADD_HL(uint8_t number);
    void printStatus();
    void OP_XOR(uint8_t number);
    void OP_DEC(EightBitRegister* reg);
    void OP_CP(uint8_t number);
    void OP_LD(uint16_t address, uint8_t reg);
    void OP_RL(EightBitRegister* reg, bool isRegisterA = false);
    void OP_LD(EightBitRegister* reg, uint16_t address);
    void OP_INC(EightBitRegister* reg);
    void OP_BIT(EightBitRegister* reg, int bit);
    void stackPush(SixteenBitRegister* reg);
    void stackPop(SixteenBitRegister* reg);

    // OPERATORS //
    void NOP();
    void CP_N();
    void XOR_A();
    void LD_SP_NN();
    void RST_38H();
    void LD_NN_SP();
    void LDI_HL_A();
    void LD_A_N();
    void LDH_C_A();
    void INC_C();
    void INC_HL();
    void DEC_B();
    void JR_NZ_N();
    void LD_HL_NN();
    void LDD_HL_A();
    void BIT_7_H();
    void LD_C_N();
    void LD_HL_A();
    void LDH_N_A();
    void LD_DE_NN();
    void LD_A_DE();
    void CALL_NN();
    void LD_C_L();
    void LD_B_N();
    void PUSH_BC();
    void POP_BC();
    void RL_C();
    void RL_A();
};

#endif //GAMETEK_PROCESSOR_HH
