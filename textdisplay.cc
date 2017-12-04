//
//  TextDisplay.cpp
//  CS246
//
//  Created by Yunkun Yang on 2017-11-29.
//  Copyright © 2017 611. All rights reserved.
//

#include "textdisplay.h"
#include "CardType.h"
#include "iostream"
#include "fstream"
#include "ascii_graphics.h"
#include "SubscriptionType.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "enchantment.h"
#include "DInfo.h"
#include "card.h"
#include <string>
#include "dstate.h"
using namespace std;

TextDisplay::TextDisplay(){
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_EMPTY);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_EMPTY);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_EMPTY);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    veccard.emplace_back(CARD_TEMPLATE_EMPTY);
    veccard.emplace_back(CARD_TEMPLATE_BORDER);
    
    vechand.emplace_back(CARD_TEMPLATE_BORDER);
    vechand.emplace_back(CARD_TEMPLATE_BORDER);
    vechand.emplace_back(CARD_TEMPLATE_BORDER);
    vechand.emplace_back(CARD_TEMPLATE_BORDER);
    vechand.emplace_back(CARD_TEMPLATE_BORDER);
    
}

TextDisplay::~TextDisplay() {}

SubscriptionType TextDisplay::getSubType() const{
    return SubscriptionType::TextOnly;
}


void TextDisplay::update(Subject<DInfo, dstate> &notifier){
    struct DInfo f = notifier.getInfo();
    struct MyInfo* p1 = f.P1;
    struct MyInfo* p2 = f.P2;
    
    
    card_template_t p1card = display_player_card(1,p1->pName,p1->life,p1->mana);
    card_template_t p2card = display_player_card(2,p2->pName,p2->life,p2->mana);
    veccard[17] = p1card;
    veccard[2] = p2card;
    
//// From here, all cards should use field names from different types of cards
    
    
    if(p1->pRitual.type == "Ritual"){
        
        card_template_t p1Ritual = display_ritual(p1->pRitual.name,p1->pRitual.cost,p1->pRitual.ritual_cost,
                                                  p1->pRitual.desc,p1->pRitual.ritual_charges);
        veccard[15] = p2card;
    }
    
    if(p2->pRitual.type == "Ritual"){
        card_template_t p1Ritual = display_ritual(p2->pRitual.name,p2->pRitual.cost,p2->pRitual.ritual_cost,
                                                  p2->pRitual.desc,p2->pRitual.ritual_charges);
        veccard[0] = p2card;
    }
    
    if(p1->pGYard.type == "Minion"){
        card_template_t p1GY = display_minion_activated_ability(p1->pGYard.name,p1->pGYard.cost,
                                                                p1->pGYard.att,p1->pGYard.def,
                                                                    p1->pGYard.ability_cost, p1->pGYard.desc);
        veccard[15] = p1GY;
    }
    
    if(p2->pGYard.type == "Minion"){
        card_template_t p2GY = display_minion_activated_ability(p2->pGYard.name,p2->pGYard.cost,
                                                                p2->pGYard.att,p2->pGYard.def,
                                                                p2->pGYard.ability_cost, p2->pGYard.desc);
        veccard[4] = p2GY;
    }
    
    vector<CardInfo> board1 = p1->pBoard;
    vector<CardInfo> board2 = p2->pBoard;
    
    for (int i = 0; i < board1.size(); i++) {
        string temptype = board1[i].type;
        CardInfo temp = board1[i];
        card_template_t p1temp;
        
        if(temptype == "Minion"){
            
            if(temp.ability_cost != 0){
                p1temp = display_minion_activated_ability(temp.name,temp.cost,temp.att,
                                                                          temp.def, temp.ability_cost, temp.desc);
            }
            else{
                p1temp = display_minion_triggered_ability(temp.name,temp.cost,temp.att,temp.def, temp.desc);
            };
        }
        
        if(temptype == "Spell"){
            p1temp = display_spell(temp.name,temp.cost,temp.desc);
        }
        
        if(temptype == "Enchantment"){
            if(temp.withAttDef){
                p1temp =  display_enchantment_attack_defence(temp.name,temp.cost,temp.desc,to_string(temp.att),to_string(temp.def));
            }
            else {
                p1temp =  display_enchantment(temp.name,temp.cost,temp.desc);
            }
        }
        
        if(temptype == "Ritual"){
            p1temp = display_ritual(temp.name, temp.cost, temp.ritual_cost, temp.desc , temp.ritual_charges);
        }
        
        veccard[10+i]=p1temp;
        vechand[i] = p1temp;
    }
    
    
    for (int i = 0; i < board1.size(); i++) {
        string temptype = board2[i].type;
        CardInfo temp = board2[i];
        card_template_t p2temp;
        
        if(temptype == "Minion"){
            
            
            if(temp.ability_cost != 0){
                p2temp = display_minion_activated_ability(temp.name,temp.cost,temp.att,
                                                          temp.def, temp.ability_cost, temp.desc);
            }
            else{
                p2temp = display_minion_triggered_ability(temp.name,temp.cost,temp.att,temp.def, temp.desc);
            };
        }
        
        if(temptype == "Spell"){
            p2temp = display_spell(temp.name,temp.cost,temp.desc);
        }
        
        if(temptype == "Enchantment"){
            if(temp.withAttDef){
                p2temp =  display_enchantment_attack_defence(temp.name,temp.cost,temp.desc,
                                                             to_string(temp.att),to_string(temp.def));
            }
            else {
                p2temp =  display_enchantment(temp.name,temp.cost,temp.desc);
            }
        }
        
        if(temptype == "Ritual"){
            p2temp = display_ritual(temp.name, temp.cost, temp.ritual_cost, temp.desc , temp.ritual_charges);
        }
        
        veccard[5+i]=p2temp;
    }
};

