#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class System
{
public:
    System();
    void Step(int command, sf::Vector2f pos);
    void Draw(sf::RenderWindow& widnow);

private:
    void drawPath(sf::RenderWindow &window);
    void init_circles(); 
    void display_matrix();
    sf::Color get_rgb(int color);
    int get_color_number(sf::Color color);
    vector<sf::Vector2i> findPaths(sf::Vector2i start, sf::Vector2i end);
    vector<sf::Vector2i> findFinalPath(sf::Vector2i start, sf::Vector2i end, vector<vector<int>> paths);
    sf::Vector2i coordinatesToIndex(sf::Vector2f coords);

    bool fiveInARow(sf::Vector2i start, vector<sf::Vector2i>& coords);
    void moveDirection(sf::Vector2i start, int direction, vector<sf::Vector2i>& coords);
    
    vector<sf::CircleShape> circles;
    vector<vector<sf::RectangleShape>> grid;
    vector<vector<int>> adj_matrix;
    vector<sf::Vector2i> path;
    int currentCircle;
    int currentPathIndex;
    bool inMotion;

    enum COLORS {NO_COLOR, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};
};

#endif // SYSTEM_H
