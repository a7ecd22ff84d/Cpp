#ifndef __BASEDEMO_H
#define __BASEDEMO_H

#include <string_view>
#include <qstatusbar.h>
#include <qwidget.h>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/DemoContext.h"

namespace Qsd
{
class BaseDemo : public QWidget
{
public:
	BaseDemo(const DemoContext& context);

	virtual void run() = 0;
	virtual QString getDescription() const = 0;

protected:
	QtSfmlCanvas* canvas;
	QStatusBar* statusBar;
	QTimer* displayTimer;
};

} // namespace Qsd

#endif