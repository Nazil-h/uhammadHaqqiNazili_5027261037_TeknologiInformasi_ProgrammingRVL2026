# ⚔️ When YH Jago CPP — RPG

Game RPG berbasis teks (terminal) yang ditulis dalam **C++**, menampilkan sistem pertarungan turn-based dengan 3 pilihan karakter, skill unik, inventory, dan 3 gelombang musuh yang semakin kuat.

---

## 🗂️ Struktur File

```
RPG/
├── main.cpp        # Entry point — inisialisasi karakter & game loop
├── character.h     # Class Character (base), Warrior, Mage, Archer, Monster
├── inventory.h     # Class Inventory (HP Potion & Mana Potion)
└── game.h          # Class Game — logika battle, giliran, dan wave
```

---

## 🎮 Cara Main

### Kompilasi

```bash
g++ -o main main.cpp
```

### Jalankan

```bash
./main
```

---

## 🧙 Karakter

| Karakter | HP  | ATK | MP  | DEF | Skill                                        |
|----------|-----|-----|-----|-----|----------------------------------------------|
| Warrior  | 150 | 25  | 50  | 15  | **Gebukan +1000 aura** — ATK ×1.5, -20 MP   |
| Mage     | 90  | 40  | 100 | 8   | **Kutukan UU ITE** — ATK ×2 (bypass DEF), -30 MP |
| Archer   | 110 | 35  | 70  | 10  | **Roasting Jarak Jauh** — 2 tembakan ATK, -25 MP |

---

## ⚔️ Sistem Pertarungan

Setiap giliran player memilih satu aksi:

| Aksi       | Efek                                          |
|------------|-----------------------------------------------|
| Attack     | Serangan dasar (ATK - DEF musuh)              |
| Skill      | Serangan spesial kelas (butuh MP)             |
| Defend     | Damage yang diterima -50% + MP pulih +15      |
| Inventory  | Gunakan HP Potion (+60 HP) atau Mana Potion (+40 MP) |

Musuh juga bertindak otomatis tiap giliran: normal attack, Power Strike (35% chance jika MP ≥ 20), atau defend jika HP < 50%.

---

## 👾 Daftar Musuh (Wave)

| Floor | Nama              | Tipe   | HP  | ATK | EXP |
|-------|-------------------|--------|-----|-----|-----|
| 1     | Bahlil si Goblin  | Goblin | 60  | 20  | 14  |
| 2     | Fufufafa          | Orc    | 120 | 30  | 20  |
| 3     | Pria Oslo         | Boss   | 140 | 45  | 30  |

Player bisa memilih mundur (tidak lanjut ke floor berikutnya) setelah mengalahkan musuh.

---

## 🎒 Inventory

Setiap karakter mulai dengan:
- **2× Health Potion** — memulihkan +60 HP
- **2× Mana Potion** — memulihkan +40 MP

---

## 🏗️ Arsitektur Kode

```
Character (abstract base class)
├── Warrior   : useSkill() → Gebukan +1000 aura
├── Mage      : useSkill() → Kutukan UU ITE
├── Archer    : useSkill() → Roasting Jarak Jauh
└── Monster   : useSkill() → Power Strike, performTurn() untuk AI

Game (static class)
└── startWave() → mengelola loop battle per floor

Inventory
└── HP Potion & Mana Potion management
```

---

## 📋 Requirements

- Compiler C++ dengan dukungan **C++11** atau lebih baru
- Tidak ada dependency eksternal

---

## 👤 Author

> *"Hiqanz"*
