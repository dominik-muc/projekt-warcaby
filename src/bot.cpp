#include "Warcaby/Bot/bot.h"
#include "Warcaby/Game/game.h"

int pieces_diff(Symbol current_move, Board currentBoard)
{
    //pieces_diff() - ocenia bilans bierek na planszy [relatywny]
    
    int white_pawns = 0;
    int black_pawns = 0;
    int white_kings = 0;
    int black_kings = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(currentBoard.board[i][j] == 1) white_pawns++;
            else if(currentBoard.board[i][j] == 2) black_pawns++;
            else if(currentBoard.board[i][j] == 3) white_kings++;
            else if(currentBoard.board[i][j] == 4) black_kings++;
        }
    }

    int pawn_value = 1;
    int king_value = 2;
    int material_balans = (white_pawns - black_pawns) * pawn_value + (white_kings - black_kings) * king_value;

    return material_balans;
}

int center_control(Symbol current_move, Board currentBoard)
{
    //center_control() oblicza # figur danego koloru znajdujących się w 8 centralnych polach [nierelatywny]

    int center_control = 0;

    if(current_move == SYMBOL_WHITE)
    {
        for(int i = 3; i <= 4; i++)
        {
            for(int j = 2; j <= 5; j++)
            {
                if(currentBoard.board[i][j] == 1 || currentBoard.board[i][j] == 3)
                {
                    center_control++;
                }
            }
        }
    }
    else
    {
        for(int i = 3; i <= 4; i++)
        {
            for(int j = 2; j <= 5; j++)
            {
                if(currentBoard.board[i][j] == 2 || currentBoard.board[i][j] == 4)
                {
                    center_control++;
                }
            }
        }
    }

    return center_control;
}

int last_line_defense(Symbol current_move, Board currentBoard)
{
    //last_line_defense() oblicza # bronionych pól w ostatniej lini [nierelatywny]

    int last_line = 0;
    
    if(current_move == SYMBOL_WHITE)
    {
        // setups - wszystkie możliwe ustawienia pionków w ostatniej linii
        int setups[16][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0},
            {1, 0, 1, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 1, 0},
            {1, 0, 0, 0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1, 0, 1, 0}
        };
        
        // defended_squares - ilość bronionych pól odpowiednio dla każdego setupu 
        int defended_squares[16] = {0, 1, 2, 1, 1, 2, 3, 2, 3, 4, 2, 3, 4, 4, 4, 4};

        int cnt;
        for(int i = 0; i < 16; i++)
        {
            cnt = 0;
            for(int j = 0; j < 8; j++)
            {
                // uwzgledniamy ze bialy hetman tez moze bronic ostatniej linii
                if(currentBoard.board[7][j] == setups[i][j]  || currentBoard.board[7][j] == 3)
                {
                    cnt++;
                }
            }
            if(cnt == 8)
            {
                last_line = defended_squares[i];
                return last_line;
            }
        }
    }
    else
    {
        // setups - wszystkie możliwe ustawienia czarnych pionków w ostatniej linii
        int setups[16][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 2},
            {0, 2, 0, 2, 0, 0, 0, 0},
            {0, 2, 0, 0, 0, 2, 0, 0},
            {0, 2, 0, 0, 0, 0, 0, 2},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 2, 0, 0, 0, 2},
            {0, 0, 0, 0, 0, 2, 0, 2},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 2, 0, 2, 0, 0, 0, 2},
            {0, 2, 0, 0, 0, 2, 0, 2},
            {0, 0, 0, 2, 0, 2, 0, 2},
            {0, 2, 0, 2, 0, 2, 0, 2} 
        };

        // defended_squares - ilość bronionych pól odpowiednio dla każdego setupu 
        int defended_squares[16] = {0, 1, 1, 2, 1, 2, 4, 2, 3, 3, 2, 4, 4, 4, 3, 4};

        int cnt;
        for(int i = 0; i < 16; i++)
        {
            cnt = 0;
            for(int j = 0; j < 8; j++)
            {
                // uwzgledniamy ze czarny hetman tez moze bronic ostatniej linii
                if(currentBoard.board[0][j] == setups[i][j] || currentBoard.board[0][j] == 4)
                {
                    cnt++;
                }
            }
            if(cnt == 8)
            {
                last_line = defended_squares[i];
                return last_line;
            }
        }
    }

    // gdy przeciwnik juz znalazl sie na pierwszej linii
    return last_line;
}

