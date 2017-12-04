#ifndef __MYINFO_H__
#define __MYINFO_H__

#include <vector>
#include "card.h"
#include "CardInfo.h"

struct MyInfo{
	std::string pName = "";
	int life=20;
	int mana=3;
	std::vector<CardInfo> pHand=nullptr;
	std::vector<CardInfo> pBoard=nullptr;
	Card* pGYard=nullptr;
	Card* pRitual=nullptr;
};

#endif
