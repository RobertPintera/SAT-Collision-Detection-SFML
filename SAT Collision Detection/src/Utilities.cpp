#include "Utilities.h"

sf::Vector2f getCenterShape(std::vector<sf::Vector2f>& p)
{
    float cX = 0, cY = 0, A = 0;
    for (size_t i = 0; i < p.size(); i++)
    {
        A += p[i].x * p[i == p.size() - 1 ? 0 : i + 1].y - p[i == p.size() - 1 ? 0 : i + 1].x * p[i].y;
    }

    for (size_t i = 0; i < p.size(); i++)
    {
        cX += (p[i].x + p[i == p.size() - 1 ? 0 : i + 1].x)
            * (p[i].x * p[i == p.size() - 1 ? 0 : i + 1].y - p[i == p.size() - 1 ? 0 : i + 1].x * p[i].y);
        cY += (p[i].y + p[i == p.size() - 1 ? 0 : i + 1].y)
            * (p[i].x * p[i == p.size() - 1 ? 0 : i + 1].y - p[i == p.size() - 1 ? 0 : i + 1].x * p[i].y);
    }

    cX = cX / (3.f * A);
    cY = cY / (3.f * A);


    return sf::Vector2f(cX, cY);
}

// CircleShape can not generate a perfect circle, so this class is designed to create regular polygons. 
// We can use three points to create a triangle and use them to calculate the position of the circumcenter of this figure. 
// For a large number of points in a polygon, it is better to use getCenterShape() function, which computes the centroid of a geometric shape.
sf::Vector2f getCircumcenter(const sf::CircleShape& circle)
{
    if (circle.getPointCount() < 2)
    {
        return circle.getTransform().transformPoint(circle.getPoint(0));
    }
    else if (circle.getPointCount() == 3)
    {
        return (circle.getTransform().transformPoint(circle.getPoint(0)) + circle.getTransform().transformPoint(circle.getPoint(1))) / 2.f;
    }

    uint32_t temp = static_cast<unsigned int>(circle.getPointCount() / 3.f);
    sf::Vector2f p1 = circle.getTransform().transformPoint(circle.getPoint(0));
    sf::Vector2f p2 = circle.getTransform().transformPoint(circle.getPoint(temp * 1));
    sf::Vector2f p3 = circle.getTransform().transformPoint(circle.getPoint(temp * 2));

    //Linear equations
    float a12 = 0, b12 = 0, c12 = 0;
    a12 = p2.y - p1.y;
    b12 = p1.x - p2.x;
    c12 = a12 * p1.x + b12 * p1.y;

    float a23 = 0, b23 = 0, c23 = 0;
    a23 = p3.y - p2.y;
    b23 = p2.x - p3.x;
    c23 = a23 * p2.x + b23 * p2.y;

    sf::Vector2f midPoint12 = (p1 + p2) / 2.f;
    sf::Vector2f midPoint23 = (p2 + p3) / 2.f;
    //Perpendicualar lines
    float pA12 = 0, pB12 = 0, pC12 = 0;
    pA12 = -b12;
    pB12 = a12;
    pC12 = pA12 * midPoint12.x + pB12 * midPoint12.y;

    float pA23 = 0, pB23 = 0, pC23 = 0;
    pA23 = -b23;
    pB23 = a23;
    pC23 = pA23 * midPoint23.x + pB23 * midPoint23.y;

    //Crossing Point -> Cramer's rule
    float Determinant = pA12 * pB23 - pA23 * pB12;

    if (Determinant == 0)
        return p1;

    float DeterminantX = pC12 * pB23 - pC23 * pB12;
    float DeterminantY = pA12 * pC23 - pA23 * pC12;
    float x = DeterminantX / Determinant;
    float y = DeterminantY / Determinant;

    return sf::Vector2f(x, y);
}
