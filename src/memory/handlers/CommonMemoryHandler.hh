//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_COMMONMEMORYHANDLER_HH
#define GAMETEK_COMMONMEMORYHANDLER_HH


#include <cstdint>
#include "../MemoryHandler.hh"

class CommonMemoryHandler : public MemoryHandler {
public:
    CommonMemoryHandler();
    uint8_t performRead(uint16_t address);
    void performWrite(uint16_t address, uint8_t value);
};


#endif //GAMETEK_COMMONMEMORYHANDLER_HH
