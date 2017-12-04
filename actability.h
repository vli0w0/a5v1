#ifndef actability_h
#define actability_h

#include <string>
#include <sstream>
#include <fstream>
#include "ability.h"

class Player;
class Card;

class ActAbility: public Ability{
 
public:
    ActAbility(std::istringstream &iss, Card* card);
    ~ActAbility(){};
    void useAbility(Player &p);
    void useAbility(Player &p1, Player &p2, Minion &m);

};




#endif /* actability_h */
