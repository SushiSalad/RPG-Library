#include <iostream>
#include <vector>
#include <time.h>
#include "Entity.h"
#include "Item.h"

#define player entities[0]
#define enemy entities[enemyId]

using namespace std;

vector<Armor> armors;
vector<Weapon> weapons;
vector<Consumable> consumables;

vector<Entity> entities;

bool is_number(const string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool defending() {
	int rando = rand() % 2 + 1;
	if (rando == 1) {
		return true;
	}
	else {
		return false;
	}
}

void onGameStart() {

	armors.push_back(Armor("Heavy Armor Set", 4, 20));
	armors.push_back(Armor("Sorcerer's Robes", 20, 5));
	armors.push_back(Armor("Chainmail", 10, 10));

	weapons.push_back(Weapon("Longsword", 50, true, false, 5, 0));
	weapons.push_back(Weapon("Wooden Staff", 20, false, true, 0, 5));
	weapons.push_back(Weapon("Magic Sword", 15, true, true, 4, 4));

	consumables.push_back(Consumable(50, 0, "Health Potion", "health"));

	cout << "|||WIP|||\n";

	cout << "Choose starting class:\n1. Knight\n2. Mage\n3. Swordcaster\n\n";
	string classChoice = " ";


	bool choiceMade = false;
	while (choiceMade == false) {
		cin >> classChoice;

		if (classChoice == "1" || classChoice == "Knight") {
			string name = " ";
			cout << "Enter your name: ";
			cin >> name;
			cout << endl;

			entities.push_back(Entity(name, 7, 6, 7, 2, 2));
			player.weapon = weapons[0];
			player.armor = armors[0];

			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));
			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));
			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));

			choiceMade = true;
		}
		else if (classChoice == "2" || classChoice == "Mage") {
			string name = " ";
			cout << "Enter your name: ";
			cin >> name;
			cout << endl;

			entities.push_back(Entity(name, 5, 7, 2, 7, 5));
			player.weapon = weapons[1];
			player.armor = armors[1];

			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));
			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));
			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));

			choiceMade = true;
		}
		else if (classChoice == "3" || classChoice == "Swordcaster") {
			string name = " ";
			cout << "Enter your name: ";
			cin >> name;
			cout << endl;

			entities.push_back(Entity(name, 6, 6, 5, 5, 7));
			player.weapon = weapons[2];
			player.armor = armors[2];

			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));
			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));
			player.consumableInv.push_back(Consumable(50, 0, "Health Potion", "health"));

			choiceMade = true;
		}
		else {
			cout << "Invalid choice.";
		}
	};

	 //Player creation. Player should always be the first object in the entities array.

	entities.push_back(Entity("Skeleton", 5, 5, 7, 4, 5));
	entities[1].weapon = Weapon("Skeleton's Shortsword", 30, true, false, 7, 0);

	entities.push_back(Entity("Slug", 8, 5, 7, 4, 1));
	entities[2].weapon = Weapon("Slug Bite", 45, true, false, 7, 0);

	player.addToInv(consumables[0]);

}

