Todo
###############################################################################

I. Podstawowa konfiguracja
*******************************************************************************

:)

II. Dokumentacja
*******************************************************************************
Różne pierdoły do opisania

* [OK] Moduł bazy danych - projekt jest już prawie skończony więc może warto
  to opisać, żeby w przyszłości nie tracić czasu na przypominanie sobie tego
  wszystkiego
* [OK] QtSfml - opisać aktualne działanie QtSfmlCanvas
* [OK] QtSfml - opisać aktualne działanie Programu demonstracyjnego
* [OK] QtSfml - opisać działanie generatora labiryntów
* CppTests - opisać po co i na co to

III. C++
*******************************************************************************
Nauka i testy róznych zagadnień związanych z C++

1. Rule of zero

2. Słowo kluczowe explicit

3. Virtual, override, final

 * czy jest sens pisać Virtual jeśli metoda jest final lub override
 * czysto wirtualne metody prywatne

IV. Ogólne
*******************************************************************************
Różne zadania nie związane z żadnym konkretnym projektem

4.  Jakiś sposób na dodanie logu do programów - biblioteka spdlog

5.  Ustawienia pythona - tworzenie virtual_env, instalacja modułów i
    uruchamianie skryptów z poziomu cmake

6.  Do sprawdzenia w wolnej chwili ten sposób pobierania googletest
    https://crascit.com/2015/07/25/cmake-gtest/

7.  Biblioteka do obsługi dat - hinnant/date

9.  Kiedyś tam chciałbym dodać tłumaczenia do programów

10. Klasa so obsługi tablic 2D - do zrobienia jak zrobię obsługę dynamicznego
    wyboru rozmiaru labiryntu

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

0. Błędy i sprawy ogólne

 * Błąd - nie ładuje się widok podczas uruchamiania programu.
   Widoczne w labiryntach jeśli początkowy rozmiar labiryntu jest różny od
   30x24. Pomimo tego, że do QtSfmlCanvas jest przekazywany poprawny widok to
   i tak nie jest to uwzględniane podczas zmiany rozmiaru okna.
   Kliknięcie przycisku 'reset' sprawia, że widok w oknie sfml jest ładnie
   przycinany do aktualnego rozmiaru labiryntu
 * [OK] Błąd - podczas maksymalizacji programu dzieją się różne cuda z oknem
   SFML
 * Dodać funckję resetView, która ustawi domyślny widok - zgodny aktualnym
   rozmiarem okna 

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
   program zwalnia. Potwierdza to dodany ostatnio licznik fps
 * [OK] Dodać do programu licznik klatek animacji - częsciowo powiązane z powyższym
   błędem
 * [OK] Błąd - Nie działa przełączanie między programami. Widget z kontrolkami
   nie ładuje się po zmianie programu
 * Dodać obsługę zapisu aktualnej ramki okna sfml lub nawet całego programu
 * Dodać obsługę zapisu filmu z ramki okna sfml lub nawet całego programu
 * Dodać opis programu razem z uzywanymi bibliotekami zewnętrznymi
 * Dodać obsługę File->Close
 * Wspólny interfejs do przełączania się między programami - może jakaś fabryka
   algorytmów, która pozwoli na łatwe przełączanie się między programami
 * Dodać opisy programów init i control test
 * Weryfikacja - dlaczego jest wymagany :code:`show()` w kontruktorze
   MazeProgram
 
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
 * [OK] rozszerzenie programu o nowe algorytmy
 * generowanie losowego seeda - nowy przycisk i tworzenie losowego tekstu
 * [OK] nowy algorytm - Randomized Kruskal's
 * [OK] Zmiana aktywnego algorytmu w runtime - fabryka
 * [OK] Błąd - chyba nie do końca działa seed. Przy pierwszym użyciu algorytmu
   Kruskala wynik jest inny niż przy każdym kolejnym
 * [OK] Optymalizacja - Kruskal - sprawdzić czy można w łatwy sposób usunąć zbędne
   krawędzie po dodaniu komórki do grupy lub połączeniu grup
   (remove_if(contains(...))
 * Optymalizacja - założyć, że przejścia dodawane do labirytnu będą zawsze na
   wschód lub południe. Pozwoli to pominięcie sprawdzania, która komórka jest
   pierwsza w róznych sytuacjach, np. podczas rysowania lub algorytmu kruskala
 * Dodać opis programu w Help->About this program
 * zapis wyniku do pliku graficznego
 * zapis wyniku do pliku tekstowego
 * możliwość sprawdzenia historii generowania algorytmu

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
