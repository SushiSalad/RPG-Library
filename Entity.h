#ifndef __ENTITY_H
#define __ENTITY_H

//#include "Enemy.h"
//#include "Player.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

//using namespace std;

//This class contains everything to do with an entity like the player and enemies. Stores and modifies all health, stamina, etc. data.
//The inventory is split between each type of item for better organization and also because polymorphism wasn't working well with vectors.
//There was an issue where if we tried to store say an item of type "Weapon," in an inventory (vector) of type "Item" it would just 
//tell us we couldn't do that.
//We tried upcasting weapons, armors, and consumables to a pointer of type Item (pointers because we'd get object slicing if not) but then couldn't downcast
//back to the original type.

class Entity {
public:

	int health = 0;
	int stamina = 0;
	int strength = 0;
	int attunement = 0;
	int speed = 0;
	int level = 0;

	int experience = 0;

	int healthStat = 0;
	int staminaStat = 0;
	int strengthStat = 0;
	int attunementStat = 0;

	string name = " ";

	Entity(string name, int healthStat, int staminaStat, int strengthStat, int attunementStat, int speed) { //contructor for Entity
		this->name = name;
		this->speed = speed;
		this->healthStat = healthStat;
		this->staminaStat = staminaStat;
		this->strengthStat = strengthStat;
		this->attunementStat = attunementStat;
		health = 15 * healthStat;
		stamina = 10 * staminaStat;
		strength = 2 * strengthStat;
		attunement = 2 * attunementStat;
		level = healthStat + staminaStat + attunementStat + strengthStat;
		
	}

	void showCurrents() {
		cout << "Health: " << health << endl;
		cout << "Stamina: " << stamina << endl;
	}

	int damageEntity(Entity& target, bool strong, bool defending) {
		//The main damage function. Calculates damage based on the attacker's strength/attunement and weapon damage versus the defender's armor.
		//Also increases damage if attack is strong/channeled and decreases it if the target is defending.

		if (weapon.magic == true && weapon.physical == true) {
			if (target.armor.m_armor >= weapon.damage + attunement && target.armor.p_armor >= weapon.damage + strength) {
				if (strong) {
					if (defending) {
						target.health -= 1;
						return 1;
					}
					else {
						target.health -= 2;
						return 2;
					}
				}
				else {
					if (defending) {
						target.health -= 0;
						return 0;
					}
					else {
						target.health -= 1;
						return 1;
					}
					
				}
				
			}
			else {
				if (strong) {
					if (defending) {
						target.health -= (weapon.damage / 2) * 1.1 - target.armor.m_armor;
						target.health -= (weapon.damage / 2) * 1.1 - target.armor.p_armor;
						return (weapon.damage / 2) * 1.1 - target.armor.m_armor + (weapon.damage / 2) * 1.1 - target.armor.p_armor;
					}
					else {
						target.health -= (weapon.damage / 2) * 1.5 - target.armor.m_armor;
						target.health -= (weapon.damage / 2) * 1.5 - target.armor.p_armor;
						return (weapon.damage / 2) * 1.5 - target.armor.m_armor + (weapon.damage / 2) * 1.5 - target.armor.p_armor;
					}
					
				}
				else {
					if (defending) {
						target.health -= (weapon.damage / 2) * 0.5 - target.armor.m_armor;
						target.health -= (weapon.damage / 2) * 0.5 - target.armor.p_armor;
						return (weapon.damage / 2) * 0.5 - target.armor.m_armor + (weapon.damage / 2) * 0.5 - target.armor.p_armor;
					}
					else {
						target.health -= (weapon.damage / 2) - target.armor.m_armor;
						target.health -= (weapon.damage / 2) - target.armor.p_armor;
						return (weapon.damage / 2) - target.armor.m_armor + (weapon.damage / 2) - target.armor.p_armor;
					}
					
				}

			}
		}
		else if(weapon.magic == true) {
			if (target.armor.m_armor >= weapon.damage + attunement) {
				if (strong) {
					if (defending) {
						target.health -= 1;
						return 1;
					}
					else {
						target.health -= 2;
						return 2;
					}
				}
				else {
					if (defending) {
						target.health -= 0;
						return 0;
					}
					else {
						target.health -= 1;
						return 1;
					}

				}
			}
			else {
				if (strong) {
					if (defending) {
						target.health -= weapon.damage * 1.1 - target.armor.m_armor;
						return weapon.damage * 1.1 - target.armor.m_armor;
					}
					else {
						target.health -= weapon.damage * 1.5 - target.armor.m_armor;
						return weapon.damage * 1.5 - target.armor.m_armor;
					}
					
				}
				else {
					if (defending) {
						target.health -= weapon.damage * 0.5 - target.armor.m_armor;
						return weapon.damage * 0.5 - target.armor.m_armor;
					}
					else {
						target.health -= weapon.damage - target.armor.m_armor;
						return weapon.damage - target.armor.m_armor;
					}
					
				}
				
			}
		}
		else {
			if (target.armor.p_armor >= weapon.damage + strength) {
				if (strong) {
					if (defending) {
						target.health -= 1;
						return 1;
					}
					else {
						target.health -= 2;
						return 2;
					}
				}
				else {
					if (defending) {
						target.health -= 0;
						return 0;
					}
					else {
						target.health -= 1;
						return 1;
					}

				}
			}
			else {
				if (strong) {
					if (defending) {
						target.health -= weapon.damage * 1.1 - target.armor.p_armor;
						return weapon.damage * 1.1 - target.armor.p_armor;
					}
					else {
						target.health -= weapon.damage * 1.5 - target.armor.p_armor;
						return weapon.damage * 1.5 - target.armor.p_armor;
					}

				}
				else {
					if (defending) {
						target.health -= weapon.damage * 0.5 - target.armor.p_armor;
						return weapon.damage * 0.5 - target.armor.p_armor;
					}
					else {
						target.health -= weapon.damage - target.armor.p_armor;
						return weapon.damage - target.armor.p_armor;
					}

				}
			}
		}
	}

