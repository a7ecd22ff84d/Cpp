#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct GameState
{
	sf::CircleShape circle;
	sf::RectangleShape boundaries;
};

#endif // __GAME_STATE_H