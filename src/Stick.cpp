#include "Stick.h"
#include <cmath>
#include <numbers>
#include <map>


//---------------------------------------------------------------------------------
Stick::Stick(const sf::Texture* picture, Colour colour, float angle, const sf::Vector2f& start, float len)
	  :m_colour(colour), m_angle(angle), m_startingPoint(start), m_length(len)
{
    m_length *= 30.0f;
    float pixelWidth = 30.0f;

    m_stick.setTexture(picture);
    m_stick.setSize(sf::Vector2f(m_length, pixelWidth));
    m_stick.setPosition(start);
}

//----------------------------------------------------------------------------------------
void Stick::draw(sf::RenderWindow& window)
{
    //// Print stick attributes for debugging
    //std::cout << "Stick position: " << m_stick.getPosition().x << ", " << m_stick.getPosition().y << std::endl;
    //std::cout << "Stick rotation: " << m_angle << std::endl;

    // Rotate the rectangle
    m_stick.setRotation(m_angle);
    window.draw(m_stick);

}
////---------------------------------------------------------------------------------
//int Stick::getBlockThisStick() const
//{
//	return m_blockThisStick;
//}
//
////---------------------------------------------------------------------------------
//void Stick::setBlockThisStick(int factor)
//{
//    m_blockThisStick += factor;
//}
//---------------------------------------------------------------------------------
void Stick::updateSticksBlocking(Stick* stick)
{
    m_sticksBlocking.push_back(stick);
    stick->updateSticksBlocked(this);
   // m_blockThisStick++;
}
//---------------------------------------------------------------------------------
sf::Vector2f Stick::getStartingPoint() const
{
	return m_startingPoint;
}
//--------------------------------------------------------------------------------
int Stick::getStickScore()const
{
    switch (m_colour)
    {
        case C_BLACK:
            return BLACK;
        case C_RED:
            return RED;
        case C_BLUE:
            return BLUE;
        case C_GREEN:
            return GREEN;
        case C_YELLOW:
            return YELLOW;
    }

}
//---------------------------------------------------------------------------------
sf::Vector2f Stick::getEndPoint()const
{
    // Convert angle from degrees to radians
    float angleInRadians = m_angle * std::numbers::pi_v<float> / 180.0f;

    // Calculate the coordinates of the end point
    float newX = m_startingPoint.x + m_length * cos(angleInRadians);
    float newY = m_startingPoint.y + m_length * sin(angleInRadians);

    return sf::Vector2f(newX, newY);
   
}
//--------------------------------------------------------------------------------
bool Stick::checkAndUpdateIntersection(Stick& otherStick)
{
    return doIntersect(m_startingPoint, this ->getEndPoint(),
                       otherStick.getStartingPoint(), otherStick.getEndPoint());
}
//---------------------------------------------------------------------------------
// This is the main function that returns true if line segment 'p1q1' and 'p2q2'
// intersect.
bool Stick::doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}
//---------------------------------------------------------------------------------
// This function finds the orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int Stick::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
    float val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}
//---------------------------------------------------------------------------------
// Given three collinear points p, q, r, the function checks if point q lies on 
// line segment 'pr'
bool Stick::onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;

    return false;
}


//--------------------------------------------------------------------------------
void Stick::handleStickRemove(std::multimap<int, Stick*>& removable)
{
    //go over the m_sticksBlocked and change 
    for (auto it = m_sticksBlocked.begin() ; it != m_sticksBlocked.end(); it++)
    {
       // m_sticksBlocked[i]->setBlockThisStick(-1);
        (*it)->eraseFromBlocking(this);
        if ((*it)->getNumOfBlockingMe() == 0)
        {
            removable.insert(std::make_pair((*it)->getStickScore(),(*it)));
        }
    }
}

//--------------------------------------------------------------------------------
void Stick::eraseFromBlocking(Stick* stickToDelete)
{
    m_sticksBlocking.remove(stickToDelete);
}

////--------------------------------------------------------------------------------
//bool Stick::getInRemoveable()const
//{
//    return m_inRemoveable;
//}
////--------------------------------------------------------------------------------
//void Stick::setInRemoveable(bool boolValue)
//{
//    m_inRemoveable = boolValue;
//}
//--------------------------------------------------------------------------------
std::string Stick::getStickInfo()const
{
    std::string stickInfo = std::to_string(m_colour) + " " + std::to_string(m_angle) +" "+ std::to_string(m_length/30.0f)
                            + " " +std::to_string(m_startingPoint.x) + " "+ std::to_string(m_startingPoint.y) + "\n";

    return stickInfo;

}
//----------------------------------------------------------------------------------
void Stick::updateSticksBlocked(Stick* stick)
{
    m_sticksBlocked.push_back(stick);
}

//----------------------------------------------------------------------------------
//This function checks if the user pressed on a stick

bool Stick::pressed(const sf::Vector2f& location)
{
    const auto transformedPoint = m_stick.getTransform().getInverse().transformPoint(location);
    return m_stick.getLocalBounds().contains(transformedPoint);
}
//----------------------------------------------------------------------------------
int Stick::getNumOfBlockingMe()const
{
    return m_sticksBlocking.size();
}
//----------------------------------------------------------------------------------
void Stick::highlightBlockingSticks()
{
    for (auto it = m_sticksBlocking.begin(); it != m_sticksBlocking.end(); it++)
    {
        (*it)->highlightStick();
    }
}
//---------------------------------------------------------------------------------
void Stick::stopHighlightBlockingSticks()
{
    for (auto it = m_sticksBlocking.begin(); it != m_sticksBlocking.end(); it++)
    {
        (*it)->stopHighlightStick();
    }
}
//----------------------------------------------------------------------------------
void Stick::highlightStick()
{
    m_stick.setOutlineThickness(4.f);
    m_stick.setOutlineColor(sf::Color::Magenta);
}
//----------------------------------------------------------------------------------
void Stick::stopHighlightStick()
{
    m_stick.setOutlineThickness(0);
}