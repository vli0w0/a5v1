#include "player.h"
#include <string>
using namespace std;

extern bool TEST;
extern bool Graphics;

int MAGIC_START = 3;
const int MAX_B_LEN = 5;

Player::Player(PInfo p1,PInfo p2){
    p[0] = p1;
    p[1] = p2;
	if (Graphics) gd = nullptr;
}

TInfo Player::getTInfo(){
	return tInfo;
}


void Player::pSwitch(){
	active = (active+1)%2;
	inactive = (inactive+1)%2;
}

bool Player::checkDead(PInfo &atkr,PInfo &dfdr){
	if (dfdr.dead()){
        winner = &atkr;
		gameOver=true;
		return true;
	}
}

void Player::checkMDead(PInfo &atkr,int aindx,PInfo &dfdr,int dindx){
	if (atkr.mDead(aindx-1)){
		atkr.getBoard()[aindx-1]->disenchantA();
		atkr.toGYard(aindx-1);
		/*minionLeaveNotify(); NOTIFY FUNCTION*/
		setTState(TState::l);
        tInfo = TInfo{*atkr,*atkr,atkr.getGYard().back()};
		notifyTObservers();
	}
	if (dfdr.mDead(dindx-1) && &atkr != &dfdr){
		dfdr.getBoard()[dindx-1]->disenchantA();
		dfdr.toGYard(dindx-1);
		/*minionLeaveNotify(); NOTIFY FUNCTION*/
		setTState(TState::l);
		tInfo = TInfo{*atkr,*dfdr,dfdr.getGYard().back()};
		notifyTObservers();
	}
}

void Player::notifyObservers(){
	td->update();
	gd->update();

	/*
	td->display();
	gd->display();
	*/
}

void Player::modifyMagic(PInfo &p, int ch){
	p.setMagic(ch);
}

vector <Card *> Player::getAllMinion(PInfo &pif){
	vector<Card *> v;
	vector<Card *> board=p.getBoard();
    for (auto p:board){
		if (p->getType()=="Minion"){
			v.emplace_back(p);
		}
	}
	return v;
}

void Player::initPlay(int i){
	int indx = 0;
	while (indx<i){
		p[active].play(p[active].getHand()[indx]);
	}
}

void Player::playCard(string CardName){
	Card *mCard = new Minion(CardName);
	p[active].play(mCard);
}

int Player::getMagic(){
	return p[active].getMagic();
}

