#ifndef __BASEDEMO_H
#define __BASEDEMO_H

#include <qstatusbar.h>
#include <qwidget.h>

#include "QtSfml/QtSfmlCanvas.h"

namespace Qsd
{
class BaseDemo : public QWidget
{
public:
	BaseDemo(
		QWidget* controlsWidget,
		QtSfmlCanvas* canvas,
		QStatusBar* statusBar,
		QTimer* timer);

	virtual void run() = 0;

protected:
	QtSfmlCanvas* canvas;
	QStatusBar* statusBar;
	QTimer* displayTimer;
};

} // namespace Qsd

#endif