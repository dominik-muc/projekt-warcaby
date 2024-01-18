#include "Warcaby/Renderer/text_renderer.hpp"
#include <ncurses.h>

#define MAX(a, b) (( (a)>(b)?(a):(b) ))

TextRenderer::TextRenderer()
{
    
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    refresh();
    
    board_win = newwin(34, 73, 0, 0);
    wrefresh(board_win);
    
    // text_win has width of 25 or more
    text_win = newwin(34, MAX(25, getmaxx(stdscr)-75 ), 0, 75);
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
        // horizontal position - ~8% margin of window width or 2
        mvwprintw(text_win, 2+i, MAX(2, getmaxx(text_win)/12 ), "%s", messages.front().c_str());
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

WINDOW* TextRenderer::open_popup(int x, int y, int size_x, int size_y){
    WINDOW* popup = newwin(size_x, size_y, x, y);
    box(popup, 0, 0);
    wrefresh(popup);
    return popup;
}

void TextRenderer::open_win_screen(GameState winner){
    // window (slightly above) centered or in corner if screen is too small
    WINDOW* help_win = open_popup( MAX(2, (getmaxy(stdscr)/2)-15-2), MAX(4, (getmaxx(stdscr)/2)-46), 30, 92);
    // any button to close includes mouse buttons
    mousemask(ALL_MOUSE_EVENTS, NULL);

    std::string win_name;
    if(winner == BLACK_WIN) win_name = "BLACK";
    else if(winner == WHITE_WIN) win_name = "WHITE";
    else win_name = "NOBODY! YOU CHEATED";


    // to help with positioning
    constexpr int title_start = 3;
    constexpr int text_start = 14;

    mvwaddstr(help_win, title_start  , 32, "||===|  ||\\\\    ||   ||==\\\\ ");
    mvwaddstr(help_win, title_start+1, 32, "||      || \\\\   ||   ||   ||");
    mvwaddstr(help_win, title_start+2, 32, "||===|  ||  \\\\  ||   ||   ||");
    mvwaddstr(help_win, title_start+3, 32, "||      ||   \\\\ ||   ||   ||");
    mvwaddstr(help_win, title_start+4, 32, "||===|  ||    \\\\||   ||===//");
    
    mvwaddstr(help_win, text_start, 39, "THE WINNER IS:");

    wattron(help_win, A_BOLD);
    mvwaddstr(help_win, text_start+2, (int)((92-win_name.length())/2), win_name.c_str());


    // May not be defined in some curses versions
    #ifdef A_ITALIC
        wattron(help_win, A_ITALIC);
    #endif

    wattron(help_win, A_BLINK);
    mvwaddstr(help_win, 24, 33, "<PRESS ANY BUTTON TO CLOSE>");
    wattroff(help_win, A_BLINK|A_BLINK);

    #ifdef A_ITALIC
        wattroff(help_win, A_ITALIC);
    #endif

    wrefresh(help_win);
    // wait for any input before closing
    // twice so we dont close it accidentally
    getch();
    getch();

    mousemask(0, NULL);
    wclear(help_win);
    wrefresh(help_win);
    delwin(help_win);

    // force rerender other windows
    touchwin(board_win);
    touchwin(text_win);
    wrefresh(board_win);
    wrefresh(text_win);
}

void TextRenderer::open_help(){
    // window (slightly above) centered or in corner if screen is too small
    WINDOW* help_win = open_popup( MAX(2, (getmaxy(stdscr)/2)-15-2), MAX(4, (getmaxx(stdscr)/2)-46), 30, 92);
    // any button to close includes mouse buttons
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // to help with positioning
    #define title_start 3
    #define text_start 12

    mvwaddstr(help_win, title_start  , 29, "||   ||  ||===|  ||       |===\\\\ ");
    mvwaddstr(help_win, title_start+1, 29, "||   ||  ||      ||       ||   ||");
    mvwaddstr(help_win, title_start+2, 29, "|=====|  ||===|  ||       |===// ");
    mvwaddstr(help_win, title_start+3, 29, "||   ||  ||      ||       ||     ");
    mvwaddstr(help_win, title_start+4, 29, "||   ||  ||===|  |====|   ||     ");

    mvwaddstr(help_win, text_start, 10, "This is the help menu ");
    mvwaddstr(help_win, text_start+1, 10, "Select square using arrows and confirm with enter");
    mvwaddstr(help_win, text_start+2, 10, "You can also use mouse");
    mvwaddstr(help_win, text_start+3, 10, "To quit press \'q\'");
    mvwaddstr(help_win, text_start+4, 10, "To reopen this menu press \'h\'");

    #undef title_start
    #undef text_start

    // May not be defined in some curses versions
    #ifdef A_ITALIC
        wattron(help_win, A_ITALIC);
    #endif

    wattron(help_win, A_BLINK|A_BOLD);
    mvwaddstr(help_win, 24, 33, "<PRESS ANY BUTTON TO CLOSE>");
    wattroff(help_win, A_BLINK|A_BLINK);

    #ifdef A_ITALIC
        wattroff(help_win, A_ITALIC);
    #endif

    wrefresh(help_win);
    getch();

    mousemask(0, NULL);
    wclear(help_win);
    wrefresh(help_win);
    delwin(help_win);

    // force rerender other windows
    touchwin(board_win);
    touchwin(text_win);
    wrefresh(board_win);
    wrefresh(text_win);
}

std::array<int, 2>  TextRenderer::select_square()
{
    int ch;
    int rev;
    MEVENT event;
    mousemask(BUTTON1_CLICKED | REPORT_MOUSE_POSITION, NULL);

    while(true){
        move(last_selected[0]*4+1, last_selected[1]*9+1);

        rev = (!((last_selected[0]+last_selected[1])%2) ? A_STANDOUT : A_NORMAL);

        update_square(last_selected[0], last_selected[1], A_BLINK | (((last_selected[0]+last_selected[1])%2) ? A_STANDOUT : A_NORMAL) );

        ch = getch();
        switch(ch){
            case KEY_MOUSE:
                if(getmouse(&event) == OK){
                    if(event.bstate & BUTTON1_PRESSED){
                        
                        // check if press is inside the board
                        if(event.y>32 | event.x>71){
                            break;
                        }
                        

                        update_square(last_selected[0], last_selected[1], rev);
                        
                        last_selected[0] = (event.y-1)/4;
                        last_selected[1] = (event.x-1)/9;
                        update_square(last_selected[0], last_selected[1], A_BLINK| (((last_selected[0]+last_selected[1])%2) ? A_STANDOUT : A_NORMAL) );
                        mousemask(0, NULL);
                        return last_selected;
                    }
                }
                break;
            case KEY_UP:
                update_square(last_selected[0], last_selected[1], rev);
                if(last_selected[0]!=0){
                    last_selected[0]--;
                }

                break;
            case KEY_DOWN:
                update_square(last_selected[0], last_selected[1], rev);
                if(last_selected[0]!=7){
                    last_selected[0]++;
                }

                break;
            case KEY_LEFT:
                update_square(last_selected[0], last_selected[1], rev);
                if(last_selected[1]!=0){
                    last_selected[1]--;
                }

                break;
            case KEY_RIGHT:
                update_square(last_selected[0], last_selected[1], rev);
                if(last_selected[1]!=7){
                    last_selected[1]++;
                }

                break;
            case 'h':
            case 'H':
                open_help();                
                break;
            case KEY_ENTER:
            case '\n':
            case '\r':
            case KEY_SEND:
                mousemask(0, NULL);
                return last_selected;
            case 'q':
            case 'Q':
                mousemask(0, NULL);
                closeRenderer();
                exit(0);
            default:
                break;
        }
    }
}

void TextRenderer::reset_selection(){
    last_selected = {0,0};
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
