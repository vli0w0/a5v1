#include "iohandler.h"
#include <fstream>
using namespace std;

unique_ptr<Holder> IOHandler::stdio(istream in){
	make_unique<Holder> hldr;
	string cmd;
	in>>cmd;
	hldr->info=cmd;

	char pos;
	while (in>>pos){
		(hldr->pos).emplace_back(pos);
	}
	in.clear();
	return hldr;
}

string IOHandler::fileRead(string name){
	ifstream file;
	file.open(name+".card");
	string line;
	string fileInfo = "";
	while (getline(file,line)){
		fileInfo += line;
		fileInfo += '\n';
		line.clear();
	}
	return string{fileInfo};
}

vector<Card *> IOHandler::makeDeck(string name){
	ifstream file;
	file.open(name);

	string line;
	ifsream cFile;
	string cLine;

	vector<Card *> v;
	while (getline(file,line)){
		cFile.open(line+".card");
		getline(cFile,cLine);
		if (cLine == "Enchantment"){
			v.emplace_back(new Enchantment(line));
		}
		else if (cLine == "Minion"){
			v.emplace_back(new Minion(line));
		}
		else if (cLine == "Ritual"){
			v.emplace_back(new Ritual(line));
		}
		else if (cLine == "Spell"){
			v.emplace_back(new Spell(line));
		}
		cFile.close();
	}
}

bool IOHandler::check(int length,char *cmds[],std::string check){
	for (int i=0;i<length;++i){
		if (cmds[i] == check) return true;
	}
	return false;
}

string IOHandler::returnNString(int length,char *cmds[],string check){
	for (int i=0;i<length-1;++i){
		if (cmd[i]==check){
			return cmd[i+1];
		}
	}
	else return "";
}

void IOHandler::constructInfo(string fName,string &p1,std::string &p2,int &looping){
	ifstream file;
	file.open(fName);
	getline(file,p1);
	getline(file,p2);

	string loopCond;
	while(getline(file,loopCond)){
		if (loopCond=="play 1"){
			++looping;
		}
	}
}
