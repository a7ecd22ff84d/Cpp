#include "Journal/App/Controllers/JournalPageController.h"

#include <QDebug>
#include <QObject>
#include <date/date.h>

#include "Journal/Database/Dao/EntriesDao.h"
#include "Journal/Database/Database.h"

namespace Journal
{
JournalPageController::JournalPageController(QObject* parent) : QObject(parent)
{
	auto& db = Database::instance();
	auto data = EntriesDao(db.getDatabase(), db.getSqlGenerator()).getEntries();

	entriesModel.setEntries(QVector<Entities::Entry>::fromStdVector(data));
}

void JournalPageController::initPage()
{
	qDebug() << "JournalPageController::initPage()";
}

auto JournalPageController::getEntriesModel() -> JournalEntriesModel*
{
	return &entriesModel;
}

} // namespace Journal
