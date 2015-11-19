#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

class Destructible : public Persistent {
public:
  float maxHp;
  float hp;
  float defense;
  const char *corpseName;

  Destructible(float maxHp,float hp, float defense, const char *corpseName);
  inline bool isDead() { return hp <=0; }

  float takeDamage(Actor *owner, float damage);
  float heal(float amount);
  void load(TCODZip &zip);
  void save(TCODZip &zip);
  static Destructible *create(TCODZip &zip);

  virtual void die(Actor *owner);

protected:
  enum DestructibleType {
    MONSTER,PLAYER
  };
};

class MonsterDestructible : public Destructible {
public:
  MonsterDestructible(float maxHp,float hp, float defense, const char *corpseName);
  void die(Actor *owner);
};

class PlayerDestructible : public Destructible {
public:
  PlayerDestructible(float maxHp,float hp, float defense, const char *corpseName);
  void die(Actor *owner);
};

#endif