bool fight() {
	int enemyId = rand() % (entities.size() - 1) + 1;

	cout << "You are fighting a " << enemy.name << "!\n\n";

	bool playerTurn = true;

	bool strikeFirst = false;

	if (enemy.speed > player.speed) {
		cout << "The " << enemy.name << " manages to strike first!\n\n";

		strikeFirst = true;
		playerTurn = false;
	}
	else {
		cout << "The " << enemy.name << " doesn't seem to notice you yet.\n\n";

		playerTurn = true;
	}

	bool fighting = true;

	bool playerDefending = false;
	bool enemyDefending = false;

	while (fighting) {

		playerDefending = false;

		if (enemy.health <= 0) {
			cout << "You've defeated the " << enemy.name << " !\n\n";
			player.gainExp(enemy);
			player.levelUp();
			player.resetStats();
			enemy.resetStats();
			fighting = false;
			return true;
		}
		else if(player.health <= 0) {
			cout << "You've been defeated!\n\n";
			fighting = false;
			return false;
		}


		if (playerTurn && fighting) {

			if (player.stamina < 10 * player.staminaStat) {
				if (10 * player.staminaStat - player.stamina < 10) {
					player.stamina = 10 * player.staminaStat;
				}
				else {
					player.regenStamina();
				}
			}

			player.showCurrents();

			string choice = " ";
			

			while (playerTurn) {
				cout << "Choose an action:\n1. Attack\n2. Defend\n3. Use an item.\n\nEnter a number: ";
				cin >> choice;
				cout << endl;
				if (choice == "1") {
					if (player.weapon.magic && player.weapon.physical) {
						cout << "Charge your attack?\ny or n\n\n";
						cin >> choice;
						cout << endl;
						if (choice == "y") {
							int damage = player.damageEntity(enemy, true, enemyDefending);
							cout << "You deal " << damage << " to the enemy!\n\n";
							player.useStamina(20);
							playerTurn = false;
						}
						else if (choice == "n") {
							int damage = player.damageEntity(enemy, false, enemyDefending);
							cout << "You deal " << damage << " to the enemy!\n\n";
							player.useStamina(15);
							playerTurn = false;
						}
						else {
							cout << "Invalid choice.\n";
						}
					}
					else if (player.weapon.magic) {
						cout << "Hone your attack?\ny or n\n\n";
						cin >> choice;
						if (choice == "y") {
							int damage = player.damageEntity(enemy, true, enemyDefending);
							cout << "You deal " << damage << " to the enemy!\n\n";
							player.useStamina(20);
							playerTurn = false;
						}
						else if (choice == "n") {
							int damage = player.damageEntity(enemy, false, enemyDefending);
							cout << "You deal " << damage << " to the enemy!\n\n";
							player.useStamina(15);
							playerTurn = false;
						}
						else {
							cout << "Invalid choice.";
						}
					}
					else {
						cout << "Go for a strong attack?\ny or n\n\n";
						cin >> choice;
						cout << endl;
						if (choice == "y") {
							int damage = player.damageEntity(enemy, true, enemyDefending);
							cout << "You deal " << damage << " to the enemy!\n\n";
							player.useStamina(20);
							playerTurn = false;
						}
						else if (choice == "n") {
							int damage = player.damageEntity(enemy, false, enemyDefending);
							cout << "You deal " << damage << " to the enemy!\n\n";
							player.useStamina(15);
							playerTurn = false;
						}
						else {
							cout << "Invalid choice.";
						}
					}
				}
				else if (choice == "2") {
					cout << "You decide to defend.\n\n";
					playerDefending = true;
					playerTurn = false;
				}
				else if (choice == "3") {
					if (player.consumableInv.size() == 0) { 
						cout << "You have no items to use!\n\n";
					}
					else {
						cout << "Choose an item to use: \n";
						string choice = " ";
						player.listInventory("consumables");
						cin >> choice;
						cout << endl;

						if (is_number(choice)) {
							int choiceInt = stoi(choice);
							cout << player.consumableInv.size() << endl;
							if (choiceInt <= player.consumableInv.size()) {
								player.useConsumable(player.consumableInv[choiceInt - 1], choiceInt - 1);
								playerTurn = false;
							}
							else {
								cout << "Invalid choice.\n";
							}
						}
						else {
							cout << "Invalid choice.\n";
						}
					}
					
				}
				else {
					cout << "Invalid choice.\n";
				}
			}
		}
		else if (fighting) {

			if (enemy.stamina < 10 * enemy.staminaStat) {
				if (10 * enemy.staminaStat - enemy.stamina < 10) {
					enemy.stamina = 10 * enemy.staminaStat;
				}
				else {
					enemy.regenStamina();
				}
			}

			if (defending() && strikeFirst == false) {
				enemyDefending = true;
				playerTurn = true;
			}
			else {
				enemyDefending = false;
				int damage = enemy.damageEntity(player, defending(), playerDefending);
				cout << "The " << enemy.name << " strikes you and deals " << damage << " damage!\n\n";
				playerTurn = true;
			}
		}
	}
	
}

