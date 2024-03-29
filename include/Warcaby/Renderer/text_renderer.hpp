#pragma once

#include <array>
#include <string>
#include <queue>

#ifdef _WIN32
    #define NCURSES_MOUSE_VERSION 2
    #include <curses.h>
#else
    #include <ncurses.h>
#endif


#include <Warcaby/Renderer/renderer.h>


// A minimalistic renderer. Every piece is represented by one character.
class TextRenderer : Renderer{
    public:
        TextRenderer();
        void printBoard(std::array<std::array<int, 8>, 8> board );
        
        void closeRenderer();
       
        std::array<int, 2> getUserInput();
        void reset_selection();
        
        void printMessage(std::string message);

        void open_help();
        void open_win_screen(GameState winner);
        

    private:
        // acording to FieldType from types.h
        const char* piece_art[5][3] = {
            {"        ",
             "        ",
             "        ",
          // "________"
             },

            {"        ",
             " /####\\ ",
             " \\####/ ",
          // "________"
             },

            {"   __   ",
             " /    \\ ",
             " \\ __ / ",
          // "________"
          },
            {"|\\/\\/\\/|",
             "|######|",
             "<------>",
          // "________"
          },
            {"|\\/\\/\\/|",
             "|      |",
             "<------>",
          // "________"
             }
        };

        std::queue<std::string> messages;

        WINDOW* board_win;
        WINDOW* text_win;

        WINDOW* open_popup(int x, int y, int size_x, int size_y);
        void close_popup(WINDOW* popup);

        std::array<int, 2> last_selected = {0, 0};
        std::array<int, 2> select_square();

        void update_square(int x, int y, attr_t rev);
};