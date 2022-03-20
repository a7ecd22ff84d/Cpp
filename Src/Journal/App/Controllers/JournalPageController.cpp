#include "Journal/App/Controllers/JournalPageController.h"

#include <QDebug>
#include <QObject>
#include <date/date.h>

namespace
{
using date::March;
using date::year;

} // namespace

namespace Journal
{
JournalPageController::JournalPageController(QObject* parent) : QObject(parent)
{
	auto createEntry =
		[](int id, date::year_month_day date, const std::string& title) {
			auto entry = Entities::Entry();
			entry.setId(id);
			entry.setEntryDate(date);
			entry.setTitle(title);

			return entry;
		};

	entries.append(createEntry(1, date::year(2022) / March / 01, "gadsfs"));
	entries.append(createEntry(2, date::year(2022) / March / 02, "dashfduias"));
	entries.append(createEntry(3, date::year(2022) / March / 03, "shfis"));
	entries.append(createEntry(4, date::year(2022) / March / 04, "dupadupa"));

	entriesModel.setEntries(entries);
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
