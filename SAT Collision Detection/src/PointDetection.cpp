#include "PointDetection.h"

PointDetection PointDetection::instance;

bool PointDetection::checkPoint(const sf::Shape& body, const sf::Vector2f& checkedPoint)
{
    if (typeid(body) == typeid(sf::CircleShape) && body.getPointCount() >= 30)
        return checkPoint(static_cast<const sf::CircleShape&>(body), checkedPoint);

    std::vector<sf::Vector2f> pointsBody; 

    for(size_t i = 0; i < body.getPointCount(); i++)
        pointsBody.push_back(body.getTransform().transformPoint(body.getPoint(i)));

    
    sf::Vector2f pointVector =  checkedPoint - pointsBody[0];
    std::vector<sf::Vector2f>::iterator nextPoint = pointsBody.begin();
    std::vector<sf::Vector2f>::iterator previousPoint = pointsBody.begin();

    for (size_t i = 0; i < pointsBody.size()-1; i++)
    {
        nextPoint++;
        sf::Vector2f nextVector = (*nextPoint) - pointsBody[0];
        if (crossProduct(nextVector, pointVector) < 0.f)
            break;
        previousPoint = nextPoint;
    }

    if (previousPoint == nextPoint)
        return false;

    pointVector = checkedPoint - (*previousPoint);
    sf::Vector2f edgeVector = (*nextPoint) - (*previousPoint);
    
    if (crossProduct(edgeVector,pointVector) < 0.f)
        return false;

    return true;
}

bool PointDetection::checkPoint(const sf::CircleShape& circle, const sf::Vector2f& checkedPoint)
{
    sf::Vector2f centerCircle = getCircumcenter(circle);
    if (pow(checkedPoint.x - centerCircle.x, 2) + pow(checkedPoint.y - centerCircle.y, 2) > pow(circle.getRadius(),2))
        return false;

    return true;
}

PointDetection::PointDetection()
{

}

PointDetection::~PointDetection()
{

}
