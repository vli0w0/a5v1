#include "trigability.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

TrigAbility::TrigAbility(std::istringstream &iss, Card *card){
      
    char type;
    iss >> type;
    
    if (type == 'l') {
        trigType = TState::l ;
    } else if (type == 'e') {
        trigType = TState::e ;
    } else if (type == 's') {
        trigType = TState::s ;
    } else if (type == 'f') {
        trigType = TState::f ;
    } else {
        cerr << "State info input ERROR." << endl;
    };
    
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
        cerr << "WRONG INPUT OF TRIGGER ABILITY!" << endl;
    } ;
    
    c = *card);
    
};


TState TrigAbility::getType(){
    return trigType;
};


void TrigAbility::useAbility(Player &p){
    //plays card in the player p’s hand with no target.
    
    if (summon) {
        int cardOnBoard = p.getAllMinion().size();
        int actualSumNum = min(5 - cardOnBoard, sumNum);
        
        for (int i = 1; i <= actualSumNum; i++) {
            p.playCard("Air Elemental");
        }
        
    } else if (magic) {
        p.modifyMagic(p);
        
    } else if (destroy) {
        
        //destroy opposite player's all minions
        for ( auto minion: p.getAllMinion()) {
            minion.destroy();
        };
        
    } else {
        
        for ( auto minion: p.getAllMinion()) {
            minion.modify(ATKchange, LPchange);
        };
    }
};


void TrigAbility::useAbility(Player &p1, Player &p2, Minion &m){
    //player p1 plays the card. The target is the minion m under player 2.
    if (destroy) {
        m.destroy();
        
    } else if (damage) {
        m.modify((-ATKchange), (-LPchange));
        
    } else {
        m.modify(ATKchange, LPchange);
        
    }
};

void TrigAbility::notify(TSubject<TInfo, TState> &whoFrom){
    
    TState whoFromState = whoFrom.getTState();
    TInfo whoFromInfo = whoFrom.getTInfo();
    
    // If the state has not been initialized, stop processing.
    if (whoFromState == TState::u) return;
    
    // If the state is not the trigger type, stop processing.
    if (whoFromState != trigType) return;
    
    if (all) {
        // In case the ability does not have a target
        // If ritual, update the total charges remaining
        if (c.getType() == "Ritual") {
            if (!c.canUseAbl()) return;
            c.update();
        }
        useAbility(whoFromInfo.p1);
        
    } else {
        // In case the ability DOES have a target
        if (c.getType() == "Ritual") {
            if (!c.canUseAbl()) return;
            c.update();
        }
        useAbility(whoFromInfo.p1, whoFromInfo.p2, whoFromInfo.m);
    }
};
