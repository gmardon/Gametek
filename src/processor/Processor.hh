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
    Operator *m_operators;

protected:
    void clearAllFlags();
    void toggleZeroFlagFromResult(uint8_t result);
    void setFlag(uint8_t flag);
    void flipFlag(uint8_t flag);
    void toggleFlag(uint8_t flag);
    void untoggleFlag(uint8_t flag);
    bool isSetFlag(uint8_t flag);
    void ADD_HL(uint8_t number);
    void OP_DEC(EightBitRegister* reg);
    void OP_CP(uint8_t number);
    void OP_LD(uint16_t address, uint8_t reg);
    void stackPush(SixteenBitRegister* reg);
    void stackPop(SixteenBitRegister* reg);
    // OPERATOR //
    void NOP();
    void CP_N();
    void LD_SP_NN();
    void RST_38H();
    void LD_NN_SP();
    void LD_HLI_A();
    void INC_HL();
    void DEC_B();


};

#endif //GAMETEK_PROCESSOR_HH
