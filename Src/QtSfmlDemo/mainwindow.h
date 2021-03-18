#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QTimer>

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
	void initMenuButtons();
	void reset();

private:
	Ui::MainWindow* ui;
	std::unique_ptr<TestDemo> testDemo;
	std::unique_ptr<InitialProgram> initialProgram;
	std::unique_ptr<MazeProgram> mazeProgram;

	QTimer timer;
};
#endif // MAINWINDOW_H
