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
    // Rotate the rectangle according to the angle of the stick
    m_stick.setRotation(m_angle);
    window.draw(m_stick);
}

//---------------------------------------------------------------------------------
void Stick::updateSticksBlocking(Stick* stick)
{
    m_blockingSticks.push_back(stick);
    stick->updateSticksBlocked(this);
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

    // Calculate the coordinates of the end point of the stick
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
// This is the function returns true if line segment 'p1q1' and 'p2q2' intersect.
// Tgis function is used for checking itersections between two sticks

bool Stick::doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
    {
        return true;
    }

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1))
    {
        return true;
    }

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1))
    {
        return true;
    }

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2))
    {
        return true;
    }

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2))
    {
        return true;
    }

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
// This function goes over the sticks that are blocked by the current stick and
// erases the current stick from their blockingSticks list. If the stick is now
// free it'll be added to the removeable multimap

void Stick::handleStickRemove(std::multimap<int, Stick*>& removable)
{
    for (auto it = m_blockedSticks.begin() ; it != m_blockedSticks.end(); it++)
    {
        (*it)->eraseFromBlocking(this);

        // if the stick isn't blocked anymore, add it to removeable multimap
        if ((*it)->isFree())
        {
            removable.insert(std::make_pair((*it)->getStickScore(),(*it)));
        }
    }
}

//--------------------------------------------------------------------------------
// This function is responsible of deleting stickToDelete from the blockingSticks
// list of the currenr stick

void Stick::eraseFromBlocking(Stick* stickToDelete)
{
    m_blockingSticks.remove(stickToDelete);
}

//--------------------------------------------------------------------------------
// This function is responsible of sending back a string that contains all the
// details about this current stick. It is used the player presses save and we
// need to save the board's status

std::string Stick::getStickInfo()const
{
    std::string stickInfo = std::to_string(m_colour) + " " + std::to_string(m_angle) 
                            +" "+ std::to_string(m_length/30.0f)
                            + " " +std::to_string(m_startingPoint.x) + " "
                            + std::to_string(m_startingPoint.y) + "\n";
    return stickInfo;
}

//----------------------------------------------------------------------------------
// This function is responsible of adding "stick" to the blockedSticks list of the
// current stick

void Stick::updateSticksBlocked(Stick* stick)
{
    m_blockedSticks.push_back(stick);
}

//----------------------------------------------------------------------------------
// This function checks if the current stick has been clicked on

bool Stick::pressed(const sf::Vector2f& location)
{
    const auto transformedPoint = m_stick.getTransform().getInverse().transformPoint(location);
    return m_stick.getLocalBounds().contains(transformedPoint);
}

//----------------------------------------------------------------------------------
// This function checks if the stick is blocked

bool Stick::isFree()const
{
    return m_blockingSticks.empty();
}
//----------------------------------------------------------------------------------
// This function highlights the sticks that block this stick

void Stick::highlightBlockingSticks()
{
    for (auto it = m_blockingSticks.begin(); it != m_blockingSticks.end(); it++)
    {
        (*it)->highlightStick();
    }
}
//---------------------------------------------------------------------------------
void Stick::stopHighlightBlockingSticks()
{
    for (auto it = m_blockingSticks.begin(); it != m_blockingSticks.end(); it++)
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