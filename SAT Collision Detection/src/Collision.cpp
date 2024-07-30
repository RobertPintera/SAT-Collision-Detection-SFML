#include "Collision.h"

Collision Collision::instance;

bool Collision::checkCollision(const sf::Shape& mainBody, const  sf::Shape& otherBody, sf::Vector2f& MTV)
{
    if (typeid(mainBody) == typeid(sf::CircleShape) && typeid(otherBody) == typeid(sf::CircleShape) && mainBody.getPointCount() >= 30 && otherBody.getPointCount() >= 30)
        return checkCollision(static_cast<const sf::CircleShape&>(mainBody), static_cast<const sf::CircleShape&>(otherBody), MTV);
    else if (typeid(mainBody) == typeid(sf::CircleShape) && mainBody.getPointCount() >= 30)
        return checkCollision(static_cast<const sf::CircleShape&>(mainBody), otherBody, MTV);
    else if (typeid(otherBody) == typeid(sf::CircleShape) && otherBody.getPointCount() >= 30)
        return checkCollision(mainBody, static_cast<const sf::CircleShape&>(otherBody), MTV);

    std::vector<sf::Vector2f> pointsMain;
    std::vector<sf::Vector2f> pointsOther;
    std::vector<sf::Vector2f> axes;

    for (size_t i = 0; i < mainBody.getPointCount(); i++)
        pointsMain.push_back(mainBody.getTransform().transformPoint(mainBody.getPoint(i)));

    for (size_t i = 0; i < otherBody.getPointCount(); i++)
        pointsOther.push_back(otherBody.getTransform().transformPoint(otherBody.getPoint(i)));

    //Optimalization for two RectangleShapes
    if (typeid(mainBody) == typeid(sf::RectangleShape))
    {
        for (size_t i = 0; i < 2; i++)
            axes.push_back(perpendicularAxis(pointsMain, i));
    }
    else
    {
        for (size_t i = 0; i < pointsMain.size(); i++)
            axes.push_back(perpendicularAxis(pointsMain, i));
    }

    if (typeid(otherBody) == typeid(sf::RectangleShape))
    {
        for (size_t i = 0; i < 2; i++)
            axes.push_back(perpendicularAxis(pointsOther, i));
    }
    else
    {
        for (size_t i = 0; i < pointsOther.size(); i++)
            axes.push_back(perpendicularAxis(pointsOther, i));
    }


    float minOverlap = INF;

    for (auto& axis : axes)
    {
        float min1 = INF, min2 = INF;
        float max1 = -INF, max2 = -INF;
        std::tie(min1, max1) = projectOnto(pointsMain, axis);
        std::tie(min2, max2) = projectOnto(pointsOther, axis);


        if (!(max1 > min2 && max2 > min1))
        {
            MTV = sf::Vector2f(0.f, 0.f);
            return false;
        }
        else
        {
            float overlap = std::min(max1, max2) - std::max(min1, min2);
            if (overlap < minOverlap)
            {
                minOverlap = overlap;

                MTV = axis * overlap;
            }
        }
    }

    if (dotProduct(getCenterShape(pointsMain) - getCenterShape(pointsOther), MTV) < 0.f)
        MTV *= -1.0f;

    return true;
}


bool Collision::checkCollision(const sf::CircleShape& mainCircle, const sf::CircleShape& otherCircle, sf::Vector2f& MTV)
{
    sf::Vector2f centerMain = getCircumcenter(mainCircle);
    sf::Vector2f centerOther = getCircumcenter(otherCircle);

    sf::Vector2f diff = centerMain - centerOther;

    float len = length(diff);
    float sum = mainCircle.getRadius() + otherCircle.getRadius();

    if (len >= sum)
        return false;

    sum = sum - len;

    diff = diff / len;

    MTV = diff * sum;

    return true;
}

bool Collision::checkCollision(const sf::CircleShape& mainCircle, const sf::Shape& otherBody, sf::Vector2f& MTV)
{
    sf::Vector2f centerCircle = getCircumcenter(mainCircle);

    std::vector<sf::Vector2f> pointsOther;
    std::vector<sf::Vector2f> axes;

    for (size_t i = 0; i < otherBody.getPointCount(); i++)
        pointsOther.push_back(otherBody.getTransform().transformPoint(otherBody.getPoint(i)));

    //Optimalization for Rectangle
    if (typeid(otherBody) == typeid(sf::RectangleShape))
    {
        for (size_t i = 0; i < 2; i++)
            axes.push_back(perpendicularAxis(pointsOther, i));
    }
    else
    {
        for (size_t i = 0; i < pointsOther.size(); i++)
            axes.push_back(perpendicularAxis(pointsOther, i));
    }

    axes.push_back(circleAxis(pointsOther, centerCircle));

    float minOverlap = INF;

    for (auto& axis : axes)
    {
        float min1, min2 = INF;
        float max1, max2 = -INF;

        std::tie(min1, max1) = projectCircle(centerCircle, mainCircle.getRadius(), axis);
        std::tie(min2, max2) = projectOnto(pointsOther, axis);


        if (!(max1 > min2 && max2 > min1))
        {
            MTV = sf::Vector2f(0.f, 0.f);
            return false;
        }
        else
        {
            float overlap = std::min(max1, max2) - std::max(min1, min2);
            if (overlap < minOverlap)
            {
                minOverlap = overlap;

                MTV = axis * overlap;
            }
        }
    }

    if (dotProduct(centerCircle - getCenterShape(pointsOther), MTV) < 0.0f)
        MTV *= -1.0f;

    return true;
}

bool Collision::checkCollision(const sf::Shape& mainBody, const sf::CircleShape& otherCircle, sf::Vector2f& MTV)
{
    bool result = checkCollision(otherCircle, mainBody, MTV);
    MTV *= -1.0f;

    return result;
}

sf::Vector2f Collision::circleAxis(std::vector<sf::Vector2f>& points, sf::Vector2f centerCircle)
{
    float distance = INF;
    uint32_t index = 0;
    for (size_t i = 0; i < points.size(); i++)
    {
        sf::Vector2f v = points[i] - centerCircle;
        float diff = length(v);

        if (diff > distance)
            continue;

        distance = diff;
        index = i;
    }
    sf::Vector2f axisCircle = centerCircle - points[index];

    return axisCircle / length(axisCircle);
}

sf::Vector2f Collision::perpendicularAxis(std::vector<sf::Vector2f>& points, const uint32_t index)
{
    sf::Vector2f axe = points[index] - points[index == points.size() - 1 ? 0 : index + 1];
    float len = length(axe);
    axe = sf::Vector2f(-(axe.y / len), axe.x / len);
    return axe;
}

std::tuple<float, float> Collision::projectOnto(std::vector<sf::Vector2f>& points, const sf::Vector2f& axis)
{
    float min = INF;
    float max = -INF;

    for (auto& i : points)
    {
        float length = dotProduct(axis, i);

        if (length < min)
            min = length;
        if (length > max)
            max = length;
    }

    return std::make_tuple(min, max);
}

std::tuple<float, float> Collision::projectCircle(sf::Vector2f centerCircle, float radius, sf::Vector2f axis)
{
    sf::Vector2f dir = radius * axis;

    sf::Vector2f p1 = centerCircle + dir;
    sf::Vector2f p2 = centerCircle - dir;
    float min = dotProduct(p1, axis);
    float max = dotProduct(p2, axis);
    if (min > max)
        std::swap(min, max);

    return std::make_tuple(min, max);
}

Collision::Collision()
{
}

Collision::~Collision()
{
}