void Player::gameStart(){
	while(true){
		p[active].setMagic(MAGIC_START);
		if (p[active].handSize() < 5){
			(p[active].getHand()).draw();
		}
		/*startOfTurnNotify(); NOTIFY FUNCTION */
        setTState( TState::s );
		tInfo = TInfo{&p[active],nullptr,nullptr};
		notifyTObservers();

		unique_ptr<Holder> cmd;

		int magic = p[active].getMagic();
		while (magic>0){
			cmd = IOHandler::stdio();
			string pIn = cmd->input;
			vector<int> pPos = cmd->pos;
			Card *curr = p[active].getBoard()[pPos[0]-'0'];
			if (pIn == "play"){
				if (pPos.size()==1){
					p[active].play(pPos[0]-'0',&p[inactive]);
					if ((p[active].getBoard().back())->getType()=="Minion"){
						/*minionEnterNotify() NOTIFY FUNCTION*/
						setTState(TState::e);
						tInfo = TInfo{&p[active],&p[active],p[active].getBoard().back()}
						notifyTObservers();
					} 
					if (checkDead(&p[active],&p[inactive])) break;
				}
				else if (pPos.size()==3 && (pPos[1]-'0' == 1 || pPos[1]-'0' ==2)){
					p[active].play(pPos[0]-'0',p[pPos[1]-1-'0'],pPos[2]-'0');
					checkMDead(&p[active],pPos[0]-'0',&p[pPos[1]-1-'0'],pPos[2]-'0');
					/*HARRIS' NOTIFY FUNCTION FOR MINION DAMAGE OR DEATH*/
				}
			}
			else if (pIn == "attack"){
				if (pPos.size()==1 && curr->getType()== "Minion" && curr->acting()){
					p[active].attack(pPos[0]-'0',&p[inactive]);
					if (checkDead(&p[active],&p[inactive])) break;
					/*HARRIS' NOTIFY FUNCTION FOR PLAYER DAMAGE*/
				}
				else if (pPos.size()==2 && curr->getType()== "Minion" && curr->acting()){
					p[active].attack(pPos[0]-'0',&p[inactive],pPos[1]-'0');
					checkMDead(&p[active],pPos[0]-'0',&p[inactive],pPos[1]-'0');
					/*HARRIS' NOTIFY FUNCTION FOR MINION DAMAGE OR DEATH*/
				}
				curr->modifyAct(-1);
			}
			else if (pIn == "discard"){
				if (pPos.size()=1 && TEST){
					active->getHand().erase(p[active]->getHand().begin()+pPos[0]-1-'0');
					/*HARRIS' NOTIFY FUNCTION FOR PLAYER DAMAGE*/
				}
			}
			else if (pIn == "use"){
				if (pPos.size()==1 && curr->getType()== "Minion" && curr->acting() && magic-curr.abilityCost<0 && TEST){
					p[active].use(pPos[0]-'0',&p[inactive]);
					if (checkDead(&p[active],&p[inactive])) break;
					/*HARRIS' NOTIFY FUNCTION FOR PLAYER DAMAGE*/
					magic = 0;
				}
				else if (pPos.size()==3 && pPos[1]-'0'<=1 && curr->getType()== "Minion" && curr->acting() && magic-curr.abilityCost<0 && TEST){
					p[active].use(pPos[0]-'0',p[pPos[1]-1-'0'],pPos[2]-'0');
					checkMDead(&p[active],pPos[0]-'0',&p[pPos[1]-1-'0'],pPos[2]-'0');
					/*HARRIS' NOTIFY FUNCTION FOR MINION DAMAGE OR DEATH*/
					magic = 0;
				}
				else if (pPos.size()==1 && curr->getType()== "Minion" && curr->acting() && curr.abilityCost <= magic){
					p[active].use(pPos[0]-'0',&p[inactive]);
					if (checkDead(&p[active],&p[inactive])) break;
					/*HARRIS' NOTIFY FUNCTION FOR PLAYER DAMAGE*/
					magic -= curr.abilityCost;
					}
				else if (pPos.size()==3 && pPos[1]-'0'<=1 && curr->getType()== "Minion" && curr->acting() && curr.abilityCost <= magic){
					p[active].use(pPos[0]-'0',p[pPos[1]-1-'0'],pPos[2]-'0');
					checkMDead(&p[active],pPos[0]-'0',&p[pPos[1]-1-'0'],pPos[2]-'0');
					/*HARRIS' NOTIFY FUNCTION FOR MINION DAMAGE OR DEATH*/
					magic -= curr.abilityCost;
				}
				curr->modifyAct(-1);
	
			}
			else if (pIn == "inspect"){
				if (pPos.size()=1){
					p[active].getHand()[pPos[0]-1-'0'].describe();
				}
			}
			else if (pIn == "board"){
				td->displayBoard(); 
				//need the board to be displayed on console
			}
			else if (pIn == "hand"){
				td->displayHand();
			}
			else if (pIn == "help"){
				td->displayHelp();
			}
			else if (pIn == "quit"){
				gameOver=true;
				break;
			}
			else if (pIn == "end") break;
			else if (pIn == "draw" && TEST){
				p[active].draw();
				/*HARRIS' NOTIFY FUNCTION FOR PLAYER DAMAGE*/
			}

		}
		for (auto p:active.getBoard()){
			if (p.getType() == "Minion"){
				p.setAC();
			}
		}

		for (int i=0;i<MAX_B_LEN;++i){
			if (active.mDead[i]) active.toGYard(i);
			if (inactive.mDead[i]) inactive.toGYard(i);
		}
		
		/*EndOdTurnNotify(); NOTIFY FUNCTION */
		setTState(TState::f);
		tInfo = TInfo{&p[active],nullptr,nullptr};
		notifyTObservers();

		if (gameOver) break;
		pSwitch();
		magic = p[active].getMagic();
	}
	td->gameOverNotify();
	if (gd) gd->gameOverNotify();
}
