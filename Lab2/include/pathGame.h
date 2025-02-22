/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include <iostream>
#include <vector>
#include <algorithm> // Just for shuffle
#include <random>
#include <cstring>
#include <cmath>

#ifndef PATHGAME_H
#define PATHGAME_H

class Game {
private:
    std::vector<Player> players; // List of players
    std::vector<Card> cards; // List of cards on the table
    Dealler dealler; // Dealer at the table
    int currentBet; // Current rate

public:

    Game();
    ~Game();

    void setPlayer(std::string name);  // Creating players. 
    
    void setBot(std::string name, int index);
    
    void setDealler();  // Creating a dealer.
    
    void resetGame();
    
    bool checkContinueGame();
    
    void setChipsAllPlayer(int count);
    
    int startGame();  // Issuing chips
};

#endif
