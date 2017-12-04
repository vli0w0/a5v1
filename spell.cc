#include "spell.h"
#include <string>
#include <fstream>
using namespace std;

string Spell::getType() {return "Spell";}

Spell::Spell(string s){
	istringstream strm (s);
	
	string s;
	int i;
	strm >> s;
	name = s;
	strm >> i;
	cost = i;
	
	string desc;
        getline(strm, desc);
        description = desc;
	
	string detail;
	strm >> detail;
	if (detail[0] == 'd') {
		if (detail[1] == 't') {
			destroy = true;
		} else { destroyEn = true; }
	} else if (detail[0] == 'r') {
		returnM = true;
	} else if (detail[0] == 'g') {
		gainCharge = true;
		chargeVal = (detail[1] - '0');
	} else if (detail[0] == 'n') {
		necromacy = true;
	} else if (detail[0] == 'a') {
		allAtk = true;
		atkVal = (detail[1] - '0');
	}
}

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
void Spell::updateCardInfo(){
     CInfo.type = "Spell";
     CInfo.name = name;
     CInfo.cost = cost;
     CInfo.desc = description;
}
