#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHp,float hp, float defense, 
	const char *corpseName): maxHp(maxHp),hp(hp),defense(defense)[]
	this->corpseName=strdup(corpseName);
}

Destructible::~Destructible(){
  free(corpseName);
}

Destructible *Destructible::create(TCODZip &zip){
  DestrctibleType type = (DestrctibleType)zip.getInt();
  Destructible *destructible = NULL;
  switch(type){
    case MONSTER : destructible=new MonsterDestructible(0,0,NULL); break;
    case PLAYER : destructible=new PlayerDestructible(0,0,NULL); break;
  }
  destructible->load(zip);
  return destructible;
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

float Destructible::heal(float amount){
  hp += amount;
  if (hp > maxHp){
    amount -= hp-maxHp;
    hp=maxHp;
  }
  return amount;
}

void Destructible::die(Actor *owner){
  owner ->ch='%';
  owner->col = TCODColor::darkRed;
  owner->name = corpseName;
  owner->blocks = false;
  engine.sendToBack(owner);
}

void Destructible::load(TCODZip &zip){
  maxHp=zip.getFloat();
  hp=zip.getFloat();
  defense=zip.getFloat();
  corpseName=strdup(zip.getString());
}

void Destructible::save(TCODZip &zip){
  zip.putFloat(maxHp);
  zip.putFloat(hp);
  zip.putFloat(defense);
  zip.putString(corpseName);
}

MonsterDestructible::MonsterDestructible(float maxHp, float hp, float defense, 
		const char *corpseName) :
    Destructible(maxHp,hp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner){
  engine.gui->message(TCODColor::lightGrey,"%s is died", owner->name);
  Destructible::die(owner);
}

void MonsterDestructible::save(TCODZip &zip){
  zip.putInt(MONSTER);
  Destructible::save(zip);
}

PlayerDestructible::PlayerDestructible(float maxHp,float hp, float defense, 
		const char *corpseName) :
    Destructible(maxHp,hp,defense,corpseName) {
}

void PlayerDestructible::die(Actor *owner){
  engine.gui->message(TCODColor::red,"You died!");
  Destructible::die(owner);
  engine.gameStatus=Engine::DEFEAT;
}

void PlayerDestructible::save(TCODZip &zip){
  zip.putInt(PLAYER);
  Destructible::save(zip);
}
