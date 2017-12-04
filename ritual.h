#ifndef ritual_h
#define ritual_h

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ability.h"
#include "trigability.h"
#include "card.h"
#include "CardInfo.h"
using namespace std;

class Ritual: public Card {
    
protected:
    string name;
    string description;
    int Cost;
    const Ability* ability;
    int ablCost;
    int charges;
    
    CardInfo CInfo;
    
public:
    Ritual(string s);
    ~Ritual(){delete ability};
    
    // check if the ritual has enough magic/charge to use the ability
    bool canUseAbl();
    
    // being called after an ability used. Update corresponging magic/charges info
    void update();
    
    void modify(int ablCostCh, int chargeCh);
    string getType() {return "Ritual"; };
    int& getATK() {return 0};
    void updateCardInfo();
};

#endif /* ritual_h */
