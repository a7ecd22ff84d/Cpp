#ifndef JOURNAL_ENTRIES_MODEL_H
#define JOURNAL_ENTRIES_MODEL_H

#include <qabstractitemmodel.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qvector.h>

#include "Journal/Database/Entities/Entry.h"

namespace Journal
{
class JournalEntriesModel : public QAbstractListModel
{
	Q_OBJECT // NOLINT

public:
	enum Roles
	{
		Id = Qt::UserRole,
		Date,
		Title
	};

	JournalEntriesModel(QObject* parent = nullptr);

	[[nodiscard]] auto rowCount(const QModelIndex& parent) const -> int override;
	[[nodiscard]] auto data(const QModelIndex& index, int role = Qt::DisplayRole) const
		-> QVariant override;
	[[nodiscard]] auto roleNames() const -> QHash<int, QByteArray> override;

	void setEntries(const QVector<Entities::Entry>& data);

private:
	QVector<Entities::Entry> entries;
};

} // namespace Journal

#endif
