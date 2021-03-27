Zrobione
###############################################################################

I. Podstawowa konfiguracja
*******************************************************************************
* [OK] Dokumentacja
    * [OK] init
    * [OK] foldery docelowe - bin, build
    * [OK] integracja z cmake
* [OK] Git
    * [OK] gitignore
    * [OK] repo na githubie
* [OK] CMake
    * [OK] podstawowy projekt
    * [OK] kompilacja i uruchomienie

II. Dokumentacja
*******************************************************************************
Różne pierdoły do opisania

* pomysły na projekty
    * [OK] generator baz danych
    * [OK] sfml
    * [OK] qml

III. C++
*******************************************************************************

:(

IV. Ogólne
*******************************************************************************

1.  [OK] Biblioteka sqlite - pobieranie SQlite za pomocą cmake

2.  [OK] Biblioteka testów jednostkowych - pobieranie googletest za pomocą cmake

3.  [OK] Biblioteka do formatowania tekstu - biblioteka fmt - tak jak poprzednio
    pobieranie za pomocą cmake

IV. Biblioteka bazy danych - moduł Database
*******************************************************************************
1.  [OK] Klasa Database - do łączenia z bazą danych - przechowuje handlera
    połączenia do bazy. Otwiera i zamyka połączenie. Brak testów

2.  [OK] Klasa Query i polecenie executeCommand()

    * [OK] dodać testy jednostkowe modułu database
    * [OK] zapytanie tworzące bazę danych
    * [OK] "ręczne" sprawdzenie poprawności działania - normalne testy
      jednostkowe będą możliwe do zrobienia po dodaniu klasy Dataset i funkcji
      pobierającej wynik zapytania

3.  [OK] Proste pobieranie wyniku zapytania

    * [OK] klasa Dataset operująca na wynikach zapytania sqlite 
    * [OK] testy jednostkowe
    * [OK] typy proste

4.  [OK] Obsługa parametrów w zapytaniach

    * [OK] sprawdzić na ile używalne jest to co mam w starym projekcie
    * [OK] nowa funkja w pliku TestTable - insert z parametrami
    * [OK] test jednostkowy - rozwiązanie
    * [OK] obsługa błędów - błędna nazwa parametru
    * [OK] obsługa błędów - parametr nie został ustawiony

5.  [OK] Query obsługa błędów

    * [OK] executeCommand zwraca coś z zapytania
    * [OK] zapytanie zwraca błąd - np. naruszenie contraintów
    * [OK] sprawdzanie błędów po ustawieniu parametru
    * [OK] wielokrotne używanie zapytania

6. [OK] Czas życia obiektu statement - problem polega na tym, że jeśli wykonamy
`auto dataset = Db::Query().execute()` to klasa dataset utworzy się
normalnie, ale sqlite3_stmt używany w datasecie zostanie zniszczony przez
tymczasowy obiekt Query.

    * [OK] test jednostkowy z użyciem jak powyżej
    * [OK] przechowywanie wskaźnika do sqlite3_stmt w shared_ptr
    * [OK] custom deleter, który wykona slite3_finalize() na statemencie
    * [OK] przekazywanie shared_ptr do Datasetu
    * [OK] teraz statement powininen zostać zwolniony tylko, jeśli zarówna Query jak
      i Dataset zostaną zniszczone

7.  [OK] Dataset - różne poprawki

    * [OK] obsługa błędów - błędna nazwa kolumny
    * [OK] spradzanie czy dataset jest pusty
    * [OK] obsługa wielu wierszy zapytania
    * [OK] obsługa błędów - pusty dataset

8.  [OK] Dataset - pobieranie wartości z statementu

    * [OK] przeniesienie kodu pobierającego wartości do nowego pliku
    * [OK] obsługa błędów - bład parsowania wartości kolumny na typ
    * [OK] obsługa błędów - próba pobrania wartości z nulla

9.  [OK] Obsługa optionali

    * [OK] zapis nulla do bazy danych
    * [OK] zapis optionali do bazy danych
    * [OK] odczyt nulla z bazy
    * [OK] odczyt wartości do optionala

11. [OK] Pobieranie wartości z bazy danych chyba nie działa najlepiej. Przynajmniej
    ja nie jestem z tego zadowolony. Wydaje się, że zamiast używania funkcji
    tryToCast powinienem użyć tabelki ze strony
    https://www.sqlite.org/c3ref/column_blob.html oraz informacji o castowaniu
    z https://www.sqlite.org/lang_expr.html#castexpr. Docelowo miałoby to
    działać tak, że pobieramy tekst za pomocą `sqlite3_column_text` a następnie
    w zależności od tego czy wskaźnik jest pusty czy nie podejmować decyzję co
    dalej.

VI.  Generator kodu i zapytań sql - moduł SqlQueryGenerator
*******************************************************************************

:(

VII. Połączenie okna qml z sfml - moduł QtSfml
*******************************************************************************

1. Przygotowanie środowiska pracy i przykładowy projekt

 *  [OK] instalacja qt
 *  [OK] biblioteka sfml
 *  [OK] przykładowy projekt w qml
 *  [OK] panel okna sfml w qt

2. Interakcja kontrolek z oknem sfml

 *  [OK] wyświetlenie prostego obiektu w panelu sfml
 *  [OK] przyciski do przesuwania obiektu/zmiany koloru w panelu qml
 *  [OK] reakcja na wciśnięcie przycisków
 *  [OK] wyświetlanie pozycji obiektu w panelu qml
 *  [OK] przycisk "Reset" przywracający ustawienia początkowe

3. Zmiana rozmiaru okna

 *  [OK] zmiana rozmiaru okna qml
 *  [OK] zmiana rozmiaru panelu sfml
 *  [OK] wywołanie resize na oknie sfml
 *  [OK] rozciąganie do nowego rozmiaru
 *  [OK] zachowywanie proporcji
 *  [OK] zachowywanie zoomu
 *  [OK] używanie widoków (sf::View) do zarządzania ekrnem
    https://www.sfml-dev.org/tutorials/2.1/graphics-view.php#showing-more-when-the-window-is-resized

VIII. Graficzna demonstracja działania róznych algorytmów - QtSfmlDemo
*******************************************************************************

1. Przerobienie QtSfml na bibliotekę

 * [OK] nowy projekt, QtSfmlDemo, który będzie zawierał przykładową aplikację
 * [OK] w projekcie QtSfml zostaje tylko Canvas i wyszystko co jest potrzebne do
   jego działania
 * [OK] możliwość wyboru demo/algorytmu z menu programu - przełączanie się między
   różnymi enginami
