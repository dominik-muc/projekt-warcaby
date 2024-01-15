#include "Warcaby/Renderer/text_renderer.hpp"
#include <ncurses.h>

TextRenderer::TextRenderer()
{
    initscr();
    keypad(stdscr, TRUE);
    //printw("Hello World !!!\n");    
    refresh();
}

void TextRenderer::printBoard( std::array<std::array<int, 8>, 8> board )
{
    clear();
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<8; k++){
                if(board[i][k]==2 || board[i][k]==4){
                    attron(A_BOLD | A_REVERSE);
                }
            
                printw("%s", piece_art[board[i][k]][j]);
                if(board[i][k]==2 || board[i][k]==4){
                    attroff(A_BOLD | A_REVERSE);
                }

                if(j!=7){
                    printw(" ");
                }
            }
            printw("\n");
        }
        
        printw("\n");
    }
    printw("\n");
    printw("%s", message.c_str());
    refresh();
}

void TextRenderer::closeRenderer()
{
    clear();
    endwin();
}

void TextRenderer::printMessage(std::string str)
{
    //message = str;
    //move(9, 0);
    //printw("%s", str.c_str());
    refresh();
}

std::array<int, 2>  TextRenderer::select_square()
{
    std::array<int, 2> input = {0, 0};
    int ch;
    while(true){
        move(input[0], input[1]*2);
        ch = getch();
        switch(ch){
            case KEY_UP:
                if(input[0]!=0){
                    input[0]--;
                }
                break;
            case KEY_DOWN:
                if(input[0]!=7){
                    input[0]++;
                }
                break;
            case KEY_LEFT:
                if(input[1]!=0){
                    input[1]--;
                }
                break;
            case KEY_RIGHT:
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

std::array<int, 2> TextRenderer::getUserInput()
{
    std::array<int, 2> input = select_square();
    
    
    attron(A_BLINK);
    move(input[0], input[1]*2);
    refresh();
    printw("%c", inch());
    attroff(A_BLINK);
    refresh();


    return input;
}