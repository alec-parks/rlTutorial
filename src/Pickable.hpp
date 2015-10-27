#ifndef PICKABLE_HPP
#define PICKABLE_HPP

class Pickable {
public:
	bool pick(Actor *owner, Actor *wearer);
	virtual bool use(Actor *owner, Actor * wearer);
};

class Confuser : public Pickable {
public:
	int nbTurns;
	float range;
	Confuser(int nbTurns, float range);
	bool use(Actor *owner, Actor *wearer);
};

class Healer : public Pickable{
public:
	float amount; //how much hp

	Healer(float amount);
	bool use(Actor *owner, Actor *wearer);
};

class LightningBolt: public Pickable {
public:
	float range,damage;
	LightningBolt(float range, float damage);
	bool use(Actor *owner, Actor *wearer);
};

class Fireball : public LightningBolt {
public:
	Fireball(float range, float damage);
	bool use(Actor *owner, Actor *wearer);
};

#endif
