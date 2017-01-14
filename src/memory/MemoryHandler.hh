//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_MEMORYHANDLER_HH
#define GAMETEK_MEMORYHANDLER_HH
#include <ios>

class MemoryHandler {
public:
    //MemoryHandler();
    //~MemoryHandler();

    virtual uint8_t performRead(uint16_t address) = 0;
    virtual void performWrite(uint16_t address, uint8_t value) = 0;
    //virtual void saveRam(std::ofstream &file);
    //virtual bool loadRam(std::ifstream &file, s32 fileSize);
};


#endif //GAMETEK_MEMORYHANDLER_HH
