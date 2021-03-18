#ifndef GAMECONTROLS_H
#define GAMECONTROLS_H

#include <QWidget>

#include "QtSfmlDemo/Demos/TestApp/GameEngine.h"

namespace Ui
{
class GameControls;
}

class GameControls : public QWidget
{
	Q_OBJECT

public:
	explicit GameControls(QWidget* parent, GameEngine* gameEngine);
	~GameControls();

private:
	void connectControlsToEngine();

private:
	Ui::GameControls* ui;
    GameEngine* gameEngine;
};

#endif // GAMECONTROLS_H
