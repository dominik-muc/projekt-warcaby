#include "Warcaby/Renderer/text_renderer.hpp"
#include <ncurses.h>

TextRenderer::TextRenderer()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    refresh();
    
    board_win = newwin(34, 73, 0, 0);
    wrefresh(board_win);
    
    text_win = newwin(34, 25, 0, 75);
    wrefresh(text_win);

    
}

void TextRenderer::printBoard( std::array<std::array<int, 8>, 8> board )
{
    wclear(board_win);
    box(board_win, 0, 0);
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(!((i+j)%2)){
                wattron(board_win, A_STANDOUT);
            }
            for(int k=0; k<3; k++){
                mvwprintw(board_win, i*4+1+k, j*9+1, "%s", piece_art[ board[i][j] ][k]);
            }
            if(i!=7) mvwhline(board_win, i*4+4, j*9+1, '_', 8);
            else mvwhline(board_win, 32, j*9+1, ' ', 8);
            if(!((i+j)%2)){
                wattroff(board_win, A_STANDOUT);
            }
        }
    }

    for(int i=1; i<8; i++){
        mvwaddch(board_win, 0, i*9, ACS_TTEE);
        mvwvline(board_win, 1, i*9, 0, 32);
        mvwaddch(board_win, 33, i*9, ACS_BTEE);
    }
    
    wclear(text_win);
    box(text_win, 0, 0);
    for(int i = 2 ; !messages.empty(); i++ ){
        mvwprintw(text_win, 2+i, 2, "%s", messages.front().c_str());
        messages.pop();
    }
    
    

    refresh();
    wrefresh(board_win);
    wrefresh(text_win);
}

void TextRenderer::closeRenderer()
{
    wclear(board_win);
    wrefresh(board_win);
    delwin(board_win);

    wclear(text_win);
    wrefresh(text_win);
    delwin(text_win);

    clear();
    endwin();
}

void TextRenderer::printMessage(std::string str)
{
    messages.push(str);
}

std::array<int, 2>  TextRenderer::select_square()
{
    std::array<int, 2> input = {0, 0};
    int ch;
    int rev;
    MEVENT event;
    mousemask(BUTTON1_CLICKED | REPORT_MOUSE_POSITION, NULL);

    while(true){
        move(input[0]*4+1, input[1]*9+1);

        rev = (!((input[0]+input[1])%2) ? A_STANDOUT : A_NORMAL);

        update_square(input[0], input[1], A_BLINK | (((input[0]+input[1])%2) ? A_STANDOUT : A_NORMAL) );

        ch = getch();
        switch(ch){
            case KEY_MOUSE:
                if(getmouse(&event) == OK){
                    if(event.bstate & BUTTON1_PRESSED){
                        update_square(input[0], input[1], rev);
                        
                        input[0] = (event.y-1)/4;
                        input[1] = (event.x-1)/9;
                        update_square(input[0], input[1], A_BLINK| (((input[0]+input[1])%2) ? A_STANDOUT : A_NORMAL) );
                        return input;
                    }
                }
                break;
            case KEY_UP:
                update_square(input[0], input[1], rev);
                if(input[0]!=0){
                    input[0]--;
                }

                break;
            case KEY_DOWN:
                update_square(input[0], input[1], rev);
                if(input[0]!=7){
                    input[0]++;
                }

                break;
            case KEY_LEFT:
                update_square(input[0], input[1], rev);
                if(input[1]!=0){
                    input[1]--;
                }

                break;
            case KEY_RIGHT:
                update_square(input[0], input[1], rev);
                if(input[1]!=7){
                    input[1]++;
                }

                break;
            case KEY_ENTER:
            case '\n':
            case '\r':
            case KEY_SEND:
                return input;
            case 'q':
                closeRenderer();
                exit(0);
            default:
                break;
        }
    }
}

void TextRenderer::update_square(int x, int y, attr_t rev){
    mvwchgat(board_win, x*4+1, y*9+1, 8, rev, 0, NULL);
    mvwchgat(board_win, x*4+2, y*9+1, 8, rev, 0, NULL);
    mvwchgat(board_win, x*4+3, y*9+1, 8, rev, 0, NULL);
    mvwchgat(board_win, x*4+4, y*9+1, 8, rev& (~A_BLINK), 0, NULL);
    wrefresh(board_win);
}

std::array<int, 2> TextRenderer::getUserInput()
{
    std::array<int, 2> input = select_square();
    
    move(input[0], input[1]*2);
    wrefresh(board_win);

    return input;
}
