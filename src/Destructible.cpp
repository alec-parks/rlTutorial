#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHp,float hp, float defense, const char *corpseName):
      maxHp(maxHp),hp(hp),defense(defense),corpseName(corpseName){
}

float Destructible::takeDamage(Actor *owner, float damage){
  damage -= defense;
  if (damage > 0 ){
    hp -= damage;
    if (hp <= 0){
      die(owner);
    }
  } else {
    damage = 0;
  }
  return damage;
}

void Destructible::die(Actor *owner){
  owner ->ch='%';
  owner->col = TCODColor::darkRed;
  owner->name = corpseName;
  owner->blocks = false;
  engine.sendToBack(owner);
}

MonsterDestructible::MonsterDestructible(float maxHp, float hp, float defense, const char *corpseName) :
    Destructible(maxHp,hp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner){
  printf ("%s is dead\n", owner->name);
  Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp,float hp, float defense, const char *corpseName) :
    Destructible(maxHp,hp,defense,corpseName) {
}

void PlayerDestructible::die(Actor *owner){
  printf ("You died!\n");
  Destructible::die(owner);
  engine.gameStatus=Engine::DEFEAT;
}
