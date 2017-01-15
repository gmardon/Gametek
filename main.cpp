#include <iostream>
#include "src/Gametek.hh"

int main() {
    Gametek *gametek = new Gametek();
    gametek->loadROM("/home/gmardon/delivery/gametek/resources/pokemon-rouge.gb");
    return 0;
}