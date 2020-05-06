#pragma once
#include <string>
#include "Item.h"

using namespace std;

class Weapon : public Item {
public:
    Weapon() {

    }

    Weapon(string name, int damage, bool physical, bool magic, int minStrength, int minAttunement) : Item(name) {
        this->damage = damage;
        this->physical = physical;
        this->magic = magic;
        this->minStrength = minStrength;
        this->minAttunement = minAttunement;
    }

    int damage = 0;
    bool magic;
    bool physical;
    int minStrength = 0;
    int minAttunement = 0;
};