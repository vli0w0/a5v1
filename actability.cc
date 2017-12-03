#include "actability.h"
#include <iostream>
using namespace std;

ActAbility::ActAbility(std::istringstream iss, Card *card){
    
    string targ;
    iss >> targ;
    if (targ == "all") {
        all = true;
    };
    
    string ablType;
    iss >> ablType;
    if (ablType == "summon") {
        all = true;
        summon = true;
        int i;
        iss >> i;
        sumNum = i;
    } else if (ablType == "magic") {
        all = true;
        magic = true;
        int i;
        iss >> i;
        magIncre = i;
    } else if (ablType == "destroy") {
        destroy = true;
    } else if (ablType == "damage") {
        damage = true;
        int i;
        iss >> i;
        ATKchange = i;
        iss >> i;
        LPchange = i;
    } else if (ablType == "heal") {
        damage = false;
        int i;
        iss >> i;
        ATKchange = i;
        iss >> i;
        LPchange = i;
    } else {
        cerr << "WRONG INPUT OF ABILITY!" << endl;
    }
    
    
    c = &(*card);
    // placeholder for possible card information going to somewhere else
    //       after reading in the ability info.
    
};


void ActAbility::useAbility(Player &p){
    
    //Notice that use() fn in Player should check if the player has enough magic to use the ability
    //plays card in the player p’s hand with no target.
    
    if (summon) {
        int cardOnBoard = p.getAllMinion().size();
        int actualSumNum = min(5 - cardOnBoard, sumNum);
        
        for (int i = 1; i <= actualSumNum; i++) {
            // p->PInfo->board.insert(new Card ("Air Elemental"));
        }
        
    } else if (magic) {
        p->PInfo.modifyMagic(p);
        
    } else if (destroy) {
        
        //destroy opposite player's all minions
        auto (p->pInfo.getCardStack().getMinions() &minion) {
            minion.destroy();
        };
        
    } else {
        
        auto (p->pInfo.getCardStack().getMinions() &minion) {
            minion.modify(ATKchange, LPchange);
        };
    }
};


void ActAbility::useAbility(Player &p1, Player &p2, Minion &m){
    
    //player p1 plays the card. The target is the minion m under player 2.
    if (destroy) {
        m.destroy();
        
    } else if (damage) {
        m.modify((-ATKchange), (-LPchange));
        
    } else {
        m.modify(ATKchange, LPchange);
        
    }
};
