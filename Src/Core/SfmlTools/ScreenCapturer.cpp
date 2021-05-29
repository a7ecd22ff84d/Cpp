#include "Core/SfmlTools/ScreenCapturer.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace SfmlTools
{
ScreenCapturer::ScreenCapturer(sf::RenderWindow& renderWindow)
	: renderWindow(renderWindow)
{
}

void ScreenCapturer::saveScreenshot(const std::string& filename)
{
	auto screenSize = renderWindow.getSize();
	auto texture = sf::Texture();
	texture.create(screenSize.x, screenSize.y);
	texture.update(renderWindow);
	auto image = texture.copyToImage();
	image.saveToFile(filename);
}

} // namespace SfmlTools
