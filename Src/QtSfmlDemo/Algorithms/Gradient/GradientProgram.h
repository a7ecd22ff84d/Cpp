#ifndef GRADIENTPROGRAM_H
#define GRADIENTPROGRAM_H

#include <memory>

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

public:
	explicit Gradient(DemoContext& context);

	void run() final;
	[[nodiscard]] auto getDescription() const -> QString final;

private slots:
    void update();

private:
	std::unique_ptr<Ui::GradientControls> ui;
};

} // namespace Qsd

#endif // GRADIENTPROGRAM_H
