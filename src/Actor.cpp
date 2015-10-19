#include <stdio.h>
#include <math.h>
#include "main.hpp"

char name[60];

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col) :
    x(x),y(y),ch(ch),name(name), col(col),
    blocks(true), destructible(NULL),attacker(NULL) ,ai(NULL),
    pickable(NULL),container(NULL) {
    }

Actor::~Actor(){
   if (attacker) delete attacker;
   if (destructible) delete destructible;
   if (ai) delete ai;
   if (pickable) delete pickable;
   if (container) delete container;
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

float Actor::getDistance(int cx, int cy) const{
  int dx=x-cx;
  int dy=y-cy;
  return sqrtf(dx*dx+dy*dy);
}
