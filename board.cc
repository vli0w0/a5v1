#include "board.h"

Board::Board(Player p):
	plyr{plyr}{}


void Board::gameStart(){
	plyr.gameStart();
}

void Board::initPlay(int i){
	plyr.initPlay(i);
}
