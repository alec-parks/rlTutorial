#ifndef PICKABLE_HPP
#define PICKABLE_HPP

class Pickable {
public:
	bool pick(Actor *owner, Actor *wearer);
	virtual bool use(Actor *owner, Actor * wearer);
};

class Healer : public Pickable{
public:
	float amount; //how much hp

	Healer(float amount);
	bool use(Actor *owner, Actor *wearer);
};

#endif
