#include "enchantment.h"

Enchantment::Enchantment(string name){


};

void Enchantment::play(Card *c){
	if (c->getType() != "Minion") return;

	char info = enchant[0];
	string suppliment = enchant.substr(1);
	int splmt;
	card=c;
	if (info == '+'){
		splmt = stoi(suppliment);
		c.getATK() += splmt;
		c.getLP() += splmt;
	}
	else if (info == '*'){
		splmt = stoi(suppliment);
		c.getATK() *= splmt;
		c.getLP() *= splmt;
	}
	else if (info == 't'){
		splmt = stoi(suppliment);
		c.modifyACS(splmt);
	}
	else if (info == 'c'){
		splmt = stoi(suppliment);
		c.getACost() += splmt;
	}
	else if (info == 's'){
		c.getS() = false;
	}
};

void Enchantment::updateCardInfo(){
    CInfo.type = "Enchantment";
    CInfo.name = name;
    CInfo.cost = cost;
    CInfo.desc = descn;
    CInfo.att = ATK;
    CInfo.def = DEF;
    CInfo.withAttDef = withATKDef;
}
