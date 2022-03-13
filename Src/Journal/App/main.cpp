#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Journal/App/DatabaseManager.h"
#include "Journal/App/Models/JournalEntriesModel.h"

auto main(int argc, char* argv[]) -> int
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty(
		"databaseManager", new Jrnl::DatabaseManager);

	qmlRegisterType<Journal::JournalEntriesModel>("Journal", 1, 0, "EntriesModel");
	
	const QUrl url(QStringLiteral("qrc:/LoginDialog.qml"));
	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreated,
		&app,
		[url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
