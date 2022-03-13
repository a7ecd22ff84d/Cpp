#include "Journal/App/Models/JournalEntriesModel.h"

#include <date/date.h>

#include "Journal/Database/Entities/Entry.h"

namespace
{
using date::March;
using date::year;

} // namespace

namespace Journal
{
JournalEntriesModel::JournalEntriesModel(QObject* parent)
	: QAbstractListModel(parent)
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
	entries.append(createEntry(4, date::year(2022) / March / 04, "ksdhfsd"));
}

auto JournalEntriesModel::rowCount(const QModelIndex& parent) const -> int
{
	if (parent.isValid())
		return 0;

	return entries.count();
}

auto JournalEntriesModel::data(const QModelIndex& index, int role) const -> QVariant
{
	if (!index.isValid())
		return QVariant();

	const Entities::Entry& entry = entries.at(index.row());
	if (role == Id)
	{
		return entry.getId();
	}
	else if (role == Date)
		return date::format("%F", entry.getEntryDate()).c_str();
	else if (role == Title)
		return entry.getTitle().c_str();
	else
		return QVariant();
}

auto JournalEntriesModel::roleNames() const -> QHash<int, QByteArray>
{
	static QHash<int, QByteArray> mapping{
		{Id, "id"}, {Date, "date"}, {Title, "title"}};
	return mapping;
}

} // namespace Journal
