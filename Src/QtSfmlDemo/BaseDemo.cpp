
#include "QtSfmlDemo/BaseDemo.h"

namespace Qsd
{
BaseDemo::BaseDemo(const DemoContext& context)
	: QWidget(context.controlsWidget)
	, canvas(context.canvas)
	, statusBar(context.statusBar)
	, displayTimer(context.timer)
{
}

} // namespace Qsd