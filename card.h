#ifndef card_h
#define card_h

#include <string>
#include "player.h"
#include "pinfo.h"
using namespace std;

class Card {
    
public:
    virtual ~Card() = 0;
    
    // return the card type (Minion, Enchantment, Spell, or Ritual)
    virtual String getType();
    
    // modify the card's ATK and LP value
    virtual modify(int Ach, int Lch);

    friend Player;
    friend PInfo;
    
};


#endif /* card_h */
