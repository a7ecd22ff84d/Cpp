#ifndef JOURNAL_PAGE_CONTROLLER
#define JOURNAL_PAGE_CONTROLLER

#include <QObject>
#include <QVector>

#include "Journal/App/Models/JournalEntriesModel.h"
#include "Journal/Database/Entities/Entry.h"

namespace Journal
{
class JournalPageController : public QObject
{
	Q_OBJECT // NOLINT
	Q_PROPERTY(JournalEntriesModel* entriesModel READ getEntriesModel NOTIFY entriesModelChanged)

public:
	JournalPageController(QObject* parent = nullptr);

	auto getEntriesModel() -> JournalEntriesModel*;

public slots:
	void initPage();

signals:
	void entriesModelChanged(JournalEntriesModel*);

private:
	JournalEntriesModel entriesModel;
};

} // namespace Journal

#endif