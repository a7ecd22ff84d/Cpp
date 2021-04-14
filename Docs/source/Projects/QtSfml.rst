QtSfml
===============================================================================

Prosta biblioteka do wyświetlania okna SFML w okie programu Qt.

Motywacja: Chciałbym napisać aplikację która pozwoli na graficzne
przedstawienie działania różnych algorytmów. Tworzenie wielu prostych programów
lub jednego wielkiego, który byłby sterowany tylko np. klawiszami nie wchodziło
w grę. Podobnie jak ręczne rzeźbienie kontrolek w oknie SFML. Jedyne co mi
zostało to połączenie okien Qt i SFML

Użycie
*******************************************************************************

Aktualnie zawiera tylko jedną klasę :code:`QtSfmlCanvas`. W oknie Qt należy
dodać widget a następnie użyć opcji :code:`promote to` i wybrać wyśej
wspomnianą klasę. Widgetu :code:`QtSfmlCanvas` używa się tak jak okna SFML

Aktualnie obsługiwane funckjonalności
*******************************************************************************

**Zmiana rozmiaru** - :code:`QtSfmlCanvas` reaguje na zmianę rozmiaru okna Qt.
Dostępne są trzy rodzaje zmiany rozmiaru

    * rozciągnięcie obrazu do aktualnego okna
    * zachowanie proporcji i przybliżenia obrazu
    * zachowanie proporcji przy maksymalnym możliwym przybliżeniu

**Ustawianie widoku** - działa analogicznie do funkcji :code:`setView()` z SFML

Plany na przyszłość
*******************************************************************************

* Dodanie obsługi klawiatury i myszki
* Możliwość zapisywania obrazu oraz filmowania aktualnego okna SFML

