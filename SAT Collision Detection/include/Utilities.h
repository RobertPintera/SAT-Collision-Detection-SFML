#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Z coordinates of crossed vectors
template <typename T>
inline float crossProduct(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

template <typename T>
inline float dotProduct(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline float length(sf::Vector2<T> v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f getCenterShape(std::vector<sf::Vector2f>& p);

sf::Vector2f getCircumcenter(const sf::CircleShape& circle);


#endif // UTILITIES_H
