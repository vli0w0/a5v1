#ifndef tinfo_h
#define tinfo_h

#include "tstate.h"


class Player;
class Minion;

struct TInfo {
    Player *p1 = nullptr;
    Player *p2 = nullptr;
    Minion *m = nullptr;
};


#endif /* tinfo_h */
