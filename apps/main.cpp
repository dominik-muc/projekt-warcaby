#include <iostream>
#include <Warcaby/Game/game.h>
#include <Warcaby/types.h>

#include <Warcaby/Renderer/text_renderer.hpp>
#include <Warcaby/Renderer/ascii_renderer.hpp>
#include <Warcaby/Bot/bot.h>
#include <Warcaby/zegar.h>
using namespace std;

enum RendererType{
    TEXT,
    ASCII
};

enum GameType{
    PVP,
    PVE
};

//pozwala hashować stringi. nie mam pojęcia jak działa.
constexpr unsigned int str2int(const char* str, int h = 0){ return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h]; }

int text_renderer();
int ascii_renderer();
int bot_text();
void show_help();
void flag_set(string flag);

int main(int argc, char** argv){
    //defaults:
    RendererType rtype = TEXT;
    GameType gtype = PVP;
    int set[2] = {0};
    //inne wartosci takie jak tryb rozgrywki (pvp, pve) oraz czas powinny być też defaultowo zdefiniowane
    //następnie zmieniane przy wywołaniu odpowiednich argumentów niżej. czas musi sprawdzać też argv[i+1] -> czy jest to poprawna wartość.
    //uzyskane wartości należy przekazać do funkcji text_renderer i ascii_renderer w ostatnim switchu

    for(int i = 1; i < argc; i++){
        switch(str2int(argv[i])){
            case str2int("--ascii-renderer"):
                if(set[0]){
                    flag_set(argv[i]);
                    return -1;
                }
                set[0] = 1;
                rtype = ASCII;
                break;
            case str2int("--text-renderer"):
                if(set[0]){
                    flag_set(argv[i]);
                    return -1;
                }
                set[0] = 1;
                rtype = TEXT;
                break;
            case str2int("--type"):
                do_pliku(argv[i],argv[i+1]);
                i++;
                break;
            case str2int("--time"):
                do_pliku(argv[i],argv[i+1]);
                i++;
                break;
            case str2int("--help"):
            case str2int("-h"):
                show_help();
                return 0;
            case str2int("--pve"):
                if(set[1]){
                    flag_set(argv[i]);
                    return -1;
                }
                set[1] = 1;
                gtype = PVE;
                break;
            case str2int("--pvp"):
                if(set[1]){
                    flag_set(argv[i]);
                    return -1;
                }
                set[1] = 1;
                gtype = PVP;
                break;
            default:
                cout << "Niepoprawny argument: " << argv[i] << ". Zobacz --help" << endl;
                return -1;
        }
    }
    
    switch (rtype){
    case TEXT:
        if(gtype == PVP) return text_renderer();
        return bot_text();
    case ASCII:
        if(gtype == PVP) return ascii_renderer();
        else{
            cout << "Brak wsparcia dla ascii w przypadku gry PVE." << endl;
            return -1;
        }
    default:
        return -1;
    }
}

//implementacje

void show_help(){
    cout << "Opcje: --text-renderer, --ascii-renderer, --pvp, --pve" << endl;
}

void flag_set(string flag){
    cout << "Juz ustawiono flage " << flag << "!" << endl;
    show_help();
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
        
        message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1], player);
        renderer.reset_selection();
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

        message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1], player);
    }

    renderer.closeRenderer();
    cout << "Wygral gracz: " << game.gameState << endl;
    return 0;
}

int bot_text(){
    
    // tworzymy obiekt gry
    Game game;
    array<int, 2> UserInput1, UserInput2;

    string player_white = "human";
    string player_black = "bot";
    // bot gra czarnymi (na razie)

    string currentPlayer;

    string message = "";


    TextRenderer renderer = TextRenderer();

    renderer.printBoard(game.getBoard());
    renderer.open_help();

    // glowna petla gry
    while(game.gameState == ONGOING){
        currentPlayer = game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny";
        
        renderer.printMessage(message);
        

        if(currentPlayer == "Bialy")
        {
            renderer.printMessage("Ruch gracza: " + currentPlayer);
            renderer.printBoard(game.getBoard());
            UserInput1 = renderer.getUserInput();
            UserInput2 = renderer.getUserInput();   
            renderer.printMessage("Podaj ruch");
            message = game.update(UserInput1[0], UserInput1[1], UserInput2[0], UserInput2[1], player_white);
            renderer.reset_selection();
        }
        else
        {
            renderer.printMessage("Bot " + currentPlayer + " wykonuje ruch");
            renderer.printBoard(game.getBoard());
            game.update(0, 0, 0, 0, player_black);            
        }
    }

    renderer.open_win_screen(game.gameState);
    renderer.closeRenderer();
    cout << "Wygral gracz: " << (game.currentMove == SYMBOL_WHITE ? "Bialy" : "Czarny") << endl;
    return 0;

    // wypisujemy kto wygral
    cout << "Wygral gracz: " << game.gameState << endl;
    
    return 0;
}
