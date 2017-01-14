//
// Created by gmardon on 13/01/17.
//

#ifndef GAMETEK_GAMETEK_H
#define GAMETEK_GAMETEK_H


#include "cartridge/Cartridge.hh"
#include "memory/Memory.hh"
#include "processor/Processor.hh"

class Gametek {
public:
    Gametek();

    bool loadROM(const string file_path);
    bool addMemoryHandlers();
protected:
    Cartridge *m_cartridge;
    Memory *m_memory;
    Processor *m_processor;
    int m_RTCUpdateCount;
    bool m_halt;
    void run();
};


#endif //GAMETEK_GAMETEK_H
