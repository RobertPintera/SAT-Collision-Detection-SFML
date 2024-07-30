#ifndef COLLISION_H
#define COLLISION_H

#include "Utilities.h"

constexpr float INF = std::numeric_limits<float>::infinity();

class Collision
{
public:
	static Collision instance;

public:
	bool checkCollision(const sf::Shape& mainBody, const  sf::Shape& otherBody, sf::Vector2f& MTV);
	bool checkCollision(const sf::CircleShape& mainCircle, const sf::CircleShape& otherCircle, sf::Vector2f& MTV);
	bool checkCollision(const sf::CircleShape& mainCircle, const sf::Shape& otherBody, sf::Vector2f& MTV);
	bool checkCollision(const sf::Shape& mainBody, const sf::CircleShape& otherCircle, sf::Vector2f& MTV);

protected:
	sf::Vector2f circleAxis(std::vector<sf::Vector2f>& points, sf::Vector2f centerCircle);
	sf::Vector2f perpendicularAxis(std::vector<sf::Vector2f>& points, const uint32_t index);

	std::tuple<float, float> projectOnto(std::vector<sf::Vector2f>& points, const sf::Vector2f& axis);
	std::tuple<float, float> projectCircle(sf::Vector2f centerCircle, float radius, sf::Vector2f axis);

private:
	Collision();
	virtual ~Collision();
};

#endif // !COLLISION_H
