#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Macros.h"

class Stick
{
public:
    Stick(const sf::Texture* picture, Colour colour, float angle, const sf::Vector2f& start, float len);
    ~Stick()= default;
    void draw(sf::RenderWindow& window);
    int getBlockThisStick() const;
    void setBlockThisStick(int factor);
    sf::Vector2f getStartingPoint() const;
    bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
    int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
    bool doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2);
    bool checkAndUpdateIntersection(Stick& otherStick);
    sf::Vector2f getEndPoint()const;
    void updateSticksBlocked(Stick* stick);
    int getStickScore()const;
    void handleStickRemove();
    bool getInRemoveable()const;
    void setInRemoveable(bool boolValue);
    std::string getStickInfo()const;
    void updateSticksBlocking(Stick* stick); 
  

private:
    sf::RectangleShape m_stick;
    Colour m_colour;
    float m_angle;
    sf::Vector2f m_startingPoint;
    float m_length;
    std::vector<Stick*> m_sticksBlocked;   //holds the sticks that this stick blocks
    std::vector<Stick*> m_sticksBlocking;   //holds he sticks that block this stick
    int m_blockThisStick = 0;              //holds the number of sticks that block this stick
    bool m_inRemoveable = false;             //holds if the stick is allready in removable
 
};
