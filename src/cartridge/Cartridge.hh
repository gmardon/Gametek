//
// Created by gmardon on 12/01/17.
//
#ifndef GAMETEK_CARTRIDGE_H
#define GAMETEK_CARTRIDGE_H

#include <cstdint>
#include <string>
#include "../Gametek.hh"

#define GAMEBOY_WIDTH 160
#define GAMEBOY_HEIGHT 144

using namespace std;

class Gametek;

class Cartridge {
public:
    enum CartridgeType
    {
        NoMBC,
        MBC1,
        MBC2,
        MBC3,
        MBC5,
        MBC1Multi,
        NotSupported
    };

    Cartridge(Gametek *gametek);
    ~Cartridge();

    bool readFromFile(string const file_path);
    bool readFromBuffer(const uint8_t* buffer, int size);
    bool updateMetadata();
    bool isROMReaded() const;
    const string &getName() const;
    int getROMSize() const;
    int getRAMSize() const;
    void setCartridgeType(int type);
    uint8_t *getROM() const;
    CartridgeType getType() const;
    bool isGBC() const;

private:
    uint8_t* m_data;
    bool m_readed;
    size_t m_totalSize;
    string m_name;
    bool m_GBC;
    bool m_SGB;
    int m_version;
    CartridgeType m_type;
    int m_ROMSize;
    int m_RAMSize;
    bool m_validROM;
};


#endif //GAMETEK_CARTRIDGE_H
