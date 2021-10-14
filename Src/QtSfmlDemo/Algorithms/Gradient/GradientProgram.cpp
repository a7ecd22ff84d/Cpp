#include "GradientProgram.h"

#include <memory>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <math.h>

#include "QtSfmlDemo/BaseDemo.h"
#include "QtSfmlDemo/DemoContext.h"
#include "ui_GradientControls.h"

namespace Qsd
{
Gradient::Gradient(DemoContext& context)
	: BaseDemo(context)
	, ui(std::make_unique<Ui::GradientControls>())
{
	ui->setupUi(this);

	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	displayTimer->connect(displayTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void Gradient::run()
{
	displayTimer->start();
}

[[nodiscard]] auto Gradient::getDescription() const -> QString
{
	return R"(
<h2>Gradient printer</h2>
<p>Because why not start another project with dozens of unfinished ones</p>
)";
}

void Gradient::update()
{
	canvas->clear();

	auto size = canvas->width() * canvas->height() * 4;
	auto* pixels = new sf::Uint8[size];

	for (int x = 0; x < canvas->height(); x++)
	{
		for (int y = 0; y < canvas->width(); y++)
		{
			auto color = 255 * y / canvas->width() * x / canvas->height();

			auto width = canvas->width();
			pixels[(y + x * width) * 4 + 0] = color; // R?
			pixels[(y + x * width) * 4 + 1] = color; // G?
			pixels[(y + x * width) * 4 + 2] = color; // B?
			pixels[(y + x * width) * 4 + 3] = 255;	 // A?
		}
	}

	sf::Image image;
	image.create(canvas->width(), canvas->height(), pixels);
	sf::Texture tex;
	tex.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(tex);

	canvas->draw(sprite);
	canvas->display();
}

} // namespace Qsd