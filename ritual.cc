#include "ritual.h"

Ritual::Ritual(string s){
    
    istringstream strm (s);
    
    string n;
    strm >> n;
    name = n;
    
    int cost;
    strm >> cost;
    Cost = cost;
    
    string abl;
    strm >> abl;
    
    if (abl != "TrigAbility") {
        cerr << "WRONG RITUAL FILE INPUT" << endl;
    };
    
    int i1;
    strm >> i1;
    int i2;
    strm >> i2;
    
    ablCost = i1;
    charges = i2;
    
    string d;
    getline(strm,  d);
    description = d;
    
    TrigAbility tr = TrigAbility(strm, this);
};


bool Ritual::canUseAbl(){
    if (ablCost <= charges) {return true;}
    else return false;
};


void Ritual::update() {
    charges -= ablCost;
};


void Ritual::modify(int ablCostCh, int chargeCh){
    ablCost += ablCostCh;
    charges += chargeCh;
};

void updateCardInfo(){
    CInfo.type = "Ritual";
    CInfo.name = name;
    CInfo.cost = Cost;
    CInfo.desc = description;
    int ritual_cost = ablCost;
    int ritual_charges = charges;

}

