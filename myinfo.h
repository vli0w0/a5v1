#ifndef __MYINFO_H__
#define __MYINFO_H__
#include <string>
#include "player.h"
#include "CardInfo.h"

struct MyInfo{
	std::string pName = "";
	int life=20;
	int mana=3;
	std::vector<CardInfo> pHand;
	std::vector<CardInfo> pBoard;
	CardInfo pGYard;
	CardInfo pRitual;
};

#endif
