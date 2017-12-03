#include "spell.h"
#include <string>
#include <fstream>
using namespace std;

Spell::Spell(string s){}

void Spell::play(PInfo &intr,PInfo &rcvr){
	if (necromacy){
		if (intr.boardFull() || intr.gYardEmpty())return;
		Card *tmp = intr.getGYard().back();
		tmp->destroy();
		tmp->modify(0,1);
		intr.getGYard().erase(intr.getGYard.back());
		intr.getBoard().push_back(tmp);
	}
	else if (allAtk){
		for (auto p:intr.getBoard()){
			p.modify(0,-atkVal);
		}
		for (auto q:rcvr.getBoard()){
			q.modify(0,-atkVal);
		}
	}
	else if (gainCharge){
		intr.getRitual().modify(0,chargeVal);
	}
}

void Spell::play(PInfo &intr,PInfo &rcvr,bool val){
	if (!destroy) return;
	rcvr.setRitual(nullptr);
}

void Spell::play(PInfo &intr,PInfo &rcvr,int indx){
	if (returnM){
		if (rcvr.handFull()) return;
		Card *tmp = rcvr.getBoard()[indx];
		rcvr.getBoard().erase(rcvr.getBoard().begin()+indx);
		rcvr.getHand().push_back(tmp);
	}
	else if (destroy){
		rcvr.getBoard()[indx].destroy();
	}
	else if (destroyEn){
		rcvr.getBoard()[indx].disenchant();
	}
}