void beforeFight() {

	bool staying = true;
	while (staying) {
		cout << "What would you like to do?\n1. Equip/Unequip items.\n2. Check inventory.\n3. Check stats.\n4. Return.\nEnter a number: ";
		string choice = " ";
		cin >> choice;
		cout << endl;

		if (choice == "1") {
			cout << "Would you like to equip or unequip?\n1. Equip\n2. Unequip\n\nEnter a number: ";
			cin >> choice;
			cout << endl;

			if (choice == "1") {
				cout << "What would you like to equip?\n1. Weapon\n2. Armor\n\nEnter a number: ";
				cin >> choice;
				cout << endl;

				if (choice == "1") {
					if (player.weaponInv.size() == 0) {
						cout << "There are no weapons in your inventory.\n\n";
					}
					else {
						cout << "Choose the weapon you'd like to equip: \n";
						player.listInventory("weapons");
						cout << "\nEnter a number: ";

						bool choiceMade = false;
						while (choiceMade == false) {
							cin >> choice;
							cout << endl;

							if (is_number(choice)) {
								if (stoi(choice) - 1 <= player.weaponInv.size()) {
									player.equipWeapon(player.weaponInv[stoi(choice) - 1], stoi(choice) - 1);
									choiceMade = true;
								}
								else {
									cout << "Invalid number.\n";
								}
							}
							else {
								cout << "Not a number.\n\n";
							}
						}
					}
				}
				else if (choice == "2") {
					if (player.armorInv.size() == 0) {
						cout << "There is no armor in your inventory.\n\n";
					}
					else {
						cout << "Choose the armor you'd like to equip: \n";
						player.listInventory("armor");
						cout << "\n\nEnter a number: ";

						bool choiceMade = false;
						while (choiceMade == false) {
							cin >> choice;
							cout << endl;

							if (is_number(choice)) {
								if (stoi(choice) <= player.armorInv.size()) {
									player.equipArmor(player.armorInv[stoi(choice) - 1], stoi(choice) - 1);
									choiceMade = true;
								}
								else {
									cout << "Invalid number.\n";
								}
							}
							else {
								cout << "Not a number.";
							}
						}
					}	
				}
				else {
					cout << "Invalid input.";
				}
			}
			else if (choice == "2") {
				cout << "What would you like to unequip?\n1. Weapon\n2. Armor\n\nEnter a number: ";
				cin >> choice;
				cout << endl;

				if (choice == "1") {
					player.unequip("weapon");
				}
				else if (choice == "2") {
					player.unequip("armor");
				}
				else {
					cout << "Invalid input.";
				}
			}
			else {
				cout << "Invalid input.";
			}
		}
		else if (choice == "2") {
			player.listInventory();
		}
		else if (choice == "3") {
			player.showStats();
		}
		else if (choice == "4") {
			staying = false;
		}
		else {
			cout << "Invalid input.";
		}
	}

}


bool gameUpdate() { 

	cout << "Enter fight?\ny or n\n\nor type \"quit\" to end the program.\n\n";
	string choice = " ";
	cin >> choice;
	cout << endl;

	if (choice == "y") {
		//bool won = fight();
		if (fight() == false) { return false; }
		else { return true; }
	}
	else if (choice == "n") {
		beforeFight();
		return true;
	}
	else if(choice == "quit"){
		return false;
	}
	else {
		cout << "Invalid input.\n";
	}
}





int main()
{

	srand(time(0));

	onGameStart();


	while (gameUpdate()) {}
	



	return 0;
}
