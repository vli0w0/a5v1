#include "iohandler.h"
#include "pinfo.h"
#include "player.h"
#include "board.h"
#include <fstream>
using namespace std;

#ifdef EASTEREGG
vector<string> badWords = {"fuck","dick","java","asshole"};
bool EAon = true;
#endif


int main(int argc,char *argv[]){
	TEST = IOHandler::check(argc-1,&argv[1],"-testing");
	GRAPHIC = IOHandler::check(argc-1,&argv[1],"-graphics");


	string pInit = IOHandler::returnNString(argc-1,&argv[1],"-init");
	if (pInit == "") pInit = "default.player";

	string P1name;
	string P2name;
	int P1playloop=0;
	IOHandler::constructInfo(pInit,&P1name,&P2name,&P1playloop);

	/*EASTER EGG, will be pushed to another module
	if (EAon){
		for (auto p:badWords){
			if (P1name.find(p) != string::npos){
				cout << "Player 1, very funny. "
				cout << "You are not naming yourself " << P1name << endl;
				cout << "Your name has been set to \"Player 1\""<< endl;
			}
			if (P2name.find(p) != string::npos){
				cout << "Player 2, very funny. "
				cout << "You are not naming yourself " << P2name << endl;
				cout << "Your name has been set to \"Player 2\""<< endl;
			}
		}
	}
	EASTER EGG END*/

	vector<Card *> p1Deck;
	vector<Card *> p2Deck;
	string p1DName = IOHandler::returnNString(argc-1,&argv[1],"-deck1");
	string p2DName = IOHandler::returnNString(argc-1,&argv[1],"-deck2");
	p1Deck = IOHandler::makeDeck(p1DName);
	p2Deck = IOHandler::makeDeck(p2DName);

	PInfo P1 {P1name,p1Deck};
	PInfo P2 {P2name,p2Deck};
	Player p {P1,P2};
	Board game {p};
	game.initPlay(P1playloop);
	game.gameStart();


}
