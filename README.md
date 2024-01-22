# Projekt Warcaby

W ramach projektu na zajęcia PWI przygotowaliśmy prostą grę w warcaby.

## Budowanie aplikacji
### Zależności
- CMake
- Kompilator C++, wspierający standard C++20
- ncurses (linux) / pdcurses (windows)

### Linux
W głównym katalogu wykonaj polecenie `./build_linux.sh`.

### Windows
W głównym katalogu wykonaj polecenie `./build_windows.bat`.

### MacOS
W głownym katalogu wykonaj polecenie `cmake -S . -B build`, następnie `make -C build`

## Uruchamianie aplikacji
Zbudowana aplikacja znajduje się w katalogu build/apps.  
Aby ją uruchomić, z głównego katalogu wykonaj polecenie `./build/apps/main`.

## Zasady gry
Zwykłe pionki mogą poruszać się do przodu o jedno pole na skos lub o dwa w przypadku bicia.  
Gdy pionek dojdzie do końca planszy, to zamienia się w damkę.  
Damki mogą poruszać się oraz bić zarówno do przodu, jak i do tyłu.  
Bicie jest przymusowe.

## Bot

Bot opiera się o algorytm minimax z ewaluacją pozycji przeważnie po 5. ruchu (czasami gra kończy się zanim algorytm zejdzie na głębokość 5 ruchów, wtedy ewaluacja ma miejsce wcześniej). Warto zauważyć, że wielokrotne bicie liczone jest jako 1 ruch.

Do ewaluacji służą 4 parametry, 1 relatywny (w zestawieniu z przeciwnikiem), 3 nierealtywne (bez zestawienia z przeciwnikiem). Są to odpowiednio:
* bilans materiału
* konrola centrum, kontrola ostatniej linii, bierki niezbijalne

### Bilans materiału

Różnica między ilość i wartością białych i czarnych bierek (lub czarnych i białych bierek)

### Kontrola centrum

Ilość bierek danego koloru na 4 centralnych polach planszy.

### Kontrola ostatniej linii

Ilość bronionych pól na ostatniej linii. Przykładowo jeśli żaden z białych pionków z ostatniego rzędu nie wykonał ruchu (czyli 4 ostatnie pola są bronione) to gracz grający czarnymi nie będzie mógł dorobić damki.

### Bierki niezbijalne

Ilość bierek na krańcach planszy, lub na czele trójkątnego ustawienia (takich bierek nie można zbić w 1 ruchu).


## Autorzy projektu
- Dominik Muc
- Kaja Matuszewska
- Wojciech Orański
- Dawid Pawliczek
- Rafał Pęcherz
- Stanisław Burdzicki
- Nadia Uczkiewicz

<br />
<br />

# Instrukcje Budowania
Wymagana jest biblioteka ncurses, do pobrania np. w następujący sposób
```sh
apt-get install libncurses-dev
```

# Jak grać:
- Ascii renderer:
    strzałki żeby wybrać pole. Enter żeby potwierdzić.
    Chwilowo uruchamiane jako ./build/apps/ascii_main
- Text renderer
    jak ASCII lub myszką
    Uruchamiamy jako ./build/text_main
