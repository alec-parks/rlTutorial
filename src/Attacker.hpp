#ifndef ATTACKER_HPP
#define ATTACKER_HPP

class Attacker{
public:
  float power; //attackers power

  Attacker(float power);
  void attack(Actor *owner, Actor *target);
};

#endif
