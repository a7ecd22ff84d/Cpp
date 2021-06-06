#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QTimer>

#include "Core/Factory/RegistrableFactory.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"
#include "QtSfmlDemo/Demos/Init/InitProgram.h"
#include "QtSfmlDemo/Demos/TestApp/TestDemo.h"

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

private:
	void registerDemos();
	void initMenuButtons();
	void reset(std::string_view name);

private:
	QTimer timer;
	
	Ui::MainWindow* ui;
	Qsd::DemoContext context;

	Factory::RegistrableFactory<Qsd::BaseDemo> demoFactory;
	std::unique_ptr<Qsd::BaseDemo> currentProgram;
};
#endif // MAINWINDOW_H
