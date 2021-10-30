#ifndef QTSFMLDEMO_H
#define QTSFMLDEMO_H

#include "QtSfmlDemo/BaseDemo.h"

namespace Ui
{
class QtSfmlDemo;
} // namespace Ui

namespace Visualization
{
class QtSfmlDemo : public Qsd::BaseDemo
{
	// NOLINTNEXTLINE
	Q_OBJECT

public:
	explicit QtSfmlDemo(const Qsd::DemoContext& context);
	~QtSfmlDemo() override;

	void run() final;
	[[nodiscard]] auto getDescription() const -> QString final;

private:
	void update();

private:
	Ui::QtSfmlDemo* ui;
};

} // namespace Visualization

#endif // QTSFMLDEMO_H
