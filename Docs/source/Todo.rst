Todo
###############################################################################

I. Podstawowa konfiguracja
*******************************************************************************

:)

II. Dokumentacja
*******************************************************************************
Różne pierdoły do opisania

* Moduł bazy danych - projekt jest już prawie skończony więc może warto to
  opisać, żeby w przyszłości nie tracić czasu na przypominanie sobie tego
  wszystkiego

III. C++
*******************************************************************************
Nauka i testy róznych zagadnień związanych z C++

1.  Rule of zero

IV. Ogólne
*******************************************************************************
Różne zadania nie związane z żadnym konkretnym projektem

4.  Jakiś sposób na dodanie logu do programów

5.  Ustawienia pythona - tworzenie virtual_env, instalacja modułów i
    uruchamianie skryptów z poziomu cmake

6.  Do sprawdzenia w wolnej chwili ten sposób pobierania googletest
    https://crascit.com/2015/07/25/cmake-gtest/

7.  Biblioteka do obsługi dat

9.  Kiedyś tam chciałbym dodać tłumaczenia do programów

V. Biblioteka bazy danych - moduł Database
*******************************************************************************
Moduł: Src/Database

10. Obsługa dat - do zrobienia po dodaniu biblioteki z datami

12. Zastanowić się czy chcę, żeby null i pusty string znaczyły co innego czy
    może jak trafimy na nulla w bazie danych to przerabiamy po cichu na pustego
    stringa.

VI.  Generator kodu i zapytań sql - moduł SqlQueryGenerator
*******************************************************************************

1.  Język opisu bady danych

    * gdzie powinny być umieszczone pliki z opisem baz danych tak, żeby sobie
      nie narobić syfu przy większej ilości projektów
    * lista kolumn w danej bazie wraz z typem
    * zależności między kolumnami (constrainty, indeksy, komentarze itp)

2.  Generowanie zapytań tworzących tabelę

    * klasa generatora + testy
    * zapytania tworzącę bazę danych

3.  Generowanie zapytań modyfikujących bazę danych

    * select
    * insert
    * delete
    * kolumy tabeli do selecta - potrzebne przy pobieraniu danych z wielu 
      tabeli jenocześnie
    * prefix do kolumn w selecie

4.  Generowanie encji bazodanowych

    * zapis w CMakeLists, że chcę, żeby encja powstała w tym miejscu

5. Utworzenie pliku z resourcami do plików z definicją bazy danych. Nie chcę,
   żeby w katalogu bin walały się surowe pliki tekstowe

VII. Połączenie okna qml z sfml - moduł QtSfml
*******************************************************************************

1. Przygotowanie środowiska pracy i przykładowy projekt

 *  OK instalacja qt
 *  OK biblioteka sfml
 *  OK przykładowy projekt w qml
 *  OK panel okna sfml w qt

2. Interakcja kontrolek z oknem sfml

 *  OK wyświetlenie prostego obiektu w panelu sfml
 *  OK przyciski do przesuwania obiektu/zmiany koloru w panelu qml
 *  OK reakcja na wciśnięcie przycisków
 *  OK wyświetlanie pozycji obiektu w panelu qml
 *  OK przycisk "Reset" przywracający ustawienia początkowe

3. Zmiana rozmiaru okna

 *  OK zmiana rozmiaru okna qml
 *  OK zmiana rozmiaru panelu sfml
 *  OK wywołanie resize na oknie sfml
 *  OK rozciąganie do nowego rozmiaru
 *  OK zachowywanie proporcji
 *  OK zachowywanie zoomu
 *  OK używanie widoków (sf::View) do zarządzania ekrnem
    https://www.sfml-dev.org/tutorials/2.1/graphics-view.php#showing-more-when-the-window-is-resized

4. Obsługa klawiatury i myszki

 * sterowanie obiektem na scenie za pomocą klawiszy kierunkowych
    * focus na oknie qt
    * focus na oknie sfml
 * obsługa kliknięć myszki w oknie sfml

VIII. Graficzna demonstracja działania róznych algorytmów - QtSfmlDemo
*******************************************************************************

1. Przerobienie QtSfml na bibliotekę

 * OK nowy projekt, QtSfmlDemo, który będzie zawierał przykładową aplikację
 * OK w projekcie QtSfml zostaje tylko Canvas i wyszystko co jest potrzebne do
   jego działania
 * możliwość wyboru demo/algorytmu z menu programu - przełączanie się między
   różnymi enginami

2. Algorytm - generator labiryntów

 * nowe demo na liście - "Generator labiryntów" (powiązane z poprzednim
   zadaniem
 * rysowanie siatki na ekranie
 * rysowanie predefiniowanego labiryntu
 * generowanie labiryntu o stałych rozmiarach
 * parametr generowania - rozmiar

3. Algorytm - szum Perlina

 * nowe demo na liście - "Szum Prelina"
 * generowanie szumu z stałymi parametrami
 * kontrolki do ustawiania prametrów

4. Demo "Krople deszczu"

 * Dodanie obsługi myszki do QtSfml - zadanie w projekcie QtSfml
 * nowe demo na liście
 * rysowanie fali po kliknięciu myszką w okno sfml
 * "siła" fali zależna od długości kliknięcia
 * generowanie losowych fal - rózne parametry, siła, częstotliwość itp.
 * generowanie fal po kliknięciu gdziekolwiek w programie poza oknem sfml
   (sprawdzić, czy jest to możliwe)
