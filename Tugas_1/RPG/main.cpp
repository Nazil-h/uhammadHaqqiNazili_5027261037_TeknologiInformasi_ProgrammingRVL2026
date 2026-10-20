#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "character.h"
#include "inventory.h"
#include "game.h"
using namespace std;

int main() {
    srand(time(0));

    cout << "========================================\n";
    cout << "           WHEN YH JAGO CPP\n";
    cout << "========================================\n\n";

    cout << "Pilih Karakter:\n";
    cout << "1. Warrior  (HP: 150, ATK: 25, MP: 50,  DEF: 15)\n";
    cout << "2. Mage     (HP: 90,  ATK: 40, MP: 100, DEF: 8)\n";
    cout << "3. Archer   (HP: 110, ATK: 35, MP: 60,  DEF: 10)\n\n";
    cout << "Pilihan: ";

    int pilChar;
    cin >> pilChar;
    if (pilChar < 1 || pilChar > 3) pilChar = 3;
    cin.ignore();

    string playerName;
    cout << "\nMasukkan nama hero: ";
    getline(cin, playerName);

    Character* player = nullptr;
    switch (pilChar) {
        case 1: player = new Warrior(playerName); break;
        case 2: player = new Mage(playerName);    break;
        default: player = new Archer(playerName); break;
    }

    cout << "\n[" << playerName << " si " << player->getRole()
         << " telah memasuki dungeon!]\n";

    vector<Monster*> waves = {
        new Monster("Bahlil si Goblin",  "Goblin", 60,  20, 14, 10),
        new Monster("Fufufafa        ",  "Orc",    120, 30, 30, 20),
        new Monster("Pria Oslo       ",  "Boss",   140, 45, 40, 30),
    };

    int totalExp = 0;
    bool wonAllWaves = true;

    for (int i = 0; i < (int)waves.size(); i++) {
        bool won = Game::startWave(player, waves[i], i + 1, totalExp);
        if (!won) { wonAllWaves = false; break; }

        if (i < (int)waves.size() - 1) {
            cout << "\nLanjut ke Floor " << (i + 2) << "? (y/n): ";
            char lanjut;
            cin >> lanjut;
            cin.ignore();
            if (lanjut != 'y' && lanjut != 'Y') {
                cout << "\nKamu memilih untuk mundur. Sampai jumpa!\n";
                wonAllWaves = false;
                break;
            }
        }
    }

    if (wonAllWaves) {
        cout << "\n========================================\n";
        cout << "        DUNGEON QUEST CLEARED!\n";
        cout << "========================================\n";
        cout << "Selamat, " << playerName << "! Semua floor telah dikalahkan!\n";
        cout << "Total EXP  : " << totalExp << "\n";
        cout << "HP tersisa : " << player->getHp() << " / " << player->getMaxHp() << "\n";
    }

    delete player;
    for (Monster* m : waves) delete m;

    return 0;
}
