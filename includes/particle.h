#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
// #include "random.h"
// #include "constants.h"
using namespace std;

// Random r;

class Particle{

    public:
    // Particle(): radius(r.Next(0, 20)), bubble(sf::CircleShape(radius)), velocity(sf::Vector2f(r.Next(0, 20), r.Next(0, 20))), position(sf::Vector2f(r.Next(0, 20), r.Next(0, 20))), acceleration(0), color(r.Next(0, 20), r.Next(0, 20), r.Next(0, 20)), mass(0), restitution(0){
    // }

    sf::CircleShape  _get_shape() {return bubble;}
    sf::Vector2f _get_velocity() {return velocity;}
    sf::Vector2f _get_position() {return position;}
    float _get_acceleration() {return acceleration;}
    sf::Color _get_fill_color() {return fill_color;}
    sf::Color _get_boarder_color() {return boarder_color;}
    float _get_radius() {return radius;}
    float _get_mass() {return mass;}
    float _get_restitution() {return restitution;}

    
    sf::CircleShape bubble;
    sf::Vector2f velocity;
    sf::Color fill_color;
    sf::Color boarder_color;
    sf::Vector2f position;
    float acceleration;
    float radius;
    float mass;
    float restitution;

};

#endif