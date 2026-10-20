#pragma once
#include <iostream>
using namespace std;

class Inventory {
    int hpPotions;
    int manaPotions;

public:
    Inventory() : hpPotions(2), manaPotions(2) {}

    bool useHpPotion() {
        if (hpPotions <= 0) return false;
        hpPotions--;
        return true;
    }

    bool useManaPotion() {
        if (manaPotions <= 0) return false;
        manaPotions--;
        return true;
    }

    void showInv() const {
        cout << "  1. Health Potion (+60 HP)   [Tersedia: " << hpPotions   << "]\n";
        cout << "  2. Mana Potion  (+40 MP)    [Tersedia: " << manaPotions << "]\n";
    }
};
