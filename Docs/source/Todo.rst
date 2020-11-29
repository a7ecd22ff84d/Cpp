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
    * OK qml


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

6.  Czas życia obiektu statement - problem polega na tym, że jeśli wykonamy
    `auto dataset = Db::Query().execute()` to klasa dataset utworzy się
    normalnie, ale sqlite3_stmt używany w datasecie nie zostanie zniszczony
    przez tymczasowy obiekt Query.

    * test jednostkowy z użyciem jak powyżej
    * przechowywanie wskaźnika do sqlite3_stmt w shared_ptr
    * custom deleter, który wykona slite3_finalize() na statemencie
    * przekazywanie shared_ptr do Datasetu
    * teraz statement powininen zostać zwolniony tylko, jeśli zarówna Query jak
      i Dataset zostaną zniszczone

7.  [OK] Dataset - różne poprawki

    * [OK] obsługa błędów - błędna nazwa kolumny
    * [OK] spradzanie czy dataset jest pusty
    * [OK] obsługa wielu wierszy zapytania
    * [OK] obsługa błędów - pusty dataset

8.  Dataset - pobieranie wartości z statementu

    * przeniesienie kodu pobierającego wartości do nowego pliku
    * obsługa błędów - bład parsowania wartości kolumny na typ
    * obsługa błędów - próba pobrania wartości z nulla

9.  Obsługa optionali

    * zapis nulla do bazy danych
    * zapis optionali do bazy danych
    * odczyt nulla z bazy
    * odczyt wartości do optionala

10.  Obsługa dat - do zrobienia po dodaniu biblioteki z datami