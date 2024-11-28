#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "particle.h"

using namespace std;
class System
{
public:
    System();
    void Step(int command);
    int Size();
    void Draw(sf::RenderWindow& widnow);
private:
    vector<Particle> system;
};

#endif // SYSTEM_H
