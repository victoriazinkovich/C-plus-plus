#include <cmath>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(800U, 600U), "JELLY-PHYSICS");

	sf::Vector2f min_point(0.0f, 0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

	const auto N = 6U;

	const auto M = 4U;

	const auto L = length(max_point - min_point) * 0.05f;

	const auto C = (min_point + max_point) * 0.5f;

	const auto r = 2.5f;

	std::vector < std::vector < System::particle_t > > 
		particles(N, std::vector < System::particle_t > (M, 0));

	for (auto i = 0U; i < N; ++i)
	{
		for (auto j = 0U; j < M; ++j)
		{
			auto position = sf::Vector2f(L * i, L * j) + C;

			particles[i][j] = std::make_shared < Particle > (position, position,
				sf::Vector2f(0.0f, 10.0f), r);
		}
	}

	System system(min_point, max_point, particles);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		system.update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			system.push(sf::Vector2f(0.0f, -2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			system.push(sf::Vector2f(0.0f, 2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			system.push(sf::Vector2f(-2.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			system.push(sf::Vector2f(2.0f, 0.0f));
		}

		window.clear();

		for (auto i = 0U; i < N; ++i)
		{
			for (auto j = 0U; j < M; ++j)
			{
				sf::CircleShape circle(2.0f * r);

				circle.setPosition(system.particle(i, j)->position() + sf::Vector2f(r, r));

				circle.setFillColor(sf::Color::Red);

				window.draw(circle);
			}
		}

		window.display();
	}

	// system("pause");

	return EXIT_SUCCESS;
}
