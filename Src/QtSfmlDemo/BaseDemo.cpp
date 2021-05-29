
#include "QtSfmlDemo/BaseDemo.h"

namespace Qsd
{
BaseDemo::BaseDemo(
	QWidget* controlsWidget, QtSfmlCanvas* canvas, QStatusBar* statusBar, QTimer* timer)
	: QWidget(controlsWidget)
	, canvas(canvas)
	, statusBar(statusBar)
	, displayTimer(timer)
{
}

} // namespace Qsd