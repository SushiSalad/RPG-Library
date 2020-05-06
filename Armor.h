#pragma once
#include "Item.h"

using namespace std;

class Armor : public Item {
public:
    Armor() {

    }
    Armor(string name, int m_armor, int p_armor) : Item(name) {
        this->m_armor = m_armor;
        this->p_armor = p_armor;
    }

    int m_armor = 0;
    int p_armor = 0;
};