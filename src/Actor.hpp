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
  Pickable *pickable; //something that can be picked up and used
  Container *container; //something that can contain actors

  Actor (int x, int y, int ch, const char *name, const TCODColor &col);
  ~Actor();
  void update();
  bool moveOrAttack(int x, int y);
  void render() const;
};

#endif
