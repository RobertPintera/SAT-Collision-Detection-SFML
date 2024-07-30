#include "App.h"

App::App()
{
	initWindow();
	initMainCollider();
	initColliders();
}

App::~App()
{
	mainCollider = nullptr;
	for (auto& collider : colliders)
	{
		delete collider;
		collider = nullptr;
	}
}

void App::updateEvents()
{
	while (window.pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void App::updateDeltaTime()
{
	deltatime = deltaTimeClock.restart().asSeconds();
}

void App::updateMousePosition()
{
	mousePositionScreen = sf::Mouse::getPosition();
	mousePositionWindow = sf::Mouse::getPosition(window);
	mousePositionView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void App::updateMainCollider()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		mainCollider->move(0.f,-200.f * deltatime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		mainCollider->move(0.f, 200.f * deltatime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mainCollider->move(-200.f * deltatime, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mainCollider->move(200.f * deltatime, 0.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		mainCollider->rotate(-2.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		mainCollider->rotate(2.f);
}

void App::updateCollisions()
{
	for (auto& collider : colliders)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (PointDetection::instance.checkPoint(*collider, mousePositionView))
			{
				mainCollider->setFillColor(DEFAULT_FILL_COLOR);
				mainCollider->setOutlineColor(DEFAULT_OUTLINE_COLOR);
				for (auto& collider2 : colliders)
				{
					if (mainCollider == collider2)
						continue;

					sf::Vector2f MTV = sf::Vector2f(0.f, 0.f);
					if (Collision::instance.checkCollision(*mainCollider, *collider2, MTV))
					{
						mainCollider->move(MTV);
					}
				}

				mainCollider = collider;
				mainCollider->setFillColor(PICKED_FILL_COLOR);
				mainCollider->setOutlineColor(PICKED_OUTLINE_COLOR);
			}
		}

		if (mainCollider == collider)
			continue;

		sf::Vector2f MTV = sf::Vector2f(0.f,0.f);
		if (Collision::instance.checkCollision(*mainCollider,*collider,MTV))
		{
			mainCollider->move(MTV);
		}
	}
}

void App::update()
{
	updateEvents();
	updateDeltaTime();
	updateMousePosition();
	updateMainCollider();
	updateCollisions();
}

void App::renderCollisions()
{
	for (auto& collider : colliders)
	{
		window.draw(*collider);
	}
}

void App::render()
{
	window.clear();
	renderCollisions();
	window.display();
}

void App::run()
{
	while (window.isOpen())
	{
		update();
		render();
	}
}

void App::initWindow()
{
	window.create(sf::VideoMode(1000, 800), "SAT Collision Detection", sf::Style::Default);
	window.setFramerateLimit(60);
}

void App::initMainCollider()
{
	
}

void App::initColliders()
{
	{
		sf::RectangleShape* col = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
		col->setPosition(400.f, 300.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(DEFAULT_FILL_COLOR);
		col->setOutlineThickness(1.f);
		col->setOutlineColor(DEFAULT_OUTLINE_COLOR);
		colliders.push_back(col);
		col = nullptr;
	}

	{
		sf::RectangleShape* col = new sf::RectangleShape(sf::Vector2f(100.f, 100.f));
		col->setPosition(300.f, 600.f);
		col->setRotation(30.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(sf::Color(107, 214, 136));
		col->setOutlineThickness(1.f);
		col->setOutlineColor(sf::Color::Green);
		colliders.push_back(col);
		col = nullptr;
	}

	{
		sf::CircleShape* col = new sf::CircleShape(70.f,30.f);
		col->setPosition(150.f, 350.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(DEFAULT_FILL_COLOR);
		col->setOutlineThickness(1.f);
		col->setOutlineColor(DEFAULT_OUTLINE_COLOR);
		colliders.push_back(col);
		col = nullptr;
	}

	{
		sf::CircleShape* col = new sf::CircleShape(50.f, 30.f);
		col->setPosition(450.f, 500.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(DEFAULT_FILL_COLOR);
		col->setOutlineThickness(1.f);
		col->setOutlineColor(DEFAULT_OUTLINE_COLOR);
		colliders.push_back(col);
		col = nullptr;
	}

	{
		sf::ConvexShape* col = new sf::ConvexShape(6);
		col->setPoint(0,sf::Vector2f(0.f,40.f));
		col->setPoint(1, sf::Vector2f(80.f, 20.f));
		col->setPoint(2, sf::Vector2f(180.f, 30.f));
		col->setPoint(3, sf::Vector2f(280.f, 140.f));
		col->setPoint(4, sf::Vector2f(140.f, 160.f));
		col->setPoint(5, sf::Vector2f(40.f, 100.f));
		col->setPosition(700.f, 400.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(DEFAULT_FILL_COLOR);
		col->setOutlineThickness(1.f);
		col->setOutlineColor(DEFAULT_OUTLINE_COLOR);
		colliders.push_back(col);
		col = nullptr;
	}

	{
		sf::ConvexShape* col = new sf::ConvexShape(5);
		col->setPoint(0, sf::Vector2f(0.f, 50.f));
		col->setPoint(1, sf::Vector2f(100.f, 0.f));
		col->setPoint(2, sf::Vector2f(200.f, 30.f));
		col->setPoint(3, sf::Vector2f(180.f, 70.f));
		col->setPoint(4, sf::Vector2f(100.f, 100.f));
		col->setPosition(450.f, 100.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(DEFAULT_FILL_COLOR);
		col->setOutlineThickness(1.f);
		col->setOutlineColor(DEFAULT_OUTLINE_COLOR);
		colliders.push_back(col);
		col = nullptr;
	}

	{
		sf::ConvexShape* col = new sf::ConvexShape(5);
		col->setPoint(0, sf::Vector2f(0.f, 50.f));
		col->setPoint(1, sf::Vector2f(100.f, 0.f));
		col->setPoint(2, sf::Vector2f(200.f, 30.f));
		col->setPoint(3, sf::Vector2f(180.f, 70.f));
		col->setPoint(4, sf::Vector2f(100.f, 100.f));
		col->setPosition(200.f, 150.f);
		col->setRotation(30.f);
		col->setOrigin(col->getLocalBounds().width / 2.f, col->getLocalBounds().height / 2.f);
		col->setFillColor(DEFAULT_FILL_COLOR);
		col->setOutlineThickness(1.f);
		col->setOutlineColor(DEFAULT_OUTLINE_COLOR);
		colliders.push_back(col);
		col = nullptr;
	}


	mainCollider = colliders[0];
	mainCollider->setFillColor(PICKED_FILL_COLOR);
	mainCollider->setOutlineColor(PICKED_OUTLINE_COLOR);
}
