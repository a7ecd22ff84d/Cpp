#include "Journal/App/Controllers/LoginDialogController.h"
#include "Journal/Database/Database.h"

namespace Journal
{
LoginDialogController::LoginDialogController(QObject* parent)
	: QObject(parent)
{
}

void LoginDialogController::create(const QString& filename)
{
	Database::instance().create(filename.toStdString());
}

void LoginDialogController::open(const QString& filename)
{
	Database::instance().open(filename.toStdString());
}

} // namespace Journal