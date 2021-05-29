#ifndef __DEMO_CONTEXT_H
#define __DEMO_CONTEXT_H

#include <qstatusbar.h>
#include <qwidget.h>

#include "QtSfml/QtSfmlCanvas.h"

namespace Qsd
{

struct DemoContext
{
	QWidget* controlsWidget;
	QtSfmlCanvas* canvas;
	QStatusBar* statusBar;
	QTimer* timer;
};

} // namespace Qsd

#endif