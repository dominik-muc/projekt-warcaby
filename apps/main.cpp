#include <iostream>
#include <Warcaby/Game/game.h>
#include <Warcaby/types.h>

#include <Warcaby/Renderer/text_renderer.hpp>
#include <Warcaby/Renderer/ascii_renderer.hpp>

using namespace std;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
void show_help(){
    cout << "Opcje: --text-renderer, --ascii-renderer" << endl;
}



int text_renderer(){
    // tworzymy obiekt gry
    Game game;
    TextRenderer renderer;
    array<int, 2> UserInput1, UserInput2;
    string player;
    string message = "";


    renderer.printBoard(game.getBoard());
    renderer.open_help();

    // glowna petla gry
    while(game.gameState == ONGOING){
        player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        renderer.printMessage("Ruch gracza: " + player);
        renderer.printMessage(message);
        renderer.printBoard(game.getBoard());
        
        UserInput1 = renderer.getUserInput();
        UserInput2 = renderer.getUserInput();
        
        message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1]);
    }

    
    // wypisujemy kto wygral
    
    renderer.open_win_screen(game.gameState);
    renderer.closeRenderer();

    cout << "Wygral gracz: " << (game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny") << endl;
    
    return 0;
}

int ascii_renderer() {
    
    // tworzymy obiekt gry
    Game game;
    AsciiRenderer renderer;

    array<int, 2> UserInput1, UserInput2;
    string player;
    string mess = "";

    // glowna petla gry
    while(game.gameState == ONGOING){

        renderer.printBoard(game.getBoard());
        player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        renderer.printMessage(mess + "\n\nRuch gracza: " + player + "\nPodaj ruch");
        
        UserInput1 = renderer.getUserInput();
        UserInput2 = renderer.getUserInput();
        
        mess = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1]);
        

    }

    renderer.closeRenderer();
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}

int main(int argc, char** argv){

    if(argc == 1) return text_renderer();

    for(int i = 1; i < argc; i++){
        switch(str2int(argv[i])){
            case str2int("--ascii-renderer"):
            return ascii_renderer();
                case str2int("--text-renderer"):
                return text_renderer();
            case str2int("--help"):
            case str2int("-h"):
                show_help();
                return 0;
            default:
                cout << "Niepoprawny argument: " << argv[i] << ". Zobacz --help" << endl;
                return -1;
        }
    }
    
}