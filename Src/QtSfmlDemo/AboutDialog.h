#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui
{
class AboutDialog;
}

namespace Qsd
{
class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AboutDialog(QWidget* parent = nullptr, const QString& text = "");
	~AboutDialog();

private:
	Ui::AboutDialog* ui;
};

} // namespace Qsd

#endif // ABOUTDIALOG_H
