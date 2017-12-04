#ifndef tinfo_h
#define tinfo_h

#include "tstate.h"


class Player;
class Minion;

struct TInfo {
    PInfo *p1 = nullptr;
    PInfo *p2 = nullptr;
    Card *m = nullptr;       //Minion
};


#endif /* tinfo_h */
