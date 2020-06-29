#include <iostream>
#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "npc.h"
#include "room.h"
#include "player.h"
#include "world.h"


// ----------------------------------------------------
World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* Stairs = new Room("Stairs", "You are at the bottom of a big stairs, up of them u can see a big church ");
	Room* Church = new Room("Church", "You are inside a cloud and big gotich church.");
	Room* CentralNave = new Room("CentralNave", "Central Nave of a church wich is cold and dark");
	Room* SmallRoom = new Room("SmallRoom", "Small and calm room with small fire in the midle");
	Room* Alter = new Room("Alter", "Small and calm room with small fire in the midle");

	Exit* ex1 = new Exit("up", "down", "Stairs ", Stairs, Church);
	Exit* ex2 = new Exit("up", "down", "Stairs", Church, CentralNave);
	ex2->locked = true;

	Exit* ex3 = new Exit("east", "west", "Church ", CentralNave, SmallRoom);
	Exit* ex4 = new Exit("north", "sud", "Church ", CentralNave, Alter);


	entities.push_back(Stairs);
	entities.push_back(Church);
	entities.push_back(CentralNave);
	entities.push_back(Alter);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);

	// Creatures ----
	Creature* Giant = new Creature("Giant", "It's James, the Guardian of the church.", Church);
	Giant->hit_points = 10;

	Creature* EvilCleric = new Creature("EvilCleric", "It's Lothric, The evil cleric, the owner of the church.", Alter);



	// Items -----
	Item* mailbox = new Item("Mailbox", "Looks like it might contain something.", Church);
	Item* key = new Item("Key", "Old iron key.", mailbox);
	ex2->key = key;

	Item* sword = new Item("Sword", "A simple old and rusty sword.", Stairs, WEAPON);
	sword->min_value = 4;
	sword->max_value = 7;



	Item* shield = new Item("Shield", "An old wooden shield.", Giant, ARMOUR);
	shield->min_value = 1;
	shield->max_value = 3;


	Item* sword3 = new Item("GiantSword", "An old iron Sword.", Giant, WEAPON);
	sword3->min_value = 3;
	sword3->max_value = 8;

	Item* sword4(sword3);
	sword4->parent = Giant;

	Giant->AutoEquip();

	Item* ClericSword = new Item("ClericSword", "Legendary Sword.", EvilCleric, WEAPON);
	ClericSword->min_value = 4;
	ClericSword->max_value = 8;

	Item* sword5(ClericSword);
	sword5->parent = EvilCleric;

	EvilCleric->AutoEquip();
	EvilCleric->hit_points = 0;


	Item* chalice = new Item("chalice", "there is a chalice with some wine on the table.", Alter);

	entities.push_back(Giant);
	entities.push_back(mailbox);
	entities.push_back(chalice);
	entities.push_back(sword);
	entities.push_back(shield);
	entities.push_back(ClericSword);
	entities.push_back(EvilCleric);

	// NPC ----
	npc = new Npc("Solair", "NPC Human soldier resting on the floor", SmallRoom);
	npc->hit_points = 10;
	entities.push_back(npc);



	// Player ----
	player = new Player("Hero", "You are an awesome adventurer!", Stairs);
	player->hit_points = 25;
	entities.push_back(player);

}


// ----------------------------------------------------
World::~World()
{
	for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if(args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch(args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "north") || Same(args[0], "n"))
			{
				(args.size() == 1) ? args.push_back("north") : args[1] = "north";
				player->Go(args);
			}
			else if(Same(args[0], "south") || Same(args[0], "s"))
			{
				(args.size() == 1) ? args.push_back("south") : args[1] = "south";
				player->Go(args);
			}
			else if(Same(args[0], "east") || Same(args[0], "e"))
			{
				(args.size() == 1) ? args.push_back("east") : args[1] = "east";
				player->Go(args);
			}
			else if(Same(args[0], "west") || Same(args[0], "w"))
			{
				(args.size() == 1) ? args.push_back("west") : args[1] = "west";
				player->Go(args);
			}
			else if(Same(args[0], "up") || Same(args[0], "u"))
			{
				(args.size() == 1) ? args.push_back("up") : args[1] = "up";
				player->Go(args);
			}
			else if(Same(args[0], "down") || Same(args[0], "d"))
			{
				(args.size() == 1) ? args.push_back("down") : args[1] = "down";
				player->Go(args);
			}
			else if(Same(args[0], "stats") || Same(args[0], "st"))
			{
				player->Stats();
			}
			else if (Same(args[0], "rest") || Same(args[0], "rs")) // rest in case u are in the small room
			{
				player->Rest(args);
			}
			else if(Same(args[0], "inventory") || Same(args[0], "i"))
			{
				player->Inventory();
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "go"))
			{
				player->Go(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else if(Same(args[0], "equip") || Same(args[0], "eq"))
			{
				player->Equip(args);
			}
			else if(Same(args[0], "unequip") || Same(args[0], "uneq"))
			{
				player->UnEquip(args);
			}
			else if(Same(args[0], "examine") || Same(args[0], "ex"))
			{
				player->Examine(args);
			}
			else if(Same(args[0], "attack") || Same(args[0], "at"))
			{
				player->Attack(args);
			}
			else if (Same(args[0], "talk") || Same(args[0], "tl")) // talk with npc
			{
				player->Talk(args);
			}
			else if(Same(args[0], "loot") || Same(args[0], "lt"))
			{
				player->Loot(args);
			}
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if(Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				player->UnLock(args);
			}
			else if(Same(args[0], "lock") || Same(args[0], "lk"))
			{
				player->Lock(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else
				ret = false;
			break;
		}
		default:
		ret =  false;
	}

	return ret;
}