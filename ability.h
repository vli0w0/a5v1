#ifndef ability_h
#define ability_h

class Player;
class Minion;
class Card;

class Ability {
    
protected:
    bool all = false;     // indicate the ability it affecting all minions or targeted minion
    
    bool summon = false;  // indicate whether the ability's going to summon "Air Elemental"
    int sumNum = 0;       // indicate the number of "AirElemental" this ability is going to summon
    
    bool magic = false;   // indicate whether the ability's going to increment the player's magic
    int magIncre = 0;
    
    bool destroy = false;  // indicate whether the ability's going to destroy minion(s).
    
    bool damage = false;   // indicate the good/bad effects on minion's status
    int ATKchange = 0;
    int LPchange = 0;
    
    Card *c=nullptr;                // address of card who has this ability
    
public:
    Ability() = default;
    virtual ~Ability(){};
    virtual void useAbility(Player &p) = 0;
    virtual void useAbility(Player &p1, Player &p2, Minion &m) = 0;
};


#endif /* ability_h */
