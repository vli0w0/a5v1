#include "enchantment.h"
using namespace std

Enchantment::Enchantment(string name){
	
	istringstream strm (s);
    
    	string str;
	int i
    	strm >> str;
	strm >> i;
    	name = str;
	cost = i;
	
	getline(strm, str);
	desc = str;
	
	strm >> str;;
	enchant = str;
};

void Enchantment::play(Card *c){
	if (c->getType() != "Minion") return;

	char info = enchant[0];
	string suppliment = enchant.substr(1);
	int splmt;
	card=c;
	if (info == '+'){
		splmt = stoi(suppliment);
		c->setATK(c->getATK() + splmt);
		c->setLP(c->getLP + splmt);
	}
	else if (info == '*'){
		splmt = stoi(suppliment);
		c->setATK(c->getATK * splmt);
		c->setLP(c->getLP * splmt);
	}
	else if (info == 't'){
		splmt = stoi(suppliment);
		c->modifyACS(splmt);
	}
	else if (info == 'c'){
		splmt = stoi(suppliment);
		c->modifyACost(splmt);
	}
	else if (info == 's'){
		c->setSilence(true);
	}
	c->getEnInfo().push_back(CInfo);
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
CardInfo Enchantment::getCardInfo(){
	return CInfo;
}
