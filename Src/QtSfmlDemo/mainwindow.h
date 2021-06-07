#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <string_view>

#include <QMainWindow>
#include <QMenu>
#include <QTimer>

#include "Core/Factory/RegistrableFactory.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/BaseDemo.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void aboutCurrentProgram();
	void aboutThisProgram();
	
private:
	template<typename T>
	void registerDemo(QMenu* menu, std::string_view name);
	void registerDemos();

	void reset(std::string_view name);

private:
	QTimer timer;

	Ui::MainWindow* ui;
	Qsd::DemoContext context;

	Factory::RegistrableFactory<Qsd::BaseDemo> demoFactory;
	std::unique_ptr<Qsd::BaseDemo> currentProgram;
};

#endif // MAINWINDOW_H
