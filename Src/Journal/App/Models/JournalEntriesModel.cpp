#include "Journal/App/Models/JournalEntriesModel.h"

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

void JournalEntriesModel::setEntries(const QVector<Entities::Entry>& data)
{
	entries = data;
}

} // namespace Journal
