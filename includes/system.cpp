#include "system.h"
#include "particle.h"
#include "random.h"
#include "constants.h"
#include <iostream>

float restitution = 0.8f;
const float gravity = 0.05f;
float mass = 0;
const float additionalForce = 0.6f;
System::System()
{
    Random r;
    // the shape of the object, along with its velocity, acceleration,
    // position, etc. should be part of the individual object.
    system.resize(20);
    for(int i = 0, l = system.size(); i < l; i++)
    {
        system[i].radius = r.Next(5, 30);
        system[i].bubble = sf::CircleShape(system[i].radius);
        float startX = r.Next(0, SCREEN_WIDTH - system[i].radius * 2);
        system[i].bubble.setPosition(sf::Vector2f(startX, 0));
        system[i].position = sf::Vector2f(startX, 0);
        system[i].velocity = sf::Vector2f(r.Next(2, 6), r.Next(2, 6));
        system[i].restitution = restitution;
        int r_ = r.Next(0, 255);
        int g_ = r.Next(0, 255);
        int b_ = r.Next(0, 255);
        system[i].bubble.setOutlineThickness(5);
        system[i].bubble.setOutlineColor(sf::Color(g_, b_, r_));
        system[i].boarder_color = (sf::Color(g_, b_, r_));
        system[i].bubble.setFillColor(sf::Color(r_, g_, b_));
        system[i].fill_color = sf::Color(r_, g_, b_);
    }


}


//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command)
{
    Random r;
    // all this is the responsibility of the
    //  individual object:
    for(int i = 0, l = system.size(); i < l; i++)
    {
        int r_ = r.Next(0, 255);
        int g_ = r.Next(0, 255);
        int b_ = r.Next(0, 255);
        mass = system[i].radius;
        float totalForce = mass * (gravity + additionalForce);
        float acceleration = totalForce / mass;
        system[i].velocity.y += acceleration;
        system[i].velocity.y += gravity;
        system[i].bubble.move(system[i].velocity);
        sf::FloatRect boundBox = system[i].bubble.getGlobalBounds();
        sf::Vector2f pos = system[i].bubble.getPosition();
        if ((pos.x) >= WORK_PANEL - (system[i].radius * 2))
        {
            system[i].velocity = sf::Vector2f(-1 * (system[i].velocity.x ), 1 * (system[i].velocity.y  ));
            system[i].bubble.setFillColor(sf::Color(r_, g_, b_));
            system[i].bubble.setOutlineColor(sf::Color(g_, b_, r_));
        }
        if (pos.x <= 0)
        {
            system[i].velocity = sf::Vector2f(-1 * (system[i].velocity.x ), 1 * system[i].velocity.y);
            system[i].bubble.setOutlineColor(sf::Color(g_, b_, r_));
            system[i].bubble.setFillColor(sf::Color(r_, g_, b_));
        }
        if ((pos.y) >= (SCREEN_HEIGHT) - (system[i].radius * 2 ))
        {
            system[i].bubble.setPosition(pos.x, SCREEN_HEIGHT - system[i].radius * 2);
            system[i].velocity = sf::Vector2f(1 * system[i].velocity.x, - 1 * (system[i].velocity.y * system[i].restitution) + (system[i].radius / 2));
            // system[i].velocity = sf::Vector2f(-system[i].velocity.x * system[i].restitution, system[i].velocity.y);
            // system[i].velocity = sf::Vector2f(1 * (system[i].velocity.x ), -1 * system[i].velocity.y);
            system[i].bubble.setOutlineColor(sf::Color(g_, b_, r_));
            system[i].bubble.setFillColor(sf::Color(r_, g_, b_));
        }
        if ((pos.x) >= (SCREEN_WIDTH) - (system[i].radius * 2 ))
        {
            system[i].bubble.setPosition(SCREEN_WIDTH - (system[i].radius) * 2, pos.y);
            system[i].velocity = sf::Vector2f(1 * (system[i].velocity.x ), -1 * system[i].velocity.y);
            system[i].bubble.setOutlineColor(sf::Color(g_, b_, r_));
            system[i].bubble.setFillColor(sf::Color(r_, g_, b_));
        }
        if (pos.y <= 0)
        {
            system[i].velocity = sf::Vector2f(1 * (system[i].velocity.x ), -1 * system[i].velocity.y);
            system[i].bubble.setOutlineColor(sf::Color(g_, b_, r_));
            system[i].bubble.setFillColor(sf::Color(r_, g_, b_));
        }
    }    
}

void System::Draw(sf::RenderWindow &window)
{
    window.clear();
    for(int i = 0; i < system.size(); i ++)
    {
        window.draw(system[i].bubble);
    }
}