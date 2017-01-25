//
// Created by gmardon on 12/01/17.
//

#include <ios>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "Cartridge.hh"

Cartridge::Cartridge(Gametek *gametek) {
    this->m_data = NULL;
    this->m_readed = false;
}

Cartridge::~Cartridge() {
    if (this->m_data)
        delete this->m_data;
}

bool Cartridge::readFromFile(string const file_path) {
    printf("Reading %s...\n", file_path.c_str());

    ifstream file(file_path, ios::in | ios::binary | ios::ate);

    if (file.is_open()) {
        int size = static_cast<int>(file.tellg());
        char *data = new char[size];
        file.seekg(0, ios::beg);
        file.read(data, size);
        file.close();

        string fn(file_path);
        transform(fn.begin(), fn.end(), fn.begin(), (int (*)(int)) tolower);
        string extension = fn.substr(fn.find_last_of(".") + 1);

        if (extension == "zip") {
            printf("Loading from ZIP not supported:\n");
        } else {
            m_readed = readFromBuffer(reinterpret_cast<uint8_t *>(data), size);
        }

        if (m_readed)
            printf("ROM readed\n");
        else
            printf("There was a problem readed the memory for file %s...\n", file_path.c_str());
        delete data;
    } else {
        printf("Cannot open the file %s...", file_path.c_str());
        m_readed = false;
    }
    return m_readed;
}

bool Cartridge::readFromBuffer(const uint8_t *buffer, int size) {
    if (buffer != NULL) {
        m_totalSize = size;
        m_data = new uint8_t[m_totalSize];
        memcpy(m_data, buffer, m_totalSize);
        return this->updateMetadata();
    } else
        return false;
}

bool Cartridge::updateMetadata() {
    char name[12] = {0};
    name[11] = 0;

    for (int i = 0; i < 11; i++) {
        name[i] = m_data[0x0134 + i];

        if (name[i] == 0) {
            break;
        }
    }

    this->m_name = string(strdup(name));

    this->m_GBC = (m_data[0x143] == 0x80) || (m_data[0x143] == 0xC0);
    this->m_SGB = (m_data[0x146] == 0x03);
    this->m_version = (m_data[0x14C]);
    setCartridgeType(m_data[0x147]);
    this->m_ROMSize = (m_data[0x148]);
    this->m_RAMSize = (m_data[0x149]);

    printf("ROM Name %s\n", this->m_name.c_str());
    printf("ROM Version %d\n", this->m_version);
    printf("ROM Type %d\n", this->m_type);
    printf("ROM Size %dKB\n", (int) pow(4.0, (double) m_ROMSize) / 2);
    printf("RAM Size %dKB\n", (int) pow(4.0, (double) m_RAMSize) / 2);
    printf("SUPPORT GBC %d\n", this->m_GBC);
    printf("SUPPORT SGB %d\n", this->m_SGB);
    printf("GBC ONLY %d\n", m_data[0x143] == 0xC0);

    int checksum = 0;
    for (int j = 0x134; j < 0x14E; j++)
        checksum += m_data[j];

    this->m_validROM = ((checksum + 25) & 0xFF) == 0;

    if (this->m_validROM)
        printf("ROM Checksum : OK!\n");
    else
        printf("ROM Checksum : FAILED!!!\n");

    return true;
}

bool Cartridge::isROMReaded() const {
    return m_readed;
}

const string &Cartridge::getName() const {
    return m_name;
}

int Cartridge::getROMSize() const {
    return this->m_ROMSize;
}

int Cartridge::getRAMSize() const {
    return this->m_RAMSize;
}

void Cartridge::setCartridgeType(int type) {
    CartridgeType cartridgeType;
    if ((type != 0xEA) && (this->getROMSize() == 0))
        type = 0;

    switch (type) {
        case 0x00:
            // NO MBC
        case 0x08:
            // ROM
            // SRAM
        case 0x09:
            // ROM
            // SRAM
            // BATT
            cartridgeType = NoMBC;
            break;
        case 0x01:
            // MBC1
        case 0x02:
            // MBC1
            // SRAM
        case 0x03:
            // MBC1
            // SRAM
            // BATT
        case 0xEA:
            // Hack to accept 0xEA as a MBC1 (Sonic 3D Blast 5)
        case 0xFF:
            // Hack to accept HuC1 as a MBC1
            cartridgeType = MBC1;
            break;
        case 0x05:
            // MBC2
            // SRAM
        case 0x06:
            // MBC2
            // SRAM
            // BATT
            cartridgeType = MBC2;
            break;
        case 0x0F:
            // MBC3
            // TIMER
            // BATT
        case 0x10:
            // MBC3
            // TIMER
            // BATT
            // SRAM
        case 0x11:
            // MBC3
        case 0x12:
            // MBC3
            // SRAM
        case 0x13:
            // MBC3
            // BATT
            // SRAM
        case 0xFC:
            // Game Boy Camera
            cartridgeType = MBC3;
            break;
        case 0x19:
            // MBC5
        case 0x1A:
            // MBC5
            // SRAM
        case 0x1B:
            // MBC5
            // BATT
            // SRAM
        case 0x1C:
            // RUMBLE
        case 0x1D:
            // RUMBLE
            // SRAM
        case 0x1E:
            // RUMBLE
            // BATT
            // SRAM
            cartridgeType = MBC5;
            break;
        case 0x0B:
            // MMMO1
        case 0x0C:
            // MMM01
            // SRAM
        case 0x0D:
            // MMM01
            // SRAM
            // BATT
        case 0x15:
            // MBC4
        case 0x16:
            // MBC4
            // SRAM
        case 0x17:
            // MBC4
            // SRAM
            // BATT
        case 0x22:
            // MBC7
            // BATT
            // SRAM
        case 0x55:
            // GG
        case 0x56:
            // GS3
        case 0xFD:
            // TAMA 5
        case 0xFE:
            // HuC3
            cartridgeType = NotSupported;
            printf("** This cartridge is not supported. Type: %d\n **", type);
            break;
        default:
            cartridgeType = NotSupported;
            printf("** Unknown cartridge type: %d\n **", type);
    }

    switch (type) {
        case 0x03:
        case 0x06:
        case 0x09:
        case 0x0D:
        case 0x0F:
        case 0x10:
        case 0x13:
        case 0x17:
        case 0x1B:
        case 0x1E:
        case 0x22:
        case 0xFD:
        case 0xFF:
            // m_bBattery = true;
            break;
            //default:
            // m_bBattery = false;
    }

    switch (type) {
        case 0x0F:
        case 0x10:
            // m_bRTCPresent = true;
            break;
            //default:
            // m_bRTCPresent = false;
    }

    switch (type) {
        case 0x1C:
        case 0x1D:
        case 0x1E:
            // m_bRumblePresent = true;
            break;
            //default:
            // m_bRumblePresent = false;
    }
    this->m_type = cartridgeType;
}

uint8_t *Cartridge::getROM() const {
    return (this->m_data);
}

bool Cartridge::isGBC() const {
    return (this->m_GBC);
}

Cartridge::CartridgeType Cartridge::getType() const {
    return m_type;
}
