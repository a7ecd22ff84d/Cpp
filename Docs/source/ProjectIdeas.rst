Pomysły na projekty
###############################################################################

Róże pomysły nieposortowane w żaden sposób


Generator baz danych, encji i dao w C++
*******************************************************************************
Chodzi o to, żeby zrobić narzędzie, które przyśpieszy pracę z bazami danych.
Tworzenie baz danych i ich obsługi w C++ zawsze mnie zniechęcało do zrobienia
czegoś większego w C++ :(

Projekt będzie składał się z trzech części: 

#.  Język opisu bazy danych - zapisanie struktury bazy danych w łatwym do
    parsowania formacie
#.  Generator zapytań w C++ - na podstawie struktury bazy danych będą
    dynamicznie tworzone zapytania sql. Ciekawe czy da się to zrobić constexpr
    tak, żeby kompilator utworzył wszystkie zapytania w trakcie budowania
    projektu klas
    bazodanowych na podstawie struktury bazy danych
#.  Generator encji i dao w Pythonie - narzędzie do generowania

Generator zapytań w C++
===============================================================================
Powinien obsługiwać następujące typy zapytań:

*   Tworzenie tabeli w bazie danych
*   Tworzenie podstawowych zapytań select, insert, delete, (merge? nie ma go w
    SQLite)
*   Póżniej może warto będzie dodać pobieranie części zapytania, nazwy pól,
    prefixy itp.

Python - generator encji i dao
===============================================================================
Tworzenie encji przez CMake w trakcie przygotowywania plików projektowych na
podstawie wcześniej określonych plików (zapis w CMake lub nowy plik z 
definicją, gdzie utworzyć jaki plik)

Może być problem z obsługą tego przez gita (gitignore) - nie chciałem żadnych
tymczasowych plików w folderze build

Biblioteka do obsługi SQLite w C++
*******************************************************************************
Robiłem już kiedyś coś podobnego. Korzystając ze starego kodu utworzyć nową,
ładniejszą bibliotekę do obsługi bazy danych.

Uwagi:

* Obsługa pustych wartości - optionale
* Nie korzysta z generatora zapytań - to generator powinien od niej zależeć
* Testy tego czegoś?

SFML - Silnik gry oparty o kafelki
*******************************************************************************
Prosty silnik gry wyświetlający obraz w postaci kafelków. Chciałbym zrobić
kilka prostych projektów w oparciu o ten silnik. Przykłady:

* gra snake - bo czemu nie :)
* wyszukiwanie drogi - testy różnych algorytmów (A*)
* zakres widzenia - zgapione stąd: https://www.youtube.com/watch?v=fc3nnG2CG8U& 
* generowanie labiryntów
* rozwiązywanie labiryntów
* sudoku - tworzenie różnych kafelków z trakcie gry (wartości, błędy, możliwe
  wartości itp)

Połączenie okna sfml i qml
*******************************************************************************
Chciałbym dodać interfejs do gry w sfml bez rzeźbienia kontrolek na scenie.

