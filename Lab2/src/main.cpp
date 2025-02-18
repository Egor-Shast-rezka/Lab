/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"


int main() {
    Game game;
    game.setPlayer("Egor");
    game.setPlayer("Dima");
    game.setPlayer("Vova");
    game.setPlayer("Misha");
    game.setDealler();
    while(game.startGame() == 1) {
    	std::cout << "\n";
    }
    return 0;
}
