/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"

// -----------------
Game::Game() {}
Game::~Game() {}

void Game::setPlayer(std::string name) { // Creating players. 
    Player player(name);
    players.push_back(player);
}

void Game::setDealler() { // Creating a dealer.
    Dealler diller;
    dealler = diller;
}

int Game::startGame() { // Issuing chips
    for (auto& player : players) {
        player.setChips(1000); 
    }

    dealler.shuffleDeck(); // The dealer shuffles the deck

    for (auto& player : players) { // The dealer deals 2 cards to each player
        dealler.dealCards(2, player);
    }

    for (const auto& player : players) { // Players information
        player.getName();
        player.getChips();
        player.getCardsOnDisplay();
        std::cout << "\n";
    }
    
    std::vector<std::string> Numbers = { "First", "Second", "Third"};

    for (int i = 1; i <= 3; i++){
    
        Card Card = dealler.getOneCard();
        std::cout << "\n" << Numbers[i-1] << " card: ";
        cards.push_back(Card); // Added card on table
        Card.display();

        char act = 'p';
        std::cout << "Your answer (p, c): ";
        std::cin >> act;

        if (act == 'p') {
        
            if (cards.size() > 1) {
                std::cout << "Your lose: " << currentBet << "\n";
            }
            
            std::cout << "New Game? (y, n): ";
            std::cin >> act;
            if (act == 'n') {
                
                std::cout << "End Game";
                return 0;
            }
            else {
                
                std::cout << "New Game";
                return 1;
            }
        } 
        
        if (act == 'c') {
        
            if (i != 3){
            
                std::cout << "Your Chip: ";
                int bet = 0;
                std::cin >> bet;
                currentBet += bet;
                players[0].PlaceBid(bet);
                std::cout << "Left: ";
                players[0].getChips();
            }
        }
    }
    std::vector<int> answer = dealler.SearchWinner(players, cards);
        
    if (answer.size() == 1) {
        for (std::size_t i = 0; i < answer.size(); i++) {
            if (answer[i] != 0) {
                std::cout << "Win player: " << answer[i] << "\n";
                
                char act = 'p';
                std::cout << "New Game? (y, n): ";
                std::cin >> act;
                if (act == 'n') {
                
                    std::cout << "End Game";
                    return 0;
                }
                else {
                
                    std::cout << "New Game";
                    return 1;
                }
            }
        }
    }

    std::cout << "Draw between player: ";
    for (std::size_t i = 0; i < answer.size(); i++) {
        if (answer[i] != 0) {
            std::cout << answer[i] << ", ";
        }
    }
    
    std::cout << "\n";
    
    char act = 'p';
    std::cout << "New Game? (y, n): ";
    std::cin >> act;
    if (act == 'n') {
                
        std::cout << "End Game";
        return 0;
    }
    else {
                
        std::cout << "New Game";
        return 1;
    }  
}