	void levelUp() { //checks if player can level up then allows them to allot a stat if they can or just tells them how much exp they need if they can't.

		if (experience >= level * 50) {
			string choice = " ";
			cout << "Choose stat to level:\n1. Health\n2. Stamina\n3. Strength\n4. Attunement\n\nEnter a number: ";
			cin >> choice;
			cout << endl;
			bool choiceMade = false;
			while (choiceMade == false) {
				if (choice == "1") {
					healthStat++;
					choiceMade = true;
				}
				else if (choice == "2") {
					staminaStat++;
					choiceMade = true;
				}
				else if (choice == "3") {
					strengthStat++;
					choiceMade = true;
				}
				else if (choice == "4") {
					attunementStat++;
					choiceMade = true;
				}
				else {
					cout << "Invalid choice.";
				}
			}
		}
		else {
			cout << level * 50 - experience << " experience required to level up.\n\n";
		}
	}

	void gainExp(Entity dropper) {
		experience += dropper.level * 5;

		cout << "You gained " << dropper.level * 5 << " experience!\n\n";
	}

	void resetStats() {
		health = 15 * healthStat;
		stamina = 10 * staminaStat;
		strength = 2 * strengthStat;
		attunement = 2 * attunementStat;
	}

	void healEntity(int heal) { //heals player for some amount.
		health += heal;
	}

	void useStamina(int staminaUse) { //uses stamina for some amount.
		stamina -= staminaUse;
	}

	void regenStamina() { //regens some stamina every turn.
		stamina += 10;
	}

	int physicalAttack() {
		int attack = 1 + strength;
		return attack;
	}

	int magicAttack() {
		int attack = 1 + attunement;
		return attack;
	}

	void useConsumable(Consumable consumeable, int posInInv) {
		//called when user decides to use a consumable. functionality is explained more where consumables are defined in Item.h

		if (consumeable.effecting == "health") {
			health += consumeable.positiveEffect;
			health -= consumeable.negativeEffect;
		}

		consumableInv.erase(consumableInv.begin() + posInInv);
	}

	void listEquipment() { //lists currently equiped equipment.
		cout << "Weapon: " << weapon.name << endl;
		cout << "Armor: " << armor.name << endl;
	}

	void equipWeapon(Weapon weapon, int posInInv) { //equips a new weapon.
		if (this->weapon.name == "Unarmed") {
			this->weapon = weapon;
		}
		else {
			weaponInv.push_back(this->weapon);
			this->weapon = weapon;
		}

		weaponInv.erase(weaponInv.begin() + posInInv);
	}

	void equipArmor(Armor armor, int posInInv) { //equips a new set of armor.
		if (this->armor.name == "Nothing") {
			this->armor = armor;
		}
		else {
			armorInv.push_back(this->armor);
			this->armor = armor;
		}

		armorInv.erase(armorInv.begin() + posInInv);
	}

	void unequip() { //unequips either armor or the weapon.
		cout << "What equipment do you want to unequip?\n1. Weapon\n2. Armor";
		string equipment = " ";
		cin >> equipment;

		bool choiceMade = false;
		while (choiceMade == false) {
			if (equipment == "weapon" || equipment == "Weapon" || equipment == "1") {
				weapon = Weapon("Unarmed", 0, true, false, 0, 0);
				choiceMade = true;
			}
			else if (equipment == "armor" || equipment == "Armor" || equipment == "2") {
				armor = Armor("Nothing", 0, 0);
				choiceMade = true;
			}
			else {
				cout << "Bad choice." << endl;
			}
		}
	}

