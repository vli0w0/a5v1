#ifndef __MYINFO_H__
#define __MYINFO_H__

#include <vector>
#include "card.h"

struct MyInfo{
	std::string pName = "";
	int life=20;
	int mana=3;
	std::vector<Card *> pHand=nullptr;
	std::vector<Card *> pBoard=nullptr;
	Card* pGYard=nullptr;
	Card* pRitual=nullptr;
};

#endif
