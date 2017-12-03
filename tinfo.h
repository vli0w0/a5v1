#ifndef tinfo_h
#define tinfo_h

#include "tstate.h"


class Player;
class Minion;

struct TInfo {
    Player *p1;
    Player *p2;
    Minion *m;
};


#endif /* tinfo_h */
