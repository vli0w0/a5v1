//
//  graphicdisplay.hpp
//  CS246
//
//  Created by Yunkun Yang on 2017-12-02.
//  Copyright © 2017 611. All rights reserved.
//

#ifndef graphicdisplay_h
#define graphicdisplay_h

#include <iostream>
#include "observer.h"
#include "subject.h"
#include "ascii_graphics.h"
#include <vector>
#include <string>

class CardType;

class GraphicDisplay: public Observer{
    vector<card_template_t> veccard;
    std::vector<card_template_t> vechand;
public:
    TextDisplay();
    
    void notify(Subject<DInfo, DState> &notifier) override;
    SubscriptionType getSubType() const override;
    void update(Subject<DInfo, DState> &notifier);
    
    ~GraphicDisplay();
    
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif /* graphicdisplay_h */
