#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <time.h>

#define TICK_FREQUENCY 0.5f

using namespace std;

class Entity;
class Npc;
class Player;


class World
{
public :

	World();
	~World();

	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();

private:

	clock_t tick_timer;
	list<Entity*> entities;
	Npc* npc;
	Player* player;

};

#endif //__World__