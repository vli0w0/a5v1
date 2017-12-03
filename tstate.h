#ifndef STATE_H
#define STATE_H

/* State (for notifying trigger) types are:
 s -- start of turn. I'm letting you know that now is the beginning of the turn,
 in case you need to fire trigger ability.
 
 f -- end of turn (i.e., fininshing a turn).
 
 e -- a minion enters play.
 
 l -- a minion leaves play.
 
 u -- unsettled state. There is something BAD happening.
 */

enum class TState {s, f, e, l, u};

#endif

