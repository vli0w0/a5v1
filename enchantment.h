#ifndef __ENCHANTMENT_H__
#define	__ENCHANTMENT_H__

#include <string>
#include "pinfo.h"
#include "card.h"

class Enchantment:public Card{
	std::string name;
	int cost;
	std::string desc;
    std::string ATK;
    std::string DEF;
	bool withATKDef;

	Card *card=nullptr;
	std::string enchant="";

public:
	Enchantment(std::string name);
	std::string getType() {return "Enchantment"; };
	void play(Card *c);
};


#endif
