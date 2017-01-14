//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_ROMMEMORYHANDLER_HH
#define GAMETEK_ROMMEMORYHANDLER_HH


#include "../MemoryHandler.hh"
#include "../../cartridge/Cartridge.hh"
#include "../Memory.hh"

class ROMMemoryHandler : public MemoryHandler {
public:
    ROMMemoryHandler(Cartridge *cartridge, Memory *memory);
    uint8_t performRead(uint16_t address);
    void performWrite(uint16_t address, uint8_t value);
private:
    Cartridge* m_cartridge;
    Memory* m_memory;
};


#endif //GAMETEK_ROMMEMORYHANDLER_HH
