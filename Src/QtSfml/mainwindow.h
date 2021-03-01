#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QTimer>

#include "QtSfml/GameEngine.h"
#include "QtSfml/GameState.h"
#include "QtSfml/QtSfmlCanvas.h"

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

	void initGameState();
	void initTimer();
	void connectButtonsToEngine();

private slots:
	void update();

private:
	Ui::MainWindow* ui;
	std::unique_ptr<GameEngine> gameEngine;
	GameState initialState;
	QTimer timer;
};
#endif // MAINWINDOW_H
