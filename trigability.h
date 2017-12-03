#ifndef trigability_h
#define trigability_h

#include "ability.h"
#include "tsubject.h"
#include "observer.h"
#include "tstate.h"
#include "tinfo.h"
#include <string>
#include <iostream>
#include <fstream>

class TrigAbility: public Ability, public Observer<TInfo, TState>{
    
private:
    TState trigType;
  
public:
    TrigAbility(std::istringstream &iss, Card *card);
    ~TrigAbility(){};
    
    TState getType();
    void useAbility(Player &p);
    void useAbility(Player &p1, Player &p2, Minion &m);
    void notify(TSubject<TInfo, TState> &whoFrom);

};

#endif /* trigability_h */
