#ifndef APP_H
#define APP_H

#include "Collision.h"
#include "PointDetection.h"

#define DEFAULT_FILL_COLOR sf::Color(114, 219, 123)
#define DEFAULT_OUTLINE_COLOR sf::Color(66, 138, 82)

#define PICKED_FILL_COLOR sf::Color(114, 202, 224)
#define PICKED_OUTLINE_COLOR sf::Color(53, 152, 232)


class App
{
public:
	App();
	virtual ~App();

	void updateEvents();
	void updateDeltaTime();
	void updateMousePosition();
	void updateMainCollider();
	void updateCollisions();
	void update();

	void renderCollisions();
	void render();

	void run();

private:
	sf::RenderWindow window;
	sf::Event sfEvent;
	sf::Clock deltaTimeClock;
	float deltatime;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	sf::Shape* mainCollider;
	std::vector<sf::Shape*> colliders;
	
private:
	void initWindow();
	void initMainCollider();
	void initColliders();
};

#endif // !APP_H