//
//  Cardinfo.hpp
//  CS246
//
//  Created by Yunkun Yang on 2017-12-03.
//  Copyright © 2017 611. All rights reserved.
//

#ifndef Cardinfo_h
#define Cardinfo_h

struct CardInfo {
    std::string type = "";
    std::string name = "";
    int cost = 0;
    std::string desc = "";
    int att = 0;
    int def = 0;
    int ability_cost = 0;
    int ritual_cost = 0;
    int ritual_charges = 0;
    bool withAttDef = 0;
}


#endif /* Cardinfo_h */
