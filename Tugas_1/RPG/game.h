#pragma once
#include <string>
#include "character.h"
using namespace std;

class Game {
    static void displayFloorHeader(int floor) {
        cout << "\n========================================\n";
        cout << "              DUNGEON FLOOR " << floor << "\n";
        cout << "========================================\n";
    }

    static void displayEnemy(Monster* enemy) {
        cout << "\n⚔️  Musuh muncul: " << enemy->getRole() << "\n";
        cout << "    HP: " << enemy->getHp() << " | ATK: " << enemy->getAttack() << "\n";
    }

    static void displayPlayerStatus(Character* player) {
        cout << "\n--- GILIRAN KAMU ---\n";
        cout << "HP kamu: " << player->getHp() << " | MP: " << player->getMp() << "\n";
    }

    static void displayActionMenu(Character* player) {
        cout << "\nAksi:\n";
        cout << "1. Attack       (DMG: " << player->getAttack() << ")\n";
        cout << "2. " << player->getSkillMenuText() << "\n";
        cout << "3. Defend        (DMG: -50%, MP: +15)\n";
        cout << "4. Inventory\n";
        cout << "\nPilihan: ";
    }

    static bool handleInventory(Character* player) {
        Inventory& inv = player->getInventory();
        cout << "Inventory:\n";
        inv.showInv();
        cout << "Pilih item (1/2), 0 untuk batal: ";

        int choice;
        cin >> choice;
        cout << "\n";

        if (choice == 1) {
            if (!inv.useHpPotion()) { cout << ">> HP Potion habis!\n"; return false; }
            cout << ">> Kamu menggunakan Health Potion!\n";
            player->heal(60);
            return true;
        }
        if (choice == 2) {
            if (!inv.useManaPotion()) { cout << ">> Mana Potion habis!\n"; return false; }
            int before = player->getMp();
            player->restoreMana(40);
            cout << ">> Kamu menggunakan Mana Potion!\n";
            cout << ">> MP pulih +40 (MP: " << before << " \u2192 " << player->getMp() << ")\n";
            return true;
        }

        cout << ">> Dibatalkan.\n";
        return false;
    }

    static void handlePlayerTurn(Character* player, Monster* enemy) {
        player->resetDefend();

        bool actionTaken = false;
        while (!actionTaken) {
            displayPlayerStatus(player);
            displayActionMenu(player);

            int choice;
            cin >> choice;
            cin.ignore();

            if (cin.fail()) {
                cin.clear();
                cout << "Input tidak valid.\n";
                continue;
            }
            cout << "\n";

            switch (choice) {
                case 1:
                    player->basicAttack(*enemy);
                    if (!enemy->isAlive())
                        cout << ">> " << enemy->getName() << " telah dikalahkan! 🎉\n";
                    actionTaken = true;
                    break;

                case 2:
                    actionTaken = player->useSkill(*enemy);
                    break;

                case 3:
                    player->defend();
                    cout << ">> Kamu mengambil posisi bertahan! (Damage -50% & MP +15 giliran ini)\n";
                    actionTaken = true;
                    break;

                case 4:
                    actionTaken = handleInventory(player);
                    break;

                default:
                    cout << "Pilihan tidak valid. Coba lagi.\n";
                    break;
            }
        }
    }

public:

    static bool startWave(Character* player, Monster* enemy, int waveNumber, int& totalExp) {
        displayFloorHeader(waveNumber);
        displayEnemy(enemy);

        while (player->isAlive() && enemy->isAlive()) {
            handlePlayerTurn(player, enemy);

            if (!enemy->isAlive()) {
                int exp = enemy->getExpReward();
                totalExp += exp;
                cout << ">> +" << exp << " EXP\n";
                cout << "\n========================================\n";
                cout << "           FLOOR " << waveNumber << " CLEARED! \n";
                cout << "========================================\n";
                cout << "Total EXP  : " << totalExp << "\n";
                cout << "HP tersisa : " << player->getHp() << " / " << player->getMaxHp() << "\n";
                return true;
            }

            cout << "\n--- GILIRAN MUSUH ---\n";
            enemy->performTurn(*player);

            if (!player->isAlive()) {
                cout << "\n========================================\n";
                cout << "              GAME OVER\n";
                cout << "========================================\n";
                cout << player->getRole() << " " << player->getName()
                     << " telah gugur di Floor " << waveNumber << "...\n";
                return false;
            }
        }

        return player->isAlive();
    }
};
