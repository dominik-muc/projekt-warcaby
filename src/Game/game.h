#include "./Board/board.h"
#include "./Player/player.h"

/*
Tylko funkcja Game ma mieć bezpośredni dostęp do klasy Board, inne funkcje
dostają tylko tablicę intów.
*/
class Game{
    public:
    //Player jest abstrakcyjny więc prawdopodobnie trzeba to jakoś castować idk
    Game(Player player_one, Player player_two);
    GameState nextMove();
    BoardArray getBoardState();
    private:
    Board board;
};