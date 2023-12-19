#pragma once

#include <Warcaby/Board/board.h>
#include <Warcaby/Player/player.h>


class Game{
    public:
    // konstruktor
    Game();

    // aktualny stan gry
    GameState gameState;

    // akutalny ruch
    Symbol currentMove;

    // aktualizacja gry, funkcja ta bedzeie sprawdzac czy jest poprawny ruch, jak tak to wywola board.update, jak nie to nie i poprosci jeszcze raz o ruch
    void update();
    
    // funkcja renderujaca, bedzie wywolywana po kazdym update, narazie bedzie wypisywac plansze do cout czy cos
    void render();
    
    
    private:
    Board board;
};