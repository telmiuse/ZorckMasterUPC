#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "npc.h"

// ----------------------------------------------------
Npc::Npc(const char* title, const char* description, Room* room) :
	Creature(title, description, room)
{
	type = NPC;
}

// ----------------------------------------------------
Npc::~Npc()
{
}

// ----------------------------------------------------
void Npc::Look(const vector<string>& args) const
{
	if (args.size() > 1)
	{
		for (list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if (Same((*it)->name, args[1]) || ((*it)->type == EXIT && Same(args[1], ((Exit*)(*it))->GetNameFrom((Room*)parent))))
			{
				(*it)->Look();
				return;
			}
		}

		if (Same(args[1], "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
	}
	else
	{
		parent->Look();
	}
}

void Npc::speak() 
{
	cout << "\n Take care with the alter, u will find some object with a curse... \n";
	cout << "\n This means, that this object can revive evil from the past \n";
	cout << "\n Be very careful \n";
}
