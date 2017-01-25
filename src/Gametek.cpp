
//
// Created by gmardon on 13/01/17.
//

#include <zconf.h>
#include <src/tools/hexview/HexViewWindow.h>
#include <QtWidgets/QApplication>
#include "Gametek.hh"
#include "memory/handlers/ROMMemoryHandler.hh"
#include "memory/handlers/IOMemoryHandler.hh"
#include "memory/handlers/CommonMemoryHandler.hh"

Gametek::Gametek() {
    m_state = BOOT;
    m_memory = new Memory(this);
    m_cartridge = new Cartridge(this);
    m_processor = new Processor(this);
    m_memory->init();
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
            printf("NoMBC\n");
            m_memory->setBaseHandler(new ROMMemoryHandler(m_cartridge, m_memory));
            break;
        case Cartridge::MBC1:
            printf("MBC1\n");
            //m_memory->setBaseHandler(m_pMBC1MemoryRule);
            break;
        case Cartridge::MBC1Multi:
            printf("MBC1Multi\n");
            //m_memory->setBaseHandler(m_pMultiMBC1MemoryRule);
            break;
        case Cartridge::MBC2:
            printf("MBC2\n");
            //m_memory->setBaseHandler(m_pMBC2MemoryRule);
            break;
        case Cartridge::MBC3:
            printf("MBC3\n");
            //m_memory->setBaseHandler(m_pMBC3MemoryRule);
            break;
        case Cartridge::MBC5:
            printf("MBC5\n");
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
    char **av = new char *[2];
    av[0] = strdup("./gametek");
    av[1] = NULL;
    QApplication app(*(new int(1)), av);

    HexViewWindow wgt;
    wgt.show();

    uint8_t cycles;

    if (m_cartridge->isROMReaded()) {
        m_RTCUpdateCount = 0;
        while (Gametek::getState() != HALT) {
            app.processEvents();
            cycles = m_processor->tick();
            wgt.setData((char*) m_memory->getRAM(), 65536);

            m_RTCUpdateCount++;
            if (m_RTCUpdateCount == 50) {
                m_RTCUpdateCount = 0;
                m_processor->updateRealtimeClock();
            }
            // simulate ticks \o/
            usleep(100000);
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