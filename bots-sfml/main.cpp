
/***

TODO:

4/28/2016: 
Task: Move circle shape along a line.
Why: All entities in the game will move along an edge.

***/

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main() 
{
  const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

  sf::RenderWindow window(sf::VideoMode(400, 300), "Task 1");

  // create the circle and line
  sf::CircleShape circle(8.f);
  circle.setFillColor(sf::Color::Red);
  sf::FloatRect bounds = circle.getLocalBounds();
  circle.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
  circle.setPosition(sf::Vector2f(10, 10));

  int circleMoveDir = 1;

  sf::Vector2f pointA(10, 10);
  sf::Vector2f pointB(150, 150);

  sf::Vertex line[] =
  {
    sf::Vertex(pointA),
    sf::Vertex(pointB)
  };


  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (window.isOpen())
  {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TIME_PER_FRAME)
    {
      timeSinceLastUpdate -= TIME_PER_FRAME;

      // process events
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
      }

      // update
      // calculate slope of line
      float x = pointA.y - pointB.y;
      float y = pointA.x - pointB.x;
      
      float m = (y) ? x / y : 0.f;

      circle.move(sf::Vector2f(1.f * circleMoveDir, 0.f));
      float ypos = m * circle.getPosition().x;
      circle.setPosition(circle.getPosition().x, ypos);

      if (circle.getPosition().x >= pointB.x
        && circle.getPosition().y >= pointB.y)
      {
        circle.setPosition(pointB);
        circleMoveDir = -circleMoveDir;
      }
      else if (circle.getPosition().x <= pointA.x
        && circle.getPosition().y <= pointA.y)
      {
        circle.setPosition(pointA);
        circleMoveDir = -circleMoveDir;
      }
    }

    window.clear();

    // draw
    window.draw(line, 2, sf::Lines);
    window.draw(circle);

    window.display();
  }

  return 0;
}