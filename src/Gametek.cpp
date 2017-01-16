
//
// Created by gmardon on 13/01/17.
//

#include "Gametek.hh"
#include "memory/handlers/ROMMemoryHandler.hh"
#include "memory/handlers/IOMemoryHandler.hh"
#include "memory/handlers/CommonMemoryHandler.hh"

Gametek::Gametek() {
    m_memory = new Memory(this);
    m_cartridge = new Cartridge(this);
    m_processor = new Processor(this);
    m_state = BOOT;
}

bool Gametek::loadROM(const string file_path) {
    bool loaded = m_cartridge->readFromFile(file_path);
    if (loaded) {
        m_memory->fillFromCartridge(m_cartridge);
        addMemoryHandlers();
        run();
    } else
        return false;
    return false;
}

bool Gametek::addMemoryHandlers() {
    m_memory->setIOHandler(new IOMemoryHandler());
    m_memory->setCommonHandler(new CommonMemoryHandler());

    Cartridge::CartridgeType type = m_cartridge->getType();

    bool notSupported = false;

    switch (type) {
        case Cartridge::NoMBC:
            printf("NoMBC");
            m_memory->setBaseHandler(new ROMMemoryHandler(m_cartridge, m_memory));
            break;
        case Cartridge::MBC1:
            printf("MBC1");
            //m_memory->setBaseHandler(m_pMBC1MemoryRule);
            break;
        case Cartridge::MBC1Multi:
            printf("MBC1Multi");
            //m_memory->setBaseHandler(m_pMultiMBC1MemoryRule);
            break;
        case Cartridge::MBC2:
            printf("MBC2");
            //m_memory->setBaseHandler(m_pMBC2MemoryRule);
            break;
        case Cartridge::MBC3:
            printf("MBC3");
            //m_memory->setBaseHandler(m_pMBC3MemoryRule);
            break;
        case Cartridge::MBC5:
            printf("MBC5");
            //m_memory->setBaseHandler(m_pMBC5MemoryRule);
            break;
        case Cartridge::NotSupported:
            notSupported = true;
            break;
        default:
            notSupported = true;
    }
    return !notSupported;
}

void Gametek::run() {
    uint8_t cycles;
    if (m_cartridge->isROMReaded()) {
        m_RTCUpdateCount = 0;
        while (Gametek::getState() != HALT) {
            cycles = m_processor->tick();

            m_RTCUpdateCount++;
            if (m_RTCUpdateCount == 50) {
                m_RTCUpdateCount = 0;
                m_processor->updateRealtimeClock();
            }
        }
    }
}

void Gametek::setState(GameState value) {
    this->m_state = value;
}

GameState Gametek::getState() {
    return (this->m_state);
}

Processor *Gametek::getProcessor() {
    return (this->m_processor);
}

Cartridge *Gametek::getCartridge() {
    return (this->m_cartridge);
}

Memory *Gametek::getMemory() {
    return (this->m_memory);
}