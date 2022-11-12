#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(1000U, 1000U), "BROWNIAN-PHYSICS");

	std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution <> uid_x(0.0f, 995.0f);
	std::uniform_real_distribution <> uid_y(0.0f, 995.0f);
	std::uniform_real_distribution <> uid_v(0.0f, 1.0f);

	sf::Vector2f min_point(0.0f, 0.0f);
	sf::Vector2f max_point(995.0f, 995.0f);

	const auto N = 100U;

	const double k = 1;
	const double q = 1;
	const double m = 1;
	const double T = 1000;

	const auto R = length(max_point - min_point) * 0.1f;

	const auto C = (min_point + max_point) * 0.5f;

	const auto r = 2.5f;

	std::vector < System::particle_t > particles;

	for (auto i = 0U; i < N; ++i)
	{
		auto position = sf::Vector2f(uid_x(dre), uid_y(dre));

		auto velocity = sf::Vector2f(uid_v(dre) * sqrt(k * T / m), uid_v(dre) * sqrt(k * T / m));

		particles.push_back(std::make_shared < Particle > (position, velocity, 
			sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), r));
	}

	System system(min_point, max_point, particles);

	sf::Event event;

	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();

	const std::chrono::milliseconds delay(500);

	const float dt = 500;

	std::chrono::milliseconds timer(0);

	time_point = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		timer += std::chrono::duration_cast < std::chrono::milliseconds > (
			std::chrono::steady_clock::now() - time_point);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (timer > delay)
		{
			system.update(dt / 1000);

			timer = std::chrono::milliseconds(0);

			time_point = std::chrono::steady_clock::now();
		}

		window.clear();

        sf::Vector2f left_up    = sf::Vector2f(0.0f, 0.0f);
        sf::Vector2f left_down  = sf::Vector2f(0.0f, 100.0f);
        sf::Vector2f right_up   = sf::Vector2f(100.0f, 0.0f);
        sf::Vector2f right_down = sf::Vector2f(100.0f, 100.0f);

        for (auto i = 0; i < 10; ++i)
        {
            for (auto j = 0; j < 10; ++j)
            {
                sf::ConvexShape square;
                square.setPointCount(4);

                square.setPoint(0, left_up);
                square.setPoint(1, right_up);
                square.setPoint(2, right_down);
                square.setPoint(3, left_down);

                int counter = 0;

                for (auto i = 0U; i < N; ++i)
                {
                    auto particle = particles[i];

                    if (particle->position().x > left_up.x and particle->position().x < right_up.x)
                    {
                        if (particle->position().y > left_up.y and particle->position().y < left_down.y)
                        {
                            counter++;
                        }
                    }
                }

                if (counter == 0)
                {
                    square.setFillColor(sf::Color(215, 226, 255));
                }
                if (counter == 1 or counter == 2)
                {
                    square.setFillColor(sf::Color(197, 209, 255));
                }
                if (counter == 3 or counter == 4)
                {
                    square.setFillColor(sf::Color(143, 160, 255));
                }
                if (counter == 5 or counter == 6)
                {
                    square.setFillColor(sf::Color(91, 110, 255));
                }
                if (counter >= 7)
                {
                    square.setFillColor(sf::Color(47, 74, 255));
                }

                window.draw(square);

                left_up.x    += 100.0f;
                right_up.x   += 100.0f;
                left_down.x  += 100.0f;
                right_down.x += 100.0f;
            }

            left_up.x    = 0.0f;
            right_up.x   = 100.0f;
            left_down.x  = 0.0f;
            right_down.x = 100.0f;

            left_up.y    += 100.0f;
            right_up.y   += 100.0f;
            left_down.y  += 100.0f;
            right_down.y += 100.0f;
        }

        for (auto i = 0U; i < system.particles().size(); ++i)
        {
            sf::CircleShape circle(2.0f * r);

            circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));

            circle.setFillColor(sf::Color::Black);

            window.draw(circle);
        }

		window.display();
	}

	return EXIT_SUCCESS;
}
