/*
    Egor Shastin st129457@student.spbu.ru
    
*/

#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"
#include "characters.h"
#include "gameMode.h"

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

void Game::setBot(std::string name, int index) {
    if (index == 1) {
        AIPlayer_easy bot(name);
        players.push_back(bot);
    }
    else if (index == 2) {
        AIPlayer_normal bot(name);
        players.push_back(bot);
    }
    else if (index == 3) {
        AIPlayer_hard bot(name);
        players.push_back(bot);
    }
}

void Game::resetGame() {
    cards.clear();
    dealler.newDeck();
    dealler.shuffleDeck();
    currentBet = 0;
    for (auto& player : players) {
        player.delAllCards();
    }
    std::cout << "\n";
}

bool Game::checkContinueGame() {
    char act;
    std::cout << "Do you want to continue the game? (y/n): ";
    std::cin >> act;
    return act == 'y';
}

void Game::setChipsAllPlayer(int count) {
    for (auto& player : players) {
        player.setChips(count);
    }
}

int Game::startGame() {
    do {
        //bool Allin = false;
        dealler.shuffleDeck();

        for (auto& player : players) {
            dealler.dealCards(2, player);
        }

        for (auto& player : players) {
            player.getName();
            player.getChipsOnDisplay();
            if (!player.isBot()) {
                player.getCardsOnDisplay();
            }
            std::cout << "\n";
        }

        std::vector<std::string> Numbers = { "First", "Second", "Third" };

        for (int i = 1; i <= 3; i++) {
            Card card = dealler.getOneCard();
            cards.push_back(card);

            std::cout << "\n" << Numbers[i - 1] << " card: ";
            card.display();

            for (auto& player : players) {
                if (player.isBot()) {
                    int new_currentBet = player.chipRandom(player.getChips(), currentBet);
                    player.getName();
                    if (new_currentBet == player.getChips()) {
                        std::cout << "Allin!" << "\n";
                        //Allin = true;
                    }
                    else {
                        std::cout << "Make Bet: " << new_currentBet - currentBet << "\n";
                        currentBet = new_currentBet;
                        std::cout << "Current Bet: " << currentBet << "\n";
                    }
                }
                else {
                    char act = 'p';
                    std::cout << "Your answer (p - pass, c - call): ";
                    std::cin >> act;

                    if (act == 'p') {
                        player.getName();
                        std::cout << "Player passed.\n";
                    }
                    else if (act == 'c') {
                        int bet = 0;
                        std::cout << "Your bet: ";
                        std::cin >> bet;

                        currentBet += bet;
                        player.PlaceBid(bet);
                        player.getChipsOnDisplay();
                    }
                }
            }
        }

        std::vector<int> answer = dealler.SearchWinner(players, cards);

        if (answer.size() == 1) {
            std::cout << "Player " << answer[0] << " wins!\n";
        }
        else {
            std::cout << "Draw between players: ";
            for (const auto& winner : answer) {
                std::cout << winner << " ";
            }
            std::cout << "\n";
        }

        resetGame();

    } while (checkContinueGame());

    std::cout << "Game over!\n";
    return 0;
}


