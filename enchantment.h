#ifndef __ENCHANTMENT_H__
#define	__ENCHANTMENT_H__

#include <string>
#include "pinfo.h"
#include "card.h"
#include "CardInfo.h"

class Enchantment:public Card{
	std::string name;
	int cost;
	std::string desc;
    std::string ATK;
    std::string DEF;
	bool withATKDef;

	Card *card=nullptr;
	std::string enchant="";
	
	CardInfo CInfo;

public:
	Enchantment(std::string name);
	std::string getType() {return "Enchantment"; };
	void play(Card *c);
	void updateCardInfo();
	CardInfo getCardInfo();
};


#endif
