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

1. Rule of zero

2. Słowo kluczowe explicit

3. Virtual, override, final - czy jest sens pisać Virtual jeśli metoda jest
   final lub override

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

10. Klasa so obsługi tablic 2D - do zrobienia jak zrobię obsługę dynamicznego
    wyboru rozmiaru labiryntu

11. Konwersja QString na string view -> testy i zastąpić miejsce w programie,
    gdzie użyłem prostego
    :code:`[string_view] context.seed = ui->seedEdit->text().toStdString();`

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

4. Obsługa klawiatury i myszki

 * sterowanie obiektem na scenie za pomocą klawiszy kierunkowych
    * focus na oknie qt
    * focus na oknie sfml
 * obsługa kliknięć myszki w oknie sfml

VIII. Graficzna demonstracja działania róznych algorytmów - QtSfmlDemo
*******************************************************************************

0. Błędy i sprawy ogólne
  
 * Błąd? - Problem z wydajnością przy dużej ilości elementów. Na razie problem
   dotyczy tylko labiryntów - mam wrażenie, że przy wielkich labiryntach
   program zwalnia. Do sprawdzenia, czy jest to problem ogólny czy np. wina
   sposobu wyświewietlania elementów na ekranie
 * Dodać do programu licznik klatek animacji - częsciowo powiązane z powyższym
   błędem
 * Błąd - Nie działa przełączanie między programami. Widget z kontrolkami nie
   ładuje się po zmianie programu
 * Błąd - podczas maksymalizacji programu dzieją się różne cuda z oknem SFML

2. Algorytm - generator labiryntów

 * [OK] nowe demo na liście - "Generator labiryntów" (powiązane z poprzednim
   zadaniem
 * [OK] rysowanie siatki na ekranie
 * [OK] rysowanie predefiniowanego labiryntu
 * [OK] generowanie labiryntu o stałych rozmiarach - krok po kroku
 * [OK] generowanie labiryntu o stałych rozmiarach - generowanie całego labiryntu
 * [OK] generowanie labiryntu o stałych rozmiarach - animacja
 * [OK] parametr generowania - rozmiar
 * [OK] parametr generowania - ziarno
 * zapis wyniku do pliku graficznego
 * zapis wyniku do pliku tekstowego
 * rozszerzenie programu o nowe algorytmy
 * generowanie losowego seeda - nowy przycisk i tworzenie losowego tekstu
 * [OK] nowy algorytm - Randomized Kruskal's
 * [OK] Zmiana aktywnego algorytmu w runtime - fabryka
 * Błąd - chyba nie do końca działa seed. Przy pierwszym użyciu algorytmu
   Kruskala wynik jest inny niż przy każdym kolejnym
 * Optymalizacja - Kruskal- sprawdzić czy można w łatwy sposób usunąć zbędne
   krawędzie po dodaniu komórki do grupy lub połączeniu grup
   (remove_if(contains(...))

3. Algorytm - szum Perlina

 * nowe demo na liście - "Szum Prelina"
 * generowanie szumu z stałymi parametrami
 * kontrolki do ustawiania prametrów

4. Demo "Krople deszczu"

 * Dodanie obsługi myszki do QtSfml - zadanie w projekcie QtSfml
 * nowe demo na liście
 * rysowanie fali po kliknięciu myszką w okno sfml
 * wiele fal na raz, nachodzenie się fal
 * "siła" fali zależna np. od długości kliknięcia
 * generowanie losowych fal - rózne parametry, siła, częstotliwość itp.
 * generowanie fal po kliknięciu gdziekolwiek w programie poza oknem sfml
   (sprawdzić, czy jest to możliwe)
