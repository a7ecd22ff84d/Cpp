#include "QtSfmlDemo/AboutDialog.h"

#include "./ui_AboutDialog.h"

namespace Qsd
{
AboutDialog::AboutDialog(QWidget* parent, const QString& text)
	: QDialog(parent)
	, ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
	ui->textBrowser->setText(text);

	connect(ui->closeDialog, &QPushButton::pressed, this, &AboutDialog::close);
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

} // namespace Qsd