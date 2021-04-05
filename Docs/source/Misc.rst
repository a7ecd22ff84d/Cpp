Rózne różności
===============================================================================

**Refactor**
    * namespace Mazes do wszystkiego związanego z labiryntami
    * może osobna biblioteka do obsługi kontenerów - utworzyć tam funkcję
      selectRandomElement() lub contains()

**Fabryka w c++ - template**
    Aktualnie zajmuję się tworzeniem fabryki generatorów algorytmów. Później,
    jak będę robił aplikację bazodową to chciałbym utworzyć fabrykę obiektów
    dao. 
    Wydaje się, że możliwe będzie będzie utworzenie fabryki jako template,
    która teoretycznie powinna obsłużyć każdy typ obiektu. Do sprawdzenia jak
    już skończę się bawić z labiryntami.
    Do stworzenia templatowa fabryka gdzieś w bibliotece core
