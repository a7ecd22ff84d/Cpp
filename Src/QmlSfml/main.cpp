#include <QApplication>
#include <QQmlApplicationEngine>

#include <QtSfml/SfmlWindow.h>

int main(int argc, char** argv)
{
	qmlRegisterType<SfmlWindow>("MyItems", 1, 0, "SfmlWindow");

	QApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}