#include "minion.h"
#include "card.h"
using namespace std;

Minion::Minion(string s){
    
    istringstream strm (s);
    
    string n;
    strm >> n;
    name = n;
    
    int i1, i2, i3;
    strm >> i1 >> i2 >> i3;
    cost = i1;
    ATK = i2;
    LP =  i3;
    
    strm >> n;
    if (n == "ActAbility") {
        
        strm >> i1;
        string desc;
        getline(strm, desc);
        
        abilityCost = i1;
        description = desc;
        
        Card *c;
        
        ability = new ActAbility(strm, this);
        
    } else {
        string desc;
        getline(strm, desc);
        description = desc;
        
        ability = new TrigAbility(strm, this);
    }
    
};

bool Minion::canUseAbl(Player &p){
    if (silence) return false;
    
    int tmp = p.getMagic() ;
    if (abilityCost > tmp) return false;
    return true;
};

void Minion::modify(int ATKch, int LPch){
    ATK += ATKch;
    LP += LPch;
};

void Minion::destroy(){
    LP = 0;
};

bool Minion::acting(){
    if (actionCount > 0) {
        return true;
    } else return false;
};

void Minion::modifyAct(int i) {
    actionCount += i;
};

void Minion::modifyACS(int i) {
    actionCountStable += i;
};

void Minion::disenchant(){
    string cur = *EnSeq.back();
    EnSeq.pop_back();

    char info = cur[0];
    if (info == '*'){
        ATK /= cur[1]-'0';
        LP /= cur[1]-'0';
    }
    else if (info == '+'){
        ATK -= cur[1]-'0';
        LP -= cur[1]-'0';
    }
    else if (info == 't'){
        actionCount -= cur[1]-'0';
    }
    else if (info == 'c'){
        abilityCost -= cur[1]-'0';
    }
    else if (info == 's'){
        for (auto p:EnSeq){
            if (p[0] == info) return;
        }
        silence = false;
    }
};

void Minion::disenchantA(){
    while (EnSeq.size()!=0){
        disenchant();
    }
};

void Minion::setAct() {actionCount = actionCountStable; } 

void Minion::modifyACost(int i){
    actionCount += i;
}

string Minion::getType() {return "Minion"; }

int Minion::getACS(){ return actionCountStable; }
int Minion::getATK() { return ATK;};
int Minion::getLP() {return LP;};
int Minion::getACost(){return abilityCost;};

bool Minion::getS(){ return silence;};

void Minion::setATK(int atk){ATK = atk;}
void Minion::setLP(int lp){LP = lp;}
void Minion::setSilence(bool si){silence = si;}

void Minion::updateCardInfo(){
    CInfo.type = "Minion";
    CInfo.name = name;
    CInfo.cost = cost;
    CInfo.desc = description;
    CInfo.att = ATK;
    CInfo.def = LP;
    CInfo.ability_cost = abilityCost;
};
