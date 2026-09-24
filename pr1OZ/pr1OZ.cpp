#include <iostream>
#include <Windows.h>
using namespace std;
//інтерфейс
class IWeaponBehavior {
public:
    virtual ~IWeaponBehavior() = default;
    virtual void UseWeapon() const = 0;
};
// різна поведінка всьої зброї
class AxeBehavior : public IWeaponBehavior {
public:
    void UseWeapon() const override {
        cout << "рубає сокирою!\n";
    }
};
class BowBehavior : public IWeaponBehavior {
public:
    void UseWeapon() const override {
        cout << "стріляє з лука!\n";
    }
};
class SwordBehavior : public IWeaponBehavior {
public:
    void UseWeapon() const override {
        cout << "атакує мечем!\n";
    }
};
//клас персонажа буде батьківським для персів
class Character {
protected:
    IWeaponBehavior* weapon;
public:
    Character() : weapon(nullptr) {}
    virtual ~Character() {
        delete weapon;
    }
    void SetWeapon(IWeaponBehavior* newWeapon) {
        if (weapon) {
            delete weapon;
        }
        weapon = newWeapon;
    }
    virtual void Fight() const {
        if (weapon) {
            weapon->UseWeapon();
        }
        else {
            cout << "Немає зброї в руках!\n";
        }
    }
};
// створення похідних класів персів
class Knight : public Character {
public:
    Knight() {
        weapon = new SwordBehavior();
    }
    void Fight() const override {
        cout << "Лицар: ";
        Character::Fight();
    }
};
class King : public Character {
public:
    King() {
        weapon = new BowBehavior();
    }
    void Fight() const override {
        cout << "Король: ";
        Character::Fight();
    }
};
class Troll : public Character {
public:
    Troll() {
        weapon = new AxeBehavior();
    }

    void Fight() const override {
        cout << "Троль: ";
        Character::Fight();
    }
};
int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Character* knight = new Knight();
    knight->Fight();
    cout << "\n--- Лицар змінює зброю на лук ---\n";
    knight->SetWeapon(new BowBehavior());
    knight->Fight();
    cout << "\n--- Створення інших персонажів ---\n";
    Character* troll = new Troll();
    troll->Fight();
    delete knight;
    delete troll; 
    return 0;
}