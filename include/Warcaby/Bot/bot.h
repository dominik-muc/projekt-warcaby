#pragma once

#include "Warcaby/Board/board.h"
#include <vector>
#include <utility>

using namespace std;

int pieces_diff(Symbol current_move, Board currentBoard);
int center_control(Symbol current_move, Board currentBoard); // 0 - 4
int last_line_defense(Symbol current_move, Board currentBoard); // 0 - 4
int uncapturable_pieces(Symbol current_move, Board currentBoard); // 0 - 12 
int evaluate(Symbol current_move, Board currentBoard);
pair < bool, Board >  is_move_legal(int xp, int yp, int xk, int yk, Symbol current_move, Board currentBoard, bool captured_before);
vector < Board > legal_moves_generator(Symbol current_move, Board currentBoard);
int min_max(int depth, Symbol current_move, bool isMaximizing, Board currentBoard);

const int INF = 1000000000;

class Bot
{
    public:

    //metoda move zwraca pozycje po ruchu bota
    Board move(Symbol current_move, Board currentBoard);
};