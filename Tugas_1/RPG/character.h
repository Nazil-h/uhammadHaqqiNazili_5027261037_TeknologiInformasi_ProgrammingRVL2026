#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "inventory.h"
using namespace std;

class Character {
protected:
    string name, role;
    int hp, maxHp, mp, maxMp, attack, defense;
    bool isDefend;
    Inventory inventory;

public:
    Character(string n, string r, int h, int m, int atk, int def)
        : name(n), role(r), hp(h), maxHp(h), mp(m), maxMp(m),
          attack(atk), defense(def), isDefend(false) {}

    virtual ~Character() {}

    void basicAttack(Character& target) {
        int before = target.getHp();
        cout << ">> Kamu menyerang " << target.getName() << "!\n";
        target.takeDamage(attack);
        cout << ">> " << target.getName() << " terkena " << (before - target.getHp())
             << " damage! (HP: " << before << " → " << target.getHp() << ")\n";
    }

    void monsterAttack(Character& target) {
        int before = target.getHp();
        cout << ">> " << name << " menyerang kamu!\n";
        target.takeDamageRaw(attack);
        cout << ">> Kamu terkena " << (before - target.getHp())
             << " damage! (HP: " << before << " → " << target.getHp() << ")\n";
    }

    void takeDamage(int dmg) {
        dmg = max(1, dmg - defense);
        if (isDefend) dmg /= 2;
        hp = max(0, hp - dmg);
    }

    void takeDamageRaw(int dmg) {
        if (isDefend) dmg /= 2;
        hp = max(0, hp - dmg);
    }

    void defend() {
        isDefend = true;
        restoreMana(15);
    }

    void resetDefend() { isDefend = false; }

    void heal(int amount) {
        int before = hp;
        hp = min(maxHp, hp + amount);
        cout << ">> HP pulih +" << amount
             << " (HP: " << before << " → " << hp << ")";
        if (hp == maxHp) cout << "  ← kapasitas Hp sudah max";
        cout << "\n";
    }

    void restoreMana(int amount) {
        mp = min(maxMp, mp + amount);
    }

    bool isAlive() const        { return hp > 0; }
    string getName() const      { return name; }
    string getRole() const      { return role; }
    int getHp() const           { return hp; }
    int getMaxHp() const        { return maxHp; }
    int getMp() const           { return mp; }
    int getMaxMp() const        { return maxMp; }
    int getAttack() const       { return attack; }
    int getDefense() const      { return defense; }
    bool getIsDefend() const    { return isDefend; }
    Inventory& getInventory()   { return inventory; }

    virtual bool useSkill(Character& target) = 0;
    virtual string getSkillName()     const = 0;
    virtual string getSkillMenuText() const = 0;
};

class Warrior : public Character {
    static int SKILL_COST = 20;
    static int BASE_ATK   = 25;

public:
    Warrior(string n) : Character(n, "Warrior", 150, 50, BASE_ATK, 15) {}

    bool useSkill(Character& target) override {
        if (mp < SKILL_COST) {
            cout << ">> MP tidak cukup untuk Gebukan +1000 aura! (Butuh " << SKILL_COST << " MP)\n";
            return false;
        }
        int before = target.getHp();
        mp -= SKILL_COST;
        target.takeDamage((int)(attack * 1.5));
        cout << ">> Kamu menggunakan Gebukan +1000 aura!\n";
        cout << ">> " << target.getName() << " terkena " << (before - target.getHp())
             << " damage! (HP: " << before << " → " << target.getHp() << ")\n";
        if (!target.isAlive())
            cout << ">> " << target.getName() << " telah dikalahkan! 🎉\n";
        return true;
    }

    string getSkillName() const override { return "Gebukan +1000 aura"; }
    string getSkillMenuText() const override {
        return "Gebukan +1000 aura  (DMG: " + to_string((int)(BASE_ATK * 1.5)) + ", MP: -" + to_string(SKILL_COST) + ")";
    }
};

class Mage : public Character {
    static const int SKILL_COST = 30;
    static const int BASE_ATK   = 45;

public:
    Mage(string n) : Character(n, "Mage", 90, 100, BASE_ATK, 8) {}

    bool useSkill(Character& target) override {
        if (mp < SKILL_COST) {
            cout << ">> MP tidak cukup untuk Kutukan UU ITE! (Butuh " << SKILL_COST << " MP)\n";
            return false;
        }
        int dmg = max(1, attack * 2 - target.getDefense());
        int before = target.getHp();
        mp -= SKILL_COST;
        target.takeDamageRaw(dmg);
        cout << ">> Kamu menggunakan Kutukan UU ITE!\n";
        cout << ">> " << target.getName() << " terkena " << (before - target.getHp())
             << " damage! (HP: " << before << " \u2192 " << target.getHp() << ")\n";
        if (!target.isAlive())
            cout << ">> " << target.getName() << " telah dikalahkan! 🎉\n";
        return true;
    }

    string getSkillName() const override { return "Kutukan UU ITE"; }
    string getSkillMenuText() const override {
        return "Kutukan UU ITE   (DMG: " + to_string(BASE_ATK * 2) + ", MP: -" + to_string(SKILL_COST) + ")";
    }
};

class Archer : public Character {
    static constexpr int SKILL_COST = 25;
    static constexpr int BASE_ATK   = 35;

public:
    Archer(string n) : Character(n, "Archer", 110, 70, BASE_ATK, 10) {}

    bool useSkill(Character& target) override {
        if (mp < SKILL_COST) {
            cout << ">> MP tidak cukup untuk Roasting Jarak Jauh! (Butuh " << SKILL_COST << " MP)\n";
            return false;
        }
        int before = target.getHp();
        mp -= SKILL_COST;
        target.takeDamage(attack);
        target.takeDamage(attack);
        cout << ">> Kamu menggunakan Roasting Jarak Jauh! (2 tembakan)\n";
        cout << ">> " << target.getName() << " terkena " << (before - target.getHp())
             << " damage total! (HP: " << before << " \u2192 " << target.getHp() << ")\n";
        if (!target.isAlive())
            cout << ">> " << target.getName() << " telah dikalahkan! 🎉\n";
        return true;
    }

    string getSkillName() const override { return "Roasting Jarak Jauh"; }
    string getSkillMenuText() const override {
        return "Roasting Jarak Jauh   (DMG: " + to_string(BASE_ATK) + "x2, MP: -" + to_string(SKILL_COST) + ")";
    }
};

class Monster : public Character {
    int expReward;

public:
    Monster(string n, string r, int h, int m, int atk, int exp = 30)
        : Character(n, r, h, m, atk, 0), expReward(exp) {}

    int getExpReward() const { return expReward; }

    bool useSkill(Character& target) override {
        if (mp < 20) { monsterAttack(target); return false; }
        int before = target.getHp();
        mp -= 20;
        target.takeDamageRaw((int)(attack * 1.8));
        cout << ">> " << name << " menggunakan Power Strike!\n";
        cout << ">> Kamu terkena " << (before - target.getHp())
             << " damage! (HP: " << before << " → " << target.getHp() << ")\n";
        return true;
    }

    string getSkillName()     const override { return "Power Strike"; }
    string getSkillMenuText() const override { return "Power Strike (20 MP)"; }

    void performTurn(Character& player) {
        resetDefend();
        int roll = rand() % 100;

        if (roll < 35 && mp >= 20) {
            useSkill(player);
        } else if (roll < 50 && hp < maxHp / 2) {
            defend();
            cout << ">> " << name << " mengambil posisi bertahan!\n";
        } else {
            monsterAttack(player);
        }
    }
};
