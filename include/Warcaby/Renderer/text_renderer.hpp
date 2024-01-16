#pragma once

#include <array>
#include <string>
#include <queue>

#ifdef _WIN32
    #include <pdcurses.h>
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
        void printMessage(std::string message);
        

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
             "<——————>",
          // "________"
          },
            {"|\\/\\/\\/|",
             "|      |",
             "<——————>",
          // "________"
             }
        };

        std::queue<std::string> messages;

        WINDOW* board_win;
        WINDOW* text_win;
        WINDOW* help_win;

        void destroy_win(WINDOW *local_win);


        std::array<int, 2> select_square();

        void update_square(int x, int y, attr_t rev);
};