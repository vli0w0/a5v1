#ifndef __SPELL_H__
#define __SPELL_H__

#include "card.h"
#include "pinfo.h"

class Spell:public Card{
	string name;
	string description;
	int cost;

	bool destroy;
	bool returnM;
	bool gainCharge;
	int chargeVal;
	bool destroyEn;
	bool necromacy;
	bool allAtk;
	int atkVal=0;

public:
	Spell(std::string s);
	void play(PInfo &intr,PInfo &rcvr);
	void play(PInfo &intr,PInfo &rcvr,bool val);
	void play(PInfo &intr,PInfo &rcvr,int indx);
}

#endif
