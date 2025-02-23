/*
    Egor Shastin st129457@student.spbu.ru
    
*/


#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"


int main() {
    Game game;
    game.setPlayer("Egor");
    game.setBot("Dima", 1);
    game.setChipsAllPlayer(1000);
    game.setDealler();
    game.startGame();
    return 0;
}
