//
// Created by gmardon on 13/01/17.
//

#include "ROMMemoryHandler.hh"
#include "../../cartridge/Cartridge.hh"
#include "../Memory.hh"

ROMMemoryHandler::ROMMemoryHandler(Cartridge *cartridge, Memory *memory)
{

}

uint8_t ROMMemoryHandler::performRead(uint16_t address)
{
    if (address >= 0xA000 && address < 0xC000)
    {
        if (m_cartridge->getRAMSize() > 0)
            return m_memory->get(address);
        else
        {
            printf("** Attempting to read from RAM without ram in cart %X **", address);
            return 0xFF;
        }
    }
    else
        return m_memory->get(address);
}

void ROMMemoryHandler::performWrite(uint16_t address, uint8_t value)
{

}
