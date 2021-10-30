#include <QApplication>

#include "QtSfmlDemo/mainwindow.h"

auto main(int argc, char* argv[]) -> int
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
