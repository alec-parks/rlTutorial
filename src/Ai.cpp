#include <stdio.h>
#include <math.h>
#include "main.hpp"

static const int TRACKING_TURNS=3;

MonsterAi::MonsterAi() : moveCount(0){

}

void PlayerAi::update(Actor *owner){
  if (owner->destructible && owner->destructible->isDead()){
    return;
  }
  int dx=0,dy=0;
  switch(engine.lastKey.vk)  {
      case TCODK_UP   :
      case TCODK_KP8  :
          dy=-1;
      break;
      case TCODK_DOWN :
      case TCODK_KP2  :
          dy=1;
      break;
      case TCODK_LEFT :
      case TCODK_KP4  :
          dx=-1;
      break;
      case TCODK_RIGHT :
      case TCODK_KP6  :
          dx=1;
      break;
      case TCODK_KP7 :
          dx=-1;
          dy=-1;
      break;
      case TCODK_KP9 :
          dx=1;
          dy=-1;
      break;
      case TCODK_KP1 :
          dx=-1;
          dy=1;
      break;
      case TCODK_KP3 :
          dx=1;
          dy=1;
      break;
      case TCODK_KP5 :
          dx=0;
          dy=0;
          engine.gameStatus=Engine::NEW_TURN;
      default: break;
  }
  if(dx !=0 || dy !=0){
    engine.gameStatus=Engine::NEW_TURN;
    if( moveOrAttack(owner, owner->x+dx,owner->y+dy))    {
      engine.map->computeFov();
    }
  }
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx, int targety){
  if (engine.map->isWall(targetx,targety)) {return false;}

  for (Actor **iterator=engine.actors.begin();
        iterator != engine.actors.end(); iterator++){
          Actor *actor = *iterator;
          if(actor->destructible && !actor->destructible->isDead()
             && actor->x == targetx && actor->y == targety){
               owner->attacker->attack(owner,actor);
               return false;
             }
  }
  for (Actor **iterator=engine.actors.begin();
    iterator != engine.actors.end(); iterator++) {
    Actor *actor=*iterator;
    if ( actor->destructible && actor->destructible->isDead()
         && actor->x == targetx && actor->y == targety ) {
        printf ("There's a %s here\n",actor->name);
    }
  }
  owner->x = targetx;
  owner->y = targety;
  return true;
}

void MonsterAi::update(Actor *owner){
  if (owner->destructible && owner->destructible->isDead()){
    return;
  }
  if (engine.map->isInFov(owner->x, owner->y))  {
    moveCount = TRACKING_TURNS;
  }else{
    moveCount--;
  }
  if (moveCount > 0){
    moveOrAttack(owner, engine.player->x,engine.player->y);
  }
}

void MonsterAi::moveOrAttack(Actor *owner, int targetx,int targety){
  int dx = targetx - owner->x;
  int dy = targety - owner->y;
  int stepdx = (dx > 0 ? 1 : -1);
  int stepdy = (dy > 0 ? 1 : -1);
  float distance = sqrt(dx*dx+dy*dy);

  if (distance >= 2){
    dx = (int) (round(dx/distance));
    dy = (int) (round(dy/distance));
    if(engine.map->canWalk(owner->x+dx,owner->y+dy)){
      owner->x += dx;
      owner->y += dy;
    } else if ( engine.map->canWalk(owner->x+stepdx,owner->y) ) {
            owner->x += stepdx;
    } else if ( engine.map->canWalk(owner->x,owner->y+stepdy) ) {
            owner->y += stepdy;
    }
  } else if(owner->attacker){
      owner->attacker->attack(owner,engine.player);
    }
}