void TextDisplay::describe(CardInfo m){
    card_template_t boss = display_minion_no_ability(m.name,m.cost,m.att,m.def);
    
    vector<card_template_t> children;
    
    for (int i = 0; i < m.Enchants.size(); i++) {
        card_template_t temp = display_enchantment(m.Enchants[i].name,m.Enchants[i].cost,"");
        children.emplace_back(temp);
    }
    
    // Print Boss Card;
    for (int i = 0; i < boss.size(); i++) {
        cout << boss[i];
        cout << endl;
    }
    
    int size = static_cast<int>(children.size()) + 1;
    int col = size % 5;
    int row = size / 5;
    
    //print first completed rows
    
    for (int j = 0; j < row ; j++) {
        for (int l = 0; l < 11; l++) {
            for (int i = 0; i < 5; i++) {
                cout << children[j * 5 + i][l];
            }
            cout << endl;
        }
    }
    for (int i = 0; i < 11; i ++) {
        for (int j = 0; j < col; j++) {
            cout << children[row*5 + i][j];
        }
        cout << endl;
    }
}
    





void TextDisplay::displayBoard(){
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int j = 0; j<11; j++) {
        cout << "|";
        for (int i = 0; i<5 ; i++) {
            cout << veccard[i][j];
        }
        cout << "|" << endl;
    }
    
    for (int j = 0; j<11; j++) {
        cout << "|";
        for (int i = 5; i<10 ; i++) {
            cout << veccard[i][j];
        }
        cout << "|" << endl;
    }
    
    for (int i=0; i<CENTRE_GRAPHIC.size(); i++) {
        cout << "|";
        cout << CENTRE_GRAPHIC[i];
        cout << "|"<<endl;
    }
    
    for (int j = 0; j<11; j++) {
        cout << "|";
        for (int i = 10; i<15 ; i++) {
            cout << veccard[i][j];
        }
        cout << "|" << endl;
    }
    for (int j = 0; j<11; j++) {
        cout << "|";
        for (int i = 15; i<20 ; i++) {
            cout << veccard[i][j];
        }
        cout << "|" << endl;
    }
}

