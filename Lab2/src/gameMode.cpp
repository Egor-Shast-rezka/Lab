/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"

// ---------------
EaggedDeck::EaggedDeck() : Deck() {}

void EaggedDeck::viewNextCard() {
    if (cards.empty()) {
        std::cout << "No cards left in the deck!" << std::endl;
    }
    else {
        Card card = cards.back();
        card.display();
    }
}


// ---------------

