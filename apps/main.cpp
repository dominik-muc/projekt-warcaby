#include <iostream>
#include <Warcaby/Game/game.h>
#include <Warcaby/types.h>

#include <Warcaby/Renderer/text_renderer.hpp>
#include <Warcaby/Renderer/ascii_renderer.hpp>

using namespace std;

enum RendererType{
    TEXT,
    ASCII
};

//pozwala hashować stringi. nie mam pojęcia jak działa.
constexpr unsigned int str2int(const char* str, int h = 0){ return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h]; }

int text_renderer();
int ascii_renderer();
void show_help();

int main(int argc, char** argv){
    //defaults:
    RendererType rtype = TEXT;
    //inne wartosci takie jak tryb rozgrywki (pvp, pve) oraz czas powinny być też defaultowo zdefiniowane
    //następnie zmieniane przy wywołaniu odpowiednich argumentów niżej. czas musi sprawdzać też argv[i+1] -> czy jest to poprawna wartość.
    //uzyskane wartości należy przekazać do funkcji text_renderer i ascii_renderer w ostatnim switchu

    for(int i = 1; i < argc; i++){
        switch(str2int(argv[i])){
            case str2int("--ascii-renderer"):
                rtype = ASCII;
                break;
            case str2int("--text-renderer"):
                rtype = TEXT;
                break;
            case str2int("--help"):
            case str2int("-h"):
                show_help();
                return 0;
            default:
                cout << "Niepoprawny argument: " << argv[i] << ". Zobacz --help" << endl;
                return -1;
        }
    }
    
    switch (rtype){
    case TEXT:
        return text_renderer();
    case ASCII:
        return ascii_renderer();
    default:
        return -1;
    }
}

//implementacje

void show_help(){
    cout << "Opcje: --text-renderer, --ascii-renderer" << endl;
}

//prawdopodobnie dałoby się wrzucić to do jednej funkcji -> niestety nie można się odwoływać bezpośrednio do Renderer. Jak ktoś wie jak to zrobić to byłoby miło.
//na chwilę obecną main po prostu wywołuje odpowiednią funkcję.

int text_renderer(){
    Game game;
    TextRenderer renderer;
    array<int, 2> UserInput1, UserInput2;
    string player;
    string message = "";

    renderer.printBoard(game.getBoard());
    renderer.open_help();

    while(game.gameState == ONGOING){
        player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        renderer.printMessage("Ruch gracza: " + player);
        renderer.printMessage(message);
        renderer.printBoard(game.getBoard());
        
        UserInput1 = renderer.getUserInput();
        UserInput2 = renderer.getUserInput();
        
        message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1]);
    }

    renderer.open_win_screen(game.gameState);
    renderer.closeRenderer();
    cout << "Wygral gracz: " << (game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny") << endl;
    return 0;
}

int ascii_renderer(){
    Game game;
    AsciiRenderer renderer;

    array<int, 2> UserInput1, UserInput2;
    string player;
    string message = "";

    while(game.gameState == ONGOING){
        renderer.printBoard(game.getBoard());
        player = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        renderer.printMessage(message + "\n\nRuch gracza: " + player + "\nPodaj ruch");

        UserInput1 = renderer.getUserInput();
        UserInput2 = renderer.getUserInput();

        message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1]);
    }

    renderer.closeRenderer();
    cout << "Wygral gracz: " << game.gameState << endl;
    return 0;
}