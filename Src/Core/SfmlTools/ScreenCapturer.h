#ifndef __SCREEN_CAPTURER_H
#define __SCREEN_CAPTURER_H

#include <string>

#include <Core/SfmlTools/Sfml_fwd.h>

namespace SfmlTools
{
class ScreenCapturer
{
public:
	ScreenCapturer(sf::RenderWindow& renderWindow);

	void saveScreenshot(const std::string& filename);

private:
	sf::RenderWindow& renderWindow;
};

} // namespace SfmlTools

#endif