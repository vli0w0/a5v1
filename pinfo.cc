#include "pinfo.h"
using namespace std;

PInfo::PInfo(string name,vector<Card *> v; deck,int LP,int magic):
name{name},deck{deck},LP{LP},magic{magic}{}

MyInfo PInfo::getMyInfo(){
	return res{name,LP,magic,hand,board,GYard.back(),ritual};
}

bool PInfo::dead(){
	if (LP>0) return true;
	else return false;
}

void PInfo::toGYard(int i){
	Card *tmp = board[i];
	board.erase(i);
	GYard.push_back(tmp);	
}

bool PInfo::mDead(int i){
	if (board[i-1]->dead()) return true;
	else return false;
}

void PInfo::draw(){
	if (hand.size()<5){
		random_shuffle(deck.begin(),deck.end());
		tmp = deck.begin();
		Card *replace = new(*tmp);
		hand.push_back(tmp);
		deck.push_back(replace);
	}
}

vector<Card *> &PInfo::getGYard(){
	return &(GYard);
}

void PInfo::setMagic(int mana){
	magic = mana;
}

int &PInfo::getMagic(){
	return magic;
}

void PInfo::changeLP(int k){
	LP += k;
}

int PInfo::handSize(){
	retrun hand.size();
}

vector<Card *> &PInfo::getHand(){
	return &(hand);
}

vector<Card *> &PInfo::getBoard(){
	return &board;
}

Card *getRitual(){
	return ritual;
}

void setRitual(Card *c){
	Card *tmp = ritual;
	ritual = c;
	delete tmp;
}

bool PInfo::boardFull(){
	if (board.size()>=5) return true;
	else return false;
}

bool PInfo::handFull(){
	if (hand.size()>=5) return true;
	else return false;
}

bool PInfo::gYardEmpty(){
	if (GYard == nullptr || GYard.size()==0) return true;
	return false;
}

void PInfo::play(int i,PInfo &p,int j){
	int truei = i-1;
	int truej = j-1;
	if (i>5 || i<1) return;
	if (j==0){
		string type = hand[truei]->getType();
		if (type == "Ritual"){
			Card *tmp = ritual;
			ritual = hand.begin()+truei;
			delete tmp;
			hand.erase(hand.begin()+truei);
		}
		if (type == "Minion"){
			if (handSize()<5){
				board.push_back(hand.begin()+truei);
				hand.erase(hand.begin()+truei);
			}
		}
		if (type == "Spell"){
			hand[truei]->play(&(*this),p);
			Card *tmp = hand.begin()+truei;
			hand[truei]=nullptr;
			delete tmp;
			hand.erase(hand.begin()+truei);
		}
	}
	else{
		if (type == "Enchantment"){
			hand[truei]->play(p.getBoard()[truej]);
			Card *tmp = hand.begin()+truei;
			hand[truei]=nullptr;
			delete tmp;
			hand.erase(hand.begin()+truei);
		}
		if (type == "Spell"){
			if (j+'0' == 'r'){
				hand[truei]->use(&(*this),p,true);
			}
			else if (j<=5 && j>=1){}
				hand[truei]->play(&(*this),p,truej);
		}
	}

}

void PInfo::attack(int i,PInfo &p,int j){
	int truei = i-1;
	int truej = j-1;
	int card1ATK = board[truei].ATK;
	int card1LP = board[truei].LP;

	if (j==0){
		p.changeLP(-card1ATK);
		return;
	}

	int card2ATK = p.getBoard()[truej].ATK;
	int card2LP = p.getBoard()[truej].LP;

	p.getBoard()[truej].modify(-card1ATK,-card1LP);
	board[truei].modify(-card2ATK,-card2LP);
}

void PInfo::use(int i,PInfo &p,int j){
	if (i<1 || i>5 || j<1 || j>5) return;
	int truei=i-1;
	int truej=j-1;
	if (board[truei].getType() != "Minion" || !board[truei].canUseAbl()) return;
	if (j==0){
		board[truei].useAbility(&p);
	}
	else{
		board[truei].useAbility(&(*this),p,&(*p->getBoard()[truej]))}
}
