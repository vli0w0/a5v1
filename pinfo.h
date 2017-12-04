#ifndef __PINFO_H__
#define __PINFO_H__

#include <vector>
#include <memory>
#include "card.h"
#include "myinfo.h"
#include "CardInfo.h"

class PInfo{
	std::string name;
	int LP,magic;
	std::vector<Card *> GYard;
	std::vector<Card *> board;
	std::vector<Card *> hand;
	std::vector<Card *> deck;
	Card *ritual;
    MyInfo MyI;

public:
	PInfo(std::String name,std::vector<Card *> deck,int LP=20,int magic=3);
	void updateMyInfo();

	int &getMagic();
	int setMagic();
	void changeLP(int k);

	void play(int i,PInfo &p);
	bool dead() const;
	void toGYard(int i);
	bool mDead(int i);
	int handSize();
	void draw();

	std::vector<Card *> &getGYard();
	std::vector<Card *> &getHand();
	std::vector<Card *> &getBoard();
	Card *getRitual();
	void setRitual(Card *c);

	bool boardFull();
	bool handFull();
	bool gYardEmpty();
	
	void play(int i,PInfo &p,int j=0);
	void attack(int i,PInfo &p,int j=0);
	void use(int i,PInfo &p,int j=0);
    
};

#endif
