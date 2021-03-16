#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "QtSfml/QtSfmlCanvas.h"
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

private:
	Ui::MainWindow* ui;
	std::unique_ptr<TestDemo> testDemo;
	std::unique_ptr<InitialProgram> initialProgram;
};
#endif // MAINWINDOW_H
