#ifndef __BOARD_H__
#define __BOARD_H__

#include "player.h"

class Board{
	Player plyr;

public:
	Board(Player plyr);
	void gameStart();
	void initPlay(int i);

};

#endif
