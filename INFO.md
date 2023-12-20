# Priorytety
Najpierw tworzymy api, potem dorobimy jakiś interface
Do testowania przydałyby nam się jakieś boty, mogą być głupie oraz w cmd jakiś prosty interface wyświtlający stan gry
Coś takiego jak było w zadaniu kółko i krzyżyk
Kiedy to będzie działać zrobimy interfejs dla gracza, proponuje użyć SDL2

# Struktura API (prototyp)
Potrzebujemy klasy Game, która w konstruktorze weźmie dwa uchwyty do funkcji które wywołane zwrócą ruch gracza
Nasza klasa potrzebuje innej klasy do przechowywania planszy
Klasa bedzie miala funkcje next_move() która wywolana:
    - wezmie kolejny ruch od odpowiedniego gracza (funkcji)
    - sprawdzi czy ruch jest poprawny
    - zmieni odpowiednio plansze (wywolujac jakas jej funkcje najprawdopodobniej)
    - zwroci odpowiednia wartosc (enum -> kto wygral, remis, czy trwa dalej, czy ruch byl niepoprawny)

Przydadza sie tez wczesniej wspomniane boty
Klasa Bot powinna zawierac funkcje, ktora za argument wezmie plansze (nie zmieniajac jej!) i zwroci swoj ruch
Nastepnie uchwyt do tej funkcji przekazemy do klasy game

Do tego na potrzeby testów potrzebujemy też api do wyświetlania trwajacej gry. cos w stylu GameViewer.
GameViewer bedzie zawieral petle obslugujaca gre

Funkcja main ma parsowac argumenty wejscia (moze zrobic jakies --help? itp) a nastepnie tworzyc game oraz gameviewer
oraz wywolac odpowiednia logike gameviewera zeby mozna bylo sobie testowac dzialanie.

Jest to oczywiscie prototyp, wiec jak macie jakies lepsze pomysly to dawajcie; od czegoś trzeba zaczac

# Organizacja pracy
Fajnie by było, zeby kazdy pracowal na swoim branchu
Do tego jesli zaczynacie prace nad jakas funkcjonalnoscia, stworzcie odpowieni Issue, tak, zeby inni nie robili tego co wy
No i oczywiscie zanim zaczniecie nad czyms pracowac, warto przejrzec ta zakladke
Mozecie sie dobierac dowolnie w jakies podzespoly, wtedy kilka osob bedzie pracowalo nad x rzecza, musicie sie juz dogadywac

Jesli macie pomysly tez otwierajcie issue, mamy sporo osob w grupie wiec warto to zrobic w taki sposob
Do tego beda dodatkowe punkty za estetyke

Jak chcecie miec collaba to was pododaje tylko musicie mi dac wasze konta na github. mimo wszystko nie pushujcie na maina,
za kazdym razem odpowiednie pull requesty powinny byc tworzone (nawet jesli to wy mergujecie)

# Odpalanie aplikacji
Do budowania projektu uzyjemy CMake, warto by dodac na readme jakis poradnik jak budowac/odpalac gre
wszystkie pliki zrodlowe w katalogu src, natomiast w katalogu build bedzie katalog obj na pliki obiektowe, oraz w samym katalogu build powinna znalezc sie skompilowana aplikacja

w gitignore bedziemy ignorowac katalog build

# Nazewnictwo
nazwy klas, struktow itp GameViewer
nazwy funkcji mainLoop()
nazwy pól board_, value_ itp
mozecie zmienic jak chcecie ale zeby to jakos bylo sensownie we wszystkich plikach, najwyzej potem jakis refactor siadzie to nie ma az takego znaczenia.
Ważne zeby kazda funkcja miala okreslone, jasne zadanie -> latwiej sie bedzie pracowac
Zalecam unikać nestowania, zawsze po prostu mozna walnac pomocnicza funkcje
ja moge robic jakis refactor przy mergowaniu, moze ze ktos sie lepiej na tym zna, to mowcie idc

# Pytania
jak macie pytania to issue albo grupa na mess


# Trello:
https://trello.com/b/1WFJDWvP/pwi-warcaby