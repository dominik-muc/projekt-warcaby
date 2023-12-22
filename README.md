# Projekt Warcaby

W ramach projektu na zajęcia PWI przygotowaliśmy prostą grę w warcaby.

## Budowanie aplikcaji
### Zależności
- CMake
- Kompilator C++, wspierający standard C++20
- ncurses (linux) / coś innego (windows)

### Linux
W głównym katalogu wykonaj polecenie `./build_linux.sh`.

### Windows
~~https://wiki.archlinux.org/title/installation_guide~~  
W głównym katalogu wykonaj polecenie `./build_windows.bat`.

### MacOS
~~https://wiki.archlinux.org/title/installation_guide~~
W głownym katalogu wykonaj polecenie `cmake -S . -B build`, następnie `make -C build`

## Uruchamianie aplikacji
Zbudowana aplikacja znajduje się w katalogu build/apps.  
Aby ją uruchomić, z głównego katalogu wykonaj polecenie `./build/apps/main`.

## Autorzy projektu
- Dominik Muc
- Kaja Matuszewska
- Wojciech Orański
- Dawid Pawliczek
- Rafał Pęcherz
- Stanisław Burdzicki
- Nadia Uczkiewicz