Todo
###############################################################################

I. Podstawowa konfiguracja
*******************************************************************************
* OK Dokumentacja
    * OK init
    * OK foldery docelowe - bin, build
    * OK integracja z cmake
* OK Git
    * OK gitignore
    * OK repo na githubie
* OK CMake
    * OK podstawowy projekt
    * OK kompilacja i uruchomienie


II. Dokumentacja
*******************************************************************************
Różne pierdoły do opisania

* pomysły na projekty
    * OK generator baz danych
    * OK sfml
    * qml


III. Ogólne
*******************************************************************************
Różne zadania nie związane z żadnym konkretnym projektem

1.  [OK] Biblioteka sqlite - pobieranie SQlite za pomocą cmake

2.  [OK] Biblioteka testów jednostkowych - pobieranie googletest za pomocą cmake

3.  Biblioteka do formatowania tekstu - biblioteka fmt - tak jak poprzednio
    pobieranie za pomocą cmake

4.  Jakiś sposób na dodanie logu do programów

5.  Ustawienia pythona - tworzenie virtual_env, instalacja modułów i
    uruchamianie skryptów z poziomu cmake

6.  Do sprawdzenia w wolnej chwili ten sposób pobierania googletest
    https://crascit.com/2015/07/25/cmake-gtest/

IV. Biblioteka bazy danych
*******************************************************************************
Moduł: Src/Database

1.  Klasa Database - do łączenia z bazą danych - przechowuje handlera
    połączenia do bazy. Otwiera i zamyka połączenie. Brak testów

2.  Klasa Query i polecenie executeCommand()

    * dodać testy jednostkowe modułu database
    * zapytanie tworzące bazę danych
    * "ręczne" sprawdzenie poprawności działania - normalne testy jednostkowe
      będą możliwe do zrobienia po dodaniu klasy Dataset i funkcji
      pobierającej wynik zapytania

3.  Pobieranie wyniku zapytania

    * klasa Dataset operująca na wynikach zapytania sqlite 
    * testy jednostkowe
    * typy proste
    * wartości opcjonalne
    * błędne wartości
    * inne typy (czas?)

