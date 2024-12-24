#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>
const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 1000;
const float SIDE_BAR = 400;
const int GRID_SIZE = 9;
const float WORK_PANEL = SCREEN_WIDTH - SIDE_BAR;
const float CELL_SIZE = WORK_PANEL / GRID_SIZE;


const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;

// [0] up, [1] down, [2] left, [3] right
const sf::Vector2i DIRECTIONS[4] = {sf::Vector2i(-1, 0), sf::Vector2i(1, 0), sf::Vector2i(0, -1), sf::Vector2i(0, 1)};

enum COMMANDS {
    LEFT_CLICK = 10
};
#endif // CONSTANTS_H
