#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "board.h"
#include "dinfo.h"
#include "myinfo.h"
#include "iohandler.h"
#include "subject.h"
#include "tsubject.h"
#include "tinfo.h"
#include "tstate.h"
#include "pinfo.h"
#include "card.h"
#include "dstate.h"
#include "textdisplay.h"
#include "graphicdisplay.h"

class PInfo;
class Player: public Subject<DInfo, DState>, public TSubject<TInfo, TState> {
	TInfo tInfo;

	std::vector<PInfo> p;
	int active = 0;
	int inactive = 1;

	PInfo *winner=nullptr;
	bool gameOver=false;

	TextDisplay *td;
	GraphicDisplay *gd;

	void gameStart();

protected:
	void pSwitch();
	bool checkDead(PInfo &atkr,PInfo &dfdr);
	void checkMDead(PInfo &atkr,int aindx,PInfo &dfdr,int dindx);
	void notifyObservers();

public:
	Player(PInfo p1,PInfo p2);
	~Player()=default;
	TInfo getTInfo();
	void playCard(std::string CardName);

	void modifyMagic(PInfo &p,int ch);
	std::vector<Card *> getAllMinion();
	int getMagic();
	void initPlay(int i);

	friend Board;
};

#endif
