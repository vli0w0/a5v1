#ifndef tinfo_h
#define tinfo_h

#include "tstate.h"


class Player;
class Minion;

struct TInfo {
    PInfo *p1 = nullptr;
    PInfo *p2 = nullptr;
    Minion *m = nullptr;
};


#endif /* tinfo_h */