void TextDisplay::displayHand(){
    for (int j = 0; j<11; j++) {
        cout << "|";
        for (int i = 0; i<5 ; i++) {
            cout << vechand[i][j];
        }
        cout << "|" << endl;
    }
}

void TextDisplay::gameOverNotify(){
        cout << "ERGAMEE    RGA    OVERGAMEEEVV  GAMEEOV       OVERGAM  OO    GA    OVERGA  E OVERG" << endl;
        cout << "OVERGAM    VER    EEOVERGAEEOO  ERGAME        EEOVERG  ME    ER   ME OVE   AME OVE" << endl;
        cout << "EE         COV    AM   VE   ME  OV            AM   VE  AM    OV   GA       RG    O" << endl;
        cout << "AM         MEOO   RG   OO   GA  EE            RG    O   RG  ME    ER       VE   ME" << endl;
        cout << "RG  EOO   RGAME   VE   ME   ER  AMEOV         VE   ME   VE  GA    OVERGA   OERGA" << endl;
        cout << "VE  AME   VE GA   OO   GA   OV  RGAME         OO   GA   EE  ER    E OVER   ME OVER" << endl;
        cout << "OO   GA   O  ER   ME   ER   EE  VE            ME   ER    E  O     AM       GA   O" << endl;
        cout << "ME   ER   ME  VE  GA   OV   AM  EO            GA   OV    A  E     RG       ER   ME" << endl;
        cout << "GAME OV  RGA  EO  ER   EE   RG  MEEOVER       ERGAMEE    RRAA     VERGAME  OV   GA" << endl;
        cout << "ERGAMEE  VER  ME  OV   AM   VE  GAMEEOE       OVERGAM     ER       OVERG   E     RG" << endl << endl;
}

void TextDisplay::displayHelp(){
    cout << "         |--------------------------------------------|" << endl;
    cout << "         | Help:                                      |" << endl;
    cout << "         |   help -- Display this message.            |" << endl;
    cout << "         |   end -- End the current player's turn.    |" << endl;
    cout << "         |   quit -- End the game.                    |" << endl;
    cout << "         |   attack minion other-minion --            |"<<endl;
    cout << "         |Orders minion to attack other-minion.       |"<< endl;
    cout << "         |   attack minion -- Orders minion to        |"<<endl;
    cout <<"          |attack the opponent.                        |"<< endl;
    cout << "         |   play card [target-player target-card]    |"<<endl;
    cout << "         |-- Play card,optionally targeting           |"<<endl;
    cout << "         |    target-card owned by target-player.     |"<<endl;
    cout << "         |    use minion [target-player target-card]  |"<<endl;
    cout << "         |-- Use minion's special ability, optionally |"<<endl;
    cout << "         |targeting target-card owned by              |"<<endl;
    cout << "         |target-player.                              |"<<endl;
    cout << "         |   inspect minion -- View a minion's card   |"<<endl;
    cout << "         |   and all enchantments on that minion.     |" << endl;
    cout << "         |   hand -- Describe all cards in your hand. |" << endl;
    cout << "         |   board -- Describe all cards on the board.|" << endl;
    cout << "         |--------------------------------------------|" << endl << endl;
}



/// Need to change to display board and hand
ostream &operator<<(ostream &out, const TextDisplay &td){
    out << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for(int i = 0; i < 66; ++i){
        out << "|";
        for(int j = 0; j < 165; ++j){
            // print ActRituals/PlayerInfo/GY1/Hands*2
        }
        out << "|" << endl;
    }
    for(int i = 0; i < 11; ++i){
        out << "|";
        for(int j = 0; j < 165; ++j){
            // out The game name, see BasicMap <<
        }
        out << "|" << endl;
    }
    for(int i = 0; i < 66; ++i){
        out << "|";
        for(int j = 0; j < 165; ++j){
            // print ActRituals/PlayerInfo/GY1/Hands*2
        }
        out << "|" << endl;
    }
    out << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    return out;
}
