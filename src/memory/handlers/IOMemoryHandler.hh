//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_IOHANDLER_HH
#define GAMETEK_IOHANDLER_HH


#include "../MemoryHandler.hh"

class IOMemoryHandler : public MemoryHandler {
public:
    IOMemoryHandler();
    uint8_t performRead(uint16_t address);
    void performWrite(uint16_t address, uint8_t value);
};


#endif //GAMETEK_IOHANDLER_HH