	void unequip(string equipment) { //unequips either armor or the weapon.
		bool choiceMade = false;
		while (choiceMade == false) {
			if (equipment == "weapon" || equipment == "Weapon" || equipment == "1") {
				weaponInv.push_back(weapon);
				weapon = Weapon("Unarmed", 0, true, false, 0, 0);
				choiceMade = true;
			}
			else if (equipment == "armor" || equipment == "Armor" || equipment == "2") {
				armorInv.push_back(armor);
				armor = Armor("Nothing", 0, 0);
				choiceMade = true;
			}
			else {
				cout << "Bad choice." << endl;
			}
		}
	}

	void addToInv(Consumable consumable) { //following overloaded functions just add an item to the respective inventory.
		consumableInv.push_back(consumable);
	}

	void addToInv(Armor armor) {
		armorInv.push_back(armor);
	}

	void addToInv(Weapon weapon) {
		weaponInv.push_back(weapon);
	}

	void listInventory() { //lists every item in chosen inventory
		string inventory = " ";
		cout << "Choose inventory to list:\n1. Weapons\n2. Armor\n3. Consumables\n\nEnter a number: ";
		

		bool choiceMade = false;
		while (choiceMade == false) {
			cin >> inventory;
			if (inventory == "1") {
				if (weaponInv.size() == 0) {
					cout << "There are no weapons in your inventory.\n\n";
					cin.ignore();
				}
				else {
					for (int invIter = 0; invIter < weaponInv.size(); invIter++) {
						cout << invIter + 1 << ". " << weaponInv[invIter].name << endl;
					}
					cout << endl;
					cin.ignore();
				}
				choiceMade = true;
			}
			else if (inventory == "2") {
				if (armorInv.size() == 0) {
					cout << "There is no armor in your inventory.\n\n";
					cin.ignore();
				}
				else {
					for (int invIter = 0; invIter < armorInv.size(); invIter++) {
						cout << invIter + 1 << ". " << armorInv[invIter].name << endl;
					}
					cout << endl;
					cin.ignore();
				}
				choiceMade = true;
			}
			else if (inventory == "3") {
				if (consumableInv.size() == 0) {
					cout << "You have no consumables.\n\n";
					cin.ignore();
				}
				else {
					for (int invIter = 0; invIter < consumableInv.size(); invIter++) {
						cout << invIter + 1 << ". " << consumableInv[invIter].name << endl;
					}
					cout << endl;
					cin.ignore();
				}
				choiceMade = true;
			}
			else {
				cout << "Invalid input.\n\n";
			}
		}
		
	}

	void listInventory(string inventory) { //overloaded inventory function for instances where the user does not choose inside the function.
		bool choiceMade = false;
		while (choiceMade == false) {
			if (inventory == "weapons") {
				if (weaponInv.size() == 0) {
					cout << "There are no weapons in your inventory.\n\n";
					cin.ignore();
				}
				else {
					for (int invIter = 0; invIter < weaponInv.size(); invIter++) {
						cout << invIter + 1 << ". " << weaponInv[invIter].name << endl;
					}
					cin.ignore();
					cout << endl;
				}
				choiceMade = true;
			}
			else if (inventory == "armor") {
				if (armorInv.size() == 0) {
					cout << "There is no armor in your inventory.\n\n";
					cin.ignore();
				}
				else {
					for (int invIter = 0; invIter < armorInv.size(); invIter++) {
						cout << invIter + 1 << ". " << armorInv[invIter].name << endl;
					}
					cin.ignore();
					cout << endl;
				}
				choiceMade = true;
			}
			else if (inventory == "consumables") {
				if (consumableInv.size() == 0) {
					cout << "You have no consumables.\n\n";
					cin.ignore();
				}
				else {
					for (int invIter = 0; invIter < consumableInv.size(); invIter++) {
						cout << invIter + 1 << ". " << consumableInv[invIter].name << endl;
					}
					cin.ignore();
					cout << endl;
				}
				choiceMade = true;
			}
			else {
				cout << "Invalid input.\n\n";
			}
		}

	}

	void showStats() {
		cout << "Name: " << name << endl;
		cout << "Level: " << level << endl << endl;
		cout << "Health: " << healthStat << endl;
		cout << "Stamina: " << staminaStat << endl;
		cout << "Strength: " << strengthStat << endl;
		cout << "Attunement: " << attunementStat << endl << endl;
	}

	Weapon weapon;
	Armor armor;

	vector<Consumable> consumableInv;
	vector<Armor> armorInv;
	vector<Weapon> weaponInv;
};

#endif // !__ENTITY_H