int uncapturable_pieces(Symbol current_move, Board currentBoard)
{
    // uncapturable_pieces() oblicza # figury znajdujących się na krańcach planszy lub na czele ustawienia w kształcie trójkąta [nierelatywny]
    int uncapturable = 0;

    // szukanie bierek na krawedziach planszy

    if(current_move == SYMBOL_WHITE)
    {
        // w poziomie
        for(int j = 0; j < 8; j++)
        {
            if(currentBoard.board[7][j] == 1 || currentBoard.board[7][j] == 3)
            {
                uncapturable++;
            }
            if(currentBoard.board[0][j] == 1 || currentBoard.board[0][j] == 3)
            {
                uncapturable++;
            }
        }

        // w pionie
        for(int i = 1; i < 7; i++)
        {
            if(currentBoard.board[i][0] == 1 || currentBoard.board[i][0] == 3)
            {
                uncapturable++;
            }
            if(currentBoard.board[i][7] == 1 || currentBoard.board[i][7] == 3)
            {
                uncapturable++;
            }
        }
    }
    else
    {
        // w poziomie
        for(int j = 0; j < 8; j++)
        {
            if(currentBoard.board[7][j] == 2 || currentBoard.board[7][j] == 4)
            {
                uncapturable++;
            }
            if(currentBoard.board[0][j] == 2 || currentBoard.board[0][j] == 4)
            {
                uncapturable++;
            }
        }

        // w pionie
        for(int i = 1; i < 7; i++)
        {
            if(currentBoard.board[i][0] == 2 || currentBoard.board[i][0] == 4)
            {
                uncapturable++;
            }
            if(currentBoard.board[i][7] == 2 || currentBoard.board[i][7] == 4)
            {
                uncapturable++;
            }
        }       
    }


    // szukanie trojkatnego ustawienia
    if(current_move == SYMBOL_WHITE)
    {
        for(int i = 1; i < 7; i++)
        {
            for(int j = 1; j < 7; j++)
            {
                if(currentBoard.board[i][j] == 1 || currentBoard.board[i][j] == 3)
                {
                    if(currentBoard.board[i + 1][j + 1] == 1 || currentBoard.board[i + 1][j + 1] == 3)
                    {
                        if(currentBoard.board[i + 1][j - 1] == 1 || currentBoard.board[i + 1][j - 1] == 1)
                        {
                            uncapturable++;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i = 6; i >= 1; i--)
        {
            for(int j = 1; j < 7; j++)
            {
                if(currentBoard.board[i][j] == 2 || currentBoard.board[i][j] == 4)
                {
                    if(currentBoard.board[i - 1][j + 1] == 2 || currentBoard.board[i - 1][j + 1] == 4)
                    {
                        if(currentBoard.board[i - 1][j - 1] == 2 || currentBoard.board[i - 1][j - 1] == 4)
                        {
                            uncapturable++;
                        }
                    }
                }
            }
        }
    }

    return uncapturable;
}



int evaluate(Symbol current_move, Board currentBoard)
{
    // funkcja evaluate() ocenia pozycję na podstawie jej atrybutów
    // nazwa_parametru [relatywny] - w zestawieniu z przeciwnikiem
    // nazwa_parametru [nierelatywny] - bez zestawienia z przeciwnikiem

    // MATERIAŁ (bilans bierek) [relatywny]
    int pd = pieces_diff(current_move, currentBoard);

    // KONTROLA CENTRUM (# figur danego koloru znajdujących się w 8 centralnych polach) [nierelatywny] 
    int cc = center_control(current_move, currentBoard);

    // OBRONA OSTATNIEJ LINII (# bronionych pól w ostatniej linii) [nierelatywny]
    int lld = last_line_defense(current_move, currentBoard);

    //FIGURY KTÓRYCH NIE DA SIĘ ZBIĆ (figury na krańcach planszy lub na czele ustawienia w kształcie trójkąta) [nierelatywny]    
    int uc = uncapturable_pieces(current_move, currentBoard);
    
    // 0,7 pawn = 4 center square control
    // 0,55 pawn = 5 uncapturable pieces
    // 0,5 pawn = 4 last line squares deffened
    int p1, p2, p3, p4;
    p1 = 100;
    p2 = 17;
    p3 = 15;
    p4 = 10;

    int eval = p1 * pd + p2 * cc + p3 * lld + p4 * uc;
    return eval;
}


pair < bool, Board >  is_move_legal(int xp, int yp, int xk, int yk, Symbol current_move, Board currentBoard, bool captured_before)
{
    //is_move_legal() jest istotnie zmodyfikowaną na potrzeby bota metodą isMoveLegal z klasy Game

    // na samym poczatku sprawdzamy czy ruch jest na planszy
    if (xp < 0 || xp > 7 || yp < 0 || yp > 7 || xk < 0 || xk > 7 || yk < 0 || yk > 7)
    {
        return {false, currentBoard};
    }

    // sprawdzamy czy na polu poczatkowym jest pionek gracza ktory ma aktualnie ruch
    if (current_move == SYMBOL_WHITE)
    {
        if (!(currentBoard.board[xp][yp] == 1 || currentBoard.board[xp][yp] == 3))
        {
            return {false, currentBoard};
        }
    }
    else if (current_move == SYMBOL_BLACK)
    {
        if (!(currentBoard.board[xp][yp] == 2 || currentBoard.board[xp][yp] == 4))
        {
            return {false, currentBoard};
        }
    }

    if(captured_before)
    {
       if(xp == xk && yp == yk)
       {
            // za pomoca wielkrotnych bic dotarlismy figura z pola (xp, yp) na pole (xk, yk)
            return {true, currentBoard};
       }
    }
    else
    {
        // sprawdzamy czy na polu koncowym jest puste pole
        if (currentBoard.board[xk][yk] != 0)
        {
            return {false, currentBoard};
        }        
    }

    pair < bool, Board > reaches_xk_yk = {false, currentBoard}; // reaches_xk_yk.first = true, gdy jedno lub wielokrotne bicie prowadzi do pola (xk, yk), wtedy reaches_xk_yk.second jest pozycja po ruchu figurą z pola (xp, yp) na pole (xk, yk)

    if (current_move == SYMBOL_WHITE)
    {
        if (currentBoard.board[xp][yp] == 1)
        {
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if (0 <= (xp - 2) && (yp - 2) >= 0 && currentBoard.board[xp - 2][yp - 2] == 0 && (currentBoard.board[xp - 1][yp - 1] == 2 || currentBoard.board[xp - 1][yp - 1] == 4))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp - 1][yp - 1] = 0;
                if(xp - 2 == 0)
                {
                    // promocja na damke
                    currentBoard.board[xp - 2][yp - 2] = 3; 
                }
                else
                {
                    currentBoard.board[xp - 2][yp - 2] = 1; 
                }
                reaches_xk_yk = is_move_legal(xp - 2, yp - 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp - 2) >= 0 && (yp + 2) <= 7 && currentBoard.board[xp - 2][yp + 2] == 0 && (currentBoard.board[xp - 1][yp + 1] == 2 || currentBoard.board[xp - 1][yp + 1] == 4))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp - 1][yp + 1] = 0;
                if(xp - 2 == 0)
                {
                    // promocja na damke
                    currentBoard.board[xp - 2][yp + 2] = 3; 
                }
                else
                {
                    currentBoard.board[xp - 2][yp + 2] = 1; 
                }
                reaches_xk_yk = is_move_legal(xp - 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;  
            }
        }
        else if (currentBoard.board[xp][yp] == 3)
        {
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if ((xp - 2) >= 0 && (yp - 2) >= 0 && currentBoard.board[xp - 2][yp - 2] == 0 && (currentBoard.board[xp - 1][yp - 1] == 2 || currentBoard.board[xp - 1][yp - 1] == 4))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp - 1][yp - 1] = 0;
                currentBoard.board[xp - 2][yp - 2] = 3;
                reaches_xk_yk = is_move_legal(xp - 2, yp - 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp - 2) >= 0 && (yp + 2) <= 7 && currentBoard.board[xp - 2][yp + 2] == 0 && (currentBoard.board[xp - 1][yp + 1] == 2 || currentBoard.board[xp - 1][yp + 1] == 4))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp - 1][yp + 1] = 0;
                currentBoard.board[xp - 2][yp + 2] = 3; 
                reaches_xk_yk = is_move_legal(xp - 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp + 2) <= 7 && (yp - 2) >= 0 && currentBoard.board[xp + 2][yp - 2] == 0 && (currentBoard.board[xp + 1][yp - 1] == 2 || currentBoard.board[xp + 1][yp - 1] == 4))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp + 1][yp - 1] = 0;
                currentBoard.board[xp + 2][yp - 2] = 3; 
                reaches_xk_yk = is_move_legal(xp + 2, yp - 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp + 2) <= 7 && (yp + 2) <= 7 && currentBoard.board[xp + 2][yp + 2] == 0 && (currentBoard.board[xp + 1][yp + 1] == 2 || currentBoard.board[xp + 1][yp + 1] == 4))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp + 1][yp + 1] = 0;
                currentBoard.board[xp + 2][yk + 2] = 3; 
                reaches_xk_yk = is_move_legal(xp + 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }      
        }
    }
    else if (current_move == SYMBOL_BLACK)
    {
        if(currentBoard.board[xp][yp] == 2)
        {
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if ((xp + 2) <= 7 && (yp - 2) >= 0 && currentBoard.board[xp + 2][yp - 2] == 0 && (currentBoard.board[xp + 1][yp - 1] == 1 || currentBoard.board[xp + 1][yp - 1] == 3))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp + 1][yp - 1] = 0;
                if(xp + 2 == 7)
                {
                    currentBoard.board[xp + 2][yp - 2] = 4; 
                }
                else
                {
                    currentBoard.board[xp + 2][yp - 2] = 2; 
                }
                reaches_xk_yk = is_move_legal(xp + 2, yp - 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp + 2) <= 7 && (yp + 2) <= 7 && currentBoard.board[xp + 2][yp + 2] == 0 && (currentBoard.board[xp + 1][yp + 1] == 1 || currentBoard.board[xp + 1][yp + 1] == 3))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp + 1][yp + 1] = 0;
                if(xp + 2 == 7)
                {
                    currentBoard.board[xp + 2][yp + 2] = 4; 
                }
                else
                {
                    currentBoard.board[xp + 2][yp + 2] = 2; 
                }
                reaches_xk_yk = is_move_legal(xp + 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
        }
        else if (currentBoard.board[xp][yp] == 4)
        {
            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
            if ((xp - 2) >= 0 && (yp - 2) >= 0 && currentBoard.board[xp - 2][yp - 2] == 0 && (currentBoard.board[xp - 1][yp - 1] == 1 || currentBoard.board[xp - 1][yp - 1] == 3))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp - 1][yp - 1] = 0;
                currentBoard.board[xp - 2][yp - 2] = 4;
                reaches_xk_yk = is_move_legal(xp + 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp - 2) >= 0 && (yp + 2) <= 7 && currentBoard.board[xp - 2][yp + 2] == 0 && (currentBoard.board[xp - 1][yp + 1] == 1 || currentBoard.board[xp - 1][yp + 1] == 3))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp - 1][yp + 1] = 0;
                currentBoard.board[xp - 2][yp + 2] = 4;
                reaches_xk_yk = is_move_legal(xp + 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp + 2) <= 7 && (yp - 2) >= 0 && currentBoard.board[xp + 2][yp - 2] == 0 && (currentBoard.board[xp + 1][yp - 1] == 1 || currentBoard.board[xp + 1][yp - 1] == 3))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp + 1][yp - 1] = 0;
                currentBoard.board[xp + 2][yp - 2] = 4;
                reaches_xk_yk = is_move_legal(xp + 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }
            else if ((xp + 2) <= 7 && (yp + 2) <= 7 && currentBoard.board[xp + 2][yp + 2] == 0 && (currentBoard.board[xp + 1][yp + 1] == 1 || currentBoard.board[xp + 1][yp + 1] == 3))
            {
                // wykonujemy bicie
                currentBoard.board[xp][yp] = 0;
                currentBoard.board[xp + 1][yp + 1] = 0;
                currentBoard.board[xp + 2][yp + 2] = 4;
                reaches_xk_yk = is_move_legal(xp + 2, yp + 2, xk, yk, current_move, currentBoard, true);
                if(reaches_xk_yk.first == true) return reaches_xk_yk;
            }      
        }
    }

    if(captured_before == false)
    {
        // nie ma mozliwego bicia figurą z (xp, yp)
        

        //sprawdzamy czy sa jakies bicia przymusowe pozostalymi figurami koloru figury z (xp, yp)

        if(current_move == SYMBOL_WHITE)
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8 ; j++)
                {
                    if(i != xp || j != yp)
                    {
                        // wybralismy dowolna figure poza figura z pola (xp, yp)
                        if (currentBoard.board[i][j] == 1)
                        {
                            if ((i - 2) >= 0 && (j - 2) >= 0 && currentBoard.board[i - 2][j - 2] == 0 && (currentBoard.board[i - 1][j - 1] == 2 || currentBoard.board[i - 1][j - 1] == 4))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i - 2) >= 0 && (j + 2) <= 7 && currentBoard.board[i - 2][j + 2] == 0 && (currentBoard.board[i - 1][j + 1] == 2 || currentBoard.board[i - 1][j + 1] == 4))
                            {
                                return {false, currentBoard};
                            }
                        }
                        else if (currentBoard.board[i][j] == 3)
                        {
                            if ((i - 2) >= 0 && (j - 2) >= 0 && currentBoard.board[i - 2][j - 2] == 0 && (currentBoard.board[i - 1][j - 1] == 2 || currentBoard.board[i - 1][j - 1] == 4))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i - 2) >= 0 && (j + 2) <= 7 && currentBoard.board[i - 2][j + 2] == 0 && (currentBoard.board[i - 1][j + 1] == 2 || currentBoard.board[i - 1][j + 1] == 4))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i + 2) <= 7 && (j - 2) >= 0 && currentBoard.board[i + 2][j - 2] == 0 && (currentBoard.board[i + 1][j - 1] == 2 || currentBoard.board[i + 1][j - 1] == 4))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i + 2) <= 7 && (j + 2) <= 7 && currentBoard.board[i + 2][j + 2] == 0 && (currentBoard.board[i + 1][j + 1] == 2 || currentBoard.board[i + 1][j + 1] == 4))
                            {
                                return {false, currentBoard};
                            }      
                        }
                    }
                }
            }                
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8 ; j++)
                {
                    if(i != xp || j != yp)
                    {
                        // wybralismy dowolna figure poza figura z pola (xp, yp)
                        if(currentBoard.board[i][j] == 2)
                        {
                            if ((i + 2) <= 7 && (j - 2) >= 0 && currentBoard.board[i + 2][j - 2] == 0 && (currentBoard.board[i + 1][j - 1] == 1 || currentBoard.board[i + 1][j - 1] == 3))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i + 2) <= 7 && (j + 2) <= 7 && currentBoard.board[i + 2][j + 2] == 0 && (currentBoard.board[i + 1][j + 1] == 1 || currentBoard.board[i + 1][j + 1] == 3))
                            {
                                return {false, currentBoard};
                            }
                        }
                        else if (currentBoard.board[i][j] == 4)
                        {
                            // sprawdzamy czy mozemy wykonac bicie, tzn czy pomiedzy polem na ktory chcemy przejsc(chcemy przejsc o 2 na ukos), tzn na polu o 1 na ukos jest przeciwnik, wtedy go bijemy
                            if ((i - 2) >= 0 && (j - 2) >= 0 && currentBoard.board[i - 2][j - 2] == 0 && (currentBoard.board[i - 1][j - 1] == 1 || currentBoard.board[i - 1][j - 1] == 3))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i - 2) >= 0 && (j + 2) <= 7 && currentBoard.board[i - 2][j + 2] == 0 && (currentBoard.board[i - 1][j + 1] == 1 || currentBoard.board[i - 1][j + 1] == 3))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i + 2) <= 7 && (j - 2) >= 0 && currentBoard.board[i + 2][j - 2] == 0 && (currentBoard.board[i + 1][j - 1] == 1 || currentBoard.board[i + 1][j - 1] == 3))
                            {
                                return {false, currentBoard};
                            }
                            else if ((i + 2) <= 7 && (j + 2) <= 7 && currentBoard.board[i + 2][j + 2] == 0 && (currentBoard.board[i + 1][j + 1] == 1 || currentBoard.board[i + 1][j + 1] == 3))
                            {
                                return {false, currentBoard};
                            }
                        }
                    }
                }
            }                
        }
    

        //sprawdzamy czy mozna przejsc o 1 pole na skos figurą (xp, yp) na pole (xk, yk)
        if (current_move == SYMBOL_WHITE)
        {
            if (currentBoard.board[xp][yp] == 1)
            {            
                if (xk == xp - 1 && (yk == yp - 1 || yk == yp + 1))
                {
                    currentBoard.board[xp][yp] = 0;
                    if(xk == 0)
                    {
                        currentBoard.board[xk][yk] = 3; 
                    }
                    else
                    {
                        currentBoard.board[xk][yk] = 1; 
                    }
                    return {true, currentBoard};
                }
            }
            else if(currentBoard.board[xp][yp] == 3)
            {
                if ((xk == xp + 1 || xk == xp - 1 ) && (yk == yp - 1 || yk == yp + 1))
                {
                    currentBoard.board[xp][yp] = 0;
                    currentBoard.board[xk][yk] = 3;
                    return {true, currentBoard};
                }
            }
        }
        else if (current_move == SYMBOL_BLACK)
        {
            if (currentBoard.board[xp][yp] == 2)
            {
                if (xk == xp + 1 && (yk == yp - 1 || yk == yp + 1))
                {
                    currentBoard.board[xp][yp] = 0;
                    if(xk == 7)
                    {
                        currentBoard.board[xk][yk] = 4; 
                    }
                    else
                    {
                        currentBoard.board[xk][yk] = 2; 
                    }
                    return {true, currentBoard};
                }
            }
            else if(currentBoard.board[xp][yp] == 4)
            {
                if ((xk == xp + 1 || xk == xp - 1 ) && (yk == yp - 1 || yk == yp + 1))
                {
                    currentBoard.board[xp][yp] = 0;
                    currentBoard.board[xk][yk] = 4; 
                    return {true, currentBoard};
                }                    
            }

        }
    }
    

    return {false, currentBoard};
}

