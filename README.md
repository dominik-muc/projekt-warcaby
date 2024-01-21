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
