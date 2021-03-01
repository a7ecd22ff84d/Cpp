Instalacja
*******************************************************************************

Czyli czego potrzebuję, żeby to wszystko skompilować i uruchomić

Większość bibliotek powinna zostać pobrana i skompilowana przez CMake, będzie
to działać tak długo aż się nie zmienią linki do bibliotek :) Niektóre
narzędzia i biblioteki wymagają osobnej instalacji (np. Qt). Brak tutaj opisu
instalacji samego systemu budowania. Być może dodam coś takiego jak będę
przenosił projekt na nowy system. 

Qt
===============================================================================

Instalacja qt
sudo apt-get install qt5-default

Dodatkowo będzie potrzebny qml, bez tego cmake rzuci błędem
Could not find a package configuration file provided by "Qt5Qml"...

Można to zainstalować za pomocą polecenia

.. code-block:: console

    sudo  apt-get install qtdeclarative5-dev

Źródło: https://forum.kde.org/viewtopic.php?f=305&t=142524

Oprócz tego w trakcie próby rozwiązania będu instalowałem jeszcze coś takiego

.. code-block:: console

    sudo apt install qml-module-qtquick-controls
    sudo apt install qtquickcontrols2-5-dev

Źródło: https://stackoverflow.com/questions/61035958/qtcreator-cant-find-qt-quick-on-ubuntu-18-04

Nie wiem czy w jakikolwiek sposób pomogło ale zapisuję na przyszłość.

Tutaj też jest ciekawa lista tego co trzeba zainstalować
https://www.apriorit.com/dev-blog/475-qt-qml-with-cmake