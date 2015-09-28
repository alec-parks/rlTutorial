#ifndef ACTOR_HPP
#define ACTOR_HPP

class Actor {
public:
  const char *name; //Actors name
  int x,y; //position
  int ch; //ascii code
  TCODColor col; //color
  bool blocks; //can you move through this actor
  Attacker *attacker; //something that deals damage
  Destructible *destructible; //can it be damaged
  Ai *ai; //something self updating

  Actor (int x, int y, int ch, const char *name, const TCODColor &col);
  void update();
  bool moveOrAttack(int x, int y);
  void render() const;
};

#endif
