#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Journal/App/Controllers/JournalPageController.h"
#include "Journal/App/Controllers/LoginDialogController.h"
#include "Journal/App/Models/JournalEntriesModel.h"

auto main(int argc, char* argv[]) -> int
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // TODO: po co to?
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	auto loginDialogController = new Journal::LoginDialogController();

	engine.rootContext()->setContextProperty(
		"loginDialogController", loginDialogController);

	qmlRegisterType<Journal::JournalEntriesModel>("Journal", 1, 0, "EntriesModel");
	qmlRegisterType<Journal::JournalPageController>("Journal", 1, 0, "JournalPageController");

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
