#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Engine::Engine()
{
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
    player = new Actor(40,25,'@',TCODColor::white);
    actors.push(player);
    map = new Map(80,45);
}

Engine::~Engine()
{
    actors.clearAndDelete();
    delete map;
}

void Engine::update()
{
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
    switch(key.vk)
    {
        case TCODK_UP :
        case TCODK_KP8 :
            if ( ! map->isWall(player->x,player->y-1))
            {
                player->y--;
            }
        break;
        case TCODK_DOWN :
        case TCODK_KP2 :
            if ( ! map->isWall(player->x,player->y+1))
            {
                player->y++;
            }
        break;
        case TCODK_LEFT :
        case TCODK_KP4 :
            if ( ! map->isWall(player->x-1,player->y))
            {
                player->x--;
            }
        break;
        case TCODK_RIGHT :
        case TCODK_KP6 :
            if ( ! map->isWall(player->x+1,player->y))
            {
                player->x++;
            }
        break;
        case TCODK_KP7 :
            if (! map->isWall(player->x-1,player->y-1))
            {
              player->x--;
              player->y--;
            }
        break;
        case TCODK_KP9 :
            if (! map->isWall(player->x+1,player->y-1))
            {
              player->x++;
              player->y--;
            }
        break;
        case TCODK_KP1 :
            if (! map->isWall(player->x-1,player->y+1))
            {
              player->x--;
              player->y++;
            }
        break;
        case TCODK_KP3 :
            if (! map->isWall(player->x+1,player->y+1))
            {
              player->x++;
              player->y++;
            }
        break;
        default: break;
    }
}

void Engine::render()
{
    TCODConsole::root->clear();
    // draw the map
    map->render();
    // draw the actors
    for (Actor **iterator=actors.begin();
      iterator != actors.end(); iterator++)
      {
        (*iterator)->render();
      }
}
