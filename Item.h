#pragma once

using namespace std;

class Item {
public:
    Item() {
        name = " ";
    }

    Item(string name) {
        this->name = name;
    }

    Item(string name, string description) {
        this->name = name;
        this->description = description;
    }

    //virtual void foo() = 0;

    string name = " ";

    string description = " ";
};

struct Consumable : public Item {
    Consumable(int positiveEffect, int negativeEffect, string name, string effecting) : Item(name){
        this->positiveEffect = positiveEffect;
        this->negativeEffect = negativeEffect;

        this->effecting = effecting;
    }

    int positiveEffect;
    int negativeEffect;

    string effecting;
};

