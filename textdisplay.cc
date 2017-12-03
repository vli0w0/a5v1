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


void TextDisplay::update(Subject<DInfo, State> &notifier){
    struct DInfo f = notifier.getInfo();
    struct MyInfo p1 = f.p1;
    struct MyInfo p2 = f.p2;
    
    
    card_template_t p1card = display_player_card(1,p1.pName,p1.life,p1.mana);
    card_template_t p2card = display_player_card(2,p2.pName,p2.life,p2.mana);
    veccard[17] = p1card;
    veccard[2] = p2card;
    
//// From here, all cards should use field names from different types of cards
    
    
    if(!p1.pRitual){
        card_template_t p1Ritual = display_ritual(p1.pRitual->name,p1.pRitual->cost,p1.pRitual->ablCost;
                                                  p1.pRitual->description,p1.pRitual->charge;
                                                  );
        veccard[15] = p2card;
    }
    
    if(!p2.pRitual){
        card_template_t p1Ritual = display_ritual(p2.pRitual->name,p2.pRitual->cost,p2.pRitual->ablCost;
                                                  p2.pRitual->description,p2.pRitual->charge;
                                                  )
        veccard[0] = p2card;
    }
    
    if(!p1.pGYard){
        card_template_t p1GY = display_minion_activated_ability(p1.pGYard->name,p1.pGYard->cost,
                                                                p1.pGYard->ATK,p1.pGYard->LP,
                                                                    p1.pGYard->abilityCost, p1.pGYard->description);
        veccard[15] = p1GY;
    }
    
    if(p2.pGYard){
        card_template_t p2GY = display_minion_activated_ability(p2.pGYard->name,p2.pGYard->cost,
                                                                p2.pGYard->ATK,p2.pGYard->LP,
                                                                p2.pGYard->abilityCost, p2.pGYard->description);
        veccard[4] = p2GY;
    }
    
    CardStack board1 = p1.pBoard;
    CardStack board2 = p2.pBoard;
    
    for (int i = 0; i < board1.size(); i++) {
        CardType temptype = board1[i]->getType();
        
        if(temptype == CardType::Minion){
            CardType temp = CardType::Minion;
            temp = board1[i];
            
            if(temp->silence){
                card_template_t p1temp = display_minion_activated_ability(temp->name,temp->cost,temp->ATK,
                                                                          temp->LP, temp->abilityCost, temp->description);
            }
            else{
                card_template_t p1temp = display_minion_activated_ability(temp->name,temp->cost,
                                                                          temp->ATK,temp->LP, temp->description)
            }
        }
        
        if(temptype == CardType::Spell){
            CardType temp = CardType::Spell;
            temp = board1[i];
            card_template_t p1temp = display_spell(temp->name,temp->cost,temp->description);
        }
        
        if(temptype == CardType::Enchantment){
            CardType temp = CardType::Enchantment;
            temp = board1[i];
            
            if(temp->withATKDef){
                card_template_t p1temp =  display_enchantment_attack_defence(temp->name,temp->cost,temp->desc,
                                                                             temp->ATK,temp->DEF);
            }
            else {
                card_template_t p1temp =  display_enchantment(temp->name,temp->cost,temp->desc);
            }
        }
        
        /// RITUAL COST!!!
        if(temptype == CardType::Ritual){
            CardType temp = CardType::Ritual;
            temp = board1[i];
            
            card_template_t p1temp = display_ritual(temp->name, temp->Cost, temp->ablCost, temp->description , temp->charges);
        }
        veccard[10+i]=p1temp;
        veccard[i] = p1temp;
    }
    
    
    for (int i = 0; i < board2.size(); i++) {
        CardType temptype = board2[i] -> type;
        
        if(temptype == CardType::Minion){
            
            CardType temp = CardType::Minion;
            temp = board2[i];
            
            if(temp->silence){
                card_template_t p2temp = display_minion_activated_ability(temp->name,temp->cost,temp->ATK,
                                                                          temp->LP, temp->abilityCost, temp->description);
            }
            else{
                card_template_t p2temp = display_minion_activated_ability(temp->name,temp->cost,
                                                                          temp->ATK,temp->LP, temp->description);
            }
        }
        
        if(temptype == CardType::Spell){
            CardType temp = CardType::Spell;
            temp = board2[i];
            card_template_t p2temp = display_spell(temp->name,temp->cost,temp->description);
        }
        
        if(temptype == GridCardType::Enchantment){
            CardType temp = CardType::Enchantment;
            temp = board2[i];
            if(temp->attack_defence){
                card_template_t p2temp =  display_enchantment_attack_defence(temp->name,temp->cost,temp->desc,
                                                                             temp->ATK,temp->DEF);
            }
            else {
                card_template_t p2temp =  display_enchantment(temp->name,temp->cost,temp->desc);
            }
        }
        
        /// RITUAL COST!!!
        if(temptype == GridCardType::Ritual){
            CardType temp = CardType::Ritual;
            temp = board2[i];
            card_template_t p2temp = display_ritual(temp->name, temp->Cost, temp->ablCost, temp->description , temp->charges);
        }
        veccard[5+i]=p2temp;
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

void TextDisplay::displayHelp(){
    cout << "         |--------------------------------------------|" << endl;
    cout << "         | Help:                                      |" << endl;
    cout << "         |   help -- Display this message.            |" << endl;
    cout << "         |   end -- End the current player's turn.    |" << endl;
    cout << "         |   quit -- End the game.                    |" << endl;
    cout << "         |   attack minion other-minion --            |"<<endl
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
