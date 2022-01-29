#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <memory>

#include <QObject>

#include "Journal/Database/Database.h"

namespace Jrnl
{
class DatabaseManager : public QObject
{
   Q_OBJECT // NOLINT

public slots: 
	// auto create(const std::string& filename) -> std::unique_ptr<Database>;

	void create(const QString& filename);
};

} // namespace Jrnl

#endif