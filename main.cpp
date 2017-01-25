#include <iostream>
#include <QApplication>
#include <QIcon>
#include "src/Gametek.hh"
#include "src/tools/hexview/HexViewWindow.h"

int main(int argc, char *argv[]) {
    Gametek *gametek = new Gametek();
    gametek->loadROM("/home/gmardon/delivery/gametek/resources/pokemon-rouge.gb");
    return 0;
}