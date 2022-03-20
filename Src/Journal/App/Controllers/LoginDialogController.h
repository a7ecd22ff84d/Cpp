#ifndef LOGIN_DIALOG_CONTROLLER_H
#define LOGIN_DIALOG_CONTROLLER_H

#include <QObject>

#include "Database/Database.h"

namespace Journal
{
class LoginDialogController : public QObject
{
	Q_OBJECT // NOLINT

public:
	LoginDialogController(QObject* parent = nullptr);

public slots:
	void create(const QString& filename);
	void open(const QString& filename);
};

} // namespace Journal

#endif