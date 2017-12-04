#ifndef card_h
#define card_h

#include <string>
#include "player.h"
#include "pinfo.h"

class Player;
class PInfo;
class Card {
    
public:
    virtual ~Card() = 0;
    
    // return the card type (Minion, Enchantment, Spell, or Ritual)
    virtual std::string getType();
    
    // modify the card's ATK and LP value
    virtual void modify(int Ach, int Lch);
    virtual void mofifyACT(int mod);
    virtual void updateCardInfo()=0;

    friend Player;
    friend PInfo;
    
};


#endif /* card_h */