vector < Board > legal_moves_generator(Symbol current_move, Board currentBoard)
{
    // legal_moves_generator() generuje wszystkie prawidłowe posuniecie w pozycji dla gracza o danym current_moveu
    vector < Board > moves;

    for(int xp = 0; xp < 8; xp++)
    {
        for(int yp = 0; yp < 8; yp++)
        {
            for(int xk = 0; xk < 8; xk++)
            {
                for(int yk = 0; yk < 8; yk++)
                {
                    pair < bool, Board > potenialMove = is_move_legal(xp, yp, xk, yk, current_move, currentBoard, false);
                    if(potenialMove.first == true)
                    {
                        // potencjalny ruch okazal sie poprawny
                        moves.push_back(potenialMove.second);
                    }
                }
            }
        }
    }

    return moves;
}

int min_max(int depth, Symbol current_move, bool isMaximizing, Board currentBoard)
{
    if(depth == 6)
    {
        // min_max() szedl na glebkosc 5 ruchow
        return evaluate(current_move, currentBoard);
    }

    // generacja wszystkich legalnych ruchów pozycji
    vector < Board > moves = legal_moves_generator(current_move, currentBoard);
    int best_value;
    int value;

    if(moves.size() == 0) // do rozkminienia
    {
        // brak ruchow w pozycji
        if(isMaximizing == true)
        {
            //gracz maksymalizujacy przegral, bo nie moze sie ruszyc 
            best_value = -INF;
            return -INF; 
        }
        else
        {
            //gracz minimalizujacy przegral, bo nie moze sie ruszyc
            best_value = INF;
            return INF;
        }
    }
 
    if(isMaximizing == true) // gracz maksymalizujący
    {
        best_value = -INF;

        for(unsigned int i = 0; i < moves.size(); i++)
        {
            if(current_move == SYMBOL_WHITE)
            {
                value = min_max(depth + 1, SYMBOL_BLACK, false, moves[i]);
            }
            else
            {
                value = min_max(depth + 1, SYMBOL_WHITE, false, moves[i]);
            }

            if(value > best_value) best_value = value;
        }
        return best_value;
    }
    else //gracz minimalizujący
    {
        best_value = INF;
        
        for(unsigned int i = 0; i < moves.size(); i++)
        {
            if(current_move == SYMBOL_WHITE)
            {
                value = min_max(depth + 1, SYMBOL_BLACK, true, moves[i]);
            }
            else
            {
                value = min_max(depth + 1, SYMBOL_WHITE, true, moves[i]);
            }
            if(value < best_value) best_value = value;
        }
        return best_value;
    }
}

Board Bot::move(Symbol current_move, Board currentBoard)
{
    int value;
    int best_value = -INF;
    Board best_position;

    vector < Board > moves = legal_moves_generator(current_move, currentBoard);
    
    for(unsigned int i = 0; i < moves.size(); i++)
    {
        if(current_move == SYMBOL_WHITE)
        {
            value = min_max(1, SYMBOL_BLACK, false, moves[i]);
        }
        else
        {
            value = min_max(1, SYMBOL_WHITE, false, moves[i]);
        }
        if(value > best_value)
        {
            best_value = value;
            best_position = moves[i];
        }
    }

    return best_position;
}
