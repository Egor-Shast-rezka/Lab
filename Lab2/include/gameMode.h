/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <algorithm> // Just for shuffle
#include <random>
#include <cstring>
#include <cmath>

#ifndef GAMEMODE_H
#define GAMEMODE_H

class EaggedDeck : public Deck {
public:
    EaggedDeck();
    
    void viewNextCard();
};

#endif
