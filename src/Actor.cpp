#include <stdio.h>
#include "main.hpp"

char name[60];

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col) :
    x(x),y(y),ch(ch),name(name), col(col),
    blocks(true), destructible(NULL),attacker(NULL) ,ai(NULL) {
    }

void Actor::render() const {
    TCODConsole::root->setChar(x,y,ch);
    TCODConsole::root->setCharForeground(x,y,col);
}

void Actor::update()
{
  if( ai ){
    ai -> update(this);
  }
}

bool Actor::moveOrAttack(int x, int y)
{
  if (engine.map->isWall(x,y)) {return false;}
  for (auto &actor : engine.actors)
      {
        if(actor->x == x && actor->y == y)
        {
          printf("The %s laughs at your puny attempts to attack him!\n", actor->name);
          return false;
        }
      }
    this->x = x;
    this->y = y;
    return true;
}
