# Jak umieć w CMake?

## Windows
1) Sprawdź czy masz zainstalowanego CMake komendą `cmake --help`
    - Jeżeli nie - zainstaluj https://cmake.org/download/
            Jeżeli cię zapyta czy dodać do PATH - zanacz tak
2) Jeżeli korzystasz z IDE (Visual studio code, Visual studio, Clion etc.) to ma na 99% wbudowaną obsługę cmake, dowiedz się jak korzystać z tego, bo jest lepiej
3) Jeżeli nie to znajdując się w folderze /projekt-warcaby wykonaj komendę `cmake --build ./build`
4) Gratulacje Twój plik wykonywalny znajduje się w folderze `./build/apps/<nazwa pliku>`
      
<br />
<br />

## Linux
1) Sprawdź czy masz zainstalowanego CMake komendą `cmake --help`
    - Jeżeli nie - zainstaluj apt-get --install cmake
2) Jeżeli korzystasz z IDE (Visual studio code, Visual studio, Clion etc.) to ma na 99% wbudowaną obsługę cmake, dowiedz się jak korzystać z tego, bo jest lepiej
3) Jeżeli nie to znajdując się w folderze /projekt-warcaby wykonaj komendę `cmake --build ./build`
4) Gratulacje Twój plik wykonywalny znajduje się w folderze `./build/apps/<nazwa pliku>`

<br />
<br />

# Dlaczego jest tyle folderów?
1) pliki .h i .hpp idę do folderu `./include/<kategoria>/<nazwa_pliku>`
2) odpowiadające im pliki .cpp do `./src/<kategoria>/<nazwa_pliku>`
3) W folderze `./apps` są pliki .cpp, które mają funkcję `main`. Jest ich kilka, bo jest ten nasz normalny main, ale można sobie testowe tworzyć bez edytowania maina

<br />
<br />

# Czym są te pliki CMakeLists.txt?
1) Jeżeli nie wiesz to nie ruszaj
2) Jeżeli wiesz to możesz ruszać, ale napisz o tym na grupie

Plik `./apps/CMakeLists.txt` możecie edytować jeżeli chcecie sobie dodać własny testowy plik wykonywalny Skopiujcie jedną z kopii tego co tam jest, zmieńcie nazwę na nazwę waszego testowego maina i tyle.

np. dodanie tego:
```cmake
add_executable(test_main test_main.cpp)
target_compile_features(test_main PRIVATE cxx_std_20)

target_link_libraries(test_main PRIVATE
    exLibrary
    ${CURSES_LIBRARIES}
    )
```
spowoduje powstanie przy budowaniu nowego pliku wykonywalnego `test_main` skompilowanego z pliku `test_main.cpp`

Jak uruchomicie `cmake --build ./build` to w `./build/apps` pojawi się kilka programów - każdy odpowiadający jednemu plikowi z funkcją `main`