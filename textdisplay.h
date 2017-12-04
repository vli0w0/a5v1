//
//  TextDisplay.hpp
//  CS246
//
//  Created by Yunkun Yang on 2017-11-29.
//  Copyright © 2017 611. All rights reserved.
//

#ifndef TextDisplay_h
#define TextDisplay_h

#include <iostream>
#include "observer.h"
#include "subject.h"
#include "ascii_graphics.h"
#include "SubscriptionType.h"
#include "dstate.h"
#include <vector>
#include <string>

class CardType;

class TextDisplay: public Observer{
    std::vector<card_template_t> veccard;
    std::vector<card_template_t> vechand;
public:
    TextDisplay();
    
    void notify(Subject<DInfo, DState> &notifier) override;
    void update(Subject<DInfo, DState> &notifier);
    DState getSubType() const;
    void displayHelp();
    void displayBoard();
    void displayHand();
    void gameOverNotify();
    void describe();
    
    ~TextDisplay();
    
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif /* TextDisplay_h */


