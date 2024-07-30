#ifndef POINTDETECTION_H
#define POINTDETECTION_H

#include "Utilities.h"

class PointDetection
{
public:
	static PointDetection instance;

	bool checkPoint(const sf::Shape& body, const sf::Vector2f& checkedPoint);
	bool checkPoint(const sf::CircleShape& circle, const sf::Vector2f& checkedPoint);

private:
	PointDetection();
	virtual ~PointDetection();
};

#endif // !POINTDETECTION_H