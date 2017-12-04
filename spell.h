#ifndef __SPELL_H__
#define __SPELL_H__

#include "card.h"
#include "pinfo.h"
#include "CardInfo.h"

class Spell:public Card{
	std::string name;
	std::string description;
	int cost;

	bool destroy = false;
	bool returnM = false;
	bool gainCharge = false;
	int chargeVal = 0;
	bool destroyEn = false;
	bool necromacy =  false;
	bool allAtk =  false;
	int atkVal = 0;
	
	CardInfo CInfo;
	
public:
	Spell(std::string s);
	std::string getType();
	void play(PInfo &intr,PInfo &rcvr);
	void play(PInfo &intr,PInfo &rcvr,bool val);
	void play(PInfo &intr,PInfo &rcvr,int indx);
	void updateCardInfo();
	CardInfo getCardInfo();
};

#endif
