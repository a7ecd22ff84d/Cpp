#ifndef GRADIENTPROGRAM_H
#define GRADIENTPROGRAM_H

#include <memory>
#include <string>

#include "QtSfmlDemo/BaseDemo.h"
#include "QtSfmlDemo/DemoContext.h"
#include "ui_GradientControls.h"

namespace Ui
{
class Gradient;
}

namespace Qsd
{
class Gradient : public BaseDemo
{
	// NOLINTNEXTLINE
	Q_OBJECT

	using GradientFunc = int (*)(int width, int height, int x, int y);

public:
	explicit Gradient(DemoContext& context);

	void run() final;
	[[nodiscard]] auto getDescription() const -> QString final;

private slots:
	void update();

private:
	std::map<std::string, GradientFunc> gradients;
	std::unique_ptr<Ui::GradientControls> ui;
};

} // namespace Qsd

#endif // GRADIENTPROGRAM_H
