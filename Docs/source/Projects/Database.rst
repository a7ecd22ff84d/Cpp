Database - biblioteka baz danych Sqlite
===============================================================================

Wrapper na bibliotekę sqlite pozwalający na wygodne użycie w kodzie C++.

Motywacja: Zrobiłem kiedyś podobną bibliotekę w moim starym projekcie ale nie
byłem z niej zadowolony. Ta biblioteka to druga wersja wrappera. Jestem z niej
o wiele bardziej zadowolony niż z poprzedniej.

Przykłady użycia
*******************************************************************************

Zakładanie nowej bazy/łaczenie do istniejącej bazy danych
-------------------------------------------------------------------------------

.. code-block:: cpp

    auto db = Db::Database("path_to_database/name_of_database.db")

Wykonanie prostego zapytania
-------------------------------------------------------------------------------

Zapytanie wstawiające wiersz do bazy danych

.. code-block:: cpp

    auto sql = "insert into test_table(first, second) values (1, 2))";
    Db::Query(sql, &db).executeCommand();

Zapytanie wybierające dane z bazy danych

.. code-block:: cpp

    auto sql = "select m.first from test_table m";

    Db::Query query(sql, &db);
    auto dataset = query.execute();

Różnica między :code:`execute()` a :code:`executeCommand()` polega na tym, że
ten pierwszy zwraca dataset z wynikami zapytania. Próba użycia złej funkcji
zakończy się błędem.

Wykonanie zapytania z parametrami
-------------------------------------------------------------------------------

.. code-block:: cpp

    auto sql = "select first, second from test_table where id = :id";
    auto query = Db::Query(sql, &db);

    query.setParam(":id", 1);
    auto dataset = query.execute();

Przed wykonaniem zapytania nastepuje sprawdzenie czy wszystkie parametry
zostały ustawione. 

Obsługiwane typy: bool, int, double, string, oraz std::optional

Pobranie wyników zapytania
-------------------------------------------------------------------------------

.. code-block:: cpp

    auto sql = "select first, second from test_table";
    auto dataset =  Db::Query(sql, &db).execute();

    while(dataset.next())
    {
        v1 = dataset.get<int>("first")
        v2 = dataset.get<std::string>("second")
    }

Obsługiwane typy: bool, int, double, string, oraz std::optional

Wielokrotne użycie tego samego obiektu Query
-------------------------------------------------------------------------------

Zapytania można używać wielokrotnie, ustawione wcześniej paramery zostają
zachowane. Trzeba tylko wcześniej wywołać metodę :code:`reset()`.

Uwaga: użycie metody reset sprawi, że dane zapisane w datasecie zostaną
usunięte

.. code-block:: cpp

    auto dataset =  Db::Query("select ccc from ...", &db).execute();
    query.setParam(":aaa", 123);
    query.setParam(":bbb", "some_value");

    query.setParam(":id", 1);
    auto dataset = query.execute();
    auto var1 = dataset.get<int>("ccc");

    query.reset();
    query.setParam(":id", 2);
    auto dataset = query.execute();
    auto var2 = dataset.get<int>("ccc");

Metoda :code:`reset()` jest wywoływana automatycznie po wykonaniu zapytania za
pomocą :code:`executeCommand()` oraz po dotarciu do ostatniego wiersza
datasetu, np. podczas iteracji za pomocą pętli :code:`while`


Plany na przyszłość
*******************************************************************************

* Dodać obsługę dat korzystając z bilbioteki :code:`Date` Howarda Hinnanta
* Dodać możliwość definiowania zapisu/odczytu własnych obiektów z bazy danych
  podobnie jak ma to miejsce w bibliotece :code:`fmt`
* Poprawić obsługę standardowych typów z wykorzystaniem :code:`type_traits`
* Napisać jakąś prostą aplikację, która z tego korzysta