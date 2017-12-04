#ifndef __IOHANDLER_H__
#define __IOHANDLER_H__

#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
#include "pinfo.h"
#include "enchantment.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"


struct Holder{
	std::string input;
	std::vector<char> pos;
};

class IOHandler{
public:
	static std::unique_ptr<Holder> stdio(std::istream in=std::cin);
	static std::string fileRead(std::string name);
	static std::vector<Card *> makeDeck(std::string name="default.deck");
	static bool check(int length,char *cmds[],std::string check);
	static std::string returnNString(int length,char *cmds[],std::string check);
	static void constructInfo(std::string fName,std::string &p1,std::string &p2,int &looping);
};

#